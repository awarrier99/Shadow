#include "Number.h"


Number::Number(long double value): Data(NUM), value(value) {}

std::string Number::display() {
    std::stringstream ss;
    ss << this->value;
    return ss.str();
}
