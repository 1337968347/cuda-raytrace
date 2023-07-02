#include "pbrt.h"

Shape::~Shape() {}

Shape::Shape(const Transform *o2w, const Transform *w2o, bool ro)
    : ObjectToWorld(o2w), WorldToObject(w2o), ReverseOrientation(ro),
      TransformSwapsHandedness(o2w->SwapsHandedness()), shapeId(nextshapeId++)
{
}

uint32_t Shape::nextshapeId = 1;

BBox Shape::WorldBound() const
{
    // 计算对象空间的包围盒，然后转换成世界空间
    return (*ObjectToWorld)(ObjectBound());
}

bool Shape::CanIntersect() const
{
    return true;
}

void Shape::Refine(vector<Reference<Shape>> &refined) const
{
    throw "细分方法没有重写";
}

bool Shape::Intersect(const Ray &ray, float *tHit, float *rayEpsilon, RayDifferential *dg) const
{
    throw "未实现的方法";
    return false;
}

bool Shape::IntersectP(const Ray &ray) const
{
    throw "未实现的方法";
    return false;
}

float Shape::Area() const
{
    throw "未实现的方法";
    return 0.;
}

float Shape::Pdf(const Point &p, const Vector &wi) const
{
    DifferentialGeometry dgLight;
    Ray ray(p, wi, 1e-3f);
    // TODO 
}