#include "GameMath.h"
#include <ctime>

using namespace std;

namespace gamemath {


Xorshift64::Xorshift64() {
    val = seed = time(0);
}


Xorshift64::Xorshift64(unsigned long long seed) {
    val = this->seed = seed;
}


Xorshift64::~Xorshift64() {}


unsigned int Xorshift64::nextInt() {
    return (unsigned int)nextLong();
}


unsigned int Xorshift64::nextInt(const int &mod) {
    return (nextLong() % mod);
}



unsigned int Xorshift64::nextInt(const int &min, const int &max) {
    return (nextLong() % (max - min + 1)) + min;
}


unsigned long Xorshift64::nextLong() {
    // This will overflow -- GOOD!
    val *= 5443;
    val += 1548586312338621L;
    val ^= val >> 19;
    val ^= val << 31;
    val ^= val >> 23;
    val ^= val << 7;
    return val;
}


unsigned short Xorshift64::nextShort() {
    return (unsigned short int)nextLong();
}


unsigned char Xorshift64::nextChar() {
    return (unsigned char)nextLong();
}


float  Xorshift64::nextFloat() {
    return (((float)nextLong()) / ((float)MAXLONG));
}


double Xorshift64::nextDouble() {
    return (((double)nextLong()) / ((double)MAXLONG));
}


bool Xorshift64::nextBool() {
    return (bool)(nextLong() & 1);
}


unsigned long long Xorshift64::getSeed() const {
    return seed;
}


void Xorshift64::setSeed(unsigned long long seed) {
    val = this->seed = seed;
}


unsigned int Xorshift64::getFromSeed(unsigned long long seed) const {
    // This will overflow -- GOOD!
    seed *= 5443;
    seed += 1548586312338621L;
    seed ^= seed >> 19;
    seed ^= seed << 31;
    seed ^= seed >> 23;
    seed ^= seed << 7;
    return seed;
}


}
