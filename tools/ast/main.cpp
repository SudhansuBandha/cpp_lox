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
        "Binary   : std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right",
        "Grouping : std::unique_ptr<Expr> expression",
        "Literal  : LiteralValue value",
        "Unary    : Token op, std::unique_ptr<Expr> right"
    };

    GenerateAst::defineAst(
        argv[1],
        "Expr",
        exprTypes);

    return 0;
}