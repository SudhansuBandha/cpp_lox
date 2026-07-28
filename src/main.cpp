#include <iostream>
#include "lox/Lox.h"

// int main() {
//     std::cout << "Hello, World!" << std::endl;
//     return 0;
// }

int main(int argc, char* argv[]){
    if(argc > 2){
        return 64;
    }
    else if (argc == 2){
        Lox::runFile(argv[1]);
    }
    else {
        Lox::runPrompt();
    }
    return 0;

}