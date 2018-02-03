#ifndef ARRAYCONTAINERS_H
#define ARRAYCONTAINERS_H
#include <string>

namespace ArrayContainers {

class IndexOutOfBound {
    public:
        IndexOutOfBound();
        IndexOutOfBound(const std::string src);
        const std::string getSource() const;
        virtual ~IndexOutOfBound();
    protected:
    private:
        std::string source;
};

unsigned int StringHash(const std::string &s);
unsigned int StringHash(char* data);

template <class T>
unsigned int GenericHash(const T& data);


/**
 * A dynamic array class similar to Java's ArrayList in
 * many ways, but with some features distinct from both
 * ArrayList and the standard C++ vector.  Notably, it
 * has both order-preserving (slower) and fast (non-order
 * preserving) method variation, allowing it to be used both
 * as an ordered list and as a fast, unordered, iteratable
 * collection.
 */
 // TODO / FIXME: Add iterators, since many people like them.
 // FIXME: Maybe this actually should be two classes, for the fast vs. ordered versions?
template <class T>
class DynamicArray {
    public:
        DynamicArray<T>();
        DynamicArray<T>(int initialSize);
        DynamicArray<T>(const DynamicArray<T>& a);
        virtual ~DynamicArray();
        DynamicArray<T> copy();
        void add(const T& added);
        void add(const T& added, unsigned int index);
        void set(const T& added, unsigned int index);
        T& get(const unsigned int index) const;
        T& peek();
        T& getNext();
        T& getNextWrap();
        void remove(unsigned int index);
        void removeFast(unsigned int index);
        void removeAll(const T &in);
        void removeAllFast(const T &in);
        bool hasMore() const;
        unsigned int size() const;
        unsigned int currentCapacity() const;
        const T* getArray() const;
        void reset() const;
        T& operator[](const unsigned int index) const;
    protected:
    private:
        T* data;
        static const T* empty;
        unsigned int elements;  // The number of elements stored
        unsigned int length;    // The size of the array
        unsigned mutable int position;  // The current element for getNext()
        void grow();
        void shrink();
};


/**
 * This is a helper class to hold the data, allowing
 * it to act as a singly linked list in case of either
 * hash collision or simple slot collisions.
 */
template <class T>
class StringHashNode {
    public:
        StringHashNode();
        StringHashNode(const std::string& key, const T& value);
        void add(const std::string& key, const T& value);
        bool matches(const std::string& key) const;
        bool isEmpty() const;
        // For removal of first node
        StringHashNode<T>* getNextNode();
        // For removal of other nodes
        void remove(const std::string& key);
        T& get(const std::string& key);
        bool contains(const std::string& key) const;
        virtual ~StringHashNode();
    private:
        const std::string key;
        const T value;
        const unsigned int hash;
        mutable StringHashNode<T>* next;
        StringHashNode<T>* tryAdd(const std::string& key, const T& value,
                StringHashNode* target);
        StringHashNode<T>* tryRemove(const std::string& key,
                StringHashNode* target, StringHashNode* previous);
};


/**
 * A hash table mapping string to type T
 * this will be use in the registry class
 * below to map strings to ints (indicies).
 */
template <class T>
class StringHashTable {
    public:
        StringHashTable();
        StringHashTable(size_t startSize);
        void add(const std::string& key, const T& value);
        void remove(const std::string& key);
        T get(const std::string& key);
        bool contains(const std::string& key);
    protected:
    private:
        StringHashNode<T>* data;
        size_t arrayLength;
        size_t capacity;
        size_t length;
        const size_t minLength;
        size_t shrinkSize;
        void grow();
        void shrink();
        void rebucket(StringHashNode<T>* oldData, const size_t oldLen);
        void makeInternalData(size_t newLength);
};


/**
 * A resources locater class mapping string to both ints and
 * to type T (through the ints, as indices).  In use the ints
 * should be gotten and cached for fast access to the underlying
 * resource (objects of type T).  For example, to load and find
 * images or models by a human-friendly name, but then access
 * them with array-like speed in performance critical use.
 */
template <class T>
class Registry {
    // TODO:  Needs more planning; will use and array for data and a
    // hash table or strings to indices within the first array.
    public:
        Registry();
        virtual ~Registry();
    protected:
    private:
        T* data;
        //StringHashTable<int> nameMap;
        void grow();
};

}
#endif // ARRAYCONTAINERS_H
