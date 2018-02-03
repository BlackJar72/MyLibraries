 #include "ArrayContainers.h"
 #include <cstring>
 #include <string>
 #include <cstring>

using namespace std;
namespace ArrayContainers {

//#define EMPTY 0xBEDEAD
const unsigned int NULLHASH = 0xBEDEAD;
const string EMPTY = string("");

/*----------------------------------------------------------------*/
/*                  THE CONTAINER NODES                           */
/*----------------------------------------------------------------*/


template <class T>
StringHashNode<T>::StringHashNode() :
        key(EMPTY), value(T()),
        hash(NULLHASH) {}


template <class T>
StringHashNode<T>::StringHashNode(const std::string& inKey, const T& inValue) :
        key(inKey), value(inValue), hash(StringHash(inKey)), next(0) {}



template <class T>
void StringHashNode<T>::add(const std::string& key, const T& value) {
    StringHashNode* target = next;
    do {
        target = tryAdd(key, value, target);
    } while(target);
}


template <class T>
StringHashNode<T>* StringHashNode<T>::tryAdd(const std::string& key, const T& value,
            StringHashNode* target) {
    if(target == 0) {
        target = new StringHashNode(key, value);
        return 0;
    } else {
        return target->next;
    }
}


// Used in removal to check if the first should be removed.
// Hoping the compiler will inline this withing this unit.
template <class T>
inline bool StringHashNode<T>::matches(const std::string& key) const {
    return (key == this->key);
}


// Used to determine if the node is empty.
// Hoping the compiler will inline this withing this unit.
template <class T>
inline bool StringHashNode<T>::isEmpty() const {
    return (hash == NULLHASH) && (key == EMPTY);
}


// For removal of first node
template <class T>
StringHashNode<T>* StringHashNode<T>::getNextNode() {
    return next;
}


// For removal of other nodes
template <class T>
void StringHashNode<T>::remove(const std::string& key) {
    #ifdef _DEBUG
    // Should never happen; implies searching wrong bucket
    // or failure to store data (or perhaps storing incorrectly).
    assert(next != NULL);
    #endif // _DEBUG
    StringHashNode* current = this;
    StringHashNode* target  = next;
    do {
        current = tryRemove(key, target, current);
        target  = current->next;
    } while (target);

}


template <class T>
StringHashNode<T>* StringHashNode<T>::tryRemove(const std::string& key,
                StringHashNode* target, StringHashNode* previous) {
    if(matches(key)){
        previous->next = target->next;
        delete target;
        return 0;
    } else {
        #ifdef _DEBUG
        // If this is true the end of the bucket has been reached without
        // finding the target.  If things are working this should not happen.
        assert(!target);
        #endif // _DEBUG
        return target;
    }
}


template <class T>
T& StringHashNode<T>::get(const std::string& key) {
    StringHashNode<T>* target = this;
    while(target && !target->isEmpty()) {
        if(target->matches(key)) {
            return target->value;
        } else {
            target = target-> next;
        }
    }
    return T();
}


template <class T>
bool StringHashNode<T>::contains(const std::string& key) const {
    StringHashNode<T>* target = this;
    while(target && !target->isEmpty()) {
        if(target->matches(key)) {
            return true;
        } else {
            target = target-> next;
        }
    }
    return false;
}


template <class T>
StringHashNode<T>::~StringHashNode(){
    if(next != NULL) {
        ~next();
    }
}


/*----------------------------------------------------------------*/
/*                   THE HASHMAP PROPER                           */
/*----------------------------------------------------------------*/


template <class T>
StringHashTable<T>::StringHashTable() {
        arrayLength = 16;
        capacity = (arrayLength * 4) / 3;
        length = 0;
        minLength = arrayLength;
        shrinkSize = 0;
        data = new StringHashNode<T>[arrayLength];
}


template <class T>
StringHashTable<T>::StringHashTable(size_t startSize) {
        arrayLength = startSize;
        capacity = (arrayLength * 4) / 3;
        length = 0;
        minLength = arrayLength;
        shrinkSize = 0;
        data = new StringHashNode<T>[arrayLength];
}


template <class T>
void StringHashTable<T>::StringHashTable::grow() {
    size_t oldLen = arrayLength;
    StringHashNode<T>* oldData = data;
    makeInternalData((arrayLength * 3) / 2);
    data = new StringHashNode<T>[arrayLength];
    rebucket(oldData, oldLen);
    delete[] oldData;
}


template <class T>
void StringHashTable<T>::StringHashTable::shrink() {
    size_t oldLen = arrayLength;
    StringHashNode<T>* oldData = data;
    makeInternalData(arrayLength / 2);
    data = new StringHashNode<T>[arrayLength];
    rebucket(oldData, oldLen);
    delete[] oldData;
}


template <class T>
void StringHashTable<T>::makeInternalData(size_t newLength) {
        arrayLength = newLength;
        capacity = (arrayLength * 4) / 3;
        length = 0;
        shrinkSize = ((arrayLength - minLength) * 3) / 16;
}


template <class T>
void StringHashTable<T>::rebucket(StringHashNode<T>* oldData, const size_t oldLen) {
    for(int i = 0; i < oldLen; i++) {
        if(!oldData[i].isEmpty()) {
            add(oldData[i]);
        }
    }
}


template <class T>
void StringHashTable<T>::add(const std::string& key, const T& value) {
    data->add[StringHash(key) % capacity](key, value);
}


template <class T>
void StringHashTable<T>::remove(const std::string& key) {
    data->remove[StringHash(key) % capacity](key);
}


template <class T>
T StringHashTable<T>::get(const std::string& key) {
    return data[StringHash(key) % capacity].get(key);
}


template <class T>
bool StringHashTable<T>::contains(const std::string& key) {
    return data->contains(key);
}


/*----------------------------------------------------------------*/
/*                 HASH FUNCTIONS BELOW                           */
/*----------------------------------------------------------------*/


/**
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

/**
 * This will produce a usable hash of a c-string.
 * Its primarily for generating decent hashes for
 * use in hash maps / hash tables.
 */
unsigned int StringHash(char* data) {
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
unsigned int GenericHash(const T& data) {
    char* bytes = reinterpret_cast<char*>(&data);
    unsigned int out = 0;
    for(int i = 0; i < sizeof(T); i++) {
        out ^= ((*(bytes + i)) << (8 * (i%4)));
        out ^=  (out << 13);
        out ^=  (out >> 5);
        out ^=  (out << 17);
        i++;
    }
    return out;
}




}
