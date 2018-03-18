#include "GameMath.h"

namespace gamemath {

GMException::GMException() {}
GMException::~GMException() {}


GMException::GMException(std::string name, std::string description) {
    this->name = name;
    this->description = description;
}


std::string GMException::getName() const {
    return name;
}


std::string GMException::getDescription() const {
    return description;
}


}
