#include "ArrayContainers.h"
#include <string>

// FIXME: Is there any point in keeping this?
// In use it has been replaced with asserts.


namespace ArrayContainers {

IndexOutOfBound::IndexOutOfBound() : source( "" )  {}


IndexOutOfBound::IndexOutOfBound(const std::string src) : source ( "Index out of Bounds: " + src ) {}



const std::string IndexOutOfBound::getSource() const {
    return source;
}


IndexOutOfBound::~IndexOutOfBound() {}

// TODO (Maybe): Have it carry a little more info

}
