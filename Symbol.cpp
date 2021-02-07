#include "Symbol.h"


Symbol::Symbol(std::unique_ptr<std::string> &data): data(std::move(data)) {}
