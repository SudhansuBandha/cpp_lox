#include <cctype>
#include <cstdlib>
#include "scanner/Scanner.h"
#include "lox/Lox.h"
#include "string"


const std::unordered_map<std::string, TokenType> Scanner::keywords = {
    {"and", TokenType::AND},
    {"class", TokenType::CLASS},
    {"else", TokenType::ELSE},
    {"false", TokenType::FALSE},
    {"for", TokenType::FOR},
    {"fun", TokenType::FUN},
    {"if", TokenType::IF},
    {"nil", TokenType::NIL},
    {"or", TokenType::OR},
    {"print", TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"super", TokenType::SUPER},
    {"this", TokenType::THIS},
    {"true", TokenType::TRUE},
    {"var", TokenType::VAR},
    {"while", TokenType::WHILE}
};



Scanner::Scanner(std::string source)
    : source(std::move(source)){
        
    }

/*Scan all the tokens*/
std::vector<Token> Scanner::scanTokens(){

    while(!isAtEnd()){
        //We are at the beginning
        start = current;
        scanToken();
    }

    tokens.emplace_back(
        TokenType::EOF_TOKEN,
        "",
        std::monostate{},
        line
    );

    return tokens;
}    

/*Create array of tokens*/
void Scanner::addToken(TokenType type){
    addToken(type, std::monostate{});
}

/*Overloaded addToken*/
void Scanner::addToken(TokenType type, const LiteralValue& literal){
    std::string lexeme = source.substr(
        start,
        current - start
    );
    tokens.emplace_back(
        type,
        lexeme,
        literal,
        line
    );
}

/*Validate whether it is at end*/
bool Scanner::isAtEnd() const{
    return current >= source.length();
}

/*Move one character ahead as well return existing char*/
char Scanner::advance(){
    return source[current++];
}

/*Add corresponding Token Type for a character*/
void Scanner::scanToken(){
    char c = advance();
    switch(c){
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break; 
        case '!':
        addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        break;
      case '=':
        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
      case '<':
        addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
      case '>':
        addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;
     case '"':
        string();
        break;   
      case '/':
        if(match('/')){
            while(peek()!= '\n' && !isAtEnd()){
                advance();
            }
        }else{
            addToken(TokenType::SLASH);
        }
        break;
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;
        case '\n':
            line++;
            break;  
        default:
            if (std::isdigit(c)) {
            number();
            } else if (isAlpha(c)) {
               identifier();
            } 
            else {
            Lox::error(line, "Unexpected character.");
         }
           break;
    }

}

/*Validate whether token is equal to special character or not*/
bool Scanner::match(char expected){
    if(isAtEnd()) return false;
    if(source[current] != expected) return false;

    current++;
    return true;
}

/*Return latest charachter without advancing*/
char Scanner::peek() const {
    if(isAtEnd()) return '\0';
    return source[current];
}

/*Evaluate String*/
void Scanner::string(){
    while(peek() != '"' && !isAtEnd()){
        if (peek() == '\n') line++;
        advance();
    }

    if(isAtEnd()){
        // Incomplete String error handling
        Lox::error(line, "Unterminated string .");
    }

    // The closing "
    advance();

    // Trim the sorrounding quotes
    std::string value = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, value);
}

/*Look for Next Character*/
char Scanner::peekNext() const
{
    if (current + 1 >= source.length()) {
        return '\0';
    }

    return source[current + 1];
}


/*Evaluate number*/
void Scanner::number()
{
    // Consume the integer part.
    while (std::isdigit(peek())) {
        advance();
    }

    // Look for a fractional part.
    if (peek() == '.' && std::isdigit(peekNext())) {

        // Consume '.'
        advance();

        // Consume the fractional digits.
        while (std::isdigit(peek())) {
            advance();
        }
    }

    double value = std::strtod(
        source.substr(start, current - start).c_str(),
        nullptr
    );

    tokens.emplace_back(
        TokenType::NUMBER,
        source.substr(start, current - start),
        value,
        line
    );
}

void Scanner::identifier()
{
    while (isAlphaNumeric(peek())) {
        advance();
    }

    std::string text =
        source.substr(start, current - start);

    auto iter = keywords.find(text);

    TokenType type =
        (iter != keywords.end())
            ? iter->second
            : TokenType::IDENTIFIER;

    addToken(type);
}


bool Scanner::isAlpha(char c)
{
    return
        (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        c == '_';
}


bool Scanner::isAlphaNumeric(char c)
{
    return isAlpha(c) || std::isdigit(c);
}