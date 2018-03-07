#include "GameMath.h"

namespace gamemath {


Mat2f::Mat2f() {
    m[0] = m[1] = m[2] = m[3] = 0;
}


Mat2f::Mat2f(const Mat2f& in) {
	m[0] = in.m[0];
	m[1] = in.m[1];
	m[2] = in.m[2];
	m[3] = in.m[3];
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
        throw GMException("Non-Invertible",
                          "Inverse of Non-Invertible Matrix (division by zero) from Mat2f");
    } else {
        out.m[0] =   m[3] / determinant;    out.m[1] = -(m[1] / determinant);
        out.m[2] = -(m[2] / determinant);   out.m[3] =   m[0] / determinant;
    }
    return out;
}


bool Mat2f::equals(const Mat2f &b) const {
    // The small overhead of a loop, but also "short-circuit" exiting...
    // ...I'm not sure if this is the better idea of not, but I'll keep it.
    for(int i = 0; i <= 2; i += 2)
        for(int j = 0; j < 2; j++)
            if(m[i + j] != b.m[i + j]) return false;
    return true;
}


/*-------------------------------------------------------------------------*/
/*                                OPERATORS                                */
/*-------------------------------------------------------------------------*/

const Mat2f operator+(const Mat2f &a, const Mat2f &b) const {
	Mat2f out(a);
	a.m[0] += b.m[0];
	a.m[1] += b.m[1];
	a.m[2] += b.m[2];
	a.m[3] += b.m[3];
}


friend const Mat2f operator-(const Mat2f &a, const Mat2f &b) const {
	Mat2f out(a);
	a.m[0] -= b.m[0];
	a.m[1] -= b.m[1];
	a.m[2] -= b.m[2];
	a.m[3] -= b.m[3];
}


friend const Mat2f operator*(const Mat2f &a, const Mat2f &b) const {
	Mat2f out(a);
    out.m[0] = (a.m[0] * b.m[0]) + (a.m[1] * b.m[2]);
    out.m[1] = (a.m[0] * b.m[1]) + (a.m[1] * b.m[3]);
    out.m[2] = (a.m[2] * b.m[0]) + (a.m[3] * b.m[2]);
    out.m[3] = (a.m[2] * b.m[1]) + (a.m[3] * b.m[3]);
    return out;

}


friend const Mat2f operator/(const Mat2f &a, const Mat2f &b) const {
	Mat2f out(a);
	Mat2f inv = b.inverse();
    out.m[0] = (a.m[0] * inv.m[0]) + (a.m[1] * inv.m[2]);
    out.m[1] = (a.m[0] * inv.m[1]) + (a.m[1] * inv.m[3]);
    out.m[2] = (a.m[2] * inv.m[0]) + (a.m[3] * inv.m[2]);
    out.m[3] = (a.m[2] * inv.m[1]) + (a.m[3] * inv.m[3]);
    return out;

}


friend const Mat2f operator*(const Mat2f &a, const float &b) {
	Mat2f out(a);
	out.m[0] *= b;
	out.m[1] *= b;
	out.m[2] *= b;
	out.m[3] *= b;
}


friend const Mat2f operator/(const Mat2f &a, const float &b) {
	Mat2f out(a);
	out.m[0] /= b;
	out.m[1] /= b;
	out.m[2] /= b;
	out.m[3] /= b;
}


const Mat2f::Mat2f& operator+(const Mat2f& b) {
	m[0] += b.m[0];
	m[1] += b.m[1];
	m[2] += b.m[2];
	m[3] += b.m[3];
	return *this;
}


const Mat2f::Mat2f& operator-(const Mat2f& b) {
	m[0] -= b.m[0];
	m[1] -= b.m[1];
	m[2] -= b.m[2];
	m[3] -= b.m[3];
	return *this;
}


const Mat2f::Mat2f& operator*(const Mat2f& b) {	
    m[0] = (m[0] * b.m[0]) + (m[1] * b.m[2]);
    m[1] = (m[0] * b.m[1]) + (m[1] * b.m[3]);
    m[2] = (m[2] * b.m[0]) + (m[3] * b.m[2]);
    m[3] = (m[2] * b.m[1]) + (m[3] * b.m[3]);
}


const Mat2f::Mat2f& operator/(const Mat2f& b) {
	Mat2f inv = b.inverse;
    m[0] = (m[0] * inv.m[0]) + (m[1] * inv.m[2]);
    m[1] = (m[0] * inv.m[1]) + (m[1] * inv.m[3]);
    m[2] = (m[2] * inv.m[0]) + (m[3] * inv.m[2]);
    m[3] = (m[2] * inv.m[1]) + (m[3] * inv.m[3]);
}


const Mat2f::Mat2f& operator*(const float& b) {
	m[0] *= b;
	m[1] *= b;
	m[2] *= b;
	m[3] *= b;
}


const Mat2f::Mat2f& operator/(const float& b) {
	m[0] /= b;
	m[1] /= b;
	m[2] /= b;
	m[3] /= b;
}

		
friend bool operator==(const Mat2f &a, const Mat2f &b) {
	return ((a[0] == b[0])   && (a[1] == b[1])   && (a[2] == b[2])   &&(a[3] == b[3])   &&
			(a[4] == b[4])   && (a[5] == b[5])   && (a[6] == b[6])   &&(a[7] == b[7])   &&
			(a[8] == b[8])   && (a[9] == b[9])   && (a[10] == b[10]) &&(a[11] == b[11]) &&
			(a[12] == b[12]) && (a[13] == b[13]) && (a[14] == b[14]) &&(a[15] == b[15]))
}


friend bool operator!=(const Mat2f &a, const Mat2f &b) {
	return ((a[0] != b[0])   || (a[1] != b[1])   || (a[2] != b[2])   ||(a[3] != b[3])   ||
			(a[4] != b[4])   || (a[5] != b[5])   || (a[6] != b[6])   ||(a[7] != b[7])   ||
			(a[8] != b[8])   || (a[9] != b[9])   || (a[10] != b[10]) ||(a[11] != b[11]) ||
			(a[12] != b[12]) || (a[13] != b[13]) || (a[14] != b[14]) ||(a[15] != b[15]))
}


friend bool operator>=(const Mat2f &a, const Mat2f &b) {
	return a.det() >= b.det();
}


friend bool operator<=(const Mat2f &a, const Mat2f &b) {
	return a.det() <= b.det();
}


friend bool operator>(const  Mat2f &a, const Mat2f &b) {
	return a.det() > b.det();
}


friend bool operator<(const  Mat2f &a, const Mat2f &b) {
	return a.det() < b.det();
}


}
