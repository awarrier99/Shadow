#ifndef SHADOW_DATA_H
#define SHADOW_DATA_H

#include <string>
#include <sstream>
#include "../ast/AST.h"


class Datatype {
public:
    inline static const char* NUMBER = "NUMBER";
    inline static const char* STRING = "STRING";
    inline static const char* FUNCTION = "FUNCTION";
};

typedef std::shared_ptr<void> void_ptr;
class Data {
public:
    explicit Data(const char* type);
    Data(const char* type, void_ptr &value);

    [[nodiscard]] std::string display() const;

    const char* type;
    void_ptr value;
};

typedef std::shared_ptr<Data> data_ptr;

class Function: public Data {
public:
    Function(astnodelist_ptr &formal_parameters, astnodelist_ptr &children);

    astnodelist_ptr formal_parameters;
    astnodelist_ptr children;
};

#endif //SHADOW_DATA_H
