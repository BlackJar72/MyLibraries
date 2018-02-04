#include "ArrayContainers.h"

namespace ArrayContainers {

const size_t   D_ARRAY_INIT_SIZE = 16;
const size_t   D_MAP_INIT_SIZE   = ((D_ARRAY_INIT_SIZE * 4) / 3) + 1;
const float D_ARRAY_GROWTH_FACTOR = 1.5;
const float D_ARRAY_SHRINK_FACTOR = 0.5;
const float D_ARRAY_SHRINK_THRESHOLD = 0.25;


template <class T>
Registry<T>::Registry() :
            data(new T[D_ARRAY_INIT_SIZE]),
            nameMap(new StringHashTable<int>(D_MAP_INIT_SIZE)),
            elements(0),
            length(D_ARRAY_INIT_SIZE) {}


template <class T>
Registry<T>::Registry(size_t startSize) :
            data(new T[startSize]),
            nameMap(new StringHashTable<int>(((startSize * 4) / 3) + 1)),
            elements(0),
            length(startSize)  {}


}
