#include "GameMath.h"
#include <ctime>

using namespace std;

namespace gamemath {

SpatialNoise::SpatialNoise() {
    seed = time(0);
}


SpatialNoise::SpatialNoise(unsigned long long seed) {
    this->seed = seed;
}


SpatialNoise::~SpatialNoise() {}


unsigned long long SpatialNoise::longFor(const int &x, const int &y, const int &z, const int &t) const {
    long out = seed + (15485077L * (long)t)
                    + (12338621L * (long)x)
                    + (15485863L * (long)y)
                    + (14416417L * (long)z);
    out ^= lrotate(out, (x % 29) + 13);
    out ^= rrotate(out, (y % 31) + 7);
    out ^= lrotate(out, (z % 23) + 19);
    out ^= rrotate(out, (t % 43) + 11);
    return out;
}


unsigned long long SpatialNoise::longFor(const int &x, const int &y, const int &z) const {
    long out = seed + (12338621L * (long)x)
                    + (15485863L * (long)y)
                    + (14416417L * (long)z);
    out ^= lrotate(out, (x % 29) + 13);
    out ^= rrotate(out, (y % 31) + 7);
    out ^= lrotate(out, (z % 23) + 19);
    out ^= rrotate(out, 11);
    return out;
}


unsigned long long SpatialNoise::longFor(const int &x, const int &y) const {
    long out = seed + (12338621L * (long)x)
                    + (15485863L * (long)y);
    out ^= lrotate(out, (x % 29) + 13);
    out ^= rrotate(out, (y % 31) + 7);
    out ^= lrotate(out, 19);
    out ^= rrotate(out, 11);
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
    return seed;
}


void SpatialNoise::setSeed(unsigned long long seed) {
    this->seed = seed;
}


}
