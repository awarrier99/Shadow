#ifndef SHADOW_SCOPE_H
#define SHADOW_SCOPE_H

#include <string>
#include <map>
#include "Symbol.h"


class Scope {
public:
    Scope() = default;
    explicit Scope(std::shared_ptr<Scope> &parent);

    void declare(std::string &var, std::shared_ptr<Symbol> &symbol);
    std::shared_ptr<Symbol> lookup(std::string &var);

    std::shared_ptr<Scope> parent;

private:
    std::map<std::string, std::shared_ptr<Symbol>> symbol_table;
};

#endif //SHADOW_SCOPE_H
