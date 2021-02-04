#include "Interpreter.h"


Interpreter::Interpreter(std::ifstream* source_file) { // TODO: lexing, parsing, and executing errors/exceptions
    this->source_file = source_file;
    this->lexer = new Lexer();
    this->parser = new Parser();
    this->executor = new Executor();
    this->executor->global = new Scope();
}

void Interpreter::pipeline() {
    char ch;
    std::stringstream buffer;
    std::string instruction;
    this->lexer->line_num = 1;
    this->lexer->cursor = 0;
    this->lexer->offset = 0;

    TokenType type = IDENT; // arbitrary, just so it's not invalid
    while (type != INVALID) {
        *this->source_file >> std::noskipws >> ch;
        if (this->source_file->eof()) break;

        if (ch == '\n') {
            this->lexer->line_num++;
            this->lexer->cursor = 0;
        }
        else if (ch == ';') {
            buffer << ch;
            instruction = buffer.str();
            this->lexer->instruction = &instruction;
            auto* token_list = this->lexer->lex_instruction();
            type = token_list->back()->type;
            buffer.str(std::string());

//            debug::print_token_list(token_list);

            this->parser->token_list = token_list;
            auto* ast = this->parser->build_ast();

            this->executor->ast = ast;
            this->executor->build_ir();
            this->executor->execute_ir();

            this->deallocate_instruction_resources();
        } else {
            buffer << ch;
        }
    }
}

void Interpreter::deallocate_instruction_resources() {
    this->lexer->instruction = nullptr;

    delete this->parser->token_list; // destructor deallocates individual tokens
    this->parser->token_list = nullptr;

//    deallocate_tree(this->executor->ast, true);
//    delete this->executor->ast;
//    this->executor->ast = nullptr;
//    deallocate_tree(this->executor->ir, false);
//    delete this->executor->ir;
//    this->executor->ir = nullptr;
//
//    for (Token* token: *this->parser->token_list) {
//        if (token->type == NUMBER) {
//            delete (int*) token->symbol->data;
//        } else if (token->type == STRING || token->type == IDENT || token->type == OP) {
//            delete (std::string*) token->symbol->data;
//        } else if (token->type == SEP) {
//            delete (char*) token->symbol->data;
//        }
//        token->symbol->data = nullptr;
//        delete token->symbol;
//        token->symbol = nullptr;
//        delete token;
//        token = nullptr;
//    }
//    delete this->parser->token_list;
//    this->parser->token_list = nullptr;
}
