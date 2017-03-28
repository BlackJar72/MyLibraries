#ifndef ARRAYCONTAINERS_H
#define ARRAYCONTAINERS_H
#include <string>

namespace ArrayContainers {

class IndexOutOfBound {
    public:
        IndexOutOfBound();
        virtual ~IndexOutOfBound();
    protected:
    private:
};

unsigned int StringHash(const std::string &s);

template <class T>
class DynamicArray {
    public:
        DynamicArray();
        virtual ~DynamicArray();
        void add(T added);
        void add(T added, unsigned int index);
        void set(T added, unsigned int index);
        T get(const unsigned int index) const;
        T peek();
        T getNext();
        T getNextWrap();
        void remove(unsigned int index);
        void removeFast(unsigned int index);
        void removeAll(const T &in);
        void removeAllFast(const T &in);
        bool hasMore() const;
        unsigned int size() const;
        const T* getArray() const;
        void reset(); // Sets position for getNext() to 0
        const T& operator[](const unsigned int index) const;
    protected:
    private:
        T* data;
        static const int INIT_SIZE;
        static const float GROWTH_FACTOR;
        static const float SHRINK_FACTOR;
        static const float SHRINK_THRESHOLD;
        unsigned int elements;  // The number of elements stored
        unsigned int length;    // The size of the array
        unsigned int position;  // The current element for getNext()
        void grow();
        void shrink();
};

/*-------------------------------------------------------------*
 *      SERIOUSLY CONSIDERING BREAKING THIS INTO PIECES        *
 *-------------------------------------------------------------*/


// This is a helper class to hold the data, allowing
// it to act as a singly linked list in case of either
// hash collision or simple slot collisions.
template <class T>
class Node {
    public:
        Node(std::string key, T value);
        void add(std::string key, T value);
        // Used in removal to check if the first should be removed
        bool matchs(std::string key);
        // For removal of first node
        Node<T>* getNextNode();
        // For removal of other nodes
        void remove(std::string key);
        T get(std::string key);
        virtual ~Node();
    private:
        Node();
        std::string key;
        T value;
        Node<T>* next;
};


// A hash table mapping string to type T
// this will be use in the registry class
// below to map strings to ints (indicies).
template <class T>
class StringHashTable {
    public:
        StringHashTable();
        virtual ~StringHashTable();
    protected:
    private:
};


// A resources locater class mapping string to both ints and
// to type T (through the ints, as indices).  In use the ints
// should be gotten and cached for fast access to the underlying
// resource (objects of type T).  For example, to load and find
// images or models by a human-friendly name, but then access
// them with array-like speed in performance critical use.
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
        void grow();
};

}
#endif // ARRAYCONTAINERS_H
