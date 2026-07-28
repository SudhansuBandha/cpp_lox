#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "lox/Lox.h"
#include "scanner/Scanner.h"

bool Lox::hadError = false;

void Lox::runFile(const std::string& path){
    std::cout << "Running file: " <<  path << std::endl;

    std::ifstream file(path);

    if(!file){
        std::cerr << "Could not open file: " << path << std::endl;
        return ;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string source = buffer.str();

    run(source);

    if(hadError){
        std::exit(65);
    }
}

void Lox::runPrompt(){

    while(true){
        std::cout << "> ";

        std::string line;

        if(!std::getline(std::cin, line)){
            break;
        }

        run(line);

        hadError = false;
    }
}

void Lox::run(const std::string& source){
    Scanner scanner(source);

    std::vector<Token> tokens = scanner.scanTokens();

    for (const auto& token: tokens){
        std::cout << token << '\n';
    }
}

void Lox::error(int line, const std::string& message){
    report(line, "", message);
}

void Lox::report(int line,
     const std::string& where,
    const std::string& message){
    std::cerr
       << " line "
       << line
       << "] Error"
       << where
       << ": "
       << message
       << std::endl;
       
    hadError = true;   
}