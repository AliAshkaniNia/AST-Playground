#ifndef H_lib_AST
#define H_lib_AST
//---------------------------------------------------------------------------
#include "ASTVisitor.hpp"
#include "EvaluationContext.hpp"
#include <memory>
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
    virtual Type getType() = 0;
    virtual double evaluate(EvaluationContext& ctx) = 0;
    virtual void optimize(std::unique_ptr<ASTNode>& thisRef) = 0;
    virtual void accept(ASTVisitor& visitor) = 0;
    // This is necessary for clean-ups
    // A default implementation is enough for the whole hierarchy, as we use smart pointers
    virtual ~ASTNode() = default;
};

class UnaryASTNode : public ASTNode {
    public:
    UnaryASTNode(std::unique_ptr<ASTNode> ptr);
    ASTNode& getInput();
    ASTNode* releaseInput();

    protected:
    std::unique_ptr<ASTNode> m_ptr;
};

class UnaryPlus : public UnaryASTNode {
    public:
    //inheriting constructors
    using UnaryASTNode::UnaryASTNode;
    Type getType() override;
    double evaluate(EvaluationContext& ctx) override;
    void optimize(std::unique_ptr<ASTNode>& thisRef) override;
    void accept(ASTVisitor& visitor) override;
};

class UnaryMinus : public UnaryASTNode {
    public:
    //inheriting constructors
    using UnaryASTNode::UnaryASTNode;
    Type getType() override;
    double evaluate(EvaluationContext& ctx) override;
    void optimize(std::unique_ptr<ASTNode>& thisRef) override;
    void accept(ASTVisitor& visitor) override;
};

class BinaryASTNode : public ASTNode {
    public:
    BinaryASTNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right);
    ASTNode& getLeft();
    ASTNode& getRight();
    ASTNode* releaseLeft();
    ASTNode* releaseRight();

    protected:
    std::unique_ptr<ASTNode> m_left, m_right;
};
class Add : public BinaryASTNode {
    public:
    //inheriting constructors
    using BinaryASTNode::BinaryASTNode;
    Type getType() override;
    double evaluate(EvaluationContext& ctx) override;
    void optimize(std::unique_ptr<ASTNode>& thisRef) override;
    void accept(ASTVisitor& visitor) override;
};
class Subtract : public BinaryASTNode {
    public:
    //inheriting constructors
    using BinaryASTNode::BinaryASTNode;
    Type getType() override;
    double evaluate(EvaluationContext& ctx) override;
    void optimize(std::unique_ptr<ASTNode>& thisRef) override;
    void accept(ASTVisitor& visitor) override;
};
class Multiply : public BinaryASTNode {
    public:
    //inheriting constructors
    using BinaryASTNode::BinaryASTNode;
    Type getType() override;
    double evaluate(EvaluationContext& ctx) override;
    void optimize(std::unique_ptr<ASTNode>& thisRef) override;
    void accept(ASTVisitor& visitor) override;
};
class Divide : public BinaryASTNode {
    public:
    //inheriting constructors
    using BinaryASTNode::BinaryASTNode;
    Type getType() override;
    double evaluate(EvaluationContext& ctx) override;
    void optimize(std::unique_ptr<ASTNode>& thisRef) override;
    void accept(ASTVisitor& visitor) override;
};
class Power : public BinaryASTNode {
    public:
    //inheriting constructors
    using BinaryASTNode::BinaryASTNode;
    Type getType() override;
    double evaluate(EvaluationContext& ctx) override;
    void optimize(std::unique_ptr<ASTNode>& thisRef) override;
    void accept(ASTVisitor& visitor) override;
};
class Constant : public ASTNode {
    public:
    Constant(double value);
    double getValue();
    Type getType() override;
    double evaluate(EvaluationContext& ctx) override;
    void optimize(std::unique_ptr<ASTNode>& thisRef) override;
    void accept(ASTVisitor& visitor) override;

    private:
    double m_double;
};

class Parameter : public ASTNode {
    public:
    Parameter(size_t idx);
    size_t getIndex();
    Type getType() override;
    double evaluate(EvaluationContext& ctx) override;
    void optimize(std::unique_ptr<ASTNode>& thisRef) override;
    void accept(ASTVisitor& visitor) override;

    private:
    size_t m_idx;
};

//---------------------------------------------------------------------------
} // namespace ast
//---------------------------------------------------------------------------
#endif
