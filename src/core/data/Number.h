#ifndef SHADOW_NUMBER_H
#define SHADOW_NUMBER_H

#include "Data.h"


class Number: public Data {
public:
    explicit Number(long double value);

    std::string display() override;

    long double value;
};

#endif //SHADOW_NUMBER_H
