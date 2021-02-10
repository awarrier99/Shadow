#include "Scope.h"


void Scope::declare(std::string &var, std::shared_ptr<Symbol> &symbol) {
    this->symbol_table[var] = symbol;
}

std::shared_ptr<Symbol> Scope::lookup(std::string &var) {
    return this->symbol_table[var];
}
