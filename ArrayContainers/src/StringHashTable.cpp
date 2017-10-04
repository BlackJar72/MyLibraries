 #include "ArrayContainers.h"
 #include <cstring>
 #include <string>
 #include "glfw3.h"

using namespace std;
namespace ArrayContainers {


template <class T>
StringHashNode<T>::StringHashNode(string key, T value) {
    this->value = value;
    this->key  = key;
    next = NULL;
}


template <class T>
StringHashNode<T>::StringHashNode(){/*Do nothing. Never use this!*/}


template <class T>
void StringHashNode<T>::add(string key, T value) {
    if(next == NULL) {
        next = new StringHashNode(key, value);
    } else {
        next->addValue(key, value);
    }
}


// Used in removal to check if the first should be removed
template <class T>
bool StringHashNode<T>::matchs(string key) {
    return (key.compare(this->key) == 0);
}


// For removal of first node
template <class T>
StringHashNode<T>* StringHashNode<T>::getNextNode() {
    return next;
}


// For removal of other nodes
template <class T>
void StringHashNode<T>::remove(string key) {
    assert(next != NULL); // Should never happen; implies searching wrong bucket
    if(next->key.compare(key) == 0){
        StringHashNode<T>* tmp = next;
        next = next->next;
        delete tmp;
    } else {
        next->remove(key);
    }
}


template <class T>
T StringHashNode<T>::get(string key) {
    // Question: Does C++ short-cicuit like Java and D?
    // That would allow this to be collapsed into a single if.
    if(next == NULL) {
        // If true, there are no other options, so this mush be
        // the correct value (assuming no bugs in placement).
        return value;
    } else if(key.compare(this->key) == 0) {
        // Comparing the string here should be both faster and more
        // than hashing it.
        return value;
    } else return next->getValue(key);
}


template <class T>
StringHashNode<T>::~StringHashNode(){
    if(next != NULL) {
        ~next();
    }
}

/*
 * This will produce a usable hash of a standard string.
 * Its primarily for generating decent hashes for
 * use in hash maps / hash tables.
 */
unsigned int StringHash(const string &s) {
    unsigned int out = 0;
    unsigned int i = 0;
    const char* data = s.c_str();
    while(data[i] != 0) {
        out ^= (data[i] << (8 * (i%4)));
        out ^=  (out << 13);
        out ^=  (out >> 5);
        out ^=  (out << 17);
        i++;
    }
    return out;
}

/*
 * This will produce a usable hash of a c-string.
 * Its primarily for generating decent hashes for
 * use in hash maps / hash tables.
 */
unsigned int StringHash(const char* data) {
    unsigned int out = 0;
    unsigned int i = 0;
    while(data[i] != 0) {
        out ^= (data[i] << (8 * (i%4)));
        out ^=  (out << 13);
        out ^=  (out >> 5);
        out ^=  (out << 17);
        i++;
    }
    return out;
}




}
