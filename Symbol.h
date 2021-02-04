#ifndef FYE_SYMBOL_H
#define FYE_SYMBOL_H

#include <string>
#include "Data.h"


class Symbol {
public:
    explicit Symbol(Data* data);

    Data* data;
};



#endif //FYE_SYMBOL_H
