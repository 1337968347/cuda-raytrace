#include <iostream>
#include <fstream>
#include "./core/pbrt.h"
#include "./core/geometry.cpp"
#include "./core/transform.cpp"
#include "./core/quaternion.cpp"

int main(int argc, const char **argv)
{

    Vector pos(10.0, 20.0, 30.0);
    Transform t = RotateX(10) * Translate(pos);


    Quaternion q(t);

    q * 2.0;


    Transform quaT = q.ToTransform();

    Vector eyePos(1.0, 0.0, 0.0);

    const Point p(0.0, 0.0, 0.0);

    FILE *fp;
    fp = fopen("example.txt", "w");

    quaT.Print(fp);
    p.Print(fp);




    return 0;
}