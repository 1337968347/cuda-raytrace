#pragma once

#include "pbrt.h"

// 4 * 4 矩阵
struct Matrix4x4
{
    float m[4][4];
    Matrix4x4()
    {
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f;
        m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2] = m[1][3] = m[2][0] =
            m[2][1] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.f;
    }
    Matrix4x4(float mat[4][4]);

    Matrix4x4(float t00,
              float t01,
              float t02,
              float t03,
              float t10,
              float t11,
              float t12,
              float t13,
              float t20,
              float t21,
              float t22,
              float t23,
              float t30,
              float t31,
              float t32,
              float t33);

    bool operator==(const Matrix4x4 &m2) const
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (m[i][j] != m2.m[i][j])
                    return false;

        return true;
    }

    friend Matrix4x4 Transpose(const Matrix4x4 &);

    void Print(FILE *f) const
    {
        fprintf(f, "[ \n");
        for (int i = 0; i < 4; ++i)
        {
            fprintf(f, "  [ ");
            for (int j = 0; j < 4; ++j)
            {
                fprintf(f, "%f", m[i][j]);
                if (j != 3)
                    fprintf(f, ", ");
            }
            fprintf(f, " ]\n");
        }
        fprintf(f, " ] ");
    }

    static Matrix4x4 Mul(const Matrix4x4 &m1, const Matrix4x4 &m2)
    {
        Matrix4x4 r;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                r.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] +
                            m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];

        return r;
    }

    friend Matrix4x4 Inverse(const Matrix4x4 &);
};

class Transform
{
public:
    Matrix4x4 m, mInv;

    Transform(){};
    Transform(const Matrix4x4 &mat) : m(mat), mInv(Inverse(mat)) {}
    Transform(const Matrix4x4 &mat, const Matrix4x4 &mInv)
        : m(mat), mInv(mInv) {}
    void Print(FILE *f) const;
    // 逆
    friend Transform Inverse(const Transform &t)
    {
        return Transform(t.mInv, t.m);
    }
    // 转置
    friend Transform Transpose(const Transform &t)
    {
        return Transform(Transpose(t.m), Transpose(t.mInv));
    }

    bool operator==(const Transform &t) { return t.m == m && t.mInv == mInv; }

    bool operator!=(const Transform &t) const
    {
        return !(t.m == m) || !(t.mInv == mInv);
    }

    bool operator<(const Transform &t2) const
    {
        for (uint32_t i = 0; i < 4; ++i)
            for (uint32_t j = 0; j < 4; ++j)
            {
                if (m.m[i][j] < t2.m.m[i][j])
                    return true;
                if (m.m[i][j] > t2.m.m[i][j])
                    return false;
            }
        return false;
    }

    const Matrix4x4 &GetMatrix() const { return m; }
    const Matrix4x4 &GetInverseMatrix() const { return mInv; }

    bool IsIdentity() const
    {
        return (m.m[0][0] == 1.f && m.m[0][1] == 0.f && m.m[0][2] == 0.f &&
                m.m[0][3] == 0.f && m.m[1][0] == 0.f && m.m[1][1] == 1.f &&
                m.m[1][2] == 0.f && m.m[1][3] == 0.f && m.m[2][0] == 0.f &&
                m.m[2][1] == 0.f && m.m[2][2] == 1.f && m.m[2][3] == 0.f &&
                m.m[3][0] == 0.f && m.m[3][1] == 0.f && m.m[3][2] == 0.f &&
                m.m[3][3] == 1.f);
    }

    bool HasScale() const
    {
        float la2 = (*this)(Vector(1, 0, 0)).LengthSquared();
        float lb2 = (*this)(Vector(0, 1, 0)).LengthSquared();
        float lc2 = (*this)(Vector(0, 0, 1)).LengthSquared();
#define NOT_ONE(x) ((x) < .999f || (x) > 1.001f)
        return (NOT_ONE(la2) || NOT_ONE(lb2) || NOT_ONE(lc2));
#undef NOT_ONE
    }

