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

const Mat2f operator+(const Mat2f &a, const Mat2f &b) {
	Mat2f out(a);
	out.m[0] += b.m[0];
	out.m[1] += b.m[1];
	out.m[2] += b.m[2];
	out.m[3] += b.m[3];
	return out;
}


const Mat2f operator-(const Mat2f &a, const Mat2f &b) {
	Mat2f out(a);
	out.m[0] -= b.m[0];
    out.m[1] -= b.m[1];
	out.m[2] -= b.m[2];
	out.m[3] -= b.m[3];
	return out;
}


const Mat2f operator*(const Mat2f &a, const Mat2f &b) {
	Mat2f out(a);
    out.m[0] = (a.m[0] * b.m[0]) + (a.m[1] * b.m[2]);
    out.m[1] = (a.m[0] * b.m[1]) + (a.m[1] * b.m[3]);
    out.m[2] = (a.m[2] * b.m[0]) + (a.m[3] * b.m[2]);
    out.m[3] = (a.m[2] * b.m[1]) + (a.m[3] * b.m[3]);
    return out;

}


const Mat2f operator/(const Mat2f &a, const Mat2f &b) {
	Mat2f out(a);
	Mat2f inv = b.inverse();
    out.m[0] = (a.m[0] * inv.m[0]) + (a.m[1] * inv.m[2]);
    out.m[1] = (a.m[0] * inv.m[1]) + (a.m[1] * inv.m[3]);
    out.m[2] = (a.m[2] * inv.m[0]) + (a.m[3] * inv.m[2]);
    out.m[3] = (a.m[2] * inv.m[1]) + (a.m[3] * inv.m[3]);
    return out;
}


const Mat2f operator*(const Mat2f &a, const float &b) {
	Mat2f out(a);
	out.m[0] *= b;
	out.m[1] *= b;
	out.m[2] *= b;
	out.m[3] *= b;
	return out;
}


const Mat2f operator/(const Mat2f &a, const float &b) {
	Mat2f out(a);
	out.m[0] /= b;
	out.m[1] /= b;
	out.m[2] /= b;
	out.m[3] /= b;
	return out;
}


const Mat2f& Mat2f::operator+=(const Mat2f& b) {
	m[0] += b.m[0];
	m[1] += b.m[1];
	m[2] += b.m[2];
	m[3] += b.m[3];
	return *this;
}


const Mat2f& Mat2f::operator-=(const Mat2f& b) {
	m[0] -= b.m[0];
	m[1] -= b.m[1];
	m[2] -= b.m[2];
	m[3] -= b.m[3];
	return *this;
}


const Mat2f& Mat2f::operator*=(const Mat2f& b) {
    m[0] = (m[0] * b.m[0]) + (m[1] * b.m[2]);
    m[1] = (m[0] * b.m[1]) + (m[1] * b.m[3]);
    m[2] = (m[2] * b.m[0]) + (m[3] * b.m[2]);
    m[3] = (m[2] * b.m[1]) + (m[3] * b.m[3]);
    return *this;
}


const Mat2f& Mat2f::operator/=(const Mat2f& b) {
	Mat2f inv = b.inverse();
    m[0] = (m[0] * inv.m[0]) + (m[1] * inv.m[2]);
    m[1] = (m[0] * inv.m[1]) + (m[1] * inv.m[3]);
    m[2] = (m[2] * inv.m[0]) + (m[3] * inv.m[2]);
    m[3] = (m[2] * inv.m[1]) + (m[3] * inv.m[3]);
    return *this;
}


const Mat2f& Mat2f::operator*=(const float& b) {
	m[0] *= b;
	m[1] *= b;
	m[2] *= b;
	m[3] *= b;
	return *this;
}


const Mat2f& Mat2f::operator/=(const float& b) {
	m[0] /= b;
	m[1] /= b;
	m[2] /= b;
	m[3] /= b;
	return *this;
}


bool operator==(const Mat2f &a, const Mat2f &b) {
	return ((a.m[0] == b.m[0])   && (a.m[1] == b.m[1])   && (a.m[2] == b.m[2])   &&(a.m[3] == b.m[3])   &&
			(a.m[4] == b.m[4])   && (a.m[5] == b.m[5])   && (a.m[6] == b.m[6])   &&(a.m[7] == b.m[7])   &&
			(a.m[8] == b.m[8])   && (a.m[9] == b.m[9])   && (a.m[10] == b.m[10]) &&(a.m[11] == b.m[11]) &&
			(a.m[12] == b.m[12]) && (a.m[13] == b.m[13]) && (a.m[14] == b.m[14]) &&(a.m[15] == b.m[15]));
}


bool operator!=(const Mat2f &a, const Mat2f &b) {
	return ((a.m[0] != b.m[0])   || (a.m[1] != b.m[1])   || (a.m[2] != b.m[2])   ||(a.m[3] != b.m[3])   ||
			(a.m[4] != b.m[4])   || (a.m[5] != b.m[5])   || (a.m[6] != b.m[6])   ||(a.m[7] != b.m[7])   ||
			(a.m[8] != b.m[8])   || (a.m[9] != b.m[9])   || (a.m[10] != b.m[10]) ||(a.m[11] != b.m[11]) ||
			(a.m[12] != b.m[12]) || (a.m[13] != b.m[13]) || (a.m[14] != b.m[14]) ||(a.m[15] != b.m[15]));
}


bool operator>=(const Mat2f &a, const Mat2f &b) {
	return a.det() >= b.det();
}


bool operator<=(const Mat2f &a, const Mat2f &b) {
	return a.det() <= b.det();
}


bool operator>(const  Mat2f &a, const Mat2f &b) {
	return a.det() > b.det();
}


bool operator<(const  Mat2f &a, const Mat2f &b) {
	return a.det() < b.det();
}


}
