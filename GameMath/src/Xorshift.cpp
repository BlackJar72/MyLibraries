#include "GameMath.h"
#include <ctime>

using namespace std;

namespace gamemath {

Xorshift::Xorshift() {
    val = seed = time(0);
}


Xorshift::Xorshift(unsigned int seed) {
    val = this->seed = seed;
}


Xorshift::~Xorshift() {}


unsigned int Xorshift::nextInt() const {
    val ^= val << 13;
    val ^= val >> 17;
    val ^= val << 5;
    return val;
}


unsigned int Xorshift::nextInt(const int &mod) const {
    return (nextInt() % mod);
}


unsigned int Xorshift::nextInt(const int &min, const int &max) const {
    return (nextInt() % (max - min + 1)) + min;
}


unsigned long Xorshift::nextLong() const {
    unsigned long long out = nextInt();
    return (out << 32) | nextInt();
}


unsigned short Xorshift::nextShort() const {
    return (unsigned short int)nextInt();
}


unsigned char Xorshift::nextChar() const {
    return (unsigned char)nextInt();
}


float  Xorshift::nextFloat() const {
    return (((float)nextInt()) / ((float)MAXINT));
}


double Xorshift::nextDouble() const {
    return (((double)nextInt()) / ((double)MAXINT));
}


bool Xorshift::nextBool() const {
    return (bool)(nextInt() & 1);
}


unsigned int Xorshift::getSeed() const {
    return seed;
}


void Xorshift::setSeed(unsigned int seed) {
    val = this->seed = seed;
}


void Xorshift::reset() {
    val = seed;
}


unsigned int Xorshift::getFromSeed(unsigned int seed) const {
        seed ^= seed << 13;
        seed ^= seed >> 17;
        seed ^= seed << 5;
        return seed;
}



}
