#ifndef CAMERA_H
#define CAMERA_H

#include "GameMath.h"


class Camera
{
    public:
        Camera() = delete;
        Camera(float aspectIn, float fovIn, float farIn, float nearIn);
        virtual ~Camera();
        void setFrustum(float aspect, float fov, float far, float near);
        bool cull(gamemath::Vec4f q, float r);
        void update();
        gamemath::Mat4f getTransform();
        void setPos(int x, int y, int z);
        void setRot(int ry, int rv);
        void setPosNRot(int x, int y, int z, int ry, int rv);
        void updateAffine();
    protected:
    private:
        gamemath::Mat4f perspective;
        gamemath::Mat4f inverse;
        gamemath::Mat4f affine;
        gamemath::Vec4f planes[6];
        float aspect, fov, far, near;
        float x, y, z, ry, rv;
};

#endif // CAMERA_H
