#include "GameMath.h"
#include <ctime>

using namespace std;

namespace gamemath {


Xorshift64::Xorshift64() {
    val = seed = time(0);
}


Xorshift64::Xorshift64(unsigned long int seed) {
    val = this->seed = time(0);
}


Xorshift64::~Xorshift64() {}


unsigned int Xorshift64::nextInt() {
    return (unsigned int)nextLong();
}


unsigned int Xorshift64::nextInt(int min, int max) {
    return (nextLong() % (max - min + 1)) + min;
}


unsigned long Xorshift64::nextLong() {
        val *= 5443;
        val += 1548586312338621L;
        val ^= val >> 19;
        val ^= val << 31;
        val ^= val << 23;
        val ^= val >> 7;
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


unsigned long int Xorshift64::getSeed() {
    return seed;
}


void Xorshift64::setSeed(unsigned long int seed) {
    val = this->seed = seed;
}


unsigned int Xorshift64::getFromSeed(unsigned long int seed) {
        seed *= 5443;
        seed += 15485863;
        seed ^= seed << 13;
        seed ^= seed << 17;
        seed ^= seed << 5;
        return seed;
}


}
