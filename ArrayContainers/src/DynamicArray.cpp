#include "ArrayContainers.h"
#include <cstring>

namespace ArrayContainers {

template <class T>
const int DynamicArray<T>::INIT_SIZE = 16;
template <class T>
const float DynamicArray<T>::GROWTH_FACTOR = 1.5;

template <class T>
DynamicArray<T>::DynamicArray() {
    length = INIT_SIZE;
    position = elements = 0;
    data = new T[length];
}


template <class T>
DynamicArray<T>::~DynamicArray() {
    delete data;
}


template <class T>
void DynamicArray<T>::grow() {
    length *= GROWTH_FACTOR;
    T* bigger = new T(length);
    memcpy(bigger, data, elements * sizeof(T));
    delete data;
    data = bigger;
}


template <class T>
void DynamicArray<T>::add(T added) {
    data[elements] = added;
    elements++;
    if(elements >= length) {
        grow();
    }
}


template <class T>
void DynamicArray<T>::add(T added, unsigned int index) {
    if(index > elements) {
        // index may be equal to elements; this would be the same as add(T).
        // TODO: Throw exception
        return;
    }
    // TDOD: Implement this
    elements++;
}


template <class T>
void DynamicArray<T>::set(T added, unsigned int index) {
    if(index >= elements) {
        // TODO: Throw execption
        return;
    }
    data[index] = added;
}


template <class T>
unsigned int DynamicArray<T>::size() const {
    return elements;
}


template <class T>
bool DynamicArray<T>::hasMore() const {
    return (position < elements);
}


template <class T>
void DynamicArray<T>::reset() {
    position = 0;
}


template <class T>
T DynamicArray<T>::getNext() {
    T* out = data + position;
    position++;
    return *out;
}


template <class T>
T DynamicArray<T>::get(const unsigned int index) const {
    if(index >= elements) {
        // TODO: Throw exception
        return data[0];
    }
    return data[index];
}


}
