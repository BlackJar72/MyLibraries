#include "MemoryPool.h"

using namespace MemoryPool;


template <class T, std::size_t SIZE>
ObjectPool<T, SIZE>::ObjectPool() {
    head = data;
    for(int i = 1; i < SIZE; i++) {
        data[i - 1].used = false;
        data[i - 1].link.next = &data[i];
    }
    data[SIZE - 1].used = false;
    data[SIZE - 1].link.next = 0;
}


template <class T, std::size_t SIZE>
ObjectPool<T, SIZE>::~ObjectPool() {}


/**
 * Add a element of type T to the pool, using the default
 * constructor.
 *
 * This will return a pointer to the elements in the
 * pool.  As usually, care should be taken in managing
 * the pointer, as it can point to invalid data if
 * the element is removed.  Under no circumstance should
 * free or delete EVER be called on the pointer, as this would
 * be dangerous undefine behavior (freeing memory in the
 * in the middle of and array that still exists).
 *
 * If the element could not be added a null pointer will be
 * returned.
 */
template <class T, std::size_t SIZE>
T* ObjectPool<T, SIZE>::add() {
    T* out = head;
    if(head) {
        head->link.element.T();
        head->used = true;
        head = head->link.next;
    }
    return out;
}


/**
 * Add a value of type T to the pool.  If the pool
 * is full, nothing will happen.  This is done by
 * copying the data of the passed in object.
 *
 * This will return a pointer to the elements in the
 * pool.  As usual, care should be taken in managing
 * the pointer, as it can point to invalid data if
 * the element is removed.  Under no circumstance should
 * free or delete EVER be called on the pointer, as this would
 * be dangerous undefine behavior (freeing memory in the
 * in the middle of and array that still exists).
 *
 * If the element could not be added a null pointer will be
 * returned.
 */
template <class T, std::size_t SIZE>
T* ObjectPool<T, SIZE>::add(const T& added) {
    T* out = head;
    if(head) {
        head->link.element = added;
        head->used = true;
        head = head->link.next;
    }
    return out;
}


/**
 * This will return a pointer to the element of
 * next slot in the pool.  This is for calling
 * non-default constructors or passing to specialized
 * factories.  The element will not be initialized
 * in any way when returned.
 *
 * If there is no room in the pool this will return a
 * null pointer; its is would be wise to check for this
 * before actually calling the constructor, or check
 * with isFull() before calling this.
 */
template <class T, std::size_t SIZE>
T* ObjectPool<T, SIZE>::nextSlot() {
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
void ObjectPool<T, SIZE>::remove(const std::size_t index) {
    #ifdef _DEBUG
    assert((index < SIZE) && !data[index].link.unused);
    #endif // _DEBUG
    data[index].link.element.~T();
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
bool ObjectPool<T, SIZE>::removeSafe(const std::size_t index) {
    bool out = (index < SIZE) && !data[index].link.unused;
    if(out) {
        remove(index);
    }
    return out;
}


/**
 * This will free the element referenced by the supplied
 * pointer.  Using a pointer to anything outside the list
 * is undefined (and dangerous), calling this on an inactive
 * element will break the pool.  Use with caution.
 *
 * This essentially the pool's local equivalent to delete.
 */
template <class T, std::size_t SIZE>
void ObjectPool<T, SIZE>::remove(T* ptr) {
    int index = (ptr - data) / sizeof(T);
    #ifdef _DEBUG
    assert((index < SIZE) && !data[index].link.unused);
    #endif // _DEBUG
    data[index].link.element.~T();
    data[index].link.next = head;
    data[index].used = false;
    head = data + index;
}


/**
 * This will free an element for reused, but only it it
 * is currently in use and a valid part of the pool.
 *
 * This a much safer and preferable method of deleting
 * pool elements.  This returns true if the element was
 * removed, or false if it was not in the pool or in not
 * use.
 */
template <class T, std::size_t SIZE>
bool ObjectPool<T, SIZE>::removeSafe(T* ptr) {
    int index = (ptr - data) / sizeof(T);
    bool out = (index < SIZE) && !data[index].link.unused;
    if(out) {
        remove(index);
    }
    return out;
}


/**
 * This will clear all elements from the pool. This will
 * also call the destructors of each element stored.
 */
template <class T, std::size_t SIZE>
void ObjectPool<T, SIZE>::clearSafe() {
    for(int i = 1; i < SIZE; i++) {
        if(data[i - 1].used) {
            data[i - 1].link.element.~T();
        }
        data[i - 1].used = false;
        data[i - 1].link.next = &data[i];
    }
        if(data[SIZE - 1].used) {
            data[SIZE - 1].link.element.~T();
        }
    data[SIZE - 1].used = false;
    data[SIZE - 1].link.next = 0;
}


/**
 * This will return the total capacity of the pool.
 */
template <class T, std::size_t SIZE>
std::size_t ObjectPool<T, SIZE>::capacity() const {
    return SIZE;
}


/**
 * This will tell if the pool is full / used up, with
 * no current room for more elements to be stored.
 * Technically true of the head of the empty elements
 * list is a null pointer.
 */
template <class T, std::size_t SIZE>
bool ObjectPool<T, SIZE>::isFull() const {
    return (head == 0); // To 1 or 0, not full address.
}


/**
 * This will clear all elements from the pool.  No
 * destructors will be called.
 */
template <class T, std::size_t SIZE>
void ObjectPool<T, SIZE>::clear() {
    for(int i = 1; i < SIZE; i++) {
        data[i - 1].used = false;
        data[i - 1].link.next = &data[i];
    }
    data[SIZE - 1].used = false;
    data[SIZE - 1].link.next = 0;
}


/**
 * This will return true if the element at that index is
 * valid / in use (which is the same thing) or false if it
 * is not.
 */
template <class T, std::size_t SIZE>
bool ObjectPool<T, SIZE>::isValid(const std::size_t index) const {
    return ((index < SIZE) && data[index].used);
}


/**
 * Get reference to the elements at the index for
 * use elsewhere.  There is no bounds checking of
 * any kind, so be careful.  There is no guarantee
 * the object returned is valid.
 */
template <class T, std::size_t SIZE>
T& ObjectPool<T, SIZE>::get(const std::size_t index) const {
    #ifdef _DEBUG
    assert((index < SIZE) && data[index].used);
    #endif // _DEBUG
    return data[index].link.element;
}


/**
 * Get and element at an index using array notation.
 * Note that while this will not go out of bounds,
 * for efficiency it is not really bounds checked, but
 * will instead wrap around to the beginning.
 * There is no guarantee the object returned is valid.
 */
template <class T, std::size_t SIZE>
T& ObjectPool<T, SIZE>::operator[](const std::size_t index) const {
    #ifdef _DEBUG
    assert((index < SIZE) && data[index].used);
    #endif // _DEBUG
    return data[index % SIZE].link.element;
};

