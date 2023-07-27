#include "pbrt.h"

class Light
{
public:
    virtual ~Light();
    Light(const Transform &l2w, int ns = 1) : nSamples(max(1, ns)), LightToWorld(l2w), WorldToLight(Inverse(l2w))
    {
        if (WorldToLight.HasScale())
        {
            printf("检测到对图像进行世界坐标到光线坐标的转换时检测到了缩放");
        }
    }
    // virtual Spectrum Sample_L(const Point &p, float pEpsilon,
    //                           const LightSample &ls, float time, Vector *wi, float *pdf,
    //                           VisibilityTester *vis) const = 0;

    const int nSamples;

protected:
    const Transform LightToWorld, WorldToLight;
};