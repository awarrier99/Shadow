#ifndef FYE_DATA_H
#define FYE_DATA_H

#include <string>


class Data {};

class Number: public Data {};

class Integer: public Number {
public:
    explicit Integer(int value);

    int value;
};

class Float: public Number {
public:
    explicit Float(float value);

    float value;
};

class String: public Data {
public:
    explicit String(std::string &value);

    std::string value;
};

class Ident: public Data {
public:
    explicit Ident(std::string &value);

    std::string value;
};

class Op: public Data {
public:
    explicit Op(std::string &value);

    std::string value;
};

class Sep: public Data {
public:
    explicit Sep(char value);

    char value;
};

#endif //FYE_DATA_H
