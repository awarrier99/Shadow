#ifndef SHADOW_NAMESPACE_H
#define SHADOW_NAMESPACE_H

#include <stack>
#include <map>
#include "Symbol.h"
#include "Data.h"


class Namespace;
typedef std::shared_ptr<Namespace> namespace_ptr;
class Namespace {
public:
    explicit Namespace(unsigned int level, namespace_ptr &parent);

    void assign(symbol_ptr &symbol, data_ptr &data);
    data_ptr retrieve(symbol_ptr &symbol);

    unsigned int level;
    namespace_ptr parent;

private:
    std::map<symbol_ptr, data_ptr> memory;
};


#endif //SHADOW_NAMESPACE_H
