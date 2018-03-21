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
            nameMap(std::unordered_map<std::string, unsigned int>(D_MAP_INIT_SIZE)),
            elements(0),
            length(D_ARRAY_INIT_SIZE) {}


template <class T>
Registry<T>::Registry(size_t startSize) :
            data(new T[startSize]),
            nameMap(std::unordered_map<std::string, unsigned int>(((startSize * 4) / 3) + 1)),
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
unsigned int Registry<T>::add(const std::string& name, const T& t) {
    if(contains(name)) {
        size_t i = nameMap[name];
        data[i] = t;
    } else {
        nameMap.emplace(name, elements);
        data[elements++] = t;
        if(elements >= length) {
            grow();
        }
        return elements - 1;
    }
}


template <class T>
template <typename... Args>
unsigned int Registry<T>::emplace(const std::string& name, Args&&... args) {
    if(contains(name)) {
        size_t i = nameMap[name];
        data[i](std::forward<Args>(args)...);
    } else {
        nameMap.emplace(name, elements);
        data[elements++](std::forward<Args>(args)...);
        if(elements >= length) {
            grow();
        }
        return elements - 1;
    }
}

template <class T>
unsigned int Registry<T>::getID(const std::string& name) const {
    #ifdef _DEBUG
    assert(contains(name), "Out of bounds index sent to Registry::getID()");
    #endif // _DEBUG
    return nameMap.at(name);
}

template <class T>
T Registry<T>::getSafer(unsigned int id) const {
    #ifdef _DEBUG
    assert(id <= elements);
    #else
    if((id < 0) || (id > elements)) {
        std::string error = std::string("Out of bounds index of ");
        error.append(std::to_string(id));
        error.append(" in class method ArrayContainers::Registry::getSafer()");
        throw IndexOutOfBound(error);
    }
    #endif // _DEBUG
    return data[id % length];
}


template <class T>
T& Registry<T>::getRefSafer(unsigned int id) const {
    #ifdef _DEBUG
    assert(id <= elements);
    #else
    if((id < 0) || (id > elements)) {
        std::string error = std::string("Out of bounds index of ");
        error.append(std::to_string(id));
        error.append(" in class method ArrayContainers::Registry::getRefSafer()");
        throw new IndexOutOfBound(error);
    }
    #endif // _DEBUG
    return data[id % length];
}


template <class T>
T* Registry<T>::getPtrSafer(unsigned int id) const {
    #ifdef _DEBUG
    assert(id <= elements);
    #else
    if((id < 0) || (id > elements)) {
        std::string error = std::string("Out of bounds index of ");
        error.append(std::to_string(id));
        error.append(" in class method ArrayContainers::Registry::getPtrSafer()");
        throw new IndexOutOfBound(error);
    }
    #endif // _DEBUG
    return data + (id % length);
}


template <class T>
T Registry<T>::get(const std::string& name) const {
    #ifdef _DEBUG
    // Allowing it to assert here lets me know this was
    // called directly, not getID().
    assert(mapContains(name));
    #endif // _DEBUG
    return get(getID(name));
}


template <class T>
T& Registry<T>::getRef(const std::string& name) const {
    #ifdef _DEBUG
    // Allowing it to assert here lets me know this was
    // called directly, not getID().
    assert(mapContains(name));
    #endif // _DEBUG
    return getRef(getID(name));
}


template <class T>
T* Registry<T>::getPtr(const std::string& name) const {
    #ifdef _DEBUG
    // Allowing it to assert here lets me know this was
    // called directly, not getID().
    assert(mapContains(name));
    #endif // _DEBUG
    return getPtr(getID(name));
}


template <class T>
bool Registry<T>::contains(const std::string& name) const {
    return nameMap.find(name) != nameMap.end();
}


template <class T>
void Registry<T>::clear() {
    nameMap.clear();
    for(T element : data) {
        element.~T();
    }
    elements = 0;
}


}
