#ifndef SHADOW_INTERPRETER_H
#define SHADOW_INTERPRETER_H

#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"
#include "Executor.h"
#include "../util/debug/debug.h"


class Interpreter {
public:
    Interpreter();
    explicit Interpreter(std::ifstream* source_file);

    void pipeline(bool repl = false);

private:
    std::ifstream* source_file;
    std::unique_ptr<Executor> executor;
};


#endif //SHADOW_INTERPRETER_H
