#ifndef SHADOW_SYMBOL_H
#define SHADOW_SYMBOL_H

#include <string>


class Symbol {
public:
    explicit Symbol(std::unique_ptr<std::string> &data);

    std::unique_ptr<std::string> data;
};



#endif //SHADOW_SYMBOL_H
