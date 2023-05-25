#pragma once

#include "memory.h"
#include "Shape.h"
#include "transform.h"
#include "geometry.h"
#include "pbrt.h"
class Shape : ReferenceCounted {
   private:
    /* data */
   public:
    Shape(const Transform* o2w, const Transform* w2o, bool ro);
    virtual ~Shape();
    // 纯虚函数 真正没有被调用
    virtual BBox objectBound() const = 0;
    // 虚函数 但是可以调用子类的方法
    virtual BBox WorldBound() const;
    virtual bool CanIntersect() const;
    virtual void Refine(Shape &refined) const;
    virtual bool Intersect () const;
};
