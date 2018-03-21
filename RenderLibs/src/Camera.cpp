#include "Camera.h"

using namespace gamemath;


Camera::Camera(float aspectIn, float fovIn, float farIn, float nearIn) :
        perspective(gamemath::Mat4f::getPerspective(aspectIn, fovIn, nearIn, farIn)),
        inverse(gamemath::Mat4f::invertProjection(perspective)),
        affine(gamemath::Mat4f::getIdentity()),
        aspect(aspect),
        fov(fov), far(far), near(near),
        x(0), y(0), z(0), ry(0), rv(0)
{
        //this->planes = Vec4f.frustrumPlanes(aspect, fov, near, far);
}


Camera::~Camera() {}


void Camera::setFrustum(float aspect, float fov, float far, float near) {
    this->aspect = aspect;
    this->fov    = fov;
    this->far    = far;
    this->near   = near;
    this->perspective = Mat4f::getPerspective(aspect, fov, near, far);
    this->inverse     = Mat4f::invertProjection(perspective);
    /*this->planes      = Vec4f.frustrumPlanes(aspect, fov, near, far);
    this->planes[0] = this->planes[0].mul(affine);
    this->planes[1] = this->planes[1].mul(affine);
    this->planes[2] = this->planes[2].mul(affine);
    this->planes[3] = this->planes[3].mul(affine);
    this->planes[4] = this->planes[4].mul(affine);
    this->planes[5] = this->planes[5].mul(affine);*/
}


bool Camera::cull(gamemath::Vec4f q, float r) {
        bool out = true;
        size_t counter = 0;
        while(out && (counter < 6)) {
            out = out && (q.dot(planes[counter++]) >= -r);
        }
        return !out;
}


void Camera::update() {
        updateAffine();
}


gamemath::Mat4f Camera::getTransform() {
        return perspective.mul(affine);
}


void Camera::setPos(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
}


void Camera::setRot(int ry, int rv) {
    this->ry = ry;
    this->rv = rv;
}


void Camera::setPosNRot(int x, int y, int z, int ry, int rv) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->ry = ry;
    this->rv = rv;
}


void Camera::updateAffine() {
    // TODO: Fixed Mat4f to allow the code to work
    // TODO: Implement this
    /*affine = Mat4f.giveRotation(ry)
            .mul(Mat4f.giveRotation(rv, (float)(Math.cos(Math.toRadians(ry))),
                                    0, (float)(Math.sin(Math.toRadians(ry)))))
            .mul(Mat4f.giveTranslation(x, -y, z)); */
}
