#ifndef FYE_SYMBOL_H
#define FYE_SYMBOL_H

#include <string>


class Symbol {
public:
    explicit Symbol(std::string* data);

    std::string* data;
};



#endif //FYE_SYMBOL_H
