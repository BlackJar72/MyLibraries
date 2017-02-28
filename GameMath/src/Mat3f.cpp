#include "GameMath.h"

namespace gamemath {


Mat3f::Mat3f() {
    m[0] = m[1] = m[2]
         = m[3] = m[4] = m[5]
         = m[6] = m[7] = m[8] = 0;
}


Mat3f::~Mat3f() {/*No dynamic allocation, so nothing to clean up*/}


float Mat3f::get(const int x, const int y) const {
    return m[(3 * x) + y];
}


void Mat3f::set(const int x, const int y, float value) {
    m[(3 * x) + y] = value;
}


Mat3f Mat3f::add(const Mat3f &b) const {
    Mat3f out = Mat3f();
    out.m[0] = m[0] + b.m[0];
    out.m[1] = m[1] + b.m[1];
    out.m[2] = m[2] + b.m[2];
    out.m[3] = m[3] + b.m[3];
    out.m[4] = m[4] + b.m[4];
    out.m[5] = m[5] + b.m[5];
    out.m[6] = m[6] + b.m[6];
    out.m[7] = m[7] + b.m[7];
    out.m[8] = m[8] + b.m[8];
    return out;
}


Mat3f Mat3f::sub(const Mat3f &b) const {
    Mat3f out = Mat3f();
    out.m[0] = m[0] - b.m[0];
    out.m[1] = m[1] - b.m[1];
    out.m[2] = m[2] - b.m[2];
    out.m[3] = m[3] - b.m[3];
    out.m[4] = m[4] - b.m[4];
    out.m[5] = m[5] - b.m[5];
    out.m[6] = m[6] - b.m[6];
    out.m[7] = m[7] - b.m[7];
    out.m[8] = m[8] - b.m[8];
    return out;
}


Mat3f Mat3f::mul(const Mat3f &b) const {
    Mat3f out = Mat3f();
    out.m[0] = (m[0] * b.m[0]) + (m[1] * b.m[3]) + (m[2] * b.m[6]);
    out.m[1] = (m[0] * b.m[1]) + (m[1] * b.m[4]) + (m[2] * b.m[7]);
    out.m[2] = (m[0] * b.m[2]) + (m[1] * b.m[5]) + (m[2] * b.m[8]);

    out.m[3] = (m[3] * b.m[0]) + (m[4] * b.m[3]) + (m[5] * b.m[6]);
    out.m[4] = (m[3] * b.m[1]) + (m[4] * b.m[4]) + (m[5] * b.m[7]);
    out.m[5] = (m[3] * b.m[2]) + (m[4] * b.m[5]) + (m[5] * b.m[8]);

    out.m[6] = (m[6] * b.m[0]) + (m[7] * b.m[3]) + (m[8] * b.m[6]);
    out.m[7] = (m[6] * b.m[1]) + (m[7] * b.m[4]) + (m[8] * b.m[7]);
    out.m[8] = (m[6] * b.m[2]) + (m[7] * b.m[5]) + (m[8] * b.m[8]);
    return out;
}


Vec3f Mat3f::mul(const Vec3f &b) const {
    return Vec3f(b.data[0]*m[0] + b.data[1]*m[1] + b.data[2]*m[2],
                 b.data[0]*m[3] + b.data[1]*m[4] + b.data[2]*m[5],
                 b.data[0]*m[6] + b.data[1]*m[7] + b.data[2]*m[8]);
}


Mat3f Mat3f::mul(const float n) const {
    Mat3f out = Mat3f();
    out.m[0] = m[0]*n;    out.m[1] = m[1]*n;    out.m[2] = m[2]*n;
    out.m[3] = m[3]*n;    out.m[4] = m[4]*n;    out.m[5] = m[5]*n;
    out.m[6] = m[6]*n;    out.m[7] = m[7]*n;    out.m[8] = m[8]*n;
    return out;
}


Mat3f Mat3f::div(const float n) const {
    Mat3f out = Mat3f();
    out.m[0] = m[0]/n;    out.m[1] = m[1]/n;    out.m[2] = m[2]/n;
    out.m[3] = m[3]/n;    out.m[4] = m[4]/n;    out.m[5] = m[5]/n;
    out.m[6] = m[6]/n;    out.m[7] = m[7]/n;    out.m[8] = m[8]/n;
    return out;
}


void  Mat3f::setIdentity() {
    m[0] = 1;   m[1] = 0;   m[2] = 0;
    m[3] = 0;   m[4] = 1;   m[5] = 0;
    m[6] = 0;   m[7] = 0;   m[8] = 1;
}


Mat3f Mat3f::getIdentity() {
    Mat3f out = Mat3f();
    out.setIdentity();
    return out;
}


float Mat3f::det() const {
       return (((m[0] * (m[4]*m[8] - m[5]*m[7]))
              - (m[1] * (m[3]*m[8] - m[5]*m[6]))
              + (m[2] * (m[3]*m[7] - m[4]*m[6]))));
}


Mat3f Mat3f::transpose() const {
        Mat3f out = Mat3f();
        out.m[0] = m[0];  out.m[3] = m[1];  out.m[6] = m[2];
        out.m[1] = m[2];  out.m[4] = m[4];  out.m[7] = m[5];
        out.m[2] = m[6];  out.m[5] = m[7];  out.m[8] = m[8];
       return out;
}


Mat3f Mat3f::minors() const {
    Mat3f out = Mat3f();

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


Mat3f Mat3f::cofactor() const {
    Mat3f out = Mat3f();
    out.m[0]  =  m[0];   out.m[1]  = -m[1];   out.m[2]  =  m[2];
    out.m[3]  = -m[3];   out.m[4]  =  m[4];   out.m[5]  = -m[5];
    out.m[6]  =  m[6];   out.m[7]  = -m[7];   out.m[8]  =  m[8];
    return out;
}


Mat3f Mat3f::inverse() const {
    Mat3f out = Mat3f();
    float determinant = det();
    if(determinant == 0) {
        throw GMException("Non-Invertible",
                          "Inverse of Non-Invertible Matrix (division by zero) from Mat3f");
    } else {
        return minors().cofactor().transpose().div(determinant);
    }
    return out;
}


bool Mat3f::equals(const Mat3f &b) const {
    // The small overhead of a loop, but also "short-circuit" exiting...
    // ...I'm not sure if this is the better idea of not, but I'll keep it.
    for(int i = 0; i <= 6; i += 3)
        for(int j = 0; j < 3; j++)
            if(m[i + j] != b.m[i + j]) return false;
    return true;
}


/*-------------------------------------------------------------------------*/
/*                                OPERATORS                                */
/*-------------------------------------------------------------------------*/


}
