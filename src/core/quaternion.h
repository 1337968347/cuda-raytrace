#pragma once

#include "pbrt.h"

struct Quaternion
{
    Quaternion()
    {
        v = Vector(0., 0., 0.);
        w = 1.f;
    }
    Quaternion &operator+=(const Quaternion &q)
    {
        v += q.v;
        w += w;
        return (*this);
    }
    friend Quaternion operator+(const Quaternion &q1, const Quaternion &q2)
    {
        Quaternion ret = q1;
        return ret += q2;
    }
    Quaternion &operator-=(const Quaternion &q)
    {
        v -= q.v;
        w -= q.w;
        return *this;
    }
    friend Quaternion operator-(const Quaternion &q1, const Quaternion &q2)
    {
        Quaternion ret = q1;
        return ret -= q2;
    }
    Quaternion &operator*=(float f)
    {
        v *= f;
        w *= f;
        return *this;
    }
    Quaternion operator*(float f) const
    {
        Quaternion ret = *this;
        ret.v *= f;
        ret.w *= f;
        return ret;
    }
    Quaternion &operator/=(float f)
    {
        v /= f;
        w /= f;
        return *this;
    }
    Quaternion operator/(float f) const
    {
        Quaternion ret = *this;
        ret.v /= f;
        ret.w /= f;
        return ret;
    }

    Transform ToTransform() const;
    Quaternion(const Transform &t);

    // 四元数通常被用来表示旋转、插值、位置、缩放等变换。一个四元数由实部和虚部组成，其中实部表示旋转的余弦值，而虚部则表示旋转轴的方向以及旋转角度的正弦值。
    // 一个四元数 
    // q 可以表示为以下形式：
    // q = a + bi + cj + dk

    // 假设一个向量v 绕单位向量 u 旋转角度 θ，对应的旋转四元数为：
    // q= cos(θ/2) +ux*sin(θ/2)i + uy*sin(θ/2)j + uz * sin(θ/2)k

    // 虚部则表示旋转轴的方向以及旋转角度的正弦值。
    Vector v;
    //  w 是旋转的余弦值
    float w;
};

Quaternion Slerp(float t, const Quaternion &q1, const Quaternion &t2);

inline Quaternion operator*(float f, const Quaternion &q)
{
    return q * f;
}

inline float Dot(const Quaternion &q1, const Quaternion &q2)
{
    return Dot(q1.v, q2.v) + q1.w * q2.w;
}

inline Quaternion Normalize(const Quaternion &q)
{
    return q / sqrtf(Dot(q, q));
}