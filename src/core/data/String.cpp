#include "String.h"


String::String(std::string &value): Data(STR), value(value) {}

std::string String::display() {
    return "'" + this->value + "'";
}
