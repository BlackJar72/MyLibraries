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


unsigned int Xorshift::nextInt() {
    // This will overflow -- GOOD!
    /*// For improved xorshift these would be added.
    val *= 5443;
    val += 15485863;
    // ...for basic, blazing fast xorshift this is all you need.*/
    val ^= val << 13;
    val ^= val >> 17;
    val ^= val << 5;
    return val;
}


unsigned int Xorshift::nextInt(int mod) {
    return (nextInt() % mod);
}


unsigned int Xorshift::nextInt(int min, int max) {
    return (nextInt() % (max - min + 1)) + min;
}


unsigned long Xorshift::nextLong() {
    unsigned long int out = nextInt();
    return (out << 32) + nextInt();
}


unsigned short Xorshift::nextShort() {
    return (unsigned short int)nextInt();
}


unsigned char Xorshift::nextChar() {
    return (unsigned char)nextInt();
}


float  Xorshift::nextFloat() {
    return (((float)nextInt()) / ((float)MAXINT));
}


double Xorshift::nextDouble() {
    return (((double)nextInt()) / ((double)MAXINT));
}


bool Xorshift::nextBool() {
    return (bool)(nextInt() & 1);
}


unsigned int Xorshift::getSeed() const {
    return seed;
}


void Xorshift::setSeed(unsigned int seed) {
    val = this->seed = seed;
}


unsigned int Xorshift::getFromSeed(unsigned int seed) const {
        /*// For improved xorshift these would be added.
        seed *= 5443;
        seed += 15485863;
        // ...for basic, blazing fast xorshift this is all you need.*/
        seed ^= seed << 13;
        seed ^= seed >> 17;
        seed ^= seed << 5;
        return seed;
}



}
