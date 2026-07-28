cmake_minimum_required(VERSION 3.20)

project(
    CraftingInterpretersCPP
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpp_lox
    src/main.cpp
    src/Lox.cpp
    src/scanner/Scanner.cpp
    src/scanner/Token.cpp
    src/scanner/TokenType.cc
)

target_include_directories(cpp_lox PRIVATE include)