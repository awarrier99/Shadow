#include "Scope.h"

void Scope::assign(std::string* var, Data* data) {
    this->data_store[*var] = data;
}

Data * Scope::retrieve(std::string* var) {
    return this->data_store[*var];
}
