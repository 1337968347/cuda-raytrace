#include <iostream>
#include <cstring>
#include <fstream>

class ImageData
{
private:
    /* data */
    int width, height;
    unsigned char *data;

public:
    ImageData(int w, int h) : width(w), height(h)
    {
        data = new unsigned char[w * h * 4];
        memset(data, 0, w * h * 4);
    }

    ~ImageData()
    {
        delete[] data;
    };

    int getWidth() const
    {
        return width;
    }

    int getHeight() const
    {
        return height;
    }
    // 获取像素数据指针
    unsigned char *getData() const { return data; }

    // 设置像素值
    void setPixel(int x, int y, const unsigned int &r, const unsigned int &g, const unsigned int &b, const unsigned int &a)
    {
        int offset = (x + y * width) * 4; // 计算偏移量
        data[offset] = r;
        data[offset + 1] = g;
        data[offset + 2] = b;
        data[offset + 3] = a;
    }

    // 获取像素值
    void getPixel(int x, int y, unsigned int &r, unsigned int &g, unsigned int &b, unsigned int &a) const
    {
        int offset = (x + y * width) * 4; // 计算偏移量
        r = data[offset];
        g = data[offset + 1];
        b = data[offset + 2];
        a = data[offset + 3];
    }

    // 保存图像到文件
    bool save(const char *filename) const
    {
        const int max_color_value = 255;
        std::ofstream image(filename);
        image << "P3" << std::endl;
        image << width << " " << height << std::endl;
        image << max_color_value << std::endl;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int idx = (y * width + x) * 4;
                int red = data[idx];
                int green = data[idx + 1];
                int blue = data[idx + 2];
                image << red << " " << green << " " << blue << " ";
            }
            image << std::endl;
        }

        image.close();
        return true;
    }
};
