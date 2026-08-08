#include <iostream>
#include "lox/Lox.h"
#include "scanner/Scanner.h"
#include "scanner/Token.h"
#include "parser/Parser.h"
#include "ast/AstPrinter.h"

// int main() {
//     std::cout << "Hello, World!" << std::endl;
//     return 0;
// }

// int main(int argc, char* argv[]){
//     if(argc > 2){
//         return 64;
//     }
//     else if (argc == 2){
//         Lox::runFile(argv[1]);
//     }
//     else {
//         Lox::runPrompt();
//     }
//     return 0;

// }

int main(){
    //std::string source = "1*2+3>5";

    //std::string source = "1 + 2 * 3 < 10 == true";

    std::string source = "1 + ;";
    
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    std::cout << "Tokens:\n";

    for(auto& token : tokens){
        std::cout<< token <<  "\n";
    }

    Parser parser(tokens);
    auto expression = parser.parse();

    if(expression){
        AstPrinter printer;

        std::cout << "Ast: "
                  << printer.print(*expression)
                  << '\n';  

    }
    return 0;
}