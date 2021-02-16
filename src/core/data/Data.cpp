#include "Data.h"


Data::Data(const char* type): type(type) {}

Data::Data(const char* type, void_ptr &value): type(type), value(value) {}

Function::Function(astnodelist_ptr &formal_parameters, astnodelist_ptr &children):
    Data(Datatype::FUNCTION), formal_parameters(std::move(formal_parameters)), children(std::move(children)) {}

std::string Data::display() const {
    if (this->type == Datatype::NUMBER) {
        auto data = std::static_pointer_cast<long double>(this->value);
        std::stringstream ss;
        ss << *data;
        return ss.str();
    }
    auto data = std::static_pointer_cast<std::string>(this->value);
    return "'" + *data + "'";
}
