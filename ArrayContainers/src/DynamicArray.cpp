#include "ArrayContainers.h"
#include <cstring>
#include <iostream>
#include <string>
#include <assert.h>

// FIXME?: I probably should have the fast non-ordered and
// the ordered versions as separate classes...?

namespace ArrayContainers {

const int   D_ARRAY_INIT_SIZE = 16;
const float D_ARRAY_GROWTH_FACTOR = 1.5;
const float D_ARRAY_SHRINK_FACTOR = 0.5;
const float D_ARRAY_SHRINK_THRESHOLD = 0.25;


template <class T>
DynamicArray<T>::DynamicArray() {
    length = D_ARRAY_INIT_SIZE;
    position = elements = 0;
    data = new T[length];
}


template <class T>
DynamicArray<T>::DynamicArray(int initialSize) {
    length = initialSize;
    position = elements = 0;
    data = new T[length];
}


template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& a) : data(new T[a.length]) {
    // Considered making a move contructor, ran into trouble :(
    memccpy(data, a.data, a.elements * sizeof(T));
}


/**
 * This does not delete objects that are stored; if
 * such objects are of a type that requires deletion
 * this must be done separately.
 */

template <class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}


template <class T>
DynamicArray<T> DynamicArray<T>::copy() {
    DynamicArray<T> out(length);
    memccpy(out.data, data, elements * sizeof(T));
    return out; // Mover constructor should get the data out effectively.
}


template <class T>
void DynamicArray<T>::grow() {
    length *= D_ARRAY_GROWTH_FACTOR;
    T* bigger = new T(length);
    memcpy(bigger, data, elements * sizeof(T));
    delete[] data;
    data = bigger;
}


template <class T>
void DynamicArray<T>::shrink() {
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
void DynamicArray<T>::add(const T& added) {
    data[elements] = added;
    elements++;
    if(elements >= length) {
        grow();
    }
}


template <class T>
void DynamicArray<T>::add(const T& added, unsigned int index) {
	#ifdef _DEBUG
    assert(index < elements);
	#endif
    if(index == elements) {
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
void DynamicArray<T>::set(const T& added, unsigned int index) {
	#ifdef _DEBUG
    assert(index < elements);
	#endif
	// Even when not compiled for debug you can't read outside the buffer
    data[index % elements].~T();
    data[index % elements] = added;
}


template <class T>
template <typename... Args>
void DynamicArray<T>::emplace(Args&&... args) {
    data[elements](std::forward<Args>(args)...);
    elements++;
    if(elements >= length) {
        grow();
    }
}


template <class T>
template <typename... Args>
void DynamicArray<T>::emplaceAt(unsigned int index, Args&&... args) {
	#ifdef _DEBUG
    assert(index < elements);
	#endif
    if(index == elements) {
        data[elements](std::forward<Args>(args)...);
        elements++;
        if(elements >= length) {
            grow();
        }
    } else {
        elements++;
        if(elements >= length) {
            grow();
        }
        for(unsigned int i = index; i < (elements - 1); i++) {
            data[i+1] = data[i];
        }
        data[index](std::forward<Args>(args)...);
    }
}


template <class T>
template <typename... Args>
void DynamicArray<T>::setNew(unsigned int index, Args&&... args) {
	#ifdef _DEBUG
    assert(index < elements);
	#endif
	// Even when not compiled for debug you can't read outside the buffer
    data[index % elements].~T();
    data[index % elements](std::forward<Args>(args)...);
}


template <class T>
unsigned int DynamicArray<T>::size() const {
    return elements;
}


template <class T>
unsigned int DynamicArray<T>::currentCapacity() const {
    return length;
}


template <class T>
bool DynamicArray<T>::hasMore() const {
    return (position < elements);
}


template <class T>
void DynamicArray<T>::reset() const {
    position = 0;
}


template <class T>
T& DynamicArray<T>::peek() {
	#ifdef _DEBUG
    assert(index < elements);
	#endif
	// Even when not compiled for release you still cannot read outside the buffer
    T* out = data + (position % elements);
    return *out;
}


template <class T>
T& DynamicArray<T>::get(const unsigned int index) const {
	#ifdef _DEBUG
    assert(index < elements);
	#endif
	// Even when not compiled for release buffer cannot read outside the buffer
    return data[index % elements];
}


template <class T>
T& DynamicArray<T>::getNext() {
    if(position >= elements) {
        throw IndexOutOfBound(std::string("T DynamicArray<T>::getNext()"));
    }
    T* out = data + position;
    position++;
	if(position == elements) {
		position--;
	}
    return *out;
}


template <class T>
T& DynamicArray<T>::getNextWrap() {
    if(position >= elements) {
            position = 0;
    }
    T* out = data + position;
    ++position;
	position %= elements;
    return *out;
}


template <class T>
void DynamicArray<T>::remove(unsigned int index) {
	#ifdef _DEBUG
    assert(index < elements);
	#endif
	// Even when not compiled for release you can't read / write outside the buffer
	index %= elements;
    for(unsigned int i = index + 1; i < elements; i++) {
        data[i-1] = data[i];
    }
    elements--;
    if(elements < ((length * D_ARRAY_SHRINK_THRESHOLD) + D_ARRAY_INIT_SIZE)) {
        shrink();
    }
}


template <class T>
void DynamicArray<T>::removeFast(unsigned int index) {
	#ifdef _DEBUG
    assert(index < elements);
	#endif
	// Even when not compiled for release you can't read / write outside the buffer
    data[index % elements] = data[elements - 1];
    elements--;
    if(elements < (length * D_ARRAY_SHRINK_THRESHOLD)) {
        shrink();
    }
}


template <class T>
void DynamicArray<T>::removeAll(const T &in) {
    unsigned int removed = 0;
    for(unsigned int i = 0; i < elements; i++) {
        bool match = (data[i] == in);
        if(removed & !match) {
            data[i - removed] = data[i];
        }
        if(match) {
            removed++;
        }
        elements -= removed;
    }
    if(elements < (length * D_ARRAY_SHRINK_THRESHOLD)) {
        shrink();
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
    if(elements < (length * D_ARRAY_SHRINK_THRESHOLD)) {
        shrink();
    }
}


/**
 * This is intended to get the array for use with
 * C libraries / APIs.
 */
template <class T>
const T* DynamicArray<T>::getArray() const {
    return data;
}


template <class T>
T& DynamicArray<T>::operator[](const unsigned int index) const {
	#ifdef _DEBUG
    assert(index < elements);
	#endif
	// Even when not compiled for release you can't read / write outside the buffer
    return data[index % elements];
}


}
