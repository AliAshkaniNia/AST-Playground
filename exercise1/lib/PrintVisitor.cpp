#include "lib/PrintVisitor.hpp"
#include "AST.hpp"
#include <iostream>
//---------------------------------------------------------------------------
namespace ast {

void PrintVisitor::visit(UnaryPlus& exp) {
    std::cout << "(+";
    exp.getInput().accept(*this);
    std::cout << ")";
}
void PrintVisitor::visit(UnaryMinus& exp) {
    std::cout << "(-";
    exp.getInput().accept(*this);
    std::cout << ")";
}
void PrintVisitor::visit(Add& exp) {
    std::cout << "(";
    exp.getLeft().accept(*this);
    std::cout << " + ";
    exp.getRight().accept(*this);
    std::cout << ")";
}
void PrintVisitor::visit(Subtract& exp) {
    std::cout << "(";
    exp.getLeft().accept(*this);
    std::cout << " - ";
    exp.getRight().accept(*this);
    std::cout << ")";
}
void PrintVisitor::visit(Multiply& exp) {
    std::cout << "(";
    exp.getLeft().accept(*this);
    std::cout << " * ";
    exp.getRight().accept(*this);
    std::cout << ")";
}
void PrintVisitor::visit(Divide& exp) {
    std::cout << "(";
    exp.getLeft().accept(*this);
    std::cout << " / ";
    exp.getRight().accept(*this);
    std::cout << ")";
}
void PrintVisitor::visit(Power& exp) {
    std::cout << "(";
    exp.getLeft().accept(*this);
    std::cout << " ^ ";
    exp.getRight().accept(*this);
    std::cout << ")";
}
void PrintVisitor::visit(Constant& exp) {
    std::cout << exp.getValue();
}
void PrintVisitor::visit(Parameter& exp) {
    std::cout << 'P' << exp.getIndex();
}

} // namespace ast
//---------------------------------------------------------------------------
