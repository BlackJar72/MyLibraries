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
        float dot(const Vec2f &b) const;
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
        bool equals(const Vec2f &b) const;
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
        friend class Mat2f;
};


class Vec3f {
    public:
        Vec3f();
        Vec3f(float x, float y, float z);
        Vec3f(float* ar);
        virtual ~Vec3f();
        float dot(const Vec3f &b) const;
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
        bool equals(const Vec3f &b) const;
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
        Vec4f(const Vec3f &vec, float w);
        virtual ~Vec4f();
        float dot(const Vec4f &b) const;
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
        Vec3f real3d() const;
        bool equals(const Vec4f &b) const;
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


/*
NOTE: Thinking about how these matrices will be copied around has
me realizing some of the real limits of my knowledge about C++ and
compiler optimization (e.g., will the copy out and assignment copy
be combined? Or will it call a constructor for each?).  I really
should learn this before committing to a system.

Also, might it not be better to perform many of these operation on
the matrix itself instead of creating a new one each time (as is
now done); this would mean more flexibility, as copies could still
be made by assignment or copy constructors, but you wouldn't have
to do this.  Also, this would make little different in efficiency
if the compiler optimizes out a constructor call, but if not it
might be more efficient by reducing the number of times a copy is
made.

In short, this needs some re-thinking and study, and may change
in the future.
*/


class Mat2f {
    public:
        Mat2f();
        virtual ~Mat2f();
        float get(const int x, const int y) const;
        void set(const int x, const int y, float value);
        Mat2f add(const Mat2f &b) const;
        Mat2f sub(const Mat2f &b) const;
        Mat2f mul(const Mat2f &b) const;
        Vec2f mul(const Vec2f &b) const;
        Mat2f mul(const float n) const;
        Mat2f div(const float n) const;
        void  setIdentity();
        static Mat2f getIdentity();
        float det() const;
        Mat2f transpose() const;
        Mat2f inverse() const;
        // TODO: Operators
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


class Xorshift {
    public:
        Xorshift();
        Xorshift(unsigned int seed);
        virtual ~Xorshift();
        unsigned int   nextInt();
        unsigned int   nextInt(int min, int max);
        unsigned long  nextLong();
        unsigned short nextShort();
        unsigned char  nextChar();
        float nextFloat();
        double nextDouble();
        bool nextBool();
        unsigned int getSeed() const;
        void setSeed(unsigned int seed);
        unsigned int getFromSeed(unsigned int seed) const;
    protected:
    private:
        const static unsigned int MAXINT = 0xffffffff;
        unsigned int seed;
        unsigned int val;
};


class Xorshift64
{
    public:
        Xorshift64();
        Xorshift64(unsigned long int seed);
        virtual ~Xorshift64();
        unsigned int   nextInt();
        unsigned int   nextInt(int min, int max);
        unsigned long  nextLong();
        unsigned short nextShort();
        unsigned char  nextChar();
        float nextFloat();
        double nextDouble();
        bool nextBool();
        unsigned long int getSeed() const;
        void setSeed(unsigned long int seed);
        unsigned int getFromSeed(unsigned long int seed) const;
    protected:
    private:
        const static unsigned long int MAXLONG = 0xffffffffffffffff;
        unsigned long int seed;
        unsigned long int val;
};


class SpatialRandom {
    public:
        SpatialRandom();
        SpatialRandom(unsigned long int seed);
        virtual ~SpatialRandom();
        unsigned long int longFor(int x, int y, int z, int t);
        unsigned long int longFor(int x, int y, int z);
        unsigned long int longFor(int x, int y);
        float floatFor(int x, int y, int z, int t);
        float floatFor(int x, int y, int z);
        float floatFor(int x, int y);
        Xorshift xorshiftFor(int x, int y, int z, int t);
        Xorshift xorshiftFor(int x, int y, int z);
        Xorshift xorshiftFor(int x, int y);
        Xorshift64 xorshift64For(int x, int y, int z, int t);
        Xorshift64 xorshift64For(int x, int y, int z);
        Xorshift64 xorshift64For(int x, int y);
        unsigned long int getSeed() const;
        void setSeed(unsigned long int seed);
    protected:
    private:
        const static unsigned long int MAXLONG = 0xffffffffffffffff;
        unsigned long int seed;
        unsigned long int val;
};


}


#endif // VECTORMATRICES_H_INCLUDED
