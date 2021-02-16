#include "Scope.h"


Scope::Scope(scope_ptr &parent): parent(parent) {}

void Scope::declare(std::string &var, symbol_ptr &symbol) {
    if (this->symbol_table.find(var) != this->symbol_table.end()) throw std::runtime_error("Symbol " + var + " has already been declared");
    this->symbol_table[var] = symbol;
}

symbol_ptr Scope::lookup(std::string &var) {
    auto it = this->symbol_table.find(var);
    if (it == this->symbol_table.end()) {
        if (!this->parent) return nullptr;
        return this->parent->lookup(var);
    }
    return it->second;
}
