#ifndef FYE_INTERPRETER_H
#define FYE_INTERPRETER_H

#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"
#include "Executor.h"
#include "util.h"


class Interpreter {
public:
    explicit Interpreter(std::ifstream* source_file);

    void pipeline();

private:
    std::ifstream* source_file;
    Lexer* lexer;
    Parser* parser;
    Executor* executor;

    void deallocate_instruction_resources();
};


#endif //FYE_INTERPRETER_H
