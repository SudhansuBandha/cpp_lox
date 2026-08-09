#pragma once

#include <string>
#include <vector>

struct ParserTestCase {
    std::string name;
    std::string source;
    std::string expectedAst;
};

struct ParserErrorTestCase {
    std::string name;
    std::string source;
};

inline const std::vector<ParserTestCase> parserTestCases = {

    {
        "number literal",
        "123",
        "123.000000"
    },

    {
        "string literal",
        "\"hello\"",
        "hello"
    },

    {
        "true literal",
        "true",
        "true"
    },

    {
        "false literal",
        "false",
        "false"
    },

    {
        "nil literal",
        "nil",
        "nil"
    },

    {
        "unary minus",
        "-123",
        "(- 123.000000)"
    },

    {
        "unary bang",
        "!true",
        "(! true)"
    },

    {
        "addition",
        "1 + 2",
        "(+ 1.000000 2.000000)"
    },

    {
        "subtraction",
        "4 - 3",
        "(- 4.000000 3.000000)"
    },

    {
        "multiplication",
        "1 * 2",
        "(* 1.000000 2.000000)"
    },

    {
        "division",
        "4 / 2",
        "(/ 4.000000 2.000000)"
    },

    {
        "multiplication precedence",
        "1 + 2 * 3",
        "(+ 1.000000 (* 2.000000 3.000000))"
    },

    {
        "subtraction precedence",
        "1 - 2 * 3",
        "(- 1.000000 (* 2.000000 3.000000))"
    },

    {
        "grouping",
        "(1 + 2) * 3",
        "(* (group (+ 1.000000 2.000000)) 3.000000)"
    },

    {
        "less than",
        "1 < 2",
        "(< 1.000000 2.000000)"
    },

    {
        "less than or equal",
        "1 <= 2",
        "(<= 1.000000 2.000000)"
    },

    {
        "greater than",
        "1 > 2",
        "(> 1.000000 2.000000)"
    },

    {
        "greater than or equal",
        "1 >= 2",
        "(>= 1.000000 2.000000)"
    },

    {
        "equality",
        "1 == 2",
        "(== 1.000000 2.000000)"
    },

    {
        "inequality",
        "1 != 2",
        "(!= 1.000000 2.000000)"
    },

    {
        "complex precedence",
        "1 + 2 * 3 < 10 == true",
        "(== (< (+ 1.000000 (* 2.000000 3.000000)) 10.000000) true)"
    },

    {
        "multiplication before subtraction",
        "1 * 2 - 3",
        "(- (* 1.000000 2.000000) 3.000000)"
    }
};

inline const std::vector<ParserErrorTestCase> parserErrorCases = {

    {
        "missing expression",
        "1 + ;"
    },

    {
        "missing closing parenthesis",
        "(1 + 2"
    },

    {
        "expression starts with operator",
        "* 123"
    }
};