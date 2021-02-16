#include "Namespace.h"


Namespace::Namespace(unsigned int level, namespace_ptr &parent): level(level), parent(parent) {}

void Namespace::assign(symbol_ptr &symbol, data_ptr &data) {
    if (symbol->level == this->level) this->memory[symbol] = data;
    else this->parent->assign(symbol, data);
}

data_ptr Namespace::retrieve(symbol_ptr &symbol) {
    if (symbol->level == this->level) {
        auto it = this->memory.find(symbol);
        if (it == this->memory.end()) return nullptr;
        return it->second;
    }

    return this->parent->retrieve(symbol);
}
