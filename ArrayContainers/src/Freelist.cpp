#include "MemoryPool.h"

using namespace MemoryPool;

template <class T, std::size_t SIZE>
Freelist<T, SIZE>::Freelist() {
    head = data;
    for(int i = 1; i < SIZE; i++) {
        data[i - 1].used = false;
        data[i - 1].link.next = &data[i];
    }
    data[SIZE - 1].used = false;
    data[SIZE - 1].link.next = 0;
}


template <class T, std::size_t SIZE>
Freelist<T, SIZE>::~Freelist() {
    delete[] data;
}


/**
 * Add a new element of type T to the pool,
 * using the default constructor.
 */
template <class T, std::size_t SIZE>
void Freelist<T, SIZE>::add() {
    if(head) {
        head->link.element.T();
        head->used = true;
        head = head->link.next;
    }
}


/**
 * Add a value of type T to the pool.  If the pool
 * is full, nothing will happen.  This is done by
 * copying the object.
 */
template <class T, std::size_t SIZE>
void Freelist<T, SIZE>::add(const T& added) {
    if(head) {
        head->link.element = added;
        head->used = true;
        head = head->link.next;
    }
}


/**
 * Create a new element using the default constructor.
 * If there was room for the new element this will
 * return true, otherwise it will return false.
 */
template <class T, std::size_t SIZE>
bool Freelist<T, SIZE>::addSafe() {
    if(head) {
        head->element.T();
        head->used = true;
        head = head->link.next;
        return true;
    }
    return false;
}


/**
 * Add a value of type T to the pool.  If the pool
 * this will return false (failure), other wise it will
 * return true (successfully added).
 */
template <class T, std::size_t SIZE>
bool Freelist<T, SIZE>::addSafe(const T& added) {
    if(head) {
        head->element = added;
        head->used = true;
        head = head->link.next;
        return true;
    }
    return false;
}


/**
 * This will return a pointer to the elements of
 * next slot in the pool.  This is for calling
 * non-default constructors or passing to specialized
 * factories.  This does not in itself do anything to
 * initialize the contents of the slot, so if it is
 * not initialized afterward it will point to invalid
 * data.
 */
template <class T, std::size_t SIZE>
T* Freelist<T, SIZE>::nextSlot() {
    T* out = head;
    if(head) {
        head->used = true;
        head = head->link.next;
    }
    return out;
}


/**
 * This will free the element at the given index to be
 * reused.  It will not check if the element is already
 * free; use this only if the element has already been
 * checked or you somehow otherwise know it is.
 */
template <class T, std::size_t SIZE>
void Freelist<T, SIZE>::remove(const std::size_t index) {
    #ifdef _DEBUG
    assert((index < SIZE) && !data[index].link.unused);
    #endif // _DEBUG
    data[index].link.next = head;
    data[index].used = false;
    head = data + index;
}


/**
 * This will free an element for reused, but only it it
 * is currently in use.  This returns true if the element was
 * removed, or false if it was not in the pool or in not
 * use.
 */
template <class T, std::size_t SIZE>
bool Freelist<T, SIZE>::removeSafe(const std::size_t index) {
    bool out = (index < SIZE) && !data[index].link.unused;
    if(out) {
        remove(index);
    }
    return out;
}


/**
 * This will return the total capacity of the pool.
 */
template <class T, std::size_t SIZE>
std::size_t Freelist<T, SIZE>::capacity() const {
    return SIZE;
}


/**
 * This will tell if the pool is full / used up, with
 * no current room for more elements to be stored.
 * Technically true of the head of the empty elements
 * list is a null pointer.
 */
template <class T, std::size_t SIZE>
bool Freelist<T, SIZE>::isFull() const {
    return head == 0;
}


/**
 * This will clear all elements from the pool.  It will
 * not call their destructors (they are simply marked for
 * reuse), so if any destructor based clean-up is needed
 * the pool should be iterated and destructors called
 * before clearing the pool.
 */
template <class T, std::size_t SIZE>
void Freelist<T, SIZE>::clear() {
    for(int i = 1; i < SIZE; i++) {
        data[i - 1].used = false;
        data[i - 1].link.next = &data[i];
    }
    data[SIZE - 1].used = false;
    data[SIZE - 1].link.next = 0;
}



/**
 * Get the FreelistElement at the index.
 * There is no bounds checking of any kind, so be careful.
 *
 * This is especially useful for iterating the elements,
 * as the full element is return and its validity my be
 * checked.  The used tag may be compared but should
 * never be changed.
 */
template <class T, std::size_t SIZE>
FreelistElement<T>& Freelist<T, SIZE>::get(const std::size_t index) const {
    #ifdef _DEBUG
    assert(((index < SIZE));
    #endif // _DEBUG
    return data[index];
}


/**
 * Get and FreelistElement at an index using array notation.
 * Note that while this will not go out of bounds,
 * for efficiency it is not really bounds checked, but
 * will instead wrap around to the beginning.
 */
template <class T, std::size_t SIZE>
FreelistElement<T>& Freelist<T, SIZE>::operator[](const std::size_t index) const {
    #ifdef _DEBUG
    assert((index < SIZE));
    #endif // _DEBUG
    return data[index % SIZE];
};

