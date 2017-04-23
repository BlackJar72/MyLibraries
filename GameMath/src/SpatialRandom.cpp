#include "GameMath.h"
#include <ctime>

using namespace std;

namespace gamemath {

SpatialNoise::SpatialNoise() {
    val = seed = time(0);
}


SpatialNoise::SpatialNoise(unsigned long long seed) {
    val = this->seed = seed;
}


SpatialNoise::~SpatialNoise() {}


unsigned long long SpatialNoise::longFor(int x, int y, int z, int t) {
    // This will overflow -- GOOD!
    long out = seed + (15485077L * (long)t)
                    + (12338621L * (long)x)
                    + (15485863L * (long)y)
                    + (14416417L * (long)z);
    out ^= out << ((x % 29) + 13);
    out ^= out >> ((y % 31) + 7);
    out ^= out << ((z % 23) + 19);
    out ^= out << ((t % 43) + 11);
    return out;
}


unsigned long long SpatialNoise::longFor(int x, int y, int z) {
    // This will overflow -- GOOD!
    long out = seed + (12338621L * (long)x)
                    + (15485863L * (long)y)
                    + (14416417L * (long)z);
    out ^= out << ((x % 29) + 13);
    out ^= out >> ((y % 31) + 7);
    out ^= out << ((z % 23) + 19);
    out ^= out >> 11;
    return out;
}


unsigned long long SpatialNoise::longFor(int x, int y) {
    // This will overflow -- GOOD!
    long out = seed + (12338621L * (long)x)
                    + (15485863L * (long)y);
    out ^= out << ((x % 29) + 13);
    out ^= out >> ((y % 31) + 7);
    out ^= out << 19;
    out ^= out >> 11;
    return out;
}


float SpatialNoise::floatFor(int x, int y, int z, int t) {
    return (((float)longFor(x, y, z, t)) / ((float)MAXLONG));
}


float SpatialNoise::floatFor(int x, int y, int z) {
    return (((float)longFor(x, y, z)) / ((float)MAXLONG));
}


float SpatialNoise::floatFor(int x, int y) {
    return (((float)longFor(x, y)) / ((float)MAXLONG));
}


Xorshift SpatialNoise::xorshiftFor(int x, int y, int z, int t) {
    return Xorshift((unsigned int)longFor(x, y, z, t));
}


Xorshift SpatialNoise::xorshiftFor(int x, int y, int z) {
    return Xorshift((unsigned int)longFor(x, y, z));
}


Xorshift SpatialNoise::xorshiftFor(int x, int y) {
    return Xorshift((unsigned int)longFor(x, y));
}


Xorshift64 SpatialNoise::xorshift64For(int x, int y, int z, int t) {
    return Xorshift64(longFor(x, y, z, t));
}


Xorshift64 SpatialNoise::xorshift64For(int x, int y, int z) {
    return Xorshift64(longFor(x, y, z));
}


Xorshift64 SpatialNoise::xorshift64For(int x, int y) {
    return Xorshift64(longFor(x, y));
}


unsigned long long SpatialNoise::getSeed() const {
    return seed;
}


void SpatialNoise::setSeed(unsigned long long seed) {
    val = (this->seed) = seed;
}


}
