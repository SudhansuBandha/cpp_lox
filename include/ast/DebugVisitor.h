# pragma once
# include "Expr.h"

class DebugVisitor : public ExprVisitor{
    public:
        void visitBinaryExpr(const Binary& expr) override;
        void visitGroupingExpr(const Grouping& expr) override;
        void visitLiteralExpr(const Literal& expr) override;
        void visitUnaryExpr(const Unary& expr) override;
};
