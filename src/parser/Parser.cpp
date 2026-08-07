#include "parser/Parser.h"

Parser::Parser(std::vector<Token> tokens):tokens(tokens){
}

std::unique_ptr<Expr> Parser::parse(){
    return expression();
}

std::unique_ptr<Expr> Parser::expression(){
    return nullptr;
}

Token Parser::advance(){
    if(!isAtEnd()){
        current++;
    }
    return previous();
}

Token Parser::peek() const{
    return tokens[current];
}

Token Parser::previous() const{
    return tokens[current -1];
}

bool Parser::check(TokenType type) const{
    if(isAtEnd()){
        return false;
    }
    return peek().type == type;
}

bool Parser::isAtEnd() const{
    return peek().type == TokenType::EOF_TOKEN;
}

bool Parser::match(const std::initializer_list<TokenType>& types){
    for(TokenType type: types){
        if(check(type)){
            advance();
            return true;
        }
    }

    return false;
}

Token Parser::consume(TokenType type, const std::string& message){
    if(check(type)){
        return advance();
    }

    throw std::runtime_error(message);
}


