#include <iostream>
#include <vector>

#include "GenerateAst.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: GenerateAst <output directory>\n";
        return 64;
    }

    std::vector<std::string> exprTypes =
    {
        "Binary   : Expr* left, Token op, Expr* right",
        "Grouping : Expr* expression",
        "Literal  : LiteralValue value",
        "Unary    : Token op, Expr* right"
    };

    GenerateAst::defineAst(
        argv[1],
        "Expr",
        exprTypes);

    return 0;
}