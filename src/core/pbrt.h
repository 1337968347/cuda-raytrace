#pragma once

#define M_PI 3.14159265358979323846f

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
using std::vector;

using std::max;
using std::min;
using std::swap;

class Point;

class Normal;

class Transform;

// 插值
inline float Lerp(float t, float v1, float v2)
{
    return (1.f - t) * v1 + t * v2;
}

inline float Clamp(float val, float min, float max)
{
    if (val < min)
        return min;
    if (val > max)
        return max;
    return val;
}

inline float Radians(float deg)
{
    return ((float)M_PI / 180.f) * deg;
}

#include "rng.h"
#include "geometry.h"
#include "transform.h"
#include "quaternion.h"
#include "shape.h"
#include "image.h"
#include "camera.h"