#include "lib/AST.hpp"
#include <cmath>
//---------------------------------------------------------------------------
namespace ast {

UnaryASTNode::UnaryASTNode(std::unique_ptr<ASTNode> ptr): m_ptr{std::move(ptr)}{

}

ASTNode& UnaryASTNode::getInput(){
    return *m_ptr;
}

ASTNode* UnaryASTNode::releaseInput(){
    return m_ptr.release();
}

ASTNode::Type UnaryPlus::getType() {
    return Type::UnaryPlus;
}   
double UnaryPlus::evaluate(EvaluationContext& ctx) {
    return this->getInput().evaluate(ctx);
}

ASTNode::Type UnaryMinus::getType() {
    return Type::UnaryMinus;
}   
double UnaryMinus::evaluate(EvaluationContext& ctx) {
    return -this->getInput().evaluate(ctx);
}

BinaryASTNode::BinaryASTNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right):
m_left(std::move(left)), m_right(std::move(right)){
    
}

ASTNode& BinaryASTNode::getLeft(){
    return *m_left;
}

ASTNode& BinaryASTNode::getRight(){
    return *m_right;
}

ASTNode* BinaryASTNode::releaseLeft(){
    return m_left.release();
}

ASTNode* BinaryASTNode::releaseRight(){
    return m_right.release();
}

ASTNode::Type Add::getType() {
    return Type::Add;
}   
double Add::evaluate(EvaluationContext& ctx) {
    return this->getLeft().evaluate(ctx)+this->getRight().evaluate(ctx);
}
ASTNode::Type Subtract::getType() {
    return Type::Subtract;
}   
double Subtract::evaluate(EvaluationContext& ctx) {
    return this->getLeft().evaluate(ctx)-this->getRight().evaluate(ctx);
}
ASTNode::Type Multiply::getType() {
    return Type::Multiply;
}   
double Multiply::evaluate(EvaluationContext& ctx) {
    return this->getLeft().evaluate(ctx)*this->getRight().evaluate(ctx);
}
ASTNode::Type Divide::getType() {
    return Type::Divide;
}   
double Divide::evaluate(EvaluationContext& ctx) {
    return this->getLeft().evaluate(ctx)/this->getRight().evaluate(ctx);
}
ASTNode::Type Power::getType() {
    return Type::Power;
}   
double Power::evaluate(EvaluationContext& ctx) {
    return std::pow(this->getLeft().evaluate(ctx),this->getRight().evaluate(ctx));
}


Constant::Constant(double value):m_double(value){

}
double Constant::getValue(){
    return m_double;
}

ASTNode::Type Constant::getType() {
    return Type::Constant;
}   
double Constant::evaluate(EvaluationContext& ctx) {
    (void)ctx;//suppressing compiler unused parameter warnings 
    return getValue();
}

Parameter::Parameter(size_t idx): m_idx(idx){

}
size_t Parameter::getIndex(){
    return m_idx;
}

ASTNode::Type Parameter::getType() {
    return Type::Parameter;
}

double Parameter::evaluate(EvaluationContext& ctx) {
    return ctx.getParameter(m_idx);
}

} // namespace ast
//---------------------------------------------------------------------------
