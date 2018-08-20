#ifndef ARRAYCONTAINERS_H
#define ARRAYCONTAINERS_H
#include <string>
#include <unordered_map>

namespace ArrayContainers {

// Fixme: There is an STL base exception this should extend
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
 *
 * This should probably be used primarily for its fast removal
 * methods, as a dynamic variant of FastArray, while basic
 * dynamic arrays should usually be std::vector's.
 */
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
        template <typename... Args>
        void emplace(Args&&... args);
        template <typename... Args>
        void emplaceAt(unsigned int index, Args&&... args);
        template <typename... Args>
        void setNew(unsigned int index, Args&&... args);
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
        inline T* begin() {return data;}
        inline T* end() {return (data + elements);}
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
 * A resources locater class mapping string to both ints and
 * to type T (through the ints, as indices).  In use the ints
 * should be gotten and cached for fast access to the underlying
 * resource (objects of type T).  For example, to load and find
 * images or models by a human-friendly name, but then access
 * them with array-like speed in performance critical use.
 */
 // This really should be redone useing stl unordered_map instead
 // of StringHashTable.  It is however, a potentially *VERY* useful
 // class to have in some situations.
template <class T>
class Registry {
    private:
        T* data;
        std::unordered_map<std::string, unsigned int>  nameMap;
        size_t elements;
        size_t length;
        void grow();
    protected:
    public:
        Registry();
        Registry(size_t startSize);
        virtual ~Registry();
        unsigned int add(const std::string& name, const T& t);
        template <typename... Args>
        unsigned int emplace(const std::string& name, Args&&... args);
        unsigned int getID(const std::string& name) const;
        // FIXME: These next three still need some error checking in debug builds
        inline T get(unsigned int id) const { return data[id]; };
        inline T& getRef(unsigned int id) const { return data[id]; };
        inline T* getPtr(unsigned int id) const { return data + id; };
        T getSafer(unsigned int id) const;
        T& getRefSafer(unsigned int id) const;
        T* getPtrSafer(unsigned int id) const;
        T get(const std::string& name) const;
        T& getRef(const std::string& name) const;
        T* getPtr(const std::string& name) const;
        bool contains(const std::string& name) const;
        void clear();
        inline T* begin() {return data;}
        inline T* end() {return (data + elements);}
};

}
#endif // ARRAYCONTAINERS_H
