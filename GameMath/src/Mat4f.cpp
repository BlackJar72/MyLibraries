#include "GameMath.h"

namespace gamemath {


Mat4f::Mat4f() {
    m[0] = m[1]  = m[2]  = m[3]
         = m[4]  = m[5]  = m[6]  = m[7]
         = m[8]  = m[9]  = m[10] = m[11]
         = m[12] = m[13] = m[14] = m[15] = 0;
}


Mat4f::~Mat4f() {/*No dynamic allocation, so nothing to clean up*/}


float Mat4f::get(const int x, const int y) const {
    return m[(4 * x) + y];
}


void Mat4f::set(const int x, const int y, float value) {
    m[(4 * x) + y] = value;
}


Mat4f Mat4f::add(const Mat4f &b) const {
    Mat4f out = Mat4f();
    out.m[0] = m[0] + b.m[0];
    out.m[1] = m[1] + b.m[1];
    out.m[2] = m[2] + b.m[2];
    out.m[3] = m[3] + b.m[3];
    out.m[4] = m[4] + b.m[4];
    out.m[5] = m[5] + b.m[5];
    out.m[6] = m[6] + b.m[6];
    out.m[7] = m[7] + b.m[7];
    out.m[8] = m[8] + b.m[8];
    out.m[9] = m[9] + b.m[9];
    out.m[10] = m[10] + b.m[10];
    out.m[11] = m[11] + b.m[11];
    out.m[12] = m[12] + b.m[12];
    out.m[13] = m[13] + b.m[13];
    out.m[14] = m[14] + b.m[14];
    out.m[15] = m[15] + b.m[15];
    return out;
}


Mat4f Mat4f::sub(const Mat4f &b) const {
    Mat4f out = Mat4f();
    out.m[0] = m[0] - b.m[0];
    out.m[1] = m[1] - b.m[1];
    out.m[2] = m[2] - b.m[2];
    out.m[3] = m[3] - b.m[3];
    out.m[4] = m[4] - b.m[4];
    out.m[5] = m[5] - b.m[5];
    out.m[6] = m[6] - b.m[6];
    out.m[7] = m[7] - b.m[7];
    out.m[8] = m[8] - b.m[8];
    out.m[9] = m[9] - b.m[9];
    out.m[10] = m[10] - b.m[10];
    out.m[11] = m[11] - b.m[11];
    out.m[12] = m[12] - b.m[12];
    out.m[13] = m[13] - b.m[13];
    out.m[14] = m[14] - b.m[14];
    out.m[15] = m[15] - b.m[15];
    return out;
}


Mat4f Mat4f::mul(const Mat4f &b) const {
    Mat4f out = Mat4f();
    out.m[0] = (m[0] * b.m[0]) + (m[1] * b.m[2]);
    out.m[1] = (m[0] * b.m[1]) + (m[1] * b.m[3]);
    out.m[2] = (m[2] * b.m[0]) + (m[3] * b.m[2]);
    out.m[3] = (m[2] * b.m[1]) + (m[3] * b.m[3]);
    return out;
}


Vec4f Mat4f::mul(const Vec4f &b) const {
        return Vec4f(b.data[0]*m[0] + b.data[1]*m[1] + b.data[2]*m[2],
                     b.data[0]*m[3] + b.data[1]*m[4] + b.data[2]*m[5],
                     b.data[0]*m[6] + b.data[1]*m[7] + b.data[2]*m[8]);
}


Mat4f Mat4f::mul(const float n) const {
    Mat4f out = Mat4f();
    out.m[0] = m[0]*n;    out.m[1] = m[1]*n;    out.m[2] = m[2]*n;
    out.m[3] = m[3]*n;    out.m[4] = m[4]*n;    out.m[5] = m[5]*n;
    out.m[6] = m[6]*n;    out.m[7] = m[7]*n;    out.m[8] = m[8]*n;
    return out;
}


Mat4f Mat4f::div(const float n) const {
    Mat4f out = Mat4f();
    out.m[0] = m[0]/n;    out.m[1] = m[1]/n;    out.m[2] = m[2]/n;
    out.m[3] = m[3]/n;    out.m[4] = m[4]/n;    out.m[5] = m[5]/n;
    out.m[6] = m[6]/n;    out.m[7] = m[7]/n;    out.m[8] = m[8]/n;
    return out;
}


void  Mat4f::setIdentity() {
    m[0] = 1;   m[1] = 0;   m[2] = 0;
    m[3] = 0;   m[4] = 1;   m[5] = 0;
    m[6] = 0;   m[7] = 0;   m[8] = 1;
}


Mat4f Mat4f::getIdentity() {
    Mat4f out = Mat4f();
    out.setIdentity();
    return out;
}


float Mat4f::det() const {
       return (((m[0] * (m[4]*m[8] - m[5]*m[7]))
              - (m[1] * (m[3]*m[8] - m[5]*m[6]))
              + (m[2] * (m[3]*m[7] - m[4]*m[6]))));
}


Mat4f Mat4f::transpose() const {
        Mat4f out = Mat4f();
        out.m[0] = m[0];  out.m[3] = m[1];  out.m[6] = m[2];
        out.m[1] = m[2];  out.m[4] = m[4];  out.m[7] = m[5];
        out.m[2] = m[6];  out.m[5] = m[7];  out.m[8] = m[8];
       return out;
}


Mat4f Mat4f::minors() const {
    Mat4f out = Mat4f();

    out.m[0]  = (m[4] * m[8]) - (m[5] * m[7]);
    out.m[1]  = (m[3] * m[8]) - (m[5] * m[6]);
    out.m[2]  = (m[3] * m[7]) - (m[4] * m[6]);

    out.m[3]  = (m[1] * m[8]) - (m[2] * m[7]);
    out.m[4]  = (m[0] * m[8]) - (m[2] * m[6]);
    out.m[5]  = (m[0] * m[7]) - (m[1] * m[6]);

    out.m[6]  = (m[1] * m[5]) - (m[2] * m[4]);
    out.m[7]  = (m[0] * m[5]) - (m[2] * m[3]);
    out.m[8]  = (m[4] * m[4]) - (m[1] * m[3]);

    return out;
}


Mat4f Mat4f::cofactor() const {
    Mat4f out = Mat4f();
    out.m[0]  =  m[0];   out.m[1]  = -m[1];   out.m[2]  =  m[2];
    out.m[3]  = -m[3];   out.m[4]  =  m[4];   out.m[5]  = -m[5];
    out.m[6]  =  m[6];   out.m[7]  = -m[7];   out.m[8]  =  m[8];
    return out;
}


Mat4f Mat4f::inverse() const {
    Mat4f out = Mat4f();
    float determinant = det();
    if(determinant == 0) {
        // TODO: Create and exception class to throw
        /*ArithmeticException e = new ArithmeticException("Warning: Tring to "
                    + "calculate in invalded matrix inverse, requiring divsion "
                    + "by 0");

        throw e;*/
    } else {
        return minors().cofactor().transpose().div(determinant);
    }
    return out;
}


bool Mat4f::equals(const Mat4f &b) const {
    // The small overhead of a loop, but also "short-circuit" exiting...
    // ...I'm not sure if this is the better idea of not, but I'll keep it.
    for(int i = 0; i <= 3; i += 3)
        for(int j = 0; j < 3; j++)
            if(m[i + j] != b.m[i + j]) return false;
    return true;
}


/*-------------------------------------------------------------------------*/
/*                                OPERATORS                                */
/*-------------------------------------------------------------------------*/


}
