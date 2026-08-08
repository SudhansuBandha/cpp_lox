#include "parser/Parser.h"

Parser::Parser(std::vector<Token> tokens):tokens(tokens){
}

std::unique_ptr<Expr> Parser::parse(){
    return expression();
}

std::unique_ptr<Expr> Parser::expression(){
    //return nullptr;
    return equality();  
}

std::unique_ptr<Expr> Parser::equality(){
    //Temporary 
    return primary();
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


std::unique_ptr<Expr> Parser::primary(){
    if(match({TokenType::FALSE})){
        return std::make_unique<Literal>(false);
    }

    if(match({TokenType::TRUE})){
        return std::make_unique<Literal>(true);
    }

    if(match({TokenType::NIL})){
        return std::make_unique<Literal>(std::monostate{});
    }

    if(match({TokenType::NUMBER, TokenType::STRING})){
        return std::make_unique<Literal>(previous().literal);
    }

    if(match({TokenType::LEFT_BRACE})){
        auto expr = expression();

        consume(TokenType::RIGHT_BRACE, "Expect ')' after expression.");

        return std::make_unique<Grouping> (
            std::move(expr)
        );
    }

    throw std::runtime_error("Expected expression.");

}