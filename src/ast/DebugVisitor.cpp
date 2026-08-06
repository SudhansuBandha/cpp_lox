#include <iostream>
#include "ast/DebugVisitor.h"

void DebugVisitor::visitBinaryExpr(const Binary& expr){
    std::cout << "Visited Binary\n";

    expr.getLeft()->accept(*this);
    expr.getRight()->accept(*this);
}

void DebugVisitor::visitGroupingExpr(const Grouping& expr)
{
    std::cout << "Visited Grouping\n";
    expr.getExpression()->accept(*this);
}

void DebugVisitor::visitLiteralExpr(const Literal& expr)
{
    std::cout << "Visited Literal\n";
}

void DebugVisitor::visitUnaryExpr(const Unary& expr)
{
    std::cout << "Visited Unary\n";
    expr.getRight()->accept(*this);
}