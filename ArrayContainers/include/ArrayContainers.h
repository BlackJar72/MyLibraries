#ifndef ARRAYCONTAINERS_H
#define ARRAYCONTAINERS_H

namespace ArrayContainers {

template <class T>
class DynamicArray {
    public:
        DynamicArray();
        virtual ~DynamicArray();
        void add(T added);
        void add(T added, unsigned int index); // TODO: Not yet implemented
        void set(T added, unsigned int index);
        T get(const unsigned int index) const;
        T getNext();
        bool hasMore() const;
        unsigned int size() const;
        void reset(); // Sets position for getNext() to 0
    protected:
        static const int INIT_SIZE;
        static const float GROWTH_FACTOR;
        unsigned int elements;  // The number of elements stored
        unsigned int length;    // The size of the array
        unsigned int position;  // The current element for getNext()
        T* data;
    private:
        void grow();
};


template <class T>
class ArrayContainer : public DynamicArray<T> {
    public:
        ArrayContainer();
        virtual ~ArrayContainer();
    protected:
    private:
};


template <class T>
class ArrayList : public DynamicArray<T> {
    public:
        ArrayList();
        virtual ~ArrayList();
    protected:
    private:
};

}
#endif // ARRAYCONTAINERS_H
