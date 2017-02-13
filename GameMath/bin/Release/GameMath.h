#ifndef GAMEMATH_H
#define GAMEMATH_H
#include <cmath>
#include <string>

// Using define here rather than const's in every
// class or global space
#define GMPI 3.14159265

using namespace std;

namespace gamemath {

class Vec2f {
    public:
        Vec2f();
        Vec2f(float x, float y);
        Vec2f(float* ar);
        virtual ~Vec2f();
        float dot(const Vec2f &b);
        float length() const;
        void normalize();
        Vec2f add(const Vec2f &b);
        Vec2f sub(const Vec2f &b);
        Vec2f add(const float b);
        Vec2f sub(const float b);
        Vec2f mul(const float b);
        Vec2f div(const float b);
        void set(const int index, const float value);
        float get(const int index) const;
        Vec2f rotate(const float angle);
        bool equals(const Vec2f &b);
        friend const Vec2f operator+(const Vec2f &a, const Vec2f &b);
        friend const Vec2f operator-(const Vec2f &a, const Vec2f &b);
        const Vec2f operator+(const float b);
        const Vec2f operator-(const float b);
        Vec2f& operator+=(const Vec2f &b);
        Vec2f& operator-=(const Vec2f &b);
        Vec2f& operator+=(const float b);
        Vec2f& operator-=(const float b);
        friend const Vec2f operator*(const Vec2f &a, const float b);
        friend const Vec2f operator/(const Vec2f &a, const float b);
        friend const Vec2f operator*(const float a, const Vec2f &b);
        friend const Vec2f operator/(const float a, const Vec2f &b);
        Vec2f& operator*=(const float b);
        Vec2f& operator/=(const float b);
        friend bool operator==(const Vec2f &a, const Vec2f &b);
        friend bool operator!=(const Vec2f &a, const Vec2f &b);
        friend bool operator>=(const Vec2f &a, const Vec2f &b);
        friend bool operator<=(const Vec2f &a, const Vec2f &b);
        friend bool operator>(const Vec2f &a, const Vec2f &b);
        friend bool operator<(const Vec2f &a, const Vec2f &b);
    protected:
    private:
        float data[2];
};


class Vec3f {
    public:
        Vec3f();
        Vec3f(float x, float y, float z);
        Vec3f(float* ar);
        virtual ~Vec3f();
        float dot(const Vec3f &b);
        float length() const;
        void normalize();
        Vec3f add(const Vec3f &b);
        Vec3f sub(const Vec3f &b);
        Vec3f add(const float b);
        Vec3f sub(const float b);
        Vec3f mul(const float b);
        Vec3f div(const float b);
        void set(const int index, const float value);
        float get(const int index) const;
        float cross(const Vec3f &b);
        bool equals(const Vec3f &b);
        friend const Vec3f operator+(const Vec3f &a, const Vec3f &b);
        friend const Vec3f operator-(const Vec3f &a, const Vec3f &b);
        const Vec3f operator+(const float b);
        const Vec3f operator-(const float b);
        Vec3f& operator+=(const Vec3f &b);
        Vec3f& operator-=(const Vec3f &b);
        Vec3f& operator+=(const float b);
        Vec3f& operator-=(const float b);
        friend const Vec3f operator*(const Vec3f &a, const float b);
        friend const Vec3f operator/(const Vec3f &a, const float b);
        friend const Vec3f operator*(const float a, const Vec3f &b);
        friend const Vec3f operator/(const float a, const Vec3f &b);
        Vec3f& operator*=(const float b);
        Vec3f& operator/=(const float b);
        friend bool operator==(const Vec3f &a, const Vec3f &b);
        friend bool operator!=(const Vec3f &a, const Vec3f &b);
        friend bool operator>=(const Vec3f &a, const Vec3f &b);
        friend bool operator<=(const Vec3f &a, const Vec3f &b);
        friend bool operator>(const Vec3f &a, const Vec3f &b);
        friend bool operator<(const Vec3f &a, const Vec3f &b);
    protected:
    private:
        float data[3];
};


class Vec4f {
    public:
        Vec4f();
        Vec4f(float x, float y, float z, float w);
        Vec4f(float* ar);
        Vec4f(const Vec3f &vec);
        virtual ~Vec4f();
        float dot(const Vec4f &b);
        float length() const;
        void normalize();
        Vec4f add(const Vec4f &b);
        Vec4f sub(const Vec4f &b);
        Vec4f add(const float b);
        Vec4f sub(const float b);
        Vec4f mul(const float b);
        Vec4f div(const float b);
        void set(const int index, const float value);
        float get(const int index) const;
        Vec3f trunc3d();
        Vec3f real3d();
        bool equals(const Vec4f &b);
        friend const Vec4f operator+(const Vec4f &a, const Vec4f &b);
        friend const Vec4f operator-(const Vec4f &a, const Vec4f &b);
        const Vec4f operator+(const float b);
        const Vec4f operator-(const float b);
        Vec4f& operator+=(const Vec4f &b);
        Vec4f& operator-=(const Vec4f &b);
        Vec4f& operator+=(const float b);
        Vec4f& operator-=(const float b);
        friend const Vec4f operator*(const Vec4f &a, const float b);
        friend const Vec4f operator/(const Vec4f &a, const float b);
        friend const Vec4f operator*(const float a, const Vec4f &b);
        friend const Vec4f operator/(const float a, const Vec4f &b);
        Vec4f& operator*=(const float b);
        Vec4f& operator/=(const float b);
        friend bool operator==(const Vec4f &a, const Vec4f &b);
        friend bool operator!=(const Vec4f &a, const Vec4f &b);
        friend bool operator>=(const Vec4f &a, const Vec4f &b);
        friend bool operator<=(const Vec4f &a, const Vec4f &b);
        friend bool operator>(const Vec4f &a, const Vec4f &b);
        friend bool operator<(const Vec4f &a, const Vec4f &b);
    protected:
    private:
        float data[4];
};


class Mat2f {
    public:
        Mat2f();
        virtual ~Mat2f();
    protected:
    private:
        float m[4];
};


class Mat3f {
    public:
        Mat3f();
        virtual ~Mat3f();
    protected:
    private:
        float m[9];
};


class Mat4f {
    public:
        Mat4f();
        virtual ~Mat4f();
    protected:
    private:
        float m[16];
};


class Quanternion {
    public:
        Quanternion();
        virtual ~Quanternion();
    protected:
    private:
        float data[4];
};


}


#endif // VECTORMATRICES_H_INCLUDED
