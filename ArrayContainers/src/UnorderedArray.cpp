#include "MemoryPool.h"
#include <assert.h>
#include <cstring>

using namespace MemoryPool;

template <class T>
UnorderedArray<T>::UnorderedArray(const unsigned int capacity) :
        length(capacity), elements(0), position(0) {
    data = new T[capacity];
}


template <class T>
UnorderedArray<T>::~UnorderedArray() {}


/**
 * Add an element to the pool.
 */
template <class T>
void UnorderedArray<T>::add() {
    #ifdef _DEBUG
    assert(elements < length);
    #endif // _DEBUG
    data[elements].T();
    elements++;
}



/**
 * Add an element to the pool.
 */
template <class T>
void UnorderedArray<T>::add(const T& added) {
    #ifdef _DEBUG
    assert(elements < length);
    #endif // _DEBUG
    data[elements] = added;
    elements++;
}


/**
 * This will return a pointer to the elements of
 * next slot in the pool.  This is for calling
 * non-default constructors or passing to specialized
 * factories.
 */
template <class T>
T* UnorderedArray<T>::nextSlot() {
    #ifdef _DEBUG
    assert(elements < length);
    #endif // _DEBUG
    return *data[elements++];
}


/**
 * Remove the element at the array index from the pool.
 */
template <class T>
void UnorderedArray<T>::remove(const unsigned int index) {
    #ifdef _DEBUG
    assert((index < length));
    #endif // _DEBUG
    data[index] = data[--elements];
}


/**
 * Remove the last retrieved elements from the pool.
 */
template <class T>
void UnorderedArray<T>::removePrevious() {
    #ifdef _DEBUG
    assert(position > 0);
    #endif // _DEBUG
    data[position - 1] = data[--elements];
}


/**
 * Returns the current number of elements in the pool.
 */
template <class T>
unsigned int UnorderedArray<T>::size() const {
    return elements;
}


/**
 * Return the total number of elements the pool can hold.
 */
template <class T>
unsigned int UnorderedArray<T>::capacity() const {
    return length;
}


/**
 * Return the number of elements that can currently be
 * added to the pool, that is the capacity minus the
 * number already stored.
 */
template <class T>
unsigned int UnorderedArray<T>::room() const {
    return length - elements;
}


/**
 * True if there is room for more elements.
 */
template <class T>
bool UnorderedArray<T>::isFull() const {
    return  elements == length;
}


/**
 * True if there is room for more elements.
 */
template <class T>
bool UnorderedArray<T>::isEmpty() const {
    return  elements == 0;
}


/**
 * Return a reference to the elements at the supplied index.
 * WARNING: This does no range checking of any kind.  You
 * have been warned.
 */
template <class T>
T& UnorderedArray<T>::get(const unsigned int index) const {
    #ifdef _DEBUG
    assert(index < elements);
    #endif // _DEBUG
    return data[index];
}


/**
 * Returns the next element from the pool, started from the
 * beginning at elements 0.  This allows a simple alternate
 * way to iterate through the pool.
 */
template <class T>
T& UnorderedArray<T>::getNext() const {
    #ifdef _DEBUG
    asset(position < elements);
    #endif // _DEBUG
    return data[position++];
}


/**
 * This will return if there are more elements in the
 * pool which could be retrieved with getNext().
 */
template <class T>
bool UnorderedArray<T>::hasMore() const {
    return position < elements;
}


/**
 * Resets the elements which will be returned by
 * getNext() to the beginning (element 0).
 */
template <class T>
void UnorderedArray<T>::reset() const {
    position = 0;
}


/**
 * This will clear all elements from the pool.  It will
 * not call their destructors (they are simply marked for
 * reuse), so if any destructor based clean-up is needed
 * the pool should be iterated and destructors called
 * before clearing the pool.
 */
template <class T>
void UnorderedArray<T>::clear(){
    position = elements = 0;
}


/**
 * Returns the currently stored elements as an
 * array.
 */
template <class T>
const T* UnorderedArray<T>::getArray() const {
    T* out = new T[elements];
    memccpy(out, data, elements * sizeof(T));
}


/**
 * Access elements of the pool as using array notation.  Not
 * that this does not do true range checking, but will wrap
 * around to 0 after the next element.  You have been warned.
 */
template <class T>
T& UnorderedArray<T>::operator[](const unsigned int index) const {
    #ifdef _DEBUG
    assert(index < elements);
    #endif // _DEBUG
    return data[index % elements];
}
