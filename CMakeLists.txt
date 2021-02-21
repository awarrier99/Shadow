cmake_minimum_required(VERSION 3.15)
project(Shadow)

set(CMAKE_CXX_STANDARD 17)

add_executable(Shadow src/main.cpp src/components/Lexer.cpp src/components/Lexer.h src/core/token/Token.cpp src/core/token/Token.h src/components/Parser.cpp src/components/Parser.h src/components/Interpreter.cpp src/components/Interpreter.h src/util/debug/debug.cpp src/util/debug/debug.h src/core/ast/AST.cpp src/core/ast/AST.h src/components/Executor.cpp src/components/Executor.h src/core/data/Data.cpp src/core/data/Data.h src/core/data/Scope.cpp src/core/data/Scope.h src/core/ast/AST.cpp src/core/ast/AST.h src/core/data/Operations.cpp src/core/data/Operations.h src/core/data/Symbol.cpp src/core/data/Symbol.h src/core/data/Namespace.cpp src/core/data/Namespace.h)