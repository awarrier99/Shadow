#ifndef SHADOW_SYMBOL_H
#define SHADOW_SYMBOL_H

#include <string>
#include "Token.h"
#include "../ast/AST.h"


class Symbol {
public:
    explicit Symbol(string_ptr &name);
    Symbol(string_ptr &name, bool is_const, unsigned int level);
    virtual ~Symbol() = default;

    string_ptr name;
    const bool is_builtin;
    const bool is_const;
    unsigned int level;
};

typedef std::shared_ptr<Symbol> symbol_ptr;

#endif //SHADOW_SYMBOL_H
