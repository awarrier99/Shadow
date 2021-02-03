#ifndef FYE_INTERPRETER_H
#define FYE_INTERPRETER_H

#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"
#include "util.h"


class Interpreter {
public:
    explicit Interpreter(std::ifstream* source_file);

    void pipeline();

private:
    std::ifstream* source_file;
    Lexer* lexer;
    Parser* parser;
};


#endif //FYE_INTERPRETER_H
