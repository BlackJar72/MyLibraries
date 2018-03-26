#include <iostream>
#include <fstream>
#include <cstdlib>

void sequencialHash(char* byte, unsigned long long& hash);

/*
 * A simple utility for hashing files into 64 bit numbers.
 * This is an improved version of hash32, also for checking
 * for the likely hood of two files being identical, but now
 * (theoretically) twice as powerful, make the chance of
 * false positive practically non-existent.
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
		std::cerr << "Usage: hash64 [filename]" << std::endl << std::endl;
		exit(1);
	}
	unsigned long long hash = 0;
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
void sequencialHash(char* byte, unsigned long long& hash) {
	static size_t count = 0;
	hash ^= (*byte) << (8 * count);
	hash ^= hash << 13;
	hash ^= hash >> 5;
	hash ^= hash << 17;
	count = (++count) % 8;
}
