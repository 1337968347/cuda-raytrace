#include "pbrt.h"

DifferentialGeometry::DifferentialGeometry(const Point &p,
                                           const Vector &DPDU, const Vector &DPDV,
                                           const Normal &DNDU, const Normal &DNDV,
                                           float uu, float vv, const Shape *sh) : p(p), dpdu(DPDU), dpdv(DPDV), dndu(DNDU), dndv(DNDV), u(uu), v(vv), shape(sh)
{
    nn = Normal(Normalize(Cross(dpdu, dpdv)));
    u = uu;
    v = vv;
    shape = sh;
    dudx = dvdx = dudx = dvdy = 0;

    if (shape && (shape->ReverseOrientation ^ shape->TransformSwapsHandedness))
        nn *= -1.f;
}

void DifferentialGeometry::ComputeDifferentials(
    const RayDifferential &ray) const
{
    float d = -Dot(nn, Vector(p));
    Vector rxv(ray.rxOrigin.x, ray.rxOrigin.y, ray.rxOrigin.z);
    float tx = -(Dot(nn, rxv) + d) / Dot(nn, ray.rxDirection);

    
}