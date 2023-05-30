#include "./core/pbrt.h"
#include "./core/transform.cpp"

int main(int argc, const char** argv) {
    Matrix4x4 m1;
    m1 = Inverse(m1);
    FILE* fp;
    fp = fopen("example.txt", "w");
    m1.Print(fp);
    return 0;
}