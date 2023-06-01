#include <iostream>
#include <fstream>
#include "./core/pbrt.h"
#include "./core/transform.cpp"

int main(int argc, const char **argv)
{

    Camera camera;
    Vector eyePos(1.0, 0.0, 0.0);
    camera.setEyePosition(eyePos);

    const Transform viewTransform = camera.getViewTransform();

    FILE *fp;
    fp = fopen("example.txt", "w");
    viewTransform.Print(fp);

    return 0;
}