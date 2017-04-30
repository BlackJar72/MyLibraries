#include "GameMath.h"
#include <ctime>

using namespace std;

namespace gamemath {


SpatialNoise::SpatialNoise(unsigned long long seed1,
                           unsigned long long seed2) : seed1(seed1), seed2(seed2) {}


SpatialNoise::~SpatialNoise() {}


unsigned long long SpatialNoise::longFor(const int &x, const int &y, const int &z, const int &t) const {
    long out = seed1 + (15485077L * (long)t)
                     + (12338621L * (long)x)
                     + (15485863L * (long)y)
                     + (14416417L * (long)z);
    long alt = seed2 + (179424743L * (long)t)
                     + (154858637L * (long)y)
                     + (179426003L * (long)x)
                     + (179425819L * (long)z);
    alt ^= lrotate(alt, (x % 29) + 13);
    alt ^= rrotate(alt, (y % 31) + 7);
    alt ^= lrotate(alt, (z % 23) + 19);
    alt ^= rrotate(alt, (t % 43) + 11);
    out ^= lrotate(out, ((x & 0x7fffffff) % 13) + 5);
    out ^= rrotate(out, ((y & 0x7fffffff) % 11) + 28);
    out ^= lrotate(out, ((z & 0x7fffffff) % 7) + 13);
    out ^= rrotate(out, ((t & 0x7ffffff)% 17) + 45);
    return (out ^ alt);
}


unsigned long long SpatialNoise::longFor(const int &x, const int &y, const int &z) const {
    long out = seed1 + (12338621L * (long)x)
                     + (15485863L * (long)y)
                     + (14416417L * (long)z);
    long alt = seed2 + (154858637L * (long)y)
                     + (179426003L * (long)x)
                     + (179425819L * (long)z);
    alt ^= lrotate(alt, (x % 29) + 13);
    alt ^= rrotate(alt, (y % 31) + 7);
    alt ^= lrotate(alt, (z % 23) + 19);
    alt ^= rrotate(alt, 11);
    out ^= lrotate(out, ((x & 0x7fffffff) % 13) + 5);
    out ^= rrotate(out, ((y & 0x7fffffff) % 11) + 28);
    out ^= lrotate(out, ((z & 0x7fffffff) % 7) + 13);
    out ^= rrotate(out, 45);
    return (out ^ alt);
}


unsigned long long SpatialNoise::longFor(const int &x, const int &y) const {
    long out = seed1 + (12338621L * (long)x)
                     + (15485863L * (long)y);
    long alt = seed2 + (154858637L * (long)y)
                     + (179426003L * (long)x);
    alt ^= lrotate(alt, (x % 29) + 13);
    alt ^= rrotate(alt, (y % 31) + 7);
    alt ^= lrotate(alt, 19);
    alt ^= rrotate(alt, 11);
    out ^= lrotate(out, ((x & 0x7fffffff) % 13) + 5);
    out ^= rrotate(out, ((y & 0x7fffffff) % 11) + 28);
    out ^= lrotate(out, 13);
    out ^= rrotate(out, 45);
    return (out ^ alt);
    return out;
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


double SpatialNoise::doubleFor(const int &x, const int &y, const int &z, const int &t) const {
    return (((double)longFor(x, y, z, t)) / ((double)MAXLONG));
}


double SpatialNoise::doubleFor(const int &x, const int &y, const int &z) const {
    return (((double)longFor(x, y, z)) / ((double)MAXLONG));
}


double SpatialNoise::doubleFor(const int &x, const int &y) const {
    return (((double)longFor(x, y)) / ((double)MAXLONG));
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


Xorshift SpatialNoise::xorshiftFor(const int &x, const int &y, const int &z, const int &t) const {
    return Xorshift((unsigned int)longFor(x, y, z, t));
}


Xorshift SpatialNoise::xorshiftFor(const int &x, const int &y, const int &z) const {
    return Xorshift((unsigned int)longFor(x, y, z));
}


Xorshift SpatialNoise::xorshiftFor(const int &x, const int &y) const {
    return Xorshift((unsigned int)longFor(x, y));
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


unsigned long long SpatialNoise::getSeed() const {
    return seed1;
}


}
