#include <iostream>
#include "Lexer.h"


TokenList* Lexer::lex(std::string* source) {
    auto* token_list = new TokenList();
    TokenType type = IDENT; // arbitrary, just so it's not invalid
    int i = 0, line_num = 1;
    while (i < source->length() && type != INVALID) {
        TokenList* line_list = lex_line(source, line_num, &i);
        token_list->insert(token_list->end(), line_list->begin(), line_list->end());
        type = line_list->back()->type;
        delete line_list;
        line_num++;
    }

    return token_list;
}

TokenList* Lexer::lex_line(std::string* line, int line_num, int* i) {
    auto* token_list = new TokenList();
    int j = 0;
    while (true) {
        Token* token = Lexer::extract_token(line, line_num, *i, &j);
        token_list->push_back(token);
        if (token->type == INVALID) break;
        if (token->type == SEP && *((char*) token->symbol->data) == ';') break;
    }
    *i += j;

    return token_list;
}

Token* Lexer::extract_token(std::string* line, int line_num, int i, int* j) {
    char ch = (*line)[i + *j];
    while (ch == ' ' || ch == '\n' || ch == '\t') {
        (*j)++;
        ch = (*line)[i + *j];
    }
    int col = *j;
    (*j)++;

    Token* token;
    TokenType type = get_type(ch);
    switch(type) {
        case NUMBER:
            token = Lexer::extract_number(line, i, j, ch);
            break;
        case STRING:
            token = Lexer::extract_string(line, i, j);
            break;
        case IDENT:
            token = Lexer::extract_ident(line, i, j, ch);
            break;
        case OP:
            token = Lexer::extract_op(ch);
            break;
        case SEP:
            token = Lexer::extract_sep(ch);
            break;
        default:
            token = new Token(INVALID, 0, nullptr);
            break;
    }
    token->line = line_num;
    token->column = col;

    return token;
}

Token* Lexer::extract_number(std::string* line, int i, int* j, char first_ch) { // TODO: support floats
    std::string num_str = std::string(1, first_ch);
    char ch = (*line)[i + *j];
    while (get_type(ch) == NUMBER) {
        num_str += ch;
        (*j)++;
        ch = (*line)[i + *j];
    }

    auto* num = new int;
    *num = std::stoi(num_str);
    auto* sym = new Symbol((void*) num);
    return new Token(NUMBER, 32, sym);
}

Token* Lexer::extract_string(std::string* line, int i, int* j) {
    auto* str = new std::string;
    char ch = (*line)[i + *j];
    while (get_type(ch) != STRING) { // TODO: support escape chars
        *str += ch;
        (*j)++;
        ch = (*line)[i + *j];
    }
    (*j)++; // so we don't recheck the end quote

    auto* sym = new Symbol((void*) str);
    return new Token(STRING, 0, sym);
}

Token* Lexer::extract_ident(std::string* line, int i, int* j, char first_ch) {
    auto* ident = new std::string(1, first_ch);
    char ch = (*line)[i + *j];
    while (get_type(ch) == IDENT) {
        *ident += ch;
        (*j)++;
        ch = (*line)[i + *j];
    }

    auto* sym = new Symbol((void*) ident);
    return new Token(IDENT, 0, sym);
}

Token* Lexer::extract_op(char first_ch) {
    auto* ops = new std::string(1, first_ch);

    auto* sym = new Symbol((void*) ops);
    return new Token(OP, 0, sym);
}

Token* Lexer::extract_sep(char first_ch) {
    auto* sep = new char;
    *sep = first_ch;

    auto* sym = new Symbol((void*) sep);
    return new Token(SEP, 0, sym);
}

TokenType get_type(char ch) {
//    int extra_ident_codes[] = {}; TODO: allow for non alpha characters in identifier
    //%,*,+,-,<,=,>
    int op_codes[] = {37, 42, 43, 45, 60, 61, 62}; // TODO: add more operators, allow for += and other combos
    int code = (int) ch;
    if (code >= 48 && code <= 57) return NUMBER;
    if (code == 34) return STRING;
    if ((code >= 65 && code <= 90) || (code >= 97 && code <= 122)) return IDENT; // TODO: allow for non alpha characters in identifier
    if (std::find(std::begin(op_codes), std::end(op_codes), code) != std::end(op_codes)) return OP;
    // (,),;
    if (code == 40 || code == 41 || code == 59) return SEP;
    return INVALID;
}