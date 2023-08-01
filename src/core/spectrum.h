#include "pbrt.h"

// 波长开始范围
static const int sampledLambdaStart = 400;
// 波长结束范围
static const int sampledLambdaEnd = 700;
// 光谱采样的数量
static const int nSpectralSamples = 30;
// 光谱是否已经排序  lambda : 对应的波长数组   vals : 不同的波长对应的强度值， n: 样本数
extern bool SpectrumSamplesSorted(const float *lambda, const float *vals, int n);
// 对光谱进行排序
extern bool SortSpectrumSamples(const float *lambda, const float *vals, int n);
// 指定光谱光谱范围内光谱强度的平均值
extern float AverageSpectrumSamples(const float *lambda, const float *vals, int n, float lambdaStart, float lambdaEnd);
// 肉眼所看的颜色空间转到设备的RGB空间
inline void XYZToRGB(const float xyz[3], float rgb[3])
{
    rgb[0] = 3.240479f * xyz[0] - 1.537150f * xyz[1] - 0.498535f * xyz[2];
    rgb[1] = -0.969256f * xyz[0] + 1.875991f * xyz[1] + 0.041556f * xyz[2];
    rgb[2] = 0.055648f * xyz[0] - 0.204043f * xyz[1] + 1.057311f * xyz[2];
}

inline void RGBToXYZ(const float rgb[3], float xyz[3])
{
    xyz[0] = 0.412453f * rgb[0] + 0.357580f * rgb[1] + 0.180423f * rgb[2];
    xyz[1] = 0.212671f * rgb[0] + 0.715160f * rgb[1] + 0.072169f * rgb[2];
    xyz[2] = 0.019334f * rgb[0] + 0.119193f * rgb[1] + 0.950227f * rgb[2];
}

// 光谱的类型，分为反射光谱跟光源光谱
enum SpectrumType
{
    SPECTRUM_REFLECTANCE,
    SPECTRUM_ILLUMINANT
};
extern void Blackbody(const float *wl, int n, float temp, float *vals);
// 对光谱样本进行插值  l 是一个浮点数，表示要插值的波长
// 对给定的光谱样本进行插值，计算出指定波长处的光谱值。
extern float InterpolateSpectrumSamples(const float *lambda, const float *vals, int n, float l);

// 这是表示CIE色度学标准观察者的采样点数。
static const int nCIESamples = 471;
// 这些数组存储了CIE标准观察者的色度匹配函数。
// 它们描述了人眼对不同波长光的感知强度，分别对应于X、Y、Z三个颜色通道。
extern const float CIE_X[nCIESamples];
extern const float CIE_Y[nCIESamples];
extern const float CIE_Z[nCIESamples];
// 这个数组包含了对应于CIE色度匹配函数的波长值
extern const float CIE_lambda[nCIESamples];
// 这个常量表示CIE Y色度匹配函数在整个可见光谱范围内的积分，用于归一化光谱数据。
static const float CIE_Y_integral = 106.856895;
// 这是用于颜色转换的RGB到光谱的采样点数
static const int nRGB2SpectSamples = 32;
// 这个数组包含了用于RGB到光谱转换的波长值。
extern const float RGB2SpectLambda[nRGB2SpectSamples];
// 不同颜色表面的反射光谱数据，用于将RGB颜色转换为光谱数据。
extern const float RGBRefl2SpectWhite[nRGB2SpectSamples];
extern const float RGBRefl2SpectCyan[nRGB2SpectSamples];
extern const float RGBRefl2SpectMagenta[nRGB2SpectSamples];
extern const float RGBRefl2SpectYellow[nRGB2SpectSamples];
extern const float RGBRefl2SpectRed[nRGB2SpectSamples];
extern const float RGBRefl2SpectGreen[nRGB2SpectSamples];
extern const float RGBRefl2SpectBlue[nRGB2SpectSamples];
// 不同颜色的辐射光谱数据，用于将RGB颜色转换为光谱数据。
extern const float RGBIllum2SpectWhite[nRGB2SpectSamples];
extern const float RGBIllum2SpectCyan[nRGB2SpectSamples];
extern const float RGBIllum2SpectMagenta[nRGB2SpectSamples];
extern const float RGBIllum2SpectYellow[nRGB2SpectSamples];
extern const float RGBIllum2SpectRed[nRGB2SpectSamples];
extern const float RGBIllum2SpectGreen[nRGB2SpectSamples];
extern const float RGBIllum2SpectBlue[nRGB2SpectSamples];

template <int nSamples> class CoefficientSpectrum{
public: 
    CoefficientSpectrum(float v = 0.f){
        for(int i = 0; i< nSamples; i++){
            c[i] = v;
        }
    }
    void Print(FILE *f) const {
        fprintf(f, "[ ");
        for (int i = 0; i < nSamples; ++i) {
            fprintf(f, "%f", c[i]);
            if (i != nSamples-1) fprintf(f, ", ");
        }
        fprintf(f, "]");
    }
    CoefficientSpectrum &operator+=(const CoefficientSpectrum &s2) {
        for (int i = 0; i < nSamples; ++i)
            c[i] += s2.c[i];
        return *this;
    }
    CoefficientSpectrum operator+(const CoefficientSpectrum &s2) const {
        CoefficientSpectrum ret = *this;
        for (int i = 0; i < nSamples; ++i)
            ret.c[i] += s2.c[i];
        return ret;
    }
    CoefficientSpectrum operator-(const CoefficientSpectrum &s2) const {
        CoefficientSpectrum ret = *this;
        for (int i = 0; i < nSamples; ++i)
            ret.c[i] -= s2.c[i];
        return ret;
    }
    CoefficientSpectrum operator/(const CoefficientSpectrum &s2) const {
        CoefficientSpectrum ret = *this;
        for (int i = 0; i < nSamples; ++i)
            ret.c[i] /= s2.c[i];
        return ret;
    }
    CoefficientSpectrum operator*(const CoefficientSpectrum &sp) const {
        CoefficientSpectrum ret = *this;
        for (int i = 0; i < nSamples; ++i)
            ret.c[i] *= sp.c[i];
        return ret;
    }
    CoefficientSpectrum &operator*=(const CoefficientSpectrum &sp) {
        for (int i = 0; i < nSamples; ++i)
            c[i] *= sp.c[i];
        return *this;
    }
    CoefficientSpectrum operator*(float a) const {
        CoefficientSpectrum ret = *this;
        for (int i = 0; i < nSamples; ++i)
            ret.c[i] *= a;
        return ret;
    }
    CoefficientSpectrum &operator*=(float a) {
        for (int i = 0; i < nSamples; ++i)
            c[i] *= a;
        return *this;
    }

protected:
    float c[nSamples];
};