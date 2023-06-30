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
}