#ifndef SHADOW_SCOPE_H
#define SHADOW_SCOPE_H

#include <string>
#include <map>
#include "Symbol.h"


class Scope;
typedef std::shared_ptr<Scope> scope_ptr;
class Scope {
public:
    Scope() = default;
    explicit Scope(scope_ptr &parent);

    void declare(std::string &var, symbol_ptr &symbol);
    symbol_ptr lookup(std::string &var);

    scope_ptr parent;

private:
    std::map<std::string, symbol_ptr> symbol_table;
};

#endif //SHADOW_SCOPE_H
