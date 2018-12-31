#include <iostream>
#include <fstream>
#include <cstdlib>

void sequencialHash(char* byte, unsigned int& hash);

/*
 * A simple utility for hashing files into 32 bit numbers.
 * Hopefully I can use this to tell once and for all if
 * MinGW is really failing on Linux in the way I think it
 * is by simply creating the same binaries and basic gcc
 * rather than cross compiling.  Of course, it could be
 * used in the same way with any two files (to check for
 * probably identity).
 *
 * (Note that this is not a security application / algorithm,
 * and does not account for engineered hash collisions, nor
 * do I have any idea how easy they might be to create.  More
 * to the point, they are not cryptographic hashes and should
 * not be used as such.)
 */
int main(int argc, char** argv) {
	if(argc < 2) {
		std::cerr << std::endl << "Not file provided to hash!" << std::endl;
		std::cerr << "Usage: hash32 [filename]" << std::endl << std::endl;
		std::exit(1);
	}
	unsigned int hash = 0;
	std::ifstream file;
	file.open(argv[1]);
	if(file.is_open()) {
		char* nextByte = new char;
		while(!file.eof()) {
			file.read(nextByte, 1);
			sequencialHash(nextByte, hash);
		}
	}
	std::cout << std::endl << hash << std::endl;
}

/*
 * Using basically the same xorshift-derived hash I created for my HashMap
 * implementation -- its should be good enough for this.
 */
void sequencialHash(char* byte, unsigned int& hash) {
	static size_t count = 0;
	unsigned int longbyte = *byte;
	hash ^= longbyte << (8 * count);
	hash ^= hash << 13;
	hash ^= hash >> 5;
	hash ^= hash << 17;
	count = (++count) % 4;
}
