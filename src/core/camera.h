#include "pbrt.h"
#include "geometry.h"
#include "transform.h"

class Camera
{
public:
    Vector eyePosition;
    // x Rotate
    float x = 0.0;
    // y Rotate
    float y = 0.0;
    // 近截面
    float near = 0.01;
    // 远截面
    float far = 1000;
    // 视野范围
    float fov = 80;
    // 相机事业 左右跟上下的比例
    float aspect = 1.0;

    Camera(/* args */);

    void setEyePosition(Vector pos)
    {
        eyePosition = pos;
    }

    Transform getViewMatrix()
    {
        Transform mat4;
        return mat4;
    }
};
