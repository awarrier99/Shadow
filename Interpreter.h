#ifndef FYE_INTERPRETER_H
#define FYE_INTERPRETER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Lexer.h"
#include "Parser.h"


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
