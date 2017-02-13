#include "VectorMatrices.h"

namespace vecmatices {

Vec2f::Vec2f() {
    data[0] = data[1] = 0;
}


Vec2f::Vec2f(float x, float y) {
    data[0] = x;
    data[1] = y;
}


Vec2f::Vec2f(float* ar) {
    // Not using memcpy, this is small.
    data[0] = ar[0];
    data[1] = ar[1];
}


Vec2f::~Vec2f() {/*Nothing to do? The array is not dynamically allocated.*/}


float Vec2f::dot(const Vec2f &b) {
    return (data[0] * b.data[0]) + (data[0] * b.data[0]);
}


float Vec2f::length() const {
    return sqrt((data[0] * data[0]) + (data[1] * data[1]));
}


void Vec2f::normalize() {
    float l = length();
    data[0] *= l;
    data[1] *= l;
}


Vec2f Vec2f::add(const Vec2f &b) {
    return Vec2f(data[0] + b.data[0], data[1] + b.data[1]);
}


Vec2f Vec2f::sub(const Vec2f &b) {
    return Vec2f(data[0] - b.data[0], data[1] - b.data[1]);
}


Vec2f Vec2f::add(const float &b) {
    Vec2f direction = *this;
    direction.normalize();
    direction.mul(b);
    return direction.add(*this);
}


Vec2f Vec2f::sub(const float &b) {
    Vec2f direction = *this;
    direction.normalize();
    direction.mul(b);
    return direction.sub(*this);
}


Vec2f Vec2f::mul(const float &b) {
    return Vec2f(data[0] * b, data[1] * b);
}


Vec2f Vec2f::div(const float &b) {
    return Vec2f(data[0] / b, data[1] / b);
}


void Vec2f::set(const int &index, const float &b) {
    // Should I include error checking?  Or assume this will be remembered?
    data[index] = b;
}


float Vec2f::get(const int &index) {
    // Should I include error checking?  Or assume this will be remembered?
    return data[index];
}


Vec2f Vec2f::rotate(const float &angle) {
    float sine   = sin(angle * VECMATPI);
    float cosine = cos(angle * VECMATPI);
    return Vec2f(((data[0] * cosine) - (data[1] * sine)),
                 ((data[0] * sine)   - (data[1] * cosine)));
}


bool Vec2f::equals(const Vec2f &b) {
    return ((data[0] = b.data[0]) && (data[1] == b.data[1]));
}

/*----------------------------------------------------------*/
/*                      OPERATORS                           */
/*----------------------------------------------------------*/




const Vec2f operator+(const Vec2f &a, const Vec2f &b) {
    return Vec2f(a.data[0] + b.data[0], a.data[1] + b.data[1]);
}


const Vec2f operator-(const Vec2f &a, const Vec2f &b) {
    return Vec2f(a.data[0] - b.data[0], a.data[1] - b.data[1]);
}


const Vec2f Vec2f::operator+(const float &b) {
    Vec2f direction = *this;
    direction.normalize();
    direction.mul(b);
    return direction.add(*this);
}


const Vec2f Vec2f::operator-(const float &b) {
    Vec2f direction = *this;
    direction.normalize();
    direction.mul(b);
    return direction.sub(*this);
}


const Vec2f operator*(const Vec2f &a, const float &b) {
    return Vec2f(a.data[0] * b, a.data[1] * b);
}


const Vec2f operator/(const Vec2f &a, const float &b) {
    return Vec2f(a.data[0] / b, a.data[1] / b);
}


const Vec2f operator*(const float &a, const Vec2f &b) {
    return Vec2f(b.data[0] * a, b.data[1] * a);
}


const Vec2f operator/(const float &a, const Vec2f &b) {
    return Vec2f(b.data[0] / a, b.data[1] / a);
}


bool operator==(const Vec2f &a, const Vec2f &b) {
    return ((a.data[0] == b.data[0]) && (a.data[1] == b.data[1]));
}


bool operator!=(const Vec2f &a, const Vec2f &b) {
    return !(a == b);
}


bool operator>=(const Vec2f &a, const Vec2f &b) {
    return (a.length() >= b.length());
}


bool operator<=(const Vec2f &a, const Vec2f &b) {
    return a.length() <= b.length();
}


bool operator>(const Vec2f &a, const Vec2f &b) {
    return a.length() > b.length();
}


bool operator<(const Vec2f &a, const Vec2f &b) {
    return a.length() < b.length();
}


}
