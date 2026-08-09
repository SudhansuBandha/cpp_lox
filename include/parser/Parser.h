#pragma once

#include <memory>
#include <vector>
#include <stdexcept>
#include "scanner/Token.h"
#include "ast/Expr.h"

class ParseError : public std::runtime_error {
public:
    ParseError()
        : std::runtime_error("Parse error") {}
};

class Parser{
    public:
        explicit Parser(std::vector<Token> tokens);
        std::unique_ptr<Expr> parse();
    
    private:
        std::vector<Token> tokens;
        int current = 0;
        
        std::unique_ptr<Expr> expression();
        
        Token advance();
        Token peek() const;
        Token previous() const;

        bool check(TokenType type) const;
        bool isAtEnd() const;
        
        bool match(const std::initializer_list<TokenType>& types);
        
        Token consume(TokenType type, const std::string& message);

        std::unique_ptr<Expr> primary();
        std::unique_ptr<Expr> unary(); 
        std::unique_ptr<Expr> factor();
        std::unique_ptr<Expr> term();
        std::unique_ptr<Expr> comparison();
        std::unique_ptr<Expr> equality();
        
        ParseError error(
        const Token& token,
        const std::string& message
    );
};

