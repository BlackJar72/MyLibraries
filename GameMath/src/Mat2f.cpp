#include "GameMath.h"

namespace gamemath {


Mat2f::Mat2f() {
    m[0] = m[1] = m[2] = m[3] = 0;
}


Mat2f::~Mat2f() {/*No dynamic allocation, so nothing to clean up*/}


float Mat2f::get(const int x, const int y) const {
    return m[(2 * x) + y];
}


void Mat2f::set(const int x, const int y, float value) {
    m[(2 * x) + y] = value;
}


Mat2f Mat2f::add(const Mat2f &b) const {
    Mat2f out = Mat2f();
    out.m[0] = m[0] + b.m[0];
    out.m[1] = m[1] + b.m[1];
    out.m[2] = m[2] + b.m[2];
    out.m[3] = m[3] + b.m[3];
    return out;
}


Mat2f Mat2f::sub(const Mat2f &b) const {
    Mat2f out = Mat2f();
    out.m[0] = m[0] - b.m[0];
    out.m[1] = m[1] - b.m[1];
    out.m[2] = m[2] - b.m[2];
    out.m[3] = m[3] - b.m[3];
    return out;
}


Mat2f Mat2f::mul(const Mat2f &b) const {
    Mat2f out = Mat2f();
    out.m[0] = (m[0] * b.m[0]) + (m[1] * b.m[2]);
    out.m[1] = (m[0] * b.m[1]) + (m[1] * b.m[3]);
    out.m[2] = (m[2] * b.m[0]) + (m[3] * b.m[2]);
    out.m[3] = (m[2] * b.m[1]) + (m[3] * b.m[3]);
    return out;
}


Vec2f Mat2f::mul(const Vec2f &b) const {
        return Vec2f(b.data[0]*m[0] + b.data[1]*m[1], b.data[0]*m[2] + b.data[1]*m[3]);
}


Mat2f Mat2f::mul(const float n) const {
    Mat2f out = Mat2f();
    out.m[0] = m[0]*n;    out.m[1] = m[1]*n;
    out.m[2] = m[2]*n;    out.m[3] = m[3]*n;
    return out;
}


Mat2f Mat2f::div(const float n) const {
    Mat2f out = Mat2f();
    out.m[0] = m[0]/n;    out.m[1] = m[1]/n;
    out.m[2] = m[2]/n;    out.m[3] = m[3]/n;
    return out;
}


void  Mat2f::setIdentity() {
    m[0] = 1;   m[1] = 0;
    m[2] = 0;   m[3] = 1;
}


Mat2f Mat2f::getIdentity() {
    Mat2f out = Mat2f();
    out.setIdentity();
    return out;
}


float Mat2f::det() const {
    return ((m[0]*m[3]) - (m[1]*m[2]));
}


Mat2f Mat2f::transpose() const {
    Mat2f out = Mat2f();
    out.m[0] = m[0];  out.m[1] = m[2];
    out.m[2] = m[1];  out.m[3] = m[3];
    return out;
}


Mat2f Mat2f::inverse() const {
    Mat2f out = Mat2f();
    float determinant = det();
    if(determinant == 0) {
        // TODO: Create and exception class to throw
        /*ArithmeticException e = new ArithmeticException("Warning: Tring to "
                    + "calculate in invalded matrix inverse, requiring divsion "
                    + "by 0");

        throw e;*/
    } else {
        out.m[0] =   m[3] / determinant;    out.m[1] = -(m[1] / determinant);
        out.m[0] = -(m[2] / determinant);   out.m[3] =   m[0] / determinant;
    }
    return out;
}


}
