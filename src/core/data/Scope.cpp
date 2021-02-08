#include "Scope.h"

void Scope::assign(std::string &var, std::shared_ptr<Data> &data) {
    this->data_store[var] = data;
}

std::shared_ptr<Data> Scope::retrieve(std::string &var) {
    return this->data_store[var];
}
