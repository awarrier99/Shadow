#include "Data.h"


Data::Data(const char* type): type(type) {}

Number::Number(long double value): Data(Datatype::NUMBER), value(value) {}

std::string Number::display() {
    std::stringstream ss;
    ss << this->value;
    return ss.str();
}

String::String(std::string &value): Data(Datatype::STRING), value(value) {}

std::string String::display() {
    return "'" + this->value + "'";
}
