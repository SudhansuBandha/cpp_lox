cmake_minimum_required(VERSION 3.20)

project(
    CraftingInterpretersCPP
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------
# Main interpreter
# -------------------------
add_executable(cpp_lox
    src/main.cpp
    src/Lox.cpp
    src/scanner/Scanner.cpp
    src/scanner/Token.cpp
    src/scanner/TokenType.cc
    src/ast/Expr.cpp
    src/ast/DebugVisitor.cpp
    src/ast/AstPrinter.cpp
    src/parser/Parser.cpp
)

target_include_directories(cpp_lox PRIVATE include)

# -------------------------
# AST Generator
# -------------------------
add_executable(GenerateAst
    tools/ast/main.cpp
    tools/ast/GenerateAst.cpp
)

target_include_directories(GenerateAst PRIVATE
    include
    tools/ast
)