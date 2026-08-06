#include "ast/Expr.h"

#include <utility>

Binary::Binary(
    std::unique_ptr<Expr> left,
    Token op,
    std::unique_ptr<Expr> right
)   :
    left_(std::move(left)),
    op_(std::move(op)),
    right_(std::move(right))
{
}

Grouping::Grouping(
    std::unique_ptr<Expr> expression
)   :
    expression_(std::move(expression))
{
}

Literal::Literal(
    LiteralValue value
)   :
    value_(std::move(value))
{
}

Unary::Unary(
    Token op,
    std::unique_ptr<Expr> right
)   :
    op_(std::move(op)),
    right_(std::move(right))
{
}

