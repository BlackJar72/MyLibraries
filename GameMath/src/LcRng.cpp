#include "GameMath.h"

using namespace std;

namespace gamemath {

LcRng::LcRng() {
    val = seed = time(0);
}

LcRng::LcRng(unsigned long long seed) {
    val = this->seed = seed;
}

LcRng::~LcRng() {}


unsigned int LcRng::nextInt() const {
    val = ((val * 25214903917) + 11) & 0xffffffffffff;
    return (unsigned int)(val >> 16);
}


unsigned int LcRng::nextInt(const int &mod) const {
    return (nextInt() % mod);
}


unsigned int LcRng::nextInt(const int &min, const int &max) const {
    return (nextInt() % (max - min + 1)) + min;
}


unsigned long LcRng::nextLong() const {
    unsigned long long out;
    val = ((val * 25214903917) + 11) & 0xffffffffffff;
    out = (val >> 16);
    out <<= 32;
    val = ((val * 25214903917) + 11) & 0xffffffffffff;
    out += (val >> 16);
    return out;
}


unsigned short LcRng::nextShort() const {
    val = ((val * 25214903917) + 11) & 0xffffffffffff;
    return (unsigned short)(val >> 32);
}


unsigned char LcRng::nextChar() const {
    val = ((val * 25214903917) + 11) & 0xffffffffffff;
    return (unsigned char)(val >> 40);
}


float  LcRng::nextFloat() const {
    return (((float)nextInt()) / ((float)MAXINT));
}


double LcRng::nextDouble() const {
    return (((double)nextLong()) / ((double)MAXLONG));
}


bool LcRng::nextBool() const {
    val = ((val * 25214903917) + 11) & 0xffffffffffff;
    return (unsigned char)(val >> 24) & 0x1;
}


unsigned int LcRng::getSeed() const {
    return seed;
}


void LcRng::setSeed(unsigned int seed) {
    val = this->seed = seed;
}


void LcRng::reset() {
    val = seed;
}

}
