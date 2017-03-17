#include "GameMath.h"

namespace gamemath {

Quaternion::Quaternion() {}
Quaternion::~Quaternion() {}


Quaternion::Quaternion(float w, float x, float y, float z) {
        data[0] = w;
        data[1] = x;
        data[2] = y;
        data[3] = z;
}


Quaternion Quaternion::conjugate() const {
        return Quaternion(-data[0], -data[1], -data[2], data[3]);
}


Quaternion Quaternion::mul(const Quaternion &b) const {
    return Quaternion(
        data[0] * b.data[3] + data[3] * b.data[0] + data[1] * b.data[2] - data[2] * b.data[1],
        data[1] * b.data[3] + data[3] * b.data[1] + data[2] * b.data[0] - data[0] * b.data[2],
        data[2] * b.data[3] + data[3] * b.data[2] + data[0] * b.data[1] - data[1] * b.data[0],
        data[3] * b.data[3] - data[0] * b.data[0] - data[1] * b.data[1] - data[2] * b.data[2]);
}


const float Quaternion::length() const {
        return (float) sqrt((data[0] * data[0])
                          + (data[1] * data[1])
                          + (data[2] * data[2])
                          + (data[3] * data[3]));
}


void Quaternion::normalize() {
    float l = length();
    data[0] /= l;
    data[1] /= l;
    data[2] /= l;
    data[3] /= l;
}


Quaternion Quaternion::getNormalized() const {
    float l = length();
    return Quaternion(data[0] / l, data[1] / l, data[2] / l, data[3] / l);
}


Quaternion Quaternion::add(const Quaternion &b) const {
    return Quaternion(data[0] + b.data[0],
                      data[1] + b.data[1],
                      data[2] + b.data[2],
                      data[3] + b.data[3]);
}


Quaternion Quaternion::sub(const Quaternion &b) const {
    return Quaternion(data[0] - b.data[0],
                      data[1] - b.data[1],
                      data[2] - b.data[2],
                      data[3] - b.data[3]);
}


void Quaternion::set(size_t index, float value) {
    data[index] = value;
}


const float Quaternion::get(size_t index) const {
    return data[index];
}


const bool Quaternion::equals(const Quaternion &other) const {
    return((data[0] == other.data[0])
        && (data[1] == other.data[1])
        && (data[2] == other.data[2])
        && (data[3] == other.data[3]));
}


void Quaternion::rotate(Vec3f &in) const {
    Vec3f u = Vec3f(data[0], data[1], data[2]);
    in = ((2.0 * u.dot(in) * u)
       + (((data[3]*data[3]) - u.dot(u)) * in))
       + ((2.0 * data[3]) * u.cross(in));
}


void Quaternion::rotate(const Vec3f &in, Vec3f &out) const {
    Vec3f u = Vec3f(data[0], data[1], data[2]);
    out = ((2.0 * u.dot(in) * u)
        + (((data[3]*data[3]) - u.dot(u)) * in))
        + ((2.0 * data[3]) * u.cross(in));
}


Vec3f Quaternion::getRotated(const Vec3f &in) const {
    Vec3f u = Vec3f(data[0], data[1], data[2]);
    return (((2.0 * u.dot(in) * u)
         + (((data[3]*data[3]) - u.dot(u)) * in))
         + ((2.0 * data[3]) * u.cross(in)));
}


void Quaternion::rotate(Vec4f &in) const {
    Vec3f u = Vec3f(data[0], data[1], data[2]);
    Vec3f v = Vec3f(in.data[0], in.data[1], in.data[2]);
    Vec3f p = ((2.0 * u.dot(v) * u)
            + (((data[3]*data[3]) - u.dot(u)) * v))
            + ((2.0 * data[3]) * u.cross(v));
    in.data[0] = p.data[0];
    in.data[1] = p.data[1];
    in.data[2] = p.data[2];
}


void Quaternion::rotate(const Vec4f &in, Vec4f &out) const {
    Vec3f u = Vec3f(data[0], data[1], data[2]);
    Vec3f v = Vec3f(in.data[0], in.data[1], in.data[2]);
    Vec3f p = ((2.0 * u.dot(v) * u)
            + (((data[3]*data[3]) - u.dot(u)) * v))
            + ((2.0 * data[3]) * u.cross(v));
    out.data[0] = p.data[0];
    out.data[1] = p.data[1];
    out.data[2] = p.data[2];
}


Vec4f Quaternion::getRotated(const Vec4f &in) const {
    Vec3f u = Vec3f(data[0], data[1], data[2]);
    Vec3f v = Vec3f(in.data[0], in.data[1], in.data[2]);
    Vec3f p = ((2.0 * u.dot(v) * u)
            + (((data[3]*data[3]) - u.dot(u)) * v))
            + ((2.0 * data[3]) * u.cross(v));
    return Vec4f(p.data[0], p.data[1], p.data[2], in.data[3]);
}


Mat4f& Quaternion::toMat4f(Mat4f &in) const {
    in.m[0] = 1 - (2 * data[2] * data[2]) - (2 * data[3] * data[3]);
    in.m[1] = (2 * data[1] * data[2]) - (2 * data[0] * data[3]);
    in.m[2] = (2 * data[1] * data[3]) - (2 * data[0] * data[2]);
    in.m[3] = 0;

    in.m[4] = (2 * data[1] * data[2]) - (2 * data[0] * data[3]);
    in.m[5] = 1 - (2 * data[1] * data[1]) - (2 * data[3] * data[3]);
    in.m[6] = (2 * data[2] * data[3]) - (2 * data[0] * data[0]);
    in.m[7] = 0;

    in.m[8]  = (2 * data[1] * data[3]) - (2 * data[0] * data[2]);
    in.m[9]  = (2 * data[2] * data[3]) - (2 * data[0] * data[1]);
    in.m[10] = 1 - (2 * data[1] * data[1]) - (2 * data[2] * data[2]);
    in.m[11] = 0;

    in.m[12] = 0;   in.m[13] = 0;   in.m[14] = 0;   in.m[15] = 1;

    return in;
}


Quaternion& Quaternion::fromMat4f(Mat4f &in) {
    data[0] = sqrt(1.0 + in.m[0] + in.m[5] + in.m[10]) / 2.0;
    double w4 = (4.0 * data[0]);
    data[1] = (in.m[9] - in.m[6]) / w4;
    data[2] = (in.m[2] - in.m[8]) / w4;
    data[3] = (in.m[4] - in.m[1]) / w4;
    return *this;
}


/*-------------------------------------------------------------------------*/
/*                                OPERATORS                                */
/*-------------------------------------------------------------------------*/


const Quaternion operator+(const Quaternion &a, const Quaternion &b) {
    return Quaternion(a.data[0] + b.data[0], a.data[1] + b.data[1],
                      a.data[2] + b.data[2], a.data[3] + b.data[3]);
}


const Quaternion operator-(const Quaternion &a, const Quaternion &b) {
    return Quaternion(a.data[0] - b.data[0], a.data[1] - b.data[1],
                      a.data[2] - b.data[2], a.data[3] - b.data[3]);
}


const Quaternion operator*(const Quaternion &a, const Quaternion &b) {
    return Quaternion(
        a.data[0] * b.data[3] + a.data[3] * b.data[0] + a.data[1] * b.data[2] - a.data[2] * b.data[1],
        a.data[1] * b.data[3] + a.data[3] * b.data[1] + a.data[2] * b.data[0] - a.data[0] * b.data[2],
        a.data[2] * b.data[3] + a.data[3] * b.data[2] + a.data[0] * b.data[1] - a.data[1] * b.data[0],
        a.data[3] * b.data[3] - a.data[0] * b.data[0] - a.data[1] * b.data[1] - a.data[2] * b.data[2]);
}


const Vec3f Quaternion::operator*(const Vec3f &b) const {
    Vec3f u = Vec3f(data[0], data[1], data[2]);
    Vec3f v = Vec3f(b.data[0], b.data[1], b.data[2]);
    return ((2.0 * u.dot(v) * u)
            + (((data[3]*data[3]) - u.dot(u)) * v))
            + ((2.0 * data[3]) * u.cross(v));
}


const bool operator==(const Quaternion &a, const Quaternion &b) {
    return ((a.data[0] == b.data[0]) &&
            (a.data[1] == b.data[1]) &&
            (a.data[2] == b.data[2]) &&
            (a.data[3] == b.data[3]));
}


}
