#pragma once

#include <string>
#include <vector>
#include <string>
#include "Token.h"
#include <unordered_map>

class Scanner{
    public:
        explicit Scanner(std::string source);

        std::vector<Token> scanTokens();
    
    private:
        std::string source;
        std::vector<Token> tokens;
        
        int start = 0;
        int current = 0;
        int line = 1;
        
        void addToken(TokenType type);
        void addToken(TokenType type, const Literal& value);
        void scanToken();

        bool isAtEnd() const;
        char advance();
        bool match(char expected);
        char peek() const;
        char peekNext() const;
        void number();
        void string();

        void identifier();

        static bool isAlpha(char c);
        static bool isAlphaNumeric(char c);

        static const std::unordered_map<std::string, TokenType> keywords;
};