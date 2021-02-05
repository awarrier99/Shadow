#ifndef FYE_DATA_H
#define FYE_DATA_H

#include <string>


class Data {
public:
    virtual ~Data() = default;
};

class Number: public Data {
public:
    explicit Number(long double value);

    long double value;
};

class String: public Data {
public:
    explicit String(std::string &value);

    std::string value;
};

#endif //FYE_DATA_H
