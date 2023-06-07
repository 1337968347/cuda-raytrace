#include "pbrt.h"

class Camera
{
public:
    Vector eyePosition;
    // x Rotate
    float x = 0.0;
    // y Rotate
    float y = 0.0;
    // 近截面
    float nearPlane = 0.01;
    // 远截面
    float farPlane = 1000;
    // 视野范围
    float fov = 80;
    // 相机视野 左右跟上下的比例
    float aspect = 1.0;
    // 相机的图像的宽度和高度
    float width = 256;
    float height = 256;
    
    Transform cameraToScreen, rasterToCamera;

    Transform screenToRaster, rasterToScreen;

    Camera() : eyePosition(0, 0, 0), x(0), y(0), nearPlane(0.01), farPlane(1000), fov(80), aspect(1.0){};

    void setEyePosition(Vector pos)
    {
        eyePosition = pos;
    }

    Transform getViewTransform() const
    {
        Transform mat4;
        mat4 = RotateY(y) * RotateX(x) * Translate(-eyePosition);
        return mat4;
    }

    // 透视相机
    Transform perspective()
    {
        Transform perspective = Perspective(fov, nearPlane, farPlane);
        return perspective;
    };

    // 获取一条光线
    Ray getRay(int x, int y) const
    {
        Point ro(eyePosition);
        Vector re(x - width / 2, y - height / 2, 1);
        const Transform viewTransform = getViewTransform();
        re = viewTransform(re);
        Vector rd = Normalize(re);
        Ray ray(ro, rd, 0.0, +INFINITY, 0.0, 0);
        return ray;
    }
};