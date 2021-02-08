#ifndef SHADOW_OPERATIONS_H
#define SHADOW_OPERATIONS_H

#include <sstream>
#include <map>
#include <cmath>
#include "Data.h"
#include "Number.h"
#include "String.h"


class Operations {
public:
    static std::shared_ptr<Data> add(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b);
    static std::shared_ptr<Data> sub(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b);
    static std::shared_ptr<Data> mul(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b);
    static std::shared_ptr<Data> div(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b);
    static std::shared_ptr<Data> mod(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b);
};

#endif //SHADOW_OPERATIONS_H
