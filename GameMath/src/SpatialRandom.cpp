#include "GameMath.h"
#include <ctime>

using namespace std;

namespace gamemath {

SpatialRandom::SpatialRandom() {
    val = seed = time(0);
}


SpatialRandom::SpatialRandom(unsigned long int seed) {
    val = this->seed = time(0);
}


SpatialRandom::~SpatialRandom() {}


unsigned long int SpatialRandom::longFor(int x, int y, int z, int t) {
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


unsigned long int SpatialRandom::longFor(int x, int y, int z) {
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


unsigned long int SpatialRandom::longFor(int x, int y) {
    // This will overflow -- GOOD!
    long out = seed + (12338621L * (long)x)
                    + (15485863L * (long)y);
    out ^= out << ((x % 29) + 13);
    out ^= out >> ((y % 31) + 7);
    out ^= out << 19;
    out ^= out >> 11;
    return out;
}


float SpatialRandom::floatFor(int x, int y, int z, int t) {
    return (((float)longFor(x, y, z, t)) / ((float)MAXLONG));
}


float SpatialRandom::floatFor(int x, int y, int z) {
    return (((float)longFor(x, y, z)) / ((float)MAXLONG));
}


float SpatialRandom::floatFor(int x, int y) {
    return (((float)longFor(x, y)) / ((float)MAXLONG));
}


Xorshift SpatialRandom::xorshiftFor(int x, int y, int z, int t) {
    return Xorshift((unsigned int)longFor(x, y, z, t));
}


Xorshift SpatialRandom::xorshiftFor(int x, int y, int z) {
    return Xorshift((unsigned int)longFor(x, y, z));
}


Xorshift SpatialRandom::xorshiftFor(int x, int y) {
    return Xorshift((unsigned int)longFor(x, y));
}


Xorshift64 SpatialRandom::xorshift64For(int x, int y, int z, int t) {
    return Xorshift64(longFor(x, y, z, t));
}


Xorshift64 SpatialRandom::xorshift64For(int x, int y, int z) {
    return Xorshift64(longFor(x, y, z));
}


Xorshift64 SpatialRandom::xorshift64For(int x, int y) {
    return Xorshift64(longFor(x, y));
}


unsigned long int SpatialRandom::getSeed() const {
    return seed;
}


void SpatialRandom::setSeed(unsigned long int seed) {
    val = (this->seed) = seed;
}


}
