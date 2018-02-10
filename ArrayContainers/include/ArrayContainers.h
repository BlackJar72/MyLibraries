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

unsigned int stringHash(const std::string &s);
unsigned int wstringHash(const std::wstring &s);
unsigned int stringHash(char* data);

template <class T>
unsigned int genericHash(const T& data);


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
    // This class is *ONLY* to be used with StringHashNode
    friend class StringHashTable;
    private:
        StringHashNode();
        StringHashNode(const std::string& key, const T& value);
        virtual ~StringHashNode();

        const std::string key;
        T value;
        const unsigned int hash;
        mutable StringHashNode<T>* next;

        void add(const std::string& key, const T& value);
        bool matches(const std::string& key) const;
        bool isEmpty() const;
        StringHashNode<T>* getNextNode();
        void remove(const std::string& key);
        T& get(const std::string& key);
        bool contains(const std::string& key) const;
        unsigned int getHash() const;
        StringHashNode<T>* tryAdd(const std::string& key, const T& value,
                StringHashNode* target);
        StringHashNode<T>* tryRemove(const std::string& key,
                StringHashNode* target, StringHashNode* previous);
        void addNode(const StringHashNode<T>* node);
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
        ~StringHashTable();
        void add(const std::string& key, const T& value);
        void remove(const std::string& key);
        T get(const std::string& key) const;
        T& getRef(const std::string& key) const;
        T* getPtr(const std::string& key) const;
        bool contains(const std::string& key) const;
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
    public:
        Registry();
        Registry(size_t startSize);
        virtual ~Registry();
        unsigned int add(const std::string& name, const T& t);
        unsigned int getID(const std::string& name) const;
        // These are for raw speed, and are the main reason for thisS
        inline T get(unsigned int id) const {
            #ifdef _DEBUG
            assert((id < 0) || (id >= elements));
            #endif // _DEBUG
            return data[id];
        }
        inline T& getRef(unsigned int id) const {
            #ifdef _DEBUG
            assert((id < 0) || (id >= elements));
            #endif // _DEBUG
            return data[id];

        }
        inline T* getPtr(unsigned int id) const {
            #ifdef _DEBUG
            assert((id < 0) || (id >= elements));
            #endif // _DEBUG
            return data + id;
        }
        // These are slower but allow greater safety;
        // they will throw an index out of bounds exception.
        T getSafer(unsigned int id) const;
        T& getRefSafer(unsigned int id) const;
        T* getPtrSafer(unsigned int id) const;
        // These are for convenience but should not usually be
        // used -- they defeat the purpose of this class.
        T get(const std::string& name) const;
        T& getRef(const std::string& name) const;
        T* getPtr(const std::string& name) const;
        bool contains(const std::string& name);
    protected:
    private:
        T* data;
        StringHashTable<int> nameMap;
        size_t elements;
        size_t length;
        void grow();
        void shrink();
};

}
#endif // ARRAYCONTAINERS_H
