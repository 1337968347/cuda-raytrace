#include "pbrt.h"

class Point;

class Normal;
class Vector
{
public:
    Vector() { x = y = z = 0.f; }
    Vector(float xx, float yy, float zz) : x(xx), y(yy), z(zz){};
    Vector(const Vector &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    };

    bool HasNaNs() const { return isnan(x) || isnan(y) || isnan(z); }
    explicit Vector(const Point &p);

    Vector &operator=(const Vector &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    Vector operator+(const Vector &v) const
    {
        return Vector(x + v.x, y + v.y, z + v.z);
    }

    Vector &operator+=(const Vector &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector operator-(const Vector &v) const
    {
        return Vector(x - v.x, y - v.y, z - v.z);
    }

    Vector &operator-=(const Vector &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector operator*(float f) const { return Vector(f * x, f * y, f * z); }

    Vector &operator*=(float f)
    {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }
    Vector operator/(float f) const
    {
        float inv = 1.f / f;
        return Vector(x * inv, y * inv, z * inv);
    }

    Vector &operator/=(float f)
    {
        float inv = 1.f / f;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }
    Vector operator-() const { return Vector(-x, -y, -z); }
    float operator[](int i) const { return (&x)[i]; }

    float &operator[](int i) { return (&x)[i]; }

    float LengthSquared() const { return x * x + y * y + z * z; }
    float Length() const { return sqrtf(LengthSquared()); }
    explicit Vector(const Normal &n);

    bool operator==(const Vector &v) const
    {
        return x == v.x && y == v.y && z == v.z;
    }
    bool operator!=(const Vector &v) const
    {
        return x != v.x || y != v.y || z != v.z;
    }
    float x, y, z;
};

class Point
{
public:
    Point() { x = y = z = 0.f; };
    Point(float xx, float yy, float zz) : x(xx), y(yy), z(zz){};
    Point(const Vector &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    Point(const Point &p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
    }

    Point &operator=(const Point &p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
        return *this;
    }

    Point &operator=(const Vector &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    Point operator+(const Point &p) const
    {
        return Point(x + p.x, y + p.y, z + p.z);
    }

    Point operator+(const Vector &v) const
    {
        return Point(x + v.x, y + v.y, z + v.z);
    }

    Point &operator+=(const Point &p)
    {
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }

    Point &operator+=(const Vector &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector operator-(const Point &p) const
    {
        return Vector(x - p.x, y - p.y, z - p.z);
    }

    Point operator-(const Vector &v) const
    {
        return Point(x - v.x, y - v.y, z - v.z);
    }

    Point &operator-=(const Point &p)
    {
        x -= p.x;
        y -= p.y;
        z -= p.z;
        return *this;
    }

    Point &operator-=(const Vector &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Point operator*(float f) const { return Point(x * f, y * f, z * f); }

    Point &operator*=(float f)
    {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    Point operator/(float f) const
    {
        float inv = 1.0 / f;
        return Point(inv * x, inv * y, inv * z);
    }

    Point &operator/=(float f)
    {
        float inv = 1.0 / f;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }

    float operator[](int i) const { return (&x)[i]; }

    float &operator[](int i) { return (&x)[i]; }

    bool operator==(const Point &p) const
    {
        return p.x == x && p.y == y && p.z == z;
    }

    bool operator!=(const Point &p) const
    {
        return x != p.x || y != p.y || z != p.z;
    }

    void Print(FILE *f) const
    {
        fprintf(f, "x: %f, y: %f, z: %f \n", x, y, z);
    }

    float x, y, z;
};

class Normal
{
public:
    Normal()
    {
        x = 0.f;
        y = 0.f;
        z = 0.f;
    }
    Normal(float xx, float yy, float zz) : x(xx), y(yy), z(zz){};
    Normal(const Normal &n)
    {
        x = n.x;
        y = n.y;
        z = n.z;
    };
    explicit Normal(const Vector &v) : x(v.x), y(v.y), z(v.z){};

    Normal &operator=(const Normal &n)
    {
        x = n.x;
        y = n.y;
        z = n.z;
        return *this;
    }

    Normal operator-() const { return Normal(-x, -y, -z); }
    Normal operator+(const Normal &n) const
    {
        return Normal(x + n.x, y + n.y, z + n.z);
    }

    Normal &operator+=(const Normal &n)
    {
        x += n.x;
        y += n.y;
        z += n.z;
        return *this;
    }
    Normal operator-(const Normal &n) const
    {
        return Normal(x - n.x, y - n.y, z - n.z);
    }

    Normal &operator-=(const Normal &n)
    {
        x -= n.x;
        y -= n.y;
        z -= n.z;
        return *this;
    }
    bool HasNaNs() const { return isnan(x) || isnan(y) || isnan(z); }
    Normal operator*(float f) const { return Normal(f * x, f * y, f * z); }

    Normal &operator*=(float f)
    {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }
    Normal operator/(float f) const
    {
        float inv = 1.f / f;
        return Normal(x * inv, y * inv, z * inv);
    }

    Normal &operator/=(float f)
    {
        float inv = 1.f / f;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }

    float operator[](int i) const { return (&x)[i]; }

    float &operator[](int i) { return (&x)[i]; }

    bool operator==(const Normal &n) const
    {
        return x == n.x && y == n.y && z == n.z;
    }
    bool operator!=(const Normal &n) const
    {
        return x != n.x || y != n.y || z != n.z;
    }

    float LengthSquared() const { return x * x + y * y + z * z; }
    float Length() const { return sqrtf(LengthSquared()); }

    float x, y, z;
};

class Ray
{
public:
    Ray() : mint(0.f), maxt(INFINITY), depth(0), time(0.f){};
    Ray(const Point &origin,
        const Vector &direction,
        float start,
        float end = INFINITY,
        float t = 0.f,
        int d = 0)
        : o(origin), d(direction), mint(start), maxt(end), depth(d), time(t) {}

    Point operator()(float t) const { return o + d * t; }

    Point o;
    Vector d;
    mutable float mint, maxt;
    int depth;
    float time;
};

// 微分
class RayDifferential : public Ray
{
public:
    RayDifferential() : hasDifferentials(false){};
    RayDifferential(const Point &org,
                    const Vector &dir,
                    float start,
                    float end = INFINITY,
                    float t = 0.f,
                    int d = 0)
        : Ray(org, dir, start, end, t, d)
    {
        hasDifferentials = false;
    };

    explicit RayDifferential(const Ray &ray) : Ray(ray)
    {
        hasDifferentials = false;
    };

    void ScaleDifferentials(float s)
    {
        rxOrigin = o + (rxOrigin - o) * s;
        ryOrigin = o + (ryOrigin - o) * s;
        rxDirection = d + (rxDirection - d) * s;
        ryDirection = d + (ryDirection - d) * s;
    }

    bool hasDifferentials;
    Point rxOrigin, ryOrigin;
    Vector rxDirection, ryDirection;
};

class BBox
{
public:
    BBox()
    {
        pMax = Point(INFINITY, INFINITY, INFINITY);
        pMin = Point(-INFINITY, -INFINITY, -INFINITY);
    };

    BBox(const Point &p) : pMin(p), pMax(p) {}

    BBox(const Point &p1, const Point &p2)
    {
        pMin = Point(min(p1.x, p2.x), min(p1.y, p2.y), min(p1.z, p2.z));
        pMax = Point(max(p1.x, p2.x), max(p1.y, p2.y), max(p1.z, p2.z));
    }
    friend BBox Union(const BBox &b, const Point &p);
    friend BBox Union(const BBox &b, const BBox &b2);
    // 是否有重叠
    bool Overlaps(const BBox &b) const
    {
        bool x = (pMax.x >= b.pMin.x) && (pMin.x <= b.pMax.x);
        bool y = (pMax.y >= b.pMin.y) && (pMin.y <= b.pMax.y);
        bool z = (pMax.z >= b.pMin.z) && (pMin.z <= b.pMax.z);
        return x && y && z;
    }

    // 点是否在包围盒里
    bool Inside(const Point &pt) const
    {
        return pt.x >= pMin.x && pt.x <= pMax.x && pt.y >= pMin.y &&
               pt.y <= pMax.y && pt.z >= pMin.z && pt.z <= pMax.z;
    }

    void Expand(float delta)
    {
        pMin -= Vector(delta, delta, delta);
        pMax += Vector(delta, delta, delta);
    }

    float SurfaceArea() const
    {
        Vector box = pMax - pMin;
        return 2.f * (box.x * box.y + box.x * box.z + box.y * box.z);
    }

    float Volume() const
    {
        Vector box = pMax - pMin;
        return box.x * box.y * box.z;
    }

    int MaximumExtent() const
    {
        Vector box = pMax - pMin;
        if (box.x > box.y && box.x > box.z)
        {
            return 0;
        }
        else if (box.y > box.z)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }

    const Point &operator[](int i) const;
    Point &operator[](int i);

    Point Lerp(float tx, float ty, float tz) const
    {
        return Point(::Lerp(tx, pMin.x, pMax.x), ::Lerp(ty, pMin.y, pMax.y),
                     ::Lerp(tz, pMin.z, pMax.z));
    }

    Vector Offset(const Point &p)
    {
        return Vector((p.x - pMin.x) / (pMax.x - pMin.x),
                      (p.y - pMin.y) / (pMax.y - pMin.y),
                      (p.z - pMin.z) / (pMax.z - pMin.z));
    }

    void BoundingSphere(Point *c, float *rad) const;

    bool IntersectP(const Ray &ray,
                    float *hitt0 = NULL,
                    float *hitt1 = NULL) const;

    bool operator==(const BBox &b) const
    {
        return b.pMin == pMin && b.pMax == pMax;
    }

    bool operator!=(const BBox &b) const
    {
        return b.pMin != pMin || b.pMax != pMax;
    }

    Point pMin, pMax;
};

// Geometry Inline Functions
inline Vector::Vector(const Point &p) : x(p.x), y(p.y), z(p.z) {}

inline Vector::Vector(const Normal &n) : x(n.x), y(n.y), z(n.z) {}

inline Vector operator*(float f, const Vector &v)
{
    return v * f;
}

inline float Dot(const Vector &v1, const Vector &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float AbsDot(const Vector &v1, const Vector &v2)
{
    return fabsf(Dot(v1, v2));
}

inline Vector Cross(const Vector &v1, const Vector &v2)
{
    return Vector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                  v1.x * v2.y - v1.y * v2.x);
}

inline Vector Cross(const Normal &v1, const Vector &v2)
{
    return Vector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                  v1.x * v2.y - v1.y * v2.x);
}

inline Vector Cross(const Vector &v1, const Normal &v2)
{
    return Vector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                  v1.x * v2.y - v1.y * v2.x);
}

inline Vector Normalize(const Vector &v)
{
    return v / v.Length();
}

inline float Distance(const Point &p1, const Point &p2)
{
    return (p1 - p2).Length();
}

inline float DistanceSquared(const Point &p1, const Point &p2)
{
    return (p1 - p2).LengthSquared();
}

inline Point operator*(float f, const Point &p)
{
    return p * f;
}

inline Normal operator*(float f, const Normal &n)
{
    return Normal(f * n.x, f * n.y, f * n.z);
}

inline Normal Normalize(const Normal &n)
{
    return n / n.Length();
}

inline float Dot(const Normal &n1, const Vector &v2)
{
    return n1.x * v2.x + n1.y * v2.y + n1.z * v2.z;
}

inline float Dot(const Vector &v1, const Normal &n2)
{
    return v1.x * n2.x + v1.y * n2.y + v1.z * n2.z;
}

inline float Dot(const Normal &n1, const Normal &n2)
{
    return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

inline float AbsDot(const Normal &n1, const Vector &v2)
{
    return fabsf(n1.x * v2.x + n1.y * v2.y + n1.z * v2.z);
}

inline float AbsDot(const Vector &v1, const Normal &n2)
{
    return fabsf(v1.x * n2.x + v1.y * n2.y + v1.z * n2.z);
}

inline float AbsDot(const Normal &n1, const Normal &n2)
{
    return fabsf(n1.x * n2.x + n1.y * n2.y + n1.z * n2.z);
}

inline Normal Faceforward(const Normal &n, const Vector &v)
{
    return Dot(n, v) < 0.f ? -n : n;
}

inline Normal Faceforward(const Normal &n, const Normal &n2)
{
    return (Dot(n, n2) < 0.f) ? -n : n;
}

inline Vector Faceforward(const Vector &v, const Vector &v2)
{
    return (Dot(v, v2) < 0.f) ? -v : v;
}

inline Vector Faceforward(const Vector &v, const Normal &n2)
{
    return (Dot(v, n2) < 0.f) ? -v : v;
}

inline const Point &BBox::operator[](int i) const
{
    return (&pMin)[i];
}

inline Point &BBox::operator[](int i)
{
    return (&pMin)[i];
}

// x = sin(o1) * cos(o2)  y = sin(o1) sin(o2)  z = cos(o1)
inline Vector SphericalDirection(float sintheta, float costheta, float phi)
{
    return Vector(sintheta * cosf(phi), sintheta * sinf(phi), costheta);
}

inline Vector SphericalDirection(float sintheta,
                                 float costheta,
                                 float phi,
                                 const Vector &x,
                                 const Vector &y,
                                 const Vector &z)
{
    return sintheta * cosf(phi) * x + sintheta * sinf(phi) * y + costheta * z;
}

// 球形 左右的角度
inline float SphericalTheta(const Vector &v)
{
    return acosf(Clamp(v.z, -1.f, 1.f));
}

// 球形上下的角度
inline float SphericalPhi(const Vector &v)
{
    float p = atan2f(v.y, v.x);
    return (p < 0.f) ? p + 2.f * M_PI : p;
}