#ifndef SHADOW_OPERATIONS_H
#define SHADOW_OPERATIONS_H

#include <sstream>
#include <map>
#include <cmath>
#include "Data.h"
#include "Namespace.h"
#include "../token/Token.h"

typedef std::function<data_ptr(data_ptr&, data_ptr&)> opfunc;

class CalcOperations {
public:
    static data_ptr operate(data_ptr &a, data_ptr &b, const char* type);
    static data_ptr add(data_ptr &a, data_ptr &b);
    static data_ptr sub(data_ptr &a, data_ptr &b);
    static data_ptr mul(data_ptr &a, data_ptr &b);
    static data_ptr div(data_ptr &a, data_ptr &b);
    static data_ptr mod(data_ptr &a, data_ptr &b);

private:
    static std::map<const char*, opfunc> operation_map;
};

class AssignOperations {
public:
    static void operate(symbol_ptr &symbol, data_ptr &b, const char* type, namespace_ptr &record);

    static std::map<const char*, const char*> operation_map;
};

#endif //SHADOW_OPERATIONS_H
