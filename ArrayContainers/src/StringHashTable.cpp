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
StringHashNode<T>::StringHashNode() : key(EMPTY), value(T()), hash(NULLHASH) {}


template <class T>
StringHashNode<T>::StringHashNode(const std::string& inKey, const T& inValue) :
        key(inKey), value(inValue), hash(stringHash(inKey)), next(0) {}


template <class T>
StringHashNode<T>::~StringHashNode() {
    // Do NOT delete next; it may still be a valid node.
}


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
    } else if(target->key == key) {
        target->value = value;
        return 0;
    } else {
        return target->next;
    }
}


template <class T>
void StringHashNode<T>::addNode(const StringHashNode<T>* node) {
    StringHashNode* target = this;
    do {
        if(target->next = 0) {
            target->next = node;
            target = 0;
        } else {
            target = target->next;
        }
    } while(target);
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
unsigned int StringHashNode<T>::getHash() const {
    return hash;
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
StringHashTable<T>::~StringHashTable() {
    for(int i = 0; i < arrayLength; i++) {
        StringHashNode<T>* garbage0;
        StringHashNode<T>* garbage1 = data[i].next;
        while(garbage1) {
            garbage0 = garbage1;
            garbage1 = garbage1->next;
            delete garbage0;
        }
    }
    delete[] data;
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
            StringHashNode<T>* tmp;
            StringHashNode<T>* element = &oldData[i];
            while(element) {
                data[element->hash % arrayLength].add(*element);
                element = element->next;
                tmp = element;
                tmp->next = 0;
            }
        }
    }
}


template <class T>
void StringHashTable<T>::add(const std::string& key, const T& value) {
    StringHashNode<T> node = StringHashNode<T>(key, value);
    unsigned int bucket = node.getHash() % arrayLength;
    if(data[bucket].isEmpty()) {
        data[bucket] = node;
    } else {
        data->add[stringHash(key) % capacity](key, value);
    }
    if(++length >= capacity) {
        grow();
    }
}


template <class T>
void StringHashTable<T>::remove(const std::string& key) {
    unsigned int bucket = stringHash(key) % arrayLength;
    if(data[bucket].matches(key)) {
        if(data[bucket].next.isEmpty())
            data[bucket] = StringHashNode<T>();
        else data[bucket] = data[bucket].next;
    } else {
        data->remove[stringHash(key) % capacity](key);
    }
    if(--length < shrinkSize) {
        shrink();
    }
}


template <class T>
T StringHashTable<T>::get(const std::string& key) const {
    return data[stringHash(key) % capacity].get(key);
}


template <class T>
T& StringHashTable<T>::getRef(const std::string& key) const {
    return data[stringHash(key) % capacity].get(key);
}


template <class T>
T* StringHashTable<T>::getPtr(const std::string& key) const {
    return &data[stringHash(key) % capacity].get(key);
}


template <class T>
bool StringHashTable<T>::contains(const std::string& key) const {
    return data->contains(key);
}




}
