#include "quaternion.h"
#include "transform.h"

Transform Quaternion::ToTransform() const {
    float xx = v.x * v.x, yy = v.y * v.y, zz = v.z * v.z;
    float xy = v.x * v.y, xz = v.x * v.z, yz = v.y * v.z;
    float wx = w * v.x, wy = w * v.y, wz = w * v.z;

    Matrix4x4 m;
    m.m[0][0] = 1.f - 2.f * (yy + zz);
    m.m[0][1] = 2.f * (xy + wz);
    m.m[0][2] = 2.f * (xz - wy);
    m.m[1][0] = 2.f * (xy - wz);
    m.m[1][1] = 1.f - 2.f * (xx + zz);
    m.m[1][2] = 2.f * (yz + wx);
    m.m[2][0] = 2.f * (xz + wy);
    m.m[2][1] = 2.f * (yz - wx);
    m.m[2][2] = 1.f - 2.f * (xx + yy);

    return Transform(m, Transpose(m));
}