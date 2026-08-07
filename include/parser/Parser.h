#pragma once

#include <memory>
#include <vector>
#include "scanner/Token.h"
#include "ast/Expr.h"

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

};