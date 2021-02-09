#include "Scope.h"

void Scope::assign(std::string &var, std::shared_ptr<Data> &data) {
    this->symbol_table[var] = data;
}

std::shared_ptr<Data> Scope::retrieve(std::string &var) {
    return this->symbol_table[var];
}
