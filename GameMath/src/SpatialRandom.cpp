#include "GameMath.h"
#include <ctime>

using namespace std;

namespace gamemath {


SpatialNoise::SpatialNoise(unsigned long long seed1,
                           unsigned long long seed2) : seed1(seed1), seed2(seed2) {}


SpatialNoise::~SpatialNoise() {}


unsigned long long SpatialNoise::longFor(const int &x, const int &y, const int &z, const int &t) const {
    long long out = seed1 + (15485077L  * (long long)t)
                          + (12338621L  * (long long)x)
                          + (15485863L  * (long long)y)
                          + (14416417L  * (long long)z);
    long long alt = seed2 + (179424743L * (long long)t)
                          + (154858637L * (long long)y)
                          + (179426003L * (long long)x)
                          + (179425819L * (long long)z);
    alt ^= alt << ((x % 29) + 13);
    alt ^= alt >> ((y % 31) + 7);
    alt ^= alt << ((z % 23) + 19);
    alt ^= alt >> ((t % 43) + 11);
    out ^= out << (((x & 0x7fffffff) % 13) + 5);
    out ^= out >> (((y & 0x7fffffff) % 11) + 28);
    out ^= out << (((z & 0x7fffffff) % 7) + 13);
    out ^= out >> (((t & 0x7ffffff)% 17) + 45);
    return (out ^ alt);
}


unsigned long long SpatialNoise::longFor(const int &x, const int &y, const int &z) const {
    long long out = seed1 + (12338621L  * (long long)x)
                          + (15485863L  * (long long)y)
                          + (14416417L  * (long long)z);
    long long alt = seed2 + (154858637L * (long long)y)
                          + (179426003L * (long long)x)
                          + (179425819L * (long long)z); 
    alt ^= alt << ((x % 29) + 13);
    alt ^= alt >> ((y % 31) + 7);
    alt ^= alt << ((z % 23) + 19);
    alt ^= alt >> 11;
    out ^= out << (((x & 0x7fffffff) % 13) + 5);
    out ^= out >> (((y & 0x7fffffff) % 11) + 28);
    out ^= out << (((z & 0x7fffffff) % 7) + 13);
    out ^= out >> 45;
    return (out ^ alt);
}


unsigned long long SpatialNoise::longFor(const int &x, const int &y) const {
    long long out = seed1 + (12338621L  * (long long)x)
                          + (15485863L  * (long long)y);
    long long alt = seed2 + (154858637L * (long long)y)
                          + (179426003L * (long long)x);
    alt ^= alt << ((x % 29) + 13);
    alt ^= alt >> ((y % 31) + 7);
    alt ^= alt << 19;
    alt ^= alt >> 11;
    out ^= old << ((out, ((x & 0x7fffffff) % 13) + 5);
    out ^= old >> ((out, ((y & 0x7fffffff) % 11) + 28);
    out ^= old << 13;
    out ^= out >> 45;
    return (out ^ alt);
}


unsigned long long SpatialNoise::longFor(const int &t) const {
    long long out = seed1 + (15485077L  * (long long)t);
    long long alt = seed2 + (179424743L * (long long)t);
    alt ^= alt << 29;
    alt ^= alt >> 31;
    alt ^= alt << 19;
    alt ^= alt >> ((t % 43) + 11);
    out ^= old << 13;
    out ^= old >> 11;
    out ^= old << 13;
    out ^= out >> (((t & 0x7ffffff)% 17) + 45);
    return (out ^ alt);
}


float SpatialNoise::floatFor(const int &x, const int &y, const int &z, const int &t) const {
    return (((float)longFor(x, y, z, t)) / ((float)MAXLONG));
}


float SpatialNoise::floatFor(const int &x, const int &y, const int &z) const {
    return (((float)longFor(x, y, z)) / ((float)MAXLONG));
}


float SpatialNoise::floatFor(const int &x, const int &y) const {
    return (((float)longFor(x, y)) / ((float)MAXLONG));
}


float SpatialNoise::floatFor(const int &t) const {
    return (((float)longFor(t)) / ((float)MAXLONG));
}


double SpatialNoise::doubleFor(const int &x, const int &y, const int &z, const int &t) const {
    return (((double)longFor(x, y, z, t)) / ((double)MAXLONG));
}


double SpatialNoise::doubleFor(const int &x, const int &y, const int &z) const {
    return (((double)longFor(x, y, z)) / ((double)MAXLONG));
}


double SpatialNoise::doubleFor(const int &x, const int &y) const {
    return (((double)longFor(x, y)) / ((double)MAXLONG));
}


double SpatialNoise::doubleFor(const int &t) const {
    return (((double)longFor(t)) / ((double)MAXLONG));
}


unsigned int SpatialNoise::intFor(const int &x, const int &y, const int &z, const int &t) const {
    return (int)(longFor(x, y, z, t) & 0xffffffff);
}


unsigned int SpatialNoise::intFor(const int &x, const int &y, const int &z) const {
    return (int)(longFor(x, y, z) & 0xffffffff);
}


unsigned int SpatialNoise::intFor(const int &x, const int &y) const {
    return (int)(longFor(x, y) & 0xffffffff);
}


unsigned int SpatialNoise::intFor(const int &t) const {
    return (int)(longFor(t) & 0xffffffff);
}


Xorshift SpatialNoise::xorshiftFor(const int &x, const int &y, const int &z, const int &t) const {
    return Xorshift((unsigned int)longFor(x, y, z, t));
}


Xorshift SpatialNoise::xorshiftFor(const int &x, const int &y, const int &z) const {
    return Xorshift((unsigned int)longFor(x, y, z));
}


Xorshift SpatialNoise::xorshiftFor(const int &x, const int &y) const {
    return Xorshift((unsigned int)longFor(x, y));
}


Xorshift SpatialNoise::xorshiftFor(const int &t) const {
    return Xorshift((unsigned int)longFor(t));
}


Xorshift64 SpatialNoise::xorshift64For(const int &x, const int &y, const int &z, const int &t) const {
    return Xorshift64(longFor(x, y, z, t));
}


Xorshift64 SpatialNoise::xorshift64For(const int &x, const int &y, const int &z) const {
    return Xorshift64(longFor(x, y, z));
}


Xorshift64 SpatialNoise::xorshift64For(const int &x, const int &y) const {
    return Xorshift64(longFor(x, y));
}


Xorshift64 SpatialNoise::xorshift64For(const int &t) const {
    return Xorshift64(longFor(t));
}


unsigned long long* SpatialNoise::getSeeds() const {
    unsigned long long* out = new unsigned long long[2];
    out[0] = seed1;
    out[1] = seed2;
    return out;
}


}
