#ifndef FYE_SCOPE_H
#define FYE_SCOPE_H

#include <string>
#include <map>
#include "Data.h"


class Scope {
public:
    void assign(std::string &var, Data* data);
    Data* retrieve(std::string &var);

private:
    std::map<std::string, Data*> data_store;
};

#endif //FYE_SCOPE_H
