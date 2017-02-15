#include "GameMath.h"

namespace gamemath {

Vec4f::Vec4f() {
    data[0] = data[1] = data[2] = data[3] = 0;
}


Vec4f::Vec4f(float x, float y, float z, float w) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = w;
}


Vec4f::Vec4f(float* ar) {
    // Not using memcpy, this is small.
    data[0] = ar[0];
    data[1] = ar[1];
    data[2] = ar[2];
    data[3] = ar[3];
}



Vec4f::Vec4f(const Vec3f &vec) {
    data[0] = vec.get(0);
    data[1] = vec.get(1);
    data[2] = vec.get(2);
    data[3] = 1; // The geometric interpetation, not just convenience!
}


Vec4f::~Vec4f() {/*Nothing to do? The array is not dynamically allocated.*/}


float Vec4f::dot(const Vec4f &b) const {
    return (data[0] * b.data[0]) + (data[1] * b.data[1])
            + (data[2] * b.data[2]) + (data[3] * b.data[3]);
}


float Vec4f::length() const {
    return sqrt((data[0] * data[0]) + (data[1] * data[1])
                + (data[2] * data[2]) + (data[3] * data[3]));
}


void Vec4f::normalize() {
    float l = length();
    data[0] *= l;
    data[1] *= l;
    data[2] *= l;
    data[3] *= l;
}


Vec4f Vec4f::add(const Vec4f &b) {
    return Vec4f(data[0] + b.data[0], data[1] + b.data[1],
                 data[2] + b.data[2], data[3] + b.data[3]);
}


Vec4f Vec4f::sub(const Vec4f &b) {
    return Vec4f(data[0] - b.data[0], data[1] - b.data[1],
                 data[2] - b.data[2], data[3] - b.data[3]);
}


Vec4f Vec4f::add(const float b) {
    Vec4f direction = *this;
    direction.normalize();
    direction.mul(b);
    return direction.add(*this);
}


Vec4f Vec4f::sub(const float b) {
    Vec4f direction = *this;
    direction.normalize();
    direction.mul(b);
    return direction.sub(*this);
}


Vec4f Vec4f::mul(const float b) {
    return Vec4f(data[0] * b, data[1] * b,
                 data[2] * b, data[3] * b);
}


Vec4f Vec4f::div(const float b) {
    return Vec4f(data[0] / b, data[1] / b,
                 data[2] / b, data[3] / b);
}


void Vec4f::set(const int index, const float value) {
    // Should I include error checking?  Or assume this will be remembered?
    data[index] = value;
}


float Vec4f::get(const int index) const {
    // Should I include error checking?  Or assume this will be remembered?
    return data[index];
}


Vec3f Vec4f::trunc3d() {
    return Vec3f(data);
}


Vec3f Vec4f::real3d() const {
    return Vec3f(data[0] / data[3], data[1] / data[3], data[2] / data[4]);
}


bool Vec4f::equals(const Vec4f &b) const {
    return ((data[0] == b.data[0]) && (data[1] == b.data[1])
            && (data[2] == b.data[2]) && (data[3] == b.data[3]));
}

/*----------------------------------------------------------*/
/*                      OPERATORS                           */
/*----------------------------------------------------------*/




const Vec4f operator+(const Vec4f &a, const Vec4f &b) {
    return Vec4f(a.data[0] + b.data[0], a.data[1] + b.data[1],
                 a.data[2] + b.data[2], a.data[3] + b.data[3]);
}


const Vec4f operator-(const Vec4f &a, const Vec4f &b) {
    return Vec4f(a.data[0] - b.data[0], a.data[1] - b.data[1],
                 a.data[2] - b.data[2], a.data[3] - b.data[3]);
}


const Vec4f Vec4f::operator+(const float b) {
    Vec4f direction = *this;
    direction.normalize();
    direction.mul(b);
    return direction.add(*this);
}


const Vec4f Vec4f::operator-(const float b) {
    Vec4f direction = *this;
    direction.normalize();
    direction.mul(b);
    return direction.sub(*this);
}


Vec4f& Vec4f::operator+=(const Vec4f &b) {
    data[0] += b.data[0];
    data[1] += b.data[1];
    data[2] += b.data[2];
    data[3] += b.data[3];
    return *this;
}


Vec4f& Vec4f::operator-=(const Vec4f &b) {
    data[0] -= b.data[0];
    data[1] -= b.data[1];
    data[2] -= b.data[2];
    data[3] -= b.data[3];
    return *this;
}


Vec4f& Vec4f::operator+=(const float b) {
    Vec4f direction = *this;
    direction.normalize();
    direction.mul(b);
    data[0] += direction.data[0];
    data[1] += direction.data[1];
    data[2] += direction.data[2];
    data[3] += direction.data[3];
    return *this;
}


Vec4f& Vec4f::operator-=(const float b) {
    Vec4f direction = *this;
    direction.normalize();
    direction.mul(b);
    data[0] -= direction.data[0];
    data[1] -= direction.data[1];
    data[2] -= direction.data[2];
    data[3] -= direction.data[3];
    return *this;
}


const Vec4f operator*(const Vec4f &a, const float b) {
    return Vec4f(a.data[0] * b, a.data[1] * b,
                 a.data[2] * b, a.data[3] * b);
}


const Vec4f operator/(const Vec4f &a, const float b) {
    return Vec4f(a.data[0] / b, a.data[1] / b,
                 a.data[2] / b, a.data[3] / b);
}


const Vec4f operator*(const float a, const Vec4f &b) {
    return Vec4f(b.data[0] * a, b.data[1] * a,
                 b.data[2] * a, b.data[3] * a);
}


const Vec4f operator/(const float a, const Vec4f &b) {
    return Vec4f(b.data[0] / a, b.data[1] / a,
                 b.data[2] / a, b.data[3] / a);
}


Vec4f& Vec4f::operator*=(const float b) {
    data[0] *= b;
    data[1] *= b;
    data[2] *= b;
    data[3] *= b;
    return *this;
}


Vec4f& Vec4f::operator/=(const float b) {
    data[0] /= b;
    data[1] /= b;
    data[2] /= b;
    data[3] /= b;
    return *this;
}


bool operator==(const Vec4f &a, const Vec4f &b) {
    return ((a.data[0] == b.data[0]) && (a.data[1] == b.data[1]) &&
            (a.data[2] == b.data[2]) && (a.data[3] == b.data[3]));
}


bool operator!=(const Vec4f &a, const Vec4f &b) {
    return !(a == b);
}


bool operator>=(const Vec4f &a, const Vec4f &b) {
    return (a.length() >= b.length());
}


bool operator<=(const Vec4f &a, const Vec4f &b) {
    return a.length() <= b.length();
}


bool operator>(const Vec4f &a, const Vec4f &b) {
    return a.length() > b.length();
}


bool operator<(const Vec4f &a, const Vec4f &b) {
    return a.length() < b.length();
}


}
