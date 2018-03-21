#include "Camera.h"


Camera::Camera(float aspectIn, float fovIn, float farIn, float nearIn) :
        perspective(gamemath::Mat4f::getPerspective(aspectIn, fovIn, nearIn, farIn)),
        inverse(gamemath::Mat4f::invertProjection(perspective)),
        affine(gamemath::Mat4f::getIdentity()),
        aspect(aspect),
        fov(fov), far(far), near(near),
        x(0), y(0), z(0), ry(0), rv(0)
{
        //this.planes = Vec4f.frustrumPlanes(aspect, fov, near, far);
}


Camera::~Camera() {}
