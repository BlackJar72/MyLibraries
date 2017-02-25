#include "GameMath.h"

namespace gamemath {

Vec3f::Vec3f() {
    data[0] = data[1] = data[2] = 0;
}


Vec3f::Vec3f(float x, float y, float z) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
}


Vec3f::Vec3f(float* ar) {
    // Not using memcpy, this is small.
    data[0] = ar[0];
    data[1] = ar[1];
    data[2] = ar[2];
}


Vec3f::~Vec3f() {/*Nothing to do? The array is not dynamically allocated.*/}


float Vec3f::dot(const Vec3f &b) const {
    return (data[0] * b.data[0]) + (data[1] * b.data[1] +
            (data[2] * b.data[2]));
}


float Vec3f::length() const {
    return sqrt((data[0] * data[0]) + (data[1] * data[1])
                + (data[2] * data[2]));
}


void Vec3f::normalize() {
    float l = length();
    data[0] *= l;
    data[1] *= l;
    data[2] *= l;
}


Vec3f Vec3f::add(const Vec3f &b) {
    return Vec3f(data[0] + b.data[0], data[1] + b.data[1],
                 data[2] + b.data[2]);
}


Vec3f Vec3f::sub(const Vec3f &b) {
    return Vec3f(data[0] - b.data[0], data[1] - b.data[1],
                 data[1] - b.data[1]);
}


Vec3f Vec3f::add(const float b) {
    Vec3f direction = *this;  // Copy contructor should preserve referenced data
    direction.normalize();
    direction.mul(b);
    return direction.add(*this);
}


Vec3f Vec3f::sub(const float b) {
    Vec3f direction = *this; // Copy contructor should preserve referenced data
    direction.normalize();
    direction.mul(b);
    return direction.sub(*this);
}


Vec3f Vec3f::mul(const float b) {
    return Vec3f(data[0] * b, data[1] * b,data[2] * b);
}


Vec3f Vec3f::div(const float b) {
    return Vec3f(data[0] / b, data[1] / b, data[2] / b);
}


void Vec3f::set(const int index, const float b) {
    // Should I include error checking?  Or assume this will be remembered?
    data[index] = b;
}


float Vec3f::get(const int index) const {
    // Should I include error checking?  Or assume this will be remembered?
    return data[index];
}


float Vec3f::cross(const Vec3f &b) {
    return (((data[1] * b.data[2]) - (data[2] * b.data[1])),
            ((data[2] * b.data[0]) - (data[0] * b.data[2])),
            ((data[0] * b.data[1]) - (data[1] * b.data[0])));
}


//Vec4f Vec3f::to4d() {
//    return Vec4f(data[0], data[1], data[3], 1)
//}


bool Vec3f::equals(const Vec3f &b) const {
    return ((data[0] == b.data[0]) && (data[1] == b.data[1])
            && (data[2] == b.data[2]));
}

/*----------------------------------------------------------*/
/*                      OPERATORS                           */
/*----------------------------------------------------------*/




const Vec3f operator+(const Vec3f &a, const Vec3f &b) {
    return Vec3f(a.data[0] + b.data[0], a.data[1] + b.data[1],
                 a.data[2] + b.data[2]);
}


const Vec3f operator-(const Vec3f &a, const Vec3f &b) {
    return Vec3f(a.data[0] - b.data[0], a.data[1] - b.data[1],
                 a.data[2] - b.data[2]);
}


const Vec3f Vec3f::operator+(const float b) {
    Vec3f direction = *this;
    direction.normalize();
    direction.mul(b);
    return direction.add(*this);
}


const Vec3f Vec3f::operator-(const float b) {
    Vec3f direction = *this;
    direction.normalize();
    direction.mul(b);
    return direction.sub(*this);
}


Vec3f& Vec3f::operator+=(const Vec3f &b) {
    data[0] += b.data[0];
    data[1] += b.data[1];
    data[2] += b.data[2];
    return *this;
}


Vec3f& Vec3f::operator-=(const Vec3f &b) {
    data[0] -= b.data[0];
    data[1] -= b.data[1];
    data[2] -= b.data[2];
    return *this;
}


Vec3f& Vec3f::operator+=(const float b) {
    Vec3f direction = *this;
    direction.normalize();
    direction.mul(b);
    data[0] += direction.data[0];
    data[1] += direction.data[1];
    data[2] += direction.data[2];
    return *this;
}


Vec3f& Vec3f::operator-=(const float b) {
    Vec3f direction = *this;
    direction.normalize();
    direction.mul(b);
    data[0] -= direction.data[0];
    data[1] -= direction.data[1];
    data[2] -= direction.data[2];
    return *this;
}


const Vec3f operator*(const Vec3f &a, const float b) {
    return Vec3f(a.data[0] * b, a.data[1] * b,
                 a.data[2] * b);
}


const Vec3f operator/(const Vec3f &a, const float b) {
    return Vec3f(a.data[0] / b, a.data[1] / b,
                 a.data[2] / b);
}


const Vec3f operator*(const float a, const Vec3f &b) {
    return Vec3f(b.data[0] * a, b.data[1] * a,
                 b.data[2] * a);
}


const Vec3f operator/(const float a, const Vec3f &b) {
    return Vec3f(b.data[0] / a, b.data[1] / a,
                 b.data[2] / a);
}


Vec3f& Vec3f::operator*=(const float b) {
    data[0] *= b;
    data[1] *= b;
    data[2] *= b;
    return *this;
}


Vec3f& Vec3f::operator/=(const float b) {
    data[0] /= b;
    data[1] /= b;
    data[2] /= b;
    return *this;
}


bool operator==(const Vec3f &a, const Vec3f &b) {
    return ((a.data[0] == b.data[0]) && (a.data[1] == b.data[1])
            && (a.data[1] == b.data[1]));
}


bool operator!=(const Vec3f &a, const Vec3f &b) {
    return !(a == b);
}


bool operator>=(const Vec3f &a, const Vec3f &b) {
    return (a.length() >= b.length());
}


bool operator<=(const Vec3f &a, const Vec3f &b) {
    return a.length() <= b.length();
}


bool operator>(const Vec3f &a, const Vec3f &b) {
    return a.length() > b.length();
}


bool operator<(const Vec3f &a, const Vec3f &b) {
    return a.length() < b.length();
}


}
