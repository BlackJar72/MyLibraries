#include "MemoryPool.h"
#include <assert.h>
#include <cstring>
#include <utility>

// TODO: Re-introduce and revamp this so that dynamic array doesn't do
// double duty as both fast and ordered array based collections.

using namespace MemoryPool;

template <class T, std::size_t SIZE>
UnorderedArray<T, SIZE>::UnorderedArray() : elements(0), position(0) {}


template <class T, std::size_t SIZE>
UnorderedArray<T, SIZE>::~UnorderedArray() {}


/**
 * Add an element to the pool.
 */
template <class T, std::size_t SIZE>
template <typename... Args>
void UnorderedArray<T, SIZE>::add(Args&&... args) {
    #ifdef _DEBUG
    assert(elements < SIZE);
    #endif // _DEBUG
    data[elements].T(std::forward<Args>(args)...);
    elements++;
}


/**
 * Remove the element at the array index from the pool.
 */
template <class T, std::size_t SIZE>
void UnorderedArray<T, SIZE>::remove(const std::size_t index) {
    #ifdef _DEBUG
    assert((index < SIZE));
    #endif // _DEBUG
    data[index].~T;
    data[index] = data[elements];
    data[elements].~T;
    elements--;
}


/**
 * Remove the last retrieved elements from the pool.
 */
template <class T, std::size_t SIZE>
void UnorderedArray<T, SIZE>::removePrevious() {
    #ifdef _DEBUG
    assert(position > 0);
    #endif // _DEBUG
    data[position - 1].~T;
    data[position - 1] = data[elements];
    data[elements].~T;
    elements--;
}


/**
 * Returns the current number of elements in the pool.
 */
template <class T, std::size_t SIZE>
std::size_t UnorderedArray<T, SIZE>::size() const {
    return elements;
}


/**
 * Return the total number of elements the pool can hold.
 */
template <class T, std::size_t SIZE>
std::size_t UnorderedArray<T, SIZE>::capacity() const {
    return SIZE;
}


/**
 * Return the number of elements that can currently be
 * added to the pool, that is the capacity minus the
 * number already stored.
 */
template <class T, std::size_t SIZE>
std::size_t UnorderedArray<T, SIZE>::room() const {
    return SIZE - elements;
}


/**
 * True if there is room for more elements.
 */
template <class T, std::size_t SIZE>
bool UnorderedArray<T, SIZE>::isFull() const {
    return  elements == SIZE;
}


/**
 * True if there is room for more elements.
 */
template <class T, std::size_t SIZE>
bool UnorderedArray<T, SIZE>::isEmpty() const {
    return  elements == 0;
}


/**
 * Return a reference to the elements at the supplied index.
 * WARNING: This does no range checking of any kind.  You
 * have been warned.
 */
template <class T, std::size_t SIZE>
T& UnorderedArray<T, SIZE>::get(const std::size_t index) const {
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
template <class T, std::size_t SIZE>
T& UnorderedArray<T, SIZE>::getNext() const {
    // FIXME: I should have error checking in debug mode!
    return data[position++];
}


/**
 * This will return if there are more elements in the
 * pool which could be retrieved with getNext().
 */
template <class T, std::size_t SIZE>
bool UnorderedArray<T, SIZE>::hasMore() const {
    return position < elements;
}


/**
 * Resets the elements which will be returned by
 * getNext() to the beginning (element 0).
 */
template <class T, std::size_t SIZE>
void UnorderedArray<T, SIZE>::reset() const {
    position = 0;
}


/**
 * This will clear all elements from the pool.  It will
 * not call their destructors (they are simply marked for
 * reuse), so if any destructor based clean-up is needed
 * the pool should be iterated and destructors called
 * before clearing the pool.
 */
template <class T, std::size_t SIZE>
void UnorderedArray<T, SIZE>::clear(){
    position = elements = 0;
}


/**
 * Returns the currently stored elements as an
 * array.
 */
template <class T, std::size_t SIZE>
const T* UnorderedArray<T, SIZE>::getArray() const {
    T* out = new T[elements];
    memccpy(out, data, elements * sizeof(T));
}


/**
 * Access elements of the pool as using array notation.  Not
 * that this does not do true range checking, but will wrap
 * around to 0 after the next element.  You have been warned.
 * Also remember that the order is not constant.  This is mostly
 * for use in loops.
 */
template <class T, std::size_t SIZE>
T& UnorderedArray<T, SIZE>::operator[](const std::size_t index) const {
    #ifdef _DEBUG
    assert(index < elements);
    #endif // _DEBUG
    return data[index % elements];
}
