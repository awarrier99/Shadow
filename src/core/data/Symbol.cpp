#include "Symbol.h"


Symbol::Symbol(string_ptr &name): name(name), is_builtin(true), is_const(false), level(0) {}

Symbol::Symbol(string_ptr &name, bool is_const, unsigned int level):
    name(name), is_builtin(false), is_const(is_const), level(level) {}
