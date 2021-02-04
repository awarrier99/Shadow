#ifndef FYE_PARSER_H
#define FYE_PARSER_H

#include <string>
#include <stack>
#include <map>
#include "AST.h"
#include "util.h"


class Parser {
public:
    [[nodiscard]] AST* build_ast() const;

    TokenList* token_list;
};


#endif //FYE_PARSER_H
