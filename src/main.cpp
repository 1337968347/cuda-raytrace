#include <iostream>
#include <fstream>
#include "./core/pbrt.h"
#include "./core/transform.cpp"

int main(int argc, const char** argv) {
    
    
        const int width = 640;
    const int height = 480;
    const int max_color_value = 255;

    std::ofstream image("image.ppm");
    image << "P3" << std::endl;
    image << width << " " << height << std::endl;
    image << max_color_value << std::endl;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int red = x % (max_color_value + 1);
            int green = y % (max_color_value + 1);
            int blue = (x + y) % (max_color_value + 1);
            image << red << " " << green << " " << blue << " ";
        }
        image << std::endl;
    }

    image.close();

    return 0;
}