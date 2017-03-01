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
        throw IndexOutOfBound();
    } else if(index == elements) {
        add(added);
    } else {
        elements++;
        if(elements >= length) {
            grow();
        }
        for(unsigned int i = index; i < (elements - 1); i++) {
            data[i+1] = data[i];
        }
        data[index] = added;
    }
}


template <class T>
void DynamicArray<T>::set(T added, unsigned int index) {
    if(index >= elements) {
        throw IndexOutOfBound();
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
T DynamicArray<T>::peek() {
    T* out = data + position;
    return *out;
}


template <class T>
T DynamicArray<T>::getNext() {
    if(position >= elements) {
        throw IndexOutOfBound();
    }
    T* out = data + position;
    position++;
    return *out;
}


template <class T>
T DynamicArray<T>::getNextWrap() {
    if(position >= elements) {
            position = 0;
    }
    T* out = data + position;
    position++;
    return *out;
}


template <class T>
T DynamicArray<T>::get(const unsigned int index) const {
    if(index >= elements) {
        throw IndexOutOfBound();
    }
    return data[index];
}


template <class T>
void DynamicArray<T>::remove(unsigned int index) {
    if(index >= elements) {
        throw IndexOutOfBound();
    }
    // Move all subsequent elements to preserve order
    for(unsigned int i = index + 1; i < elements; i++) {
        data[i-1] = data[i];
    }
    elements--;
}


template <class T>
void DynamicArray<T>::removeFast(unsigned int index) {
    if(index >= elements) {
        throw IndexOutOfBound();
    }
    // Swap with the last elements; sacrifice order for speed
    data[index] = data[elements - 1];
    elements--;
}


template <class T>
void DynamicArray<T>::removeAll(const T &in) {
    unsigned int removed = 0;
    for(unsigned int i = 0; i < elements; i++) {
        if(removed) {
            data[i - removed] = data[i];
        }
        if(data[i - removed] == in) {
            removed++;
        }
        elements -= removed;
    }
}


template <class T>
void DynamicArray<T>::removeAllFast(const T &in) {
    unsigned int removed = 0;
    for(unsigned int i = 0; i < elements; i++) {
        if(data[i] == in) {
            removed++;
            data[i] = data[elements - removed];
        }
        elements -= removed;
    }
}


}
