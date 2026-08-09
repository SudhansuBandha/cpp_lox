#pragma once

#include <string>

#include "scanner/Scanner.h"
#include "parser/Parser.h"
#include "ast/AstPrinter.h"

inline std::string parseToAst(const std::string& source)
{
    Scanner scanner(source);

    auto tokens = scanner.scanTokens();

    Parser parser(tokens);

    auto expression = parser.parse();

    if (!expression) {
        return {};
    }

    AstPrinter printer;

    return printer.print(*expression);
}