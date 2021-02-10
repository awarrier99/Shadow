#ifndef SHADOW_DATA_H
#define SHADOW_DATA_H

#include <string>
#include <sstream>


class Datatype {
public:
    inline static const char* NUMBER = "NUMBER";
    inline static const char* STRING = "STRING";
};

class Data {
public:
    explicit Data(const char* type);
    virtual ~Data() = default;

    virtual std::string display() = 0;

    const char* type;
};

class Number: public Data {
public:
    explicit Number(long double value);

    std::string display() override;

    long double value;
};

class String: public Data {
public:
    explicit String(std::string &value);

    std::string display() override;

    std::string value;
};

#endif //SHADOW_DATA_H
