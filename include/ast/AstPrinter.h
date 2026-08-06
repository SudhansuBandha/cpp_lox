#pragma once

#include <string>
#include "Expr.h"

class AstPrinter : public ExprVisitor{
    public:
        std::string print(const Expr& expr);
        
        void visitBinaryExpr(const Binary& expr) override;
        void visitGroupingExpr(const Grouping& expr) override;
        void visitLiteralExpr(const Literal& expr) override;
        void visitUnaryExpr(const Unary& expr) override;
    
    private:
        std::string result_;
        
        void parenthesize(
            const std::string& name,
            const Expr* left,
            const Expr* right
        );

        void parenthesize(
            const std::string& name,
            const Expr* expr
        );
    
};