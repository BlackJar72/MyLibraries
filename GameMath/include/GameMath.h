#ifndef GAMEMATH_H
#define GAMEMATH_H
#include <cmath>
#include <string>

// Using define here rather than const's in every
// class or global space
#define GMPI 3.14159265

using namespace std;

namespace vecmatices {

class Mat2f
{
    public:
        Mat2f();
        virtual ~Mat2f();
    protected:
    private:
        float m[4];
};


class Mat3f
{
    public:
        Mat3f();
        virtual ~Mat3f();
    protected:
    private:
        float m[9];
};


class Mat4f
{
    public:
        Mat4f();
        virtual ~Mat4f();
    protected:
    private:
        float m[16];
};


class Vec2f
{
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
        Vec2f add(const float &b);
        Vec2f sub(const float &b);
        Vec2f mul(const float &b);
        Vec2f div(const float &b);
        void set(const int &index, const float &value);
        float get(const int &index);
        Vec2f rotate(const float &angle);
        bool equals(const Vec2f &b);
        // Operators, will be cut-n-past of verbal equivalent
        // to avoid function call overhead.
        friend const Vec2f operator+(const Vec2f &a, const Vec2f &b);
        friend const Vec2f operator-(const Vec2f &a, const Vec2f &b);
        const Vec2f operator+(const float &b);
        const Vec2f operator-(const float &b);
        friend const Vec2f operator*(const Vec2f &a, const float &b);
        friend const Vec2f operator/(const Vec2f &a, const float &b);
        friend const Vec2f operator*(const float &a, const Vec2f &b);
        friend const Vec2f operator/(const float &a, const Vec2f &b);
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


class Vec3f
{
    public:
        Vec3f();
        virtual ~Vec3f();
    protected:
    private:
        float data[3];
};


class Vec4f
{
    public:
        Vec4f();
        virtual ~Vec4f();
    protected:
    private:
        float data[4];
};


class Quanternion
{
    public:
        Quanternion();
        virtual ~Quanternion();
    protected:
    private:
        float data[4];
};


}


#endif // VECTORMATRICES_H_INCLUDED
