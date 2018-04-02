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


unsigned int LcRng::nextInt() {
    val = ((val * 25214903917) + 11) & 0xffffffffffff;
    return (unsigned int)(val >> 16);
}


unsigned int LcRng::nextInt(const int &mod) {
    return (nextInt() % mod);
}


unsigned int LcRng::nextInt(const int &min, const int &max) {
    return (nextInt() % (max - min + 1)) + min;
}


unsigned long LcRng::nextLong() {
    unsigned long long out;
    seed = ((seed * 25214903917) + 11) & 0xffffffffffff;
    out = (seed >> 16);
    out <<= 32;
    seed = ((seed * 25214903917) + 11) & 0xffffffffffff;
    out += (seed >> 16);
    return out;
}


unsigned short LcRng::nextShort() {
    val = ((val * 25214903917) + 11) & 0xffffffffffff;
    return (unsigned short)(val >> 32);
}


unsigned char LcRng::nextChar() {
    val = ((val * 25214903917) + 11) & 0xffffffffffff;
    return (unsigned char)(val >> 40);
}


float  LcRng::nextFloat() {
    return (((float)nextInt()) / ((float)MAXINT));
}


double LcRng::nextDouble() {
    return (((double)nextLong()) / ((double)MAXLONG));
}


bool LcRng::nextBool() {
    val = ((val * 25214903917) + 11) & 0xffffffffffff;
    return (unsigned char)(val >> 24) & 0x1;
}


unsigned int LcRng::getSeed() const {
    return seed;
}


void LcRng::setSeed(unsigned int seed) {
    val = this->seed = seed;
}

}
