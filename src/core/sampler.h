#include "pbrt.h"

class Sampler
{
public:
    Sampler(int xstart, int xend, int ystart, int yend, int spp, float sopen, float sclose)
        : xPixelStart(xstart), xPixelEnd(xend), yPixelStart(ystart), yPixelEnd(yend), samplesPerpixel(spp), shutterOpen(sopen), shutterClose(sclose){};
    virtual ~Sampler();

    // 纯虚函数，用于获取更多的采样点。
    // 传入参数 sample 是一个指向采样点数组的指针，用于返回获取到的采样点；
    virtual int getMoreSamples(Sample *sample, RNG &rng) = 0;

    // 用于返回当前采样器能够生成的最大采样点数量。
    virtual int MaximumSampleCount() = 0;

    // virtual bool ReportResults(Sample *samples, const RayDifferential *rays,
    //     const Spectrum *Ls, const Intersection *isects, int count);

    // 生成子采样器。传入参数 num 表示子采样器编号，count 表示子采样器数量
    virtual Sampler *getSubSampler(int num, int count) = 0;

    // 用于将采样点数量调整为最接近的有效值
    virtual int RoundSize(int size) const = 0;

    // 图像平面的起始结束坐标
    const int xPixelStart, xPixelEnd, yPixelStart, yPixelEnd;
    // 每个像素的样本数
    const int samplesPerpixel;
    // 快门开始和结束时间
    const float shutterOpen, shutterClose;

protected:
};

struct CameraSample
{
    float imageX, imageY;
    float lensU, lensV;
    float time;
};

// struct Sample : public CameraSample
// {
//     Sample(Sampler *sampler, SurfaceIntegrator *surf, VolumeIntegrator *vol,
//            const Scene *scene);
// }
