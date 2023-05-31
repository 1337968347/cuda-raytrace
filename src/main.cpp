#include <iostream>
#include <fstream>
#include "./core/pbrt.h"
#include "./core/transform.cpp"

int main(int argc, const char **argv)
{
    ImageData imageData(512, 512);
    const char *fileName = "demo.ppm";
    const unsigned int red = 255;
    const unsigned int green = 0;
    const unsigned int blue = 0;
    const unsigned int alpha = 255;
    for (int i = 200; i < 300; i++)
    {
        for (int j = 200; j < 400; j++)
        {
            imageData.setPixel(i, j, red, green, blue, alpha);
        }
    }

    imageData.save(fileName);
    return 0;
}