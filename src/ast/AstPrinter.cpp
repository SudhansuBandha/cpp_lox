#include "ast/AstPrinter.h"

std::string AstPrinter::print(const Expr& expr){
    result_.clear();

    expr.accept(*this);

    return result_;
}

void AstPrinter::parenthesize(
    const std::string& name,
    const Expr* expr)
{
    result_ += "(";
    result_ += name;
    result_ += " ";

    expr->accept(*this);

    result_ += ")";
}

void AstPrinter::parenthesize(
    const std::string& name,
    const Expr* left,
    const Expr* right)
{
    result_ += "(";
    result_ += name;
    result_ += " ";

    left->accept(*this);

    result_ += " ";

    right->accept(*this);

    result_ += ")";
}

void AstPrinter::visitBinaryExpr(const Binary& expr)
{
    parenthesize(
        expr.getOp().lexeme,
        expr.getLeft(),
        expr.getRight());
}

void AstPrinter::visitGroupingExpr(const Grouping& expr)
{
    parenthesize(
        "group",
        expr.getExpression());
}

void AstPrinter::visitUnaryExpr(const Unary& expr)
{
    parenthesize(
        expr.getOp().lexeme,
        expr.getRight());
}

void AstPrinter::visitLiteralExpr(const Literal& expr){

    const auto& value = expr.getValue();

    if(std::holds_alternative<std::monostate>(value)){
        result_ += "nil";
    }
    else if (std::holds_alternative<double>(value))
    {
        result_ += std::to_string(std::get<double>(value));
    }
    else if (std::holds_alternative<std::string>(value))
    {
        result_ += std::get<std::string>(value);
    }
    else if (std::holds_alternative<bool>(value))
    {
        result_ += std::get<bool>(value) ? "true" : "false";
    }
}