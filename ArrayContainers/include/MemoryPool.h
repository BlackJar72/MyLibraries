#ifndef FREELIST_H
#define FREELIST_H

#include <memory>


namespace MemoryPool {


/**
 * Simply holds an elements in a generic Freelist.  Note
 * that this is less memory efficient than a custom,
 * non-generic implementation cold be, but this is a
 * cost of being generic.
 */
template <class T>
struct FreelistElement
{
    bool used;
    union link {
        FreelistElement<T>* next;
        T element;
    };
};


/**
 * This is good if you need a to store larger object or
 * expect the pool to be fairly full most of the time,
 * and don't need to reference individual elements (i.e.,
 * you only need to iterate through the items).  Note that
 * the order is preserved, but there is no control of the
 * order in which new items are placed.
 */
template <class T>
class Freelist
{
    public:
        Freelist(const unsigned int capacity);
        virtual ~Freelist();
        void add();
        void add(const T& added);
        bool addSafe();
        bool addSafe(const T& added);
        T*   nextSlot();
        void remove(const unsigned int index);
        bool removeSafe(const unsigned int index);
        unsigned int capacity() const;
        bool isFull() const;
        void clear();
        void clearSafe();
        FreelistElement<T>& get(const unsigned int index) const;
        FreelistElement<T>& operator[](const unsigned int index) const;
    protected:
    private:
        const unsigned int length;
        const FreelistElement<T> data;
        FreelistElement<T>* head;
};


/**
 * This is good if you need a to store larger object or
 * expect the pool to be fairly full most of the time,
 * or might need to reference stored objects individually
 * since pointers to added object are returned and may be
 * used to access object randomly.
 */
template <class T>
class ObjectPool
{
    public:
        ObjectPool(const unsigned int capacity);
        virtual ~ObjectPool();
        T* add();
        T* add(const T& added);
        T* nextSlot();
        void remove(const unsigned int index);
        bool removeSafe(const unsigned int index);
        void remove(T* ptr);
        bool removeSafe(T* ptr);
        void clear();
        unsigned int capacity() const;
        bool isFull() const;
        bool isValid(const unsigned int index) const;
        T& get(const unsigned int index) const;
        T& operator[](const unsigned int index) const;
    protected:
    private:
        const unsigned int length;
        const FreelistElement<T>* data;
        FreelistElement<T>* head;
};


/**
 * This is good for small objects that can be copied quickly
 * and whose order does not matter.  This is especially good
 * if the number of items stored in the pools is highly
 * variable such the pool is often mostly empty, as it will
 * maintain good data locality and will not iterate elements
 * that are not in use.  (This could be handy for something
 * particle effects, which are typically small, spawn and
 * despawn frequently, and simply need to be rendered in
 * any order.)
 *
 * Note that because the order of items can change at any
 * time pointers into the unordered array and indices of
 * elements should never be cached and should be used with
 * caution -- generally this should be limited to using
 * indices to iterate the array.
 */
template <class T>
class UnorderedArray
{
    public:
        UnorderedArray(const unsigned int capacity);
        virtual ~UnorderedArray();
        void add();
        void add(const T& added);
        T*  nextSlot();
        void remove(const unsigned int index);
        void removePrevious();
        unsigned int size() const;
        unsigned int capacity() const;
        unsigned int room() const;
        bool isFull() const;
        bool isEmpty() const;
        T& get(const unsigned int index) const;
        T& getNext() const;
        bool hasMore() const;
        void reset() const;
        void clear();
        const T* getArray() const;
        T& operator[](const unsigned int index) const;
    protected:
    private:
        const unsigned int length;
        const T* data;
        unsigned int elements;
        unsigned mutable int position;
};

}

#endif // SKIPLIST_H
