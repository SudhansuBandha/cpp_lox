#pragma once

#include <ostream>
#include <string>
#include <variant>

#include "TokenType.h"

using LiteralValue = std::variant<
    std::monostate,
    double,
    std::string,
    bool
>;

class Token {
public:
    TokenType type;
    std::string lexeme;
    LiteralValue literal;
    int line;

    Token(
        TokenType type,
        std::string lexeme,
        LiteralValue literal,
        int line)
        : type(type),
          lexeme(std::move(lexeme)),
          literal(std::move(literal)),
          line(line) {}
};

//Stream operator
std::ostream& operator<<(std::ostream& os, const Token& token);