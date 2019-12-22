#include <iostream>
#include "Lexer.h"


std::vector<TokenList*>* Lexer::lex(std::string* source) {
//    std::string line;
    return new std::vector<TokenList*> { lex_line(source) };
}

//adds the token to the end of TokenList
TokenList* Lexer::lex_line(std::string* line) {
    auto* token_list = new TokenList {};
    int i = 0;
    while (i < line->length()) {
        token_list->push_back(Lexer::extract_token(line, &i));
    }

    return token_list;
}
//extract token by line number excluding white space and new lines
Token* Lexer::extract_token(std::string* line, int* i) {
    char ch = (*line)[*i];
    while (ch == ' ' || ch == '\n' || ch == '\t') {
        (*i)++;
        ch = (*line)[*i];
    }
    (*i)++;
    Token* token;
    TokenType type = get_type(ch);
    switch(type) {
        case NUMBER:
            token = Lexer::extract_number(line, i, ch, *i - 1);
            break;
        case STRING:
            break;
        case IDENT:
            token = Lexer::extract_ident(line, i, ch, *i - 1);
            break;
        case OP:
            token = Lexer::extract_op(line, i, ch, *i - 1);
            break;
        case SEP:
            token = Lexer::extra_sep(line, i, ch, *i - 1);
            break;
        case INVALID:
            break;
    }

    return token;
}

Token* Lexer::extract_op(std::string *line, int *i, char first_ch, int first_i) {
    auto* ops = new std::string(1, first_ch);
    char ch = (*line)[*i];
    while (get_type(ch) == OP) {
        *ops += ch;
        (*i)++;
        ch = (*line)[*i];
    }
    auto* sym = new Symbol((void*) ops);
    return new Token(OP, 0, 0, first_i, sym);
}

Token* Lexer::extra_sep(std::string *line, int *i, char first_ch, int first_i) {
    auto* sep = new std::string(1, first_ch);
    char ch = (*line)[*i];
    while (get_type(ch) == SEP) {
        *sep += ch;
        (*i)++;
        ch = (*line)[*i];
    }
    auto* sym = new Symbol((void*) sep);
    return new Token(SEP, 0, 0, first_i, sym);
}

Token* Lexer::extract_number(std::string* line, int* i, char first_ch, int first_i) { // TODO: support floats
    std::string num_str = std::string(1, first_ch);
    char ch = (*line)[*i];
    while (get_type(ch) == NUMBER) {
        num_str += ch;
        (*i)++;
        ch = (*line)[*i];
    }

    auto* num = new int;
    *num = std::stoi(num_str);
    auto* sym = new Symbol((void*) num);
    return new Token(NUMBER, 32, 0, first_i, sym); // TODO: implement line number
}
//Question: why do you do Lexer::and the function name
Token* Lexer::extract_ident(std::string* line, int* i, char first_ch, int first_i) {
    auto* ident = new std::string(1, first_ch);
    char ch = (*line)[*i];
    while (get_type(ch) == IDENT) {
        *ident += ch;
        (*i)++;
        ch = (*line)[*i];
    }
    //Question: why do you do void*
    auto* sym = new Symbol((void*) ident);
    return new Token(IDENT, 0, 0, first_i, sym);
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
    // (, ), ;
    if (code == 40 || code == 41 || code == 59) return SEP;
    return INVALID;
}