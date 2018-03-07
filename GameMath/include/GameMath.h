#ifndef GAMEMATH_H
#define GAMEMATH_H
#include <cmath>
#include <string>

// Using define here rather than const's in every
// class or global space
#define GMPI 3.14159265

using namespace std;

namespace gamemath {

class GMException
{
    public:
        GMException(string name, string description);
        virtual ~GMException();
        string getName() const;
        string getDescription() const;
    protected:
    private:
        GMException();
        string name;
        string description;
};


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
        Vec3f cross(const Vec3f &b);
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
        friend class Mat3f;
        friend class Mat4f;
        friend class Quaternion;
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
        friend class Mat4f;
        friend class Quaternion;
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
		Mat2f(const Mat2f& in);
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
        bool  equals(const Mat2f &b) const;
        // TODO: Operators		
        friend const Mat2f operator+(const Mat2f &a, const Mat2f &b);
        friend const Mat2f operator-(const Mat2f &a, const Mat2f &b);
        const Mat2f& operator+(const Mat2f& b);
        const Mat2f& operator-(const Mat2f& b);
    protected:
    private:
        float m[4];
};


class Mat3f {
    public:
        Mat3f();
        virtual ~Mat3f();
        float get(const int x, const int y) const;
        void set(const int x, const int y, float value);
        Mat3f add(const Mat3f &b) const;
        Mat3f sub(const Mat3f &b) const;
        Mat3f mul(const Mat3f &b) const;
        Vec3f mul(const Vec3f &b) const;
        Mat3f mul(const float n) const;
        Mat3f div(const float n) const;
        void  setIdentity();
        static Mat3f getIdentity();
        float det() const;
        Mat3f minors() const;
        Mat3f cofactor() const;
        Mat3f transpose() const;
        Mat3f inverse() const;
        bool  equals(const Mat3f &b) const;
        // TODO: Operators
    protected:
    private:
        float m[9];
};


class Mat4f {
    public:
        Mat4f();
        virtual ~Mat4f();
        float get(const int x, const int y) const;
        void set(const int x, const int y, float value);
        Mat4f add(const Mat4f &b) const;
        Mat4f sub(const Mat4f &b) const;
        Mat4f mul(const Mat4f &b) const;
        Vec4f mul(const Vec4f &b) const;
        Mat4f mul(const float n) const;
        Mat4f div(const float n) const;
        void  setIdentity();
        static Mat4f getIdentity();
        float det() const;
        Mat4f minors() const;
        Mat4f cofactor() const;
        Mat4f transpose() const;
        Mat4f inverse() const;
        bool  equals(const Mat4f &b) const;
        void setScale(const float x, const float y, const float z);
        void setScale(const float s);
        void setTranslation(const float x, const float y, const float z);
        void setTranslation(const Vec3f &t);
        void setTranslation(const Vec4f &t);
        void setRotaion(const float r, const float x, const float y, const float z);
        void setRotaion(const float r, const Vec3f &axis);
        void setRotaion(const float r, const Vec4f &axis);
        void setRotaion(const float r);
        void setPerspective(const float height, const float width, const float fov,
                            const float near, const float far);
        void setPerspective(const float a, const float fov, const float near,
                            const float far);
        static Mat4f invertProjection(const Mat4f &proj);
        static Mat4f getScale(const float x, const float y, const float z);
        static Mat4f getScale(const float s);
        static Mat4f getTranslation(const float x, const float y, const float z);
        static Mat4f getTranslation(const Vec3f &t);
        static Mat4f getTranslation(const Vec4f &t);
        static Mat4f getRotaion(const float r, const float x, const float y, const float z);
        static Mat4f getRotaion(const float r, const Vec3f &axis);
        static Mat4f getRotaion(const float r, const Vec4f &axis);
        static Mat4f getRotaion(const float r);
        static Mat4f getPerspective(const float height, const float width, const float fov,
                                    const float near, const float far);
        static Mat4f getPerspective(const float a, const float fov, const float near,
                                    const float far);
        // TODO: Operators
    protected:
    private:
        float m[16];
        friend class Quaternion;
};


class Quaternion {
    public:
        Quaternion(float x, float y, float z, float w);
        virtual ~Quaternion();
        Quaternion conjugate() const;
        Quaternion mul(const Quaternion &b) const;
        const float length() const;
        void normalize();
        Quaternion getNormalized() const;
        Quaternion add(const Quaternion &b) const;
        Quaternion sub(const Quaternion &b) const;
        void set(size_t index, float value);
        const float get(size_t index) const;
        const bool equals(const Quaternion &other) const;
        void rotate(Vec3f &in) const;
        void rotate(const Vec3f &in, Vec3f &out) const;
        Vec3f getRotated(const Vec3f &in) const;
        void rotate(Vec4f &in) const;
        void rotate(const Vec4f &in, Vec4f &out) const;
        Vec4f getRotated(const Vec4f &in) const;
        Mat4f& toMat4f(Mat4f &in) const;
        Quaternion& fromMat4f(Mat4f &in);
        // TODO: Operators
        friend const Quaternion operator+(const Quaternion &a, const Quaternion &b);
        friend const Quaternion operator-(const Quaternion &a, const Quaternion &b);
        friend const Quaternion operator*(const Quaternion &a, const Quaternion &b);
        const Vec3f operator*(const Vec3f &b) const;
        friend const bool operator==(const Quaternion &a, const Quaternion &b);
    protected:
    private:
        float data[4];
        Quaternion();
};


class Xorshift {
    public:
        Xorshift();
        Xorshift(unsigned int seed);
        virtual ~Xorshift();
        unsigned int   nextInt();
        unsigned int   nextInt(const int &mod);
        unsigned int   nextInt(const int &min, const int &max);
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
        Xorshift64(unsigned long long seed);
        virtual ~Xorshift64();
        unsigned int   nextInt();
        unsigned int   nextInt(const int &mod);
        unsigned int   nextInt(const int &min, const int &max);
        unsigned long  nextLong();
        unsigned short nextShort();
        unsigned char  nextChar();
        float nextFloat();
        double nextDouble();
        bool nextBool();
        unsigned long long getSeed() const;
        void setSeed(unsigned long long seed);
        unsigned int getFromSeed(unsigned long long seed) const;
    protected:
    private:
        const static unsigned long long MAXLONG = 0xffffffffffffffff;
        unsigned long long seed;
        unsigned long long val;
};


class SpatialNoise {
    public:
        SpatialNoise(unsigned long long seed1, unsigned long long seed2);
        virtual ~SpatialNoise();
        unsigned long long longFor(const int &x, const int &y, const int &z, const int &t) const;
        unsigned long long longFor(const int &x, const int &y, const int &z) const;
        unsigned long long longFor(const int &x, const int &y) const;
        float floatFor(const int &x, const int &y, const int &z, const int &t) const;
        float floatFor(const int &x, const int &y, const int &z) const;
        float floatFor(const int &x, const int &y) const;
        double doubleFor(const int &x, const int &y, const int &z, const int &t) const;
        double doubleFor(const int &x, const int &y, const int &z) const;
        double doubleFor(const int &x, const int &y) const;
        unsigned int intFor(const int &x, const int &y, const int &z, const int &t) const;
        unsigned int intFor(const int &x, const int &y, const int &z) const;
        unsigned int intFor(const int &x, const int &y) const;
        Xorshift xorshiftFor(const int &x, const int &y, const int &z, const int &t) const;
        Xorshift xorshiftFor(const int &x, const int &y, const int &z) const;
        Xorshift xorshiftFor(const int &x, const int &y) const;
        Xorshift64 xorshift64For(const int &x, const int &y, const int &z, const int &t)const;
        Xorshift64 xorshift64For(const int &x, const int &y, const int &z) const;
        Xorshift64 xorshift64For(const int &x, const int &y) const;
        unsigned long long* getSeeds() const;
    protected:
    private:
        SpatialNoise();
        inline long rrotate(const long &in, const int &by) const {
            return ((in >> by) | (in << (64 - by)));
        }
        inline long lrotate(const long &in, const int &by) const {
            return ((in << by) | (in >> (64 - by)));
        }
        const static unsigned long long MAXLONG = 0xffffffffffffffff;
        const unsigned long long seed1;
        const unsigned long long seed2;
};


}


#endif // VECTORMATRICES_H_INCLUDED
