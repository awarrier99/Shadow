#include "Memory.h"


void Memory::assign(std::shared_ptr<Symbol> &symbol, std::shared_ptr<Data> &data) {
    this->memory[symbol] = data;
}

std::shared_ptr<Data> Memory::retrieve(std::shared_ptr<Symbol> &symbol) {
    return this->memory[symbol];
}
