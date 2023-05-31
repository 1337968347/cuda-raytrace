#include <iostream>
#include <cstring>
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
    void setPixel(int x, int y, Vector)
    {
        int offset = (x + y * width) * 4; // 计算偏移量
        data[offset] = r;
        data[offset + 1] = g;
        data[offset + 2] = b;
        data[offset + 3] = a;
    }

    // 获取像素值
    void getPixel(int x, int y, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a) const
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
        // TODO: 实现保存图像的代码
        return true;
    }
};
