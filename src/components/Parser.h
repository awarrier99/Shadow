#ifndef SHADOW_PARSER_H
#define SHADOW_PARSER_H

#include <string>
#include <stack>
#include <map>
#include "../core/ast/AST.h"
#include "../util/debug/debug.h"


class Parser {
public:
    [[nodiscard]] std::unique_ptr<AST> build_ast() const;

    std::unique_ptr<TokenList> token_list;
};


#endif //SHADOW_PARSER_H
