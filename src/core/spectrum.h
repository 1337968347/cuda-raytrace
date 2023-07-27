#include "pbrt.h"

// 波长开始范围
static const int sampledLambdaStart = 400;
// 波长结束范围
static const int sampledLambdaEnd = 700;
// 光谱采样的数量
static const int nSpectralSamples = 30;
// 光谱是否已经排序
extern bool SpectrumSamplesSorted();