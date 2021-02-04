#include "Data.h"

Integer::Integer(int value): value(value) {}

Float::Float(float value): value(value) {}

String::String(std::string &value): value(value) {}

Ident::Ident(std::string &value): value(value) {}

Op::Op(std::string &value): value(value) {}

Sep::Sep(char value): value(value) {}
