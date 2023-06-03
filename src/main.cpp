#include <iostream>
#include <fstream>
#include "./core/pbrt.h"
#include "./core/geometry.cpp"
#include "./core/transform.cpp"

int main(int argc, const char **argv)
{

    Camera camera;
    Vector eyePos(1.0, 0.0, 0.0);
    camera.setEyePosition(eyePos);

    const Transform viewTransform = camera.perspective();

    const Point p(0.0, 0.0, 0.0);

    FILE *fp;
    fp = fopen("example.txt", "w");

    p.Print(fp);

    const Point p1 = viewTransform(p);

    p1.Print(fp);

    viewTransform.Print(fp);

    return 0;
}