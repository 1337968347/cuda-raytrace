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

bool Shape::Intersect(const Ray &ray, float *tHit, float *rayEpsilon, DifferentialGeometry *dg) const
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


/**
 * @brief 描述在给定点 p 处从方向 wi 进行采样的概率 
 * 
 * @param p 点
 * @param wi 光源方向
 * @return float 
 */
float Shape::Pdf(const Point &p, const Vector &wi) const
{
    DifferentialGeometry dgLight;
    Ray ray(p, wi, 1e-3f);
    ray.depth = -1;
    float thit, rayEpsilon;
    if(!Intersect(ray, &thit, &rayEpsilon, &dgLight)) return 0.0;

    // 光源跟交点距离的平方
    float distanceSquared = DistanceSquared(p, ray(thit));

    // 表面法线与光线的夹角
    float theta = AbsDot(dgLight.nn, -wi);

    // 这里返回的是pdf的倒数
    float pdf = distanceSquared / (theta * Area());

    if(isinf(pdf)) pdf = 0.0;

    return pdf;
}