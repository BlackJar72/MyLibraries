#include "ArrayContainers.h"
#include <string>

namespace ArrayContainers {

IndexOutOfBound::IndexOutOfBound() : source( "" )  {}


IndexOutOfBound::IndexOutOfBound(const std::string src) : source ( src ) {}



const std::string IndexOutOfBound::getSource() const {
    return source;
}


IndexOutOfBound::~IndexOutOfBound() {}

// TODO (Maybe): Have it carry a little more info

}