    inline Point operator()(const Point &pt) const;
    inline void operator()(const Point &pt, Point *ptrans) const;
    inline Vector operator()(const Vector &v) const;
    inline void operator()(const Vector &v, Vector *vt) const;
    inline Normal operator()(const Normal &) const;
    inline void operator()(const Normal &, Normal *nt) const;
    inline Ray operator()(const Ray &r) const;
    inline void operator()(const Ray &r, Ray *rt) const;
    inline RayDifferential operator()(const RayDifferential &r) const;
    inline void operator()(const RayDifferential &r, RayDifferential *rt) const;
    BBox operator()(const BBox &b) const;
    Transform operator*(const Transform &t2) const;
    bool SwapsHandedness() const;
};

Transform Translate(const Vector &delta);
Transform Scale(float x, float y, float z);
Transform RotateX(float angle);
Transform RotateY(float angle);
Transform RotateZ(float angle);
Transform Rotate(float angle, const Vector &axis);
Transform LookAt(const Point &pos, const Point &look, const Vector &up);
// 为啥参数这几个？
Transform Orthographic(float znear, float zfar);
Transform Perspective(float fov, float znear, float zfar);

// Transform Inline Functions
inline Point Transform::operator()(const Point &pt) const
{
    float x = pt.x;
    float y = pt.y;
    float z = pt.z;
    float xp = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
    float yp = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
    float zp = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
    float wp = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];
    if (wp == 1.)
        return Point(xp, yp, zp);
    else
        return Point(xp, yp, zp) / wp;
}

inline void Transform::operator()(const Point &pt, Point *ptrans) const
{
    float x = pt.x, y = pt.y, z = pt.z;
    ptrans->x = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
    ptrans->y = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
    ptrans->z = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
    float w = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];
    if (w != 1.f)
        *ptrans /= w;
}

inline Vector Transform::operator()(const Vector &v) const
{
    float x = v.x, y = v.y, z = v.z;
    return Vector(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
                  m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
                  m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
}

inline void Transform::operator()(const Vector &v, Vector *vt) const
{
    float x = v.x, y = v.y, z = v.z;
    vt->x = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z;
    vt->y = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z;
    vt->z = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z;
}

inline Ray Transform::operator()(const Ray &r) const
{
    Ray ret = r;
    (*this)(ret.o, &ret.o);
    (*this)(ret.d, &ret.d);
    return ret;
}

inline void Transform::operator()(const Ray &r, Ray *rt) const
{
    (*this)(r.o, &rt->o);
    (*this)(r.d, &rt->d);
    if (rt != &r)
    {
        rt->mint = r.mint;
        rt->maxt = r.maxt;
        rt->time = r.time;
        rt->depth = r.depth;
    }
}

// 将给定的光线及其差分光线应用于当前的坐标变换对象，从而获得变换后的光线和差分光线。
inline RayDifferential Transform::operator()(const RayDifferential &r) const
{
    RayDifferential ret;
    (*this)(Ray(r), &ret);
    ret.hasDifferentials = r.hasDifferentials;
    (*this)(r.rxOrigin, &ret.rxOrigin);
    (*this)(r.rxDirection, &ret.rxDirection);
    (*this)(r.ryOrigin, &ret.ryOrigin);
    (*this)(r.ryDirection, &ret.ryDirection);
    return ret;
}

inline void Transform::operator()(const RayDifferential &r,
                                  RayDifferential *rt) const
{
    (*this)(Ray(r), rt);
    rt->hasDifferentials = r.hasDifferentials;
    (*this)(r.rxOrigin, &rt->rxOrigin);
    (*this)(r.rxDirection, &rt->rxDirection);
    (*this)(r.ryOrigin, &rt->ryOrigin);
    (*this)(r.ryDirection, &rt->ryDirection);
}

class AnimatedTransform
{
public:
    AnimatedTransform(const Transform *transform1, float time1,
                      const Transform *transform2, float time2) : startTime(time1), endTime(time2), startTransform(transform1),
                                                                  endTransform(transform2), actuallyAnimated(*startTransform != *endTransform)
    {
        Decompose(transform1->m, &T[0], &R[0], &S[0]);
        Decompose(transform1->m, &T[0], &R[0], &S[0]);
    }
    static void Decompose(const Matrix4x4 &m, Vector *T, Quaternion *R, Matrix4x4 *S);

private:
    const float startTime, endTime;
    const Transform *startTransform, *endTransform;
    const bool actuallyAnimated;
    Vector T[2];
    Quaternion R[2];
    Matrix4x4 S[2];
};
