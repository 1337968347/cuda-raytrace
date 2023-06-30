#include "pbrt.h"

struct DifferentialGeometry
{
    DifferentialGeometry()
    {
        u = v = dudx = dvdx = dudy = dvdy = 0.;
        shape = NULL;
    }

    DifferentialGeometry(const Point &P, const Vector &DPDU,
                         const Vector &DPDV, const Normal &DNDU,
                         const Normal &DNDV, float uu, float vv,
                         const Shape *sh);

    void ComputeDifferentials(const RayDifferential &r) const;

    Point p;
    Normal nn;
    // 曲面上点的参数化坐标
    float u, v;
    const Shape *shape;
    // 表示点在参数空间中对应参数u和v的偏导数（偏导矢量）
    Vector dpdu, dpdv;
    // 表示法线在参数空间中对应参数u和v的偏导数
    Normal dndu, dndv;
    // 表示点在屏幕空间中x和y方向的偏导数
    mutable Vector dpdx, dpdy;
    // 表示参数u和v在屏幕空间中对应x和y方向的偏导数
    mutable float dudx, dvdx, dudy, dvdy;
};
