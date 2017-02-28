#include "GameMath.h"

namespace gamemath {

GMException::GMException() {}
GMException::~GMException() {}


GMException::GMException(string name, string description) {
    this->name = name;
    this->description = description;
}


string GMException::getName() const {
    return name;
}


string GMException::getDescription() const {
    return description;
}


}
