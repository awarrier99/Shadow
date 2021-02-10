#ifndef SHADOW_MEMORY_H
#define SHADOW_MEMORY_H

#include <map>
#include "Data.h"
#include "Symbol.h"


class Memory {
public:
    void assign(std::shared_ptr<Symbol> &symbol, std::shared_ptr<Data> &data);
    std::shared_ptr<Data> retrieve(std::shared_ptr<Symbol> &symbol);

private:
    std::map<std::shared_ptr<Symbol>, std::shared_ptr<Data>> memory;
};


#endif //SHADOW_MEMORY_H
