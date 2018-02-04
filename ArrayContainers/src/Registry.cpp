#include "ArrayContainers.h"

namespace ArrayContainers {

const size_t   D_ARRAY_INIT_SIZE = 16;
const size_t   D_MAP_INIT_SIZE   = ((D_ARRAY_INIT_SIZE * 4) / 3) + 1;
const float D_ARRAY_GROWTH_FACTOR = 1.5;
const float D_ARRAY_SHRINK_FACTOR = 0.5;
const float D_ARRAY_SHRINK_THRESHOLD = 0.25;


template <class T>
Registry<T>::Registry() :
            data(new T[D_ARRAY_INIT_SIZE]),
            nameMap(StringHashTable<int>(D_MAP_INIT_SIZE)),
            elements(0),
            length(D_ARRAY_INIT_SIZE) {}


template <class T>
Registry<T>::Registry(size_t startSize) :
            data(new T[startSize]),
            nameMap(StringHashTable<int>(((startSize * 4) / 3) + 1)),
            elements(0),
            length(startSize)  {}


template <class T>
Registry<T>::~Registry() {
    delete[] data;
}


template <class T>
void Registry<T>::grow() {
    length *= D_ARRAY_GROWTH_FACTOR;
    T* bigger = new T(length);
    memcpy(bigger, data, elements * sizeof(T));
    delete[] data;
    data = bigger;
}


template <class T>
void Registry<T>::shrink() {
    if(length <= D_ARRAY_INIT_SIZE) {
        return;
    }
    length *= D_ARRAY_SHRINK_FACTOR;
    if(length < D_ARRAY_INIT_SIZE) {
        length = D_ARRAY_INIT_SIZE;
    }
    T* smaller = new T(length);
    memcpy(smaller, data, elements * sizeof(T));
    delete data;
    data = smaller;
}


template <class T>
unsigned int Registry<T>::add(const std::string& name, const T& t) {
    nameMap.add(name, elements);
    data[++elements] = t;
    if(elements >= length) {
        grow();
    }
    return elements - 1;
}


template <class T>
unsigned int Registry<T>::getID(const std::string& name) const {
    #ifdef _DEBUG
    assert(nameMap.contains(name));
    #endif // _DEBUG
    return nameMap.get(name);
}


template <class T>
T Registry<T>::get(unsigned int id) const {
    #ifdef _DEBUG
    assert((id < 0) || (id >= elements));
    #endif // _DEBUG
    return data[id % length];
}


template <class T>
T& Registry<T>::getRef(unsigned int id) const {
    #ifdef _DEBUG
    assert((id < 0) || (id >= elements));
    #endif // _DEBUG
    return data[id % length];
}


template <class T>
T* Registry<T>::getPtr(unsigned int id) const {
    #ifdef _DEBUG
    assert((id < 0) || (id >= elements));
    #endif // _DEBUG
    return data + (id % length);
}


template <class T>
T Registry<T>::get(const std::string& name) const {
    #ifdef _DEBUG
    // Allowing it to assert here lets me know this was
    // called directly, not getID().
    assert(nameMap.contains(name));
    #endif // _DEBUG
    return get(getID(name));
}


template <class T>
T& Registry<T>::getRef(const std::string& name) const {
    #ifdef _DEBUG
    // Allowing it to assert here lets me know this was
    // called directly, not getID().
    assert(nameMap.contains(name));
    #endif // _DEBUG
    return getRef(getID(name));
}


template <class T>
T* Registry<T>::getPtr(const std::string& name) const {
    #ifdef _DEBUG
    // Allowing it to assert here lets me know this was
    // called directly, not getID().
    assert(nameMap.contains(name));
    #endif // _DEBUG
    return getPtr(getID(name));
}


template <class T>
bool Registry<T>::contains(const std::string& name) {
    return nameMap.contains(name);
}


}
