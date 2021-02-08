#ifndef SHADOW_STRING_H
#define SHADOW_STRING_H

#include <sstream>
#include "Data.h"


class String: public Data {
public:
    explicit String(std::string &value);

    std::string display() override;

    std::string value;
};


#endif //SHADOW_STRING_H
