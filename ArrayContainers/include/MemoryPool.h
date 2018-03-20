#ifndef FREELIST_H
#define FREELIST_H

#include <memory>

/*
 * TODO: Custom iterators could be useful for all these.
 */

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
template <class T, std::size_t SIZE>
class Freelist
{
    public:
        Freelist();
        virtual ~Freelist();
        template <typename... Args>
        void add(Args&&... args);
        template <typename... Args>
        bool addSafe(Args&&... args);
        void remove(const std::size_t index);
        bool removeSafe(const std::size_t index);
        std::size_t capacity() const;
        bool isFull() const;
        void clear();
        void clearSafe();
        FreelistElement<T>& get(const std::size_t index) const;
        FreelistElement<T>& operator[](const std::size_t index) const;
    protected:
    private:
        const FreelistElement<T> data[SIZE];
        FreelistElement<T>* head;
};


/**
 * This is good if you need a to store larger object or
 * expect the pool to be fairly full most of the time,
 * or might need to reference stored objects individually
 * since pointers to added object are returned and may be
 * used to access object randomly.
 */
template <class T, std::size_t SIZE>
class ObjectPool
{
    public:
        ObjectPool();
        virtual ~ObjectPool();
        template <typename... Args>
        T* add(Args&&... args); // TODO: Use nerfed pointer clasee / custom iterator here
        void remove(const std::size_t index);
        bool removeSafe(const std::size_t index);
        void remove(T* ptr);
        bool removeSafe(T* ptr);
        void clear();
        void clearSafe();
        std::size_t capacity() const;
        bool isFull() const;
        bool isValid(const std::size_t  index) const;
        T& get(const std::size_t index) const;
        T& operator[](const std::size_t index) const;
    protected:
    private:
        const FreelistElement<T> data[SIZE];
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
template <class T, std::size_t SIZE>
class UnorderedArray
{
    public:
        UnorderedArray();
        virtual ~UnorderedArray();
        template <typename... Args>
        void add(Args&&... args);
        void remove(const std::size_t index);
        void removePrevious();
        std::size_t size() const;
        std::size_t capacity() const;
        std::size_t room() const;
        bool isFull() const;
        bool isEmpty() const;
        T& get(const std::size_t index) const;
        T& getNext() const;
        bool hasMore() const;
        void reset() const;
        void clear();
        const T* getArray() const;
        T& operator[](const std::size_t index) const;
        T& operator[](const unsigned int index) const;
        // TODO: Custom iterators instead of raw pointers
        inline T* begin() {return data;}
        inline T* end() {return (data + elements);}
    private:
        const T data[SIZE];
        std::size_t  elements;
        mutable std::size_t position;
};

}

#endif // SKIPLIST_H
