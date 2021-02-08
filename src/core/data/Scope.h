#ifndef SHADOW_SCOPE_H
#define SHADOW_SCOPE_H

#include <string>
#include <map>
#include "Operations.h"


class Scope {
public:
    void assign(std::string &var, std::shared_ptr<Data> &data);
    std::shared_ptr<Data> retrieve(std::string &var);

private:
    std::map<std::string, std::shared_ptr<Data>> data_store;
};

#endif //SHADOW_SCOPE_H
