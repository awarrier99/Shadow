#ifndef SHADOW_SYMBOL_H
#define SHADOW_SYMBOL_H

#include <string>


class Symbol {
public:
    Symbol(std::string &name, bool is_const);

    std::string name;
    const bool is_const;
};


#endif //SHADOW_SYMBOL_H
