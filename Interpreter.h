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
    Interpreter();
    explicit Interpreter(std::unique_ptr<std::ifstream> &source_file);

    void pipeline(bool repl = false);

private:
    std::unique_ptr<std::ifstream> source_file;
    std::unique_ptr<Lexer> lexer;
    std::unique_ptr<Parser> parser;
    std::unique_ptr<Executor> executor;
};


#endif //FYE_INTERPRETER_H
