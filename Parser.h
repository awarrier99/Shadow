#ifndef FYE_PARSER_H
#define FYE_PARSER_H

#include <string>
#include <stack>
#include <map>
#include "AST.h"
#include "util.h"


class Parser {
public:
    [[nodiscard]] std::unique_ptr<AST> build_ast() const;

    std::unique_ptr<TokenList> token_list;
};


#endif //FYE_PARSER_H
