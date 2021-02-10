#ifndef SHADOW_OPERATIONS_H
#define SHADOW_OPERATIONS_H

#include <sstream>
#include <map>
#include <cmath>
#include "Data.h"
#include "Memory.h"
#include "../source/Token.h"


class CalcOperations {
public:
    static std::shared_ptr<Data> operate(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b, const char* type);
    static std::shared_ptr<Data> add(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b);
    static std::shared_ptr<Data> sub(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b);
    static std::shared_ptr<Data> mul(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b);
    static std::shared_ptr<Data> div(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b);
    static std::shared_ptr<Data> mod(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b);

private:
    static std::map<const char*, std::function<std::shared_ptr<Data>(std::shared_ptr<Data>&, std::shared_ptr<Data>&)>> operation_map;
    static std::map<std::pair<const char*, const char*>, std::function<std::shared_ptr<Data>(std::shared_ptr<Data>&, std::shared_ptr<Data>&)>> add_map;
    static std::map<std::pair<const char*, const char*>, std::function<std::shared_ptr<Data>(std::shared_ptr<Data>&, std::shared_ptr<Data>&)>> mul_map;
};

class AssignOperations {
public:
    static void operate(std::shared_ptr<Symbol> &symbol, std::shared_ptr<Data> &b, const char* type, Memory* memory);

    static std::map<const char*, const char*> operation_map;
};

#endif //SHADOW_OPERATIONS_H
