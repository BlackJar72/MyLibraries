#include "ArrayContainers.h"

using namespace std;

namespace ArrayContainers {

// Should always be one, but checking anyway
const size_t ASCII_STRIDE = sizeof(unsigned int) / sizeof(char);
// This is required (note that the size of wchar_t is system dependent.)
const size_t WCHAR_STRIDE = sizeof(unsigned int) / sizeof(wchar_t);
// Assuming standard 8-bit bytes, because its nearly universal and 
// I don't know a way to get the size of a byte in bits otherwise.
const size_t WCHAR_SHIFT  = sizeof(wchar_t) * 8;

/**
 * This will produce a usable hash of a standard string.
 * Its primarily for generating decent hashes for
 * use in hash maps / hash tables.
 */
unsigned int stringHash(const string &s) {
    unsigned int out = 0;
    unsigned int i = 0;
    const char* data = s.c_str();
    while(data[i] != 0) {
        out ^= (data[i] << (8 * (i % ASCII_STRIDE)));
        out ^=  (out << 13);
        out ^=  (out >> 5);
        out ^=  (out << 17);
        i++;
    }
    return out;
}


/**
 * This will produce a usable hash of a wide string.
 * Note that the same text may have different hashes
 * when stored as a wstring the when stored as a string.
 */
unsigned int wstringHash(const wstring &s) {
    unsigned int out = 0;
    unsigned int i = 0;
    const wchar_t* data = s.data();
    while(data[i] != 0) {
        out ^= (data[i] << (WCHAR_SHIFT * (i % WCHAR_STRIDE)));
        out ^=  (out << 13);
        out ^=  (out >> 5);
        out ^=  (out << 17);
        i++;
    }
    return out;
}


/**
 * This will produce a usable hash of a c-string.
 * Its primarily for generating decent hashes for
 * use in hash maps / hash tables.
 */
unsigned int stringHash(char* data) {
    unsigned int out = 0;
    unsigned int i = 0;
    while(data[i] != 0) {
        out ^= (data[i] << (8 * (i % ASCII_STRIDE)));
        out ^=  (out << 13);
        out ^=  (out >> 5);
        out ^=  (out << 17);
        i++;
    }
    return out;
}


/**
 * This will produce a usable hash a generic type as defined
 * by the template parameter.
 *
 * Note that for this to work properly T must have a constant
 * size; this should generally be true.
 *
 * Also note that pointers will be hashed based on their addresses,
 * not their contents, and are thus not valid in many case; this
 * includes pointers and arrays as members of classes / structs
 * and thus implicitly applies to classes / structs that contain
 * them.  Specifically, if the data has been serialized and reloaded
 * (or loaded elsewhere such as through a network) the hash will
 * also change, making structures dependent on them invalid.
 */
template <class T>
unsigned int genericHash(const T& data) {
    char* bytes = reinterpret_cast<char*>(&data);
    unsigned int out = 0;
    for(int i = 0; i < sizeof(T); i++) {
        out ^= ((*(bytes + i)) << (8 * (i % ASCII_STRIDE)));
        out ^=  (out << 13);
        out ^=  (out >> 5);
        out ^=  (out << 17);
        i++;
    }
    return out;
}


}
