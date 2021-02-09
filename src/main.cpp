#include "components/Interpreter.h"

int main(int argc, char** argv) {
//    signal(SIGINT, Interpreter::terminate);

    if (argc != 2) {
        auto interpreter = Interpreter();
        interpreter.pipeline(true);
    } else {
        char* source_filename = argv[1];
        auto source_file = std::ifstream(source_filename);
        if (!source_file.is_open()) {
            std::cerr << "Error: File " << source_filename << " could not be opened" << std::endl;
            return 1;
        }
        auto interpreter = Interpreter(&source_file);
        interpreter.pipeline();
    }

    return 0;
}
