#include "StringTokenizer.h"
#include <string>

using namespace std;

namespace stringtoken {

/**
 * Creates a new, empty CharSet.
 */
CharSet::CharSet() {
    data = new char[BYTES];
    clear();
}


/**
 * Creates a new char set contain the characters in the c_string array.
 */
CharSet::CharSet(const unsigned char *in) {
	data = new char[BYTES];
    clear();
	add(in);
}


/**
 * Creates a new char set contain the characters in the string.
 */
CharSet::CharSet(const string &in) {
	data = new char[BYTES];
    clear();
	add(in);
}



CharSet::~CharSet() {
    delete data;
}


/**
 * Removes all characters CharSet, making it an empty set.
 */
void CharSet::clear() {
    for(int i = 0; i < BYTES; i++) {
        data[i] = 0;
    }
}


/**
 * Adds the character from the charset.
 */
 void CharSet::add(const unsigned char &in) {
 if(in > 255) return;
		bit = ((int) in) % BITS;
		loc = ((int) in) / BITS;
		if((data[loc] &  (1 << bit)) == 0) {
			data[loc] |= (1 << bit);
    }
}


/**
 * Removes the character from the charset.
 */
void CharSet::remove(const unsigned char &in) {
	if(in > 255) return;
	bit = ((int) in) % BITS;
	loc = ((int) in) / BITS;
	if((data[loc] & (1 << bit)) != 0) {
		data[loc] &= ~(1 << bit);
	}
}


/**
 * Adds all the characters in the c-string array to the CharSet.
 */
void CharSet::add(const unsigned char *in) {
	for(int i = 0; in[i] != '\0'; i++) {
		add(in[i]);
	}
}


/**
 * Removes all the characters in the c-string array from the CharSet.
 */
void CharSet::remove(const unsigned char *in) {
	for(int i = 0; in[i] != '\0'; i++) {
		remove(in[i]);
	}
}


/**
 * Adds all the characters in the string to the CharSet.
 */
void CharSet::add(const string &in) {
    int l = in.size();
	for(int i = 0; i < l; i++) {
		add(in.at(i));
	}
}


/**
 * Removes all the characters in the string from the CharSet.
 */
void CharSet::remove(const string &in) {
    int l = in.size();
	for(int i = 0; i < l; i++) {
		remove(in.at(i));
	}
}


/**
 * Adds all the characters in the other CharSet to this CharSet.
 */
void CharSet::add(const CharSet &in) {
	for(int i = 0; i < BYTES; i++) {
		data[i] |= in.data[i];
	}
}


/**
 * Removes all the characters in the other CharSet from this CharSet.
 */
void CharSet::remove(const CharSet &in) {
	for(int i = 0; i < BYTES; i++) {
		data[i] &= ~in.data[i];
	}
}

/**
 * Return the union of this CharSet and the input.
 */
CharSet* CharSet::setUnion(const CharSet &in) {
	CharSet* out = new CharSet();
	for(int i = 0; i < BYTES; i++) {
		out->data[i] = in.data[i] | data[i];
	}
	return out;
}


/**
 * Return the intersection of this CharSet and the input.
 */
CharSet* CharSet::intersection(const CharSet &in) {
	CharSet* out = new CharSet();
	for(int i = 0; i < BYTES; i++) {
		out->data[i] = in.data[i] & data[i];
	}
	return out;
}


/**
 * Return the complement of this CharSet.
 */
CharSet* CharSet::complement() {
	CharSet* out = new CharSet();
	for(int i = 0; i < BYTES; i++) {
		out->data[i] = ~data[i];
	}
	return out;
}


/**
 * Returns true if and only if the character in a member of the
 * CharSet.
 */
bool CharSet::contains(const unsigned char &in) {
	if(in > 255) return false;
	bit = ((int) in) % BITS;
	loc = ((int) in) / BITS;
	return (data[loc] & (1 << bit)) != 0;
}


/**
 * Returns true (aka, 0) if the CharSet is an empty set,
 * otherwise returns non-zero (aka, true).
 */
bool CharSet::isEmpty() {
    for(int i = 0; i < BYTES; i++) {
        if(data[i] != 0) return false;
    }
    return true;
}

}

