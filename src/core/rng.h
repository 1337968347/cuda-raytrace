#include "pbrt.h"

// 随机数生成器
class RNG
{
public:
    RNG(uint32_t seed = 1234UL)
    {
        mti = N + 1; // 代表当前随机数生成器没有被初始化
        Seed(seed);
    }

    void Seed(uint32_t seed) const;
    float RandomFloat() const;
    uint32_t RandomUint() const;

private:
    static const int N = 624;
    mutable unsigned long mt[N]; // 无符号随机数数组
    mutable int mti;             // 当前随机数下标
};