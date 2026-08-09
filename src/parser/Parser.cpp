#include "parser/Parser.h"
#include <iostream>

Parser::Parser(std::vector<Token> tokens):tokens(tokens){
}

std::unique_ptr<Expr> Parser::parse(){
    try {
        return expression();
    }
    catch (const ParseError&) {
        return nullptr;
    }
}

std::unique_ptr<Expr> Parser::expression(){
    //return nullptr;
    return equality();  
}

std::unique_ptr<Expr> Parser::equality(){ 
    auto expr = comparison();

    while (match({
        TokenType::BANG_EQUAL,
        TokenType::EQUAL_EQUAL
    })) {
        Token operatorToken = previous();

        auto right = comparison();

        expr = std::make_unique<Binary>(
            std::move(expr),
            operatorToken,
            std::move(right)
        );
    }

    return expr;
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

    throw error(peek(), message);
}

std::unique_ptr<Expr> Parser::comparison() {
    auto expr = term();

    while (match({
        TokenType::GREATER,
        TokenType::GREATER_EQUAL,
        TokenType::LESS,
        TokenType::LESS_EQUAL
    })) {
        Token operatorToken = previous();

        auto right = term();

        expr = std::make_unique<Binary>(
            std::move(expr),
            operatorToken,
            std::move(right)
        );
    }

    return expr;
}

std::unique_ptr<Expr> Parser::term() {
    auto expr = factor();

    while (match({
        TokenType::MINUS,
        TokenType::PLUS
    })) {
        Token operatorToken = previous();

        auto right = factor();

        expr = std::make_unique<Binary>(
            std::move(expr),
            operatorToken,
            std::move(right)
        );
    }

    return expr;
}

std::unique_ptr<Expr> Parser::factor(){
    auto expr = unary();

    while(match({TokenType::SLASH, TokenType::STAR})){
        Token operatorToken = previous();
        auto right = unary();

        expr = std::make_unique<Binary>(
            std::move(expr),
            operatorToken,
            std::move(right)
        );
    }
    return expr;
}

std::unique_ptr<Expr> Parser::unary(){
    if(match({ TokenType::BANG, TokenType::MINUS })){
        Token operatorToken = previous();
        auto right = unary();

        return std::make_unique<Unary>(
            operatorToken, 
            std::move(right)
        );
    }
    
    return primary();
};

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

    if(match({TokenType::LEFT_PAREN})){
        auto expr = expression();

        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");

        return std::make_unique<Grouping> (
            std::move(expr)
        );
    }

    throw error(
        peek(),
        "Expect expression."
    );

}

ParseError Parser::error(
    const Token& token,
    const std::string& message
) {
    if (token.type == TokenType::EOF_TOKEN) {
        std::cerr
            << "[line " << token.line
            << "] Error at end: "
            << message
            << '\n';
    } else {
        std::cerr
            << "[line " << token.line
            << "] Error at '"
            << token.lexeme
            << "': "
            << message
            << '\n';
    }

    return ParseError();
}

