#include "Interpreter.h"


Interpreter::Interpreter(std::ifstream* source_file) {
    this->source_file = source_file;
    this->lexer = new Lexer();
    this->parser = new Parser();
}

void Interpreter::pipeline() {
    char ch;
    std::stringstream buffer;
    std::string instruction;
    this->lexer->instruction = &instruction;
    this->lexer->line_num = 1;
    this->lexer->cursor = 0;
    this->lexer->offset = 0;

    TokenType type = IDENT; // arbitrary, just so it's not invalid
    while (type != INVALID) {
        *this->source_file >> std::noskipws >> ch;
        if (this->source_file->eof()) break;

        buffer << ch;

        if (ch == '\n') {
            this->lexer->line_num++;
            this->lexer->cursor = 0;
        }
        else if (ch == ';') {
            instruction = buffer.str();
            auto* token_list = this->lexer->lex_instruction();
            type = token_list->back()->type;

            for (Token* token: *token_list) { // test
                switch(token->type) {
                    case NUMBER:
                        std::cout << "Type: NUMBER" << " Line: " << token->line <<
                            " Column: " << token->column << " Symbol: " << *((int*) token->symbol->data) << std::endl;
                        break;
                    case STRING:
                        std::cout << "Type: STRING" << " Line: " << token->line <<
                            " Column: " << token->column << " Symbol: " << *((std::string*) token->symbol->data) << std::endl;
                        break;
                    case IDENT:
                        std::cout << "Type: IDENT" << " Line: " << token->line <<
                            " Column: " << token->column << " Symbol: " << *((std::string*) token->symbol->data) << std::endl;
                        break;
                    case OP:
                        std::cout << "Type: OP" << " Line: " << token->line <<
                            " Column: " << token->column << " Symbol: " << *((std::string*) token->symbol->data) << std::endl;
                        break;
                    case SEP:
                        std::cout << "Type: SEP" << " Line: " << token->line <<
                            " Column: " << token->column << " Symbol: " << *((char*) token->symbol->data) << std::endl;
                        break;
                    case INVALID:
                        std::cout << "Type: INVALID" << " Line: " << token->line << " Column: " << token->column << std::endl;
                        break;
                }
            }

            buffer.str(std::string());
        }
    }
}
