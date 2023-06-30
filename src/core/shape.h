#pragma once

#include "pbrt.h"

class Shape
{
private:
    /* data */
public:
    Shape(const Transform *o2w, const Transform *w2o, bool ro);
    virtual ~Shape();
    virtual BBox objectBound() const = 0;
    virtual BBox WorldBound() const;
    virtual bool CanIntersect() const;
    // 细分
    virtual void Refine(vector<Reference<Shape>> &refined) const;
    virtual bool Intersect(const Ray &ray, float *tHit, float *rayEpsilon, RayDifferential *dg) const;
    virtual bool IntersectP(const Ray &ray) const;
    virtual void GetShadingGeometry(const Transform &obj2world, const DifferentialGeometry &dg, DifferentialGeometry *dgShading) const
    {
        *dgShading = dg;
    }
    virtual float Area() const;
    virtual Point Sample(float u1, float u2, Normal *Ns) const
    {
        throw "Unimplemented Shape::Sample() method called";
        return Point();
    }
    // 计算给定形状点的概率密度函数（PDF）
    virtual float Pdf(const Point &pShape) const
    {
        return 1.f / Area();
    }
    virtual Point Sample(const Point &p, float u1, float u2, Normal *Ns) const
    {
        return Sample(u1, u2, Ns);
    }
    virtual float Pdf(const Point &p, const Vector &wi) const;
    // Shape public Data
    const Transform *ObjectToWorld, *WorldToObject;
    // 是否面被反转， 是否切换了左右手坐标系
    const bool ReverseOrientation, TransformsSwapsHandedness;
    const uint32_t shapeId;
    // 下一个shape的id ， 自增
    static uint32_t nextshapeId;
};
