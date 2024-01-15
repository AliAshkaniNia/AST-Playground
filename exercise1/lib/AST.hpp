#ifndef H_lib_AST
#define H_lib_AST
//---------------------------------------------------------------------------
#include <memory>
#include "EvaluationContext.hpp"
//---------------------------------------------------------------------------
namespace ast {
//---------------------------------------------------------------------------
/// Base class for AST nodes
class ASTNode {
    public:
    /// All possible types of ASTNodes
    enum class Type {
        UnaryPlus,
        UnaryMinus,
        Add,
        Subtract,
        Multiply,
        Divide,
        Power,
        Constant,
        Parameter
    };
    // Every AST node should implement these functions so they are pure virtuals
    virtual Type  getType() = 0 ;
    virtual double evaluate(EvaluationContext& ctx) = 0;

    // This is necessary for clean-ups 
    // A default implementation is enough for the whole hierarchy, as we use smart pointers 
    virtual ~ASTNode()=default;
};

class UnaryASTNode : public ASTNode{
public:
    UnaryASTNode(std::unique_ptr<ASTNode> ptr);
    ASTNode& getInput();
    ASTNode* releaseInput();

protected:
    std::unique_ptr<ASTNode> m_ptr;
};

class UnaryPlus: public UnaryASTNode{
public:
    //inheriting constructors
    using UnaryASTNode::UnaryASTNode;
    Type  getType() override ;
    double evaluate(EvaluationContext& ctx) override ;
};

class UnaryMinus: public UnaryASTNode{
public:
    //inheriting constructors
    using UnaryASTNode::UnaryASTNode;
    Type  getType() override ;
    double evaluate(EvaluationContext& ctx) override ;
};

class BinaryASTNode: public ASTNode{
    
};
class Add: public BinaryASTNode{

};
class Subtract: public BinaryASTNode{

};
class Multiply: public BinaryASTNode{

};
class Divide: public BinaryASTNode{

};
class Power: public BinaryASTNode{

};
class Constant: public ASTNode{
public:
    Constant(double value);
    double getValue();
    Type  getType() override ;
    double evaluate(EvaluationContext& ctx) override ;
private:
    double m_double;
};
class Parameter: public ASTNode{

};

//---------------------------------------------------------------------------
} // namespace ast
//---------------------------------------------------------------------------
#endif
