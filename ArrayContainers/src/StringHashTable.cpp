 #include "ArrayContainers.h"
 #include <cstring>
 #include <string>

using namespace std;
namespace ArrayContainers {


template <class T>
Node<T>::Node(string key, T value) {
    this->value = value;
    this->key  = key;
    next = NULL;
}


template <class T>
Node<T>::Node(){/*Do norhing; this should never be called*/}


template <class T>
void Node<T>::add(string key, T value) {
    if(next == NULL) {
        next = new Node(key, value);
    } else {
        next->addValue(key, value);
    }
}


// Used in removal to check if the first should be removed
template <class T>
bool Node<T>::matchs(string key) {
    return (key.compare(this->key) == 0);
}


// For removal of first node
template <class T>
Node<T>* Node<T>::getNextNode() {
    return next;
}


// For removal of other nodes
template <class T>
void Node<T>::remove(string key) {
    assert(next != NULL); // Should never happen; implies searching wrong bucket
    if(next->key.compare(key) == 0){
        Node<T>* tmp = next;
        next = next->next;
        delete tmp;
    } else {
        next->remove(key);
    }
}


template <class T>
T Node<T>::get(string key) {
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
Node<T>::~Node(){
    if(next != NULL) {
        ~next();
    }
}


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




}
