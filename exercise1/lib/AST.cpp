#include "lib/AST.hpp"
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

} // namespace ast
//---------------------------------------------------------------------------
