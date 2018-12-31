#include <iostream>
#include <fstream>
#include <cstdlib>

bool compare(std::ifstream& file1, std::ifstream&  file2);

/*
 * Since hashing isn't perfect, this will compare two files byte-by-byte;
 * it should also actually be faster than hashing both files.
 */
int main(int argc, char** argv) {
	if(argc < 3) {
		std::cerr << std::endl << "Not files provided to compare!" << std::endl;
		std::cerr << "Usage: compare [filename1] [filename1]" << std::endl << std::endl;
		std::exit(1);
	}
	unsigned int hash = 0;
	std::ifstream file1;
	std::ifstream file2;
	file1.open(argv[1]);
	file2.open(argv[2]);
	if(file1.is_open() && file2.is_open()) {
        if(compare(file1, file2)) {
            std::cout << "True (files are the same) " << std::endl;
        } else {
            std::cout << "False (files are different) " << std::endl;
        }
	} else {
        std::cout << "Could not open both files!" << std::endl;
	}
}

/*
 * Compares each byte and returns false as soon as a pair
 * does not match (or if the files aren't the same size).
 * Otherwise this returns true.
 */
bool compare(std::ifstream& file1, std::ifstream&  file2) {
    char* b1 = new char;
    char* b2 = new char;
    while(!file1.eof() && !file2.eof()) {
        file1.read(b1, 1);
        file2.read(b2, 1);
        if(*b1 != *b2) {
            return false;
        }
    }
    if(!file1.eof() || !file2.eof()) {
        return false;
    }
    return true;
}

