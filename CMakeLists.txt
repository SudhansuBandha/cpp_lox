cmake_minimum_required(VERSION 3.20)

project(
    CraftingInterpretersCPP
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================
# Core interpreter library
# ============================================================

add_library(lox_core
    src/Lox.cpp

    src/scanner/Scanner.cpp
    src/scanner/Token.cpp
    src/scanner/TokenType.cc

    src/ast/Expr.cpp
    src/ast/DebugVisitor.cpp
    src/ast/AstPrinter.cpp

    src/parser/Parser.cpp
)

target_include_directories(
    lox_core
    PUBLIC
        include
)

# ============================================================
# Main interpreter
# ============================================================

add_executable(cpp_lox
    src/main.cpp
)

target_link_libraries(
    cpp_lox
    PRIVATE
        lox_core
)

# ============================================================
# AST Generator
# ============================================================

add_executable(GenerateAst
    tools/ast/main.cpp
    tools/ast/GenerateAst.cpp
)

target_include_directories(
    GenerateAst
    PRIVATE
        include
        tools/ast
)

# ============================================================
# Tests
# ============================================================

include(CTest)
enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
)

FetchContent_MakeAvailable(googletest)

add_executable(
    parser_tests
    tests/parser/ParserTest.cpp
)

target_link_libraries(
    parser_tests
    PRIVATE
        lox_core
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(parser_tests)