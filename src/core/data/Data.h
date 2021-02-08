#ifndef SHADOW_DATA_H
#define SHADOW_DATA_H

#include <string>
#include <sstream>


enum Datatype {
    NUM,
    STR
};

class Data {
public:
    explicit Data(Datatype datatype);
    virtual ~Data() = default;

    virtual std::string display() = 0;

    Datatype datatype;
};

#endif //SHADOW_DATA_H
