#include "lib/AST.hpp"
#include <cmath>
//---------------------------------------------------------------------------
namespace ast {

UnaryASTNode::UnaryASTNode(std::unique_ptr<ASTNode> ptr) : m_ptr{std::move(ptr)} {
}

ASTNode& UnaryASTNode::getInput() {
    return *m_ptr;
}

ASTNode* UnaryASTNode::releaseInput() {
    return m_ptr.release();
}

ASTNode::Type UnaryPlus::getType() {
    return Type::UnaryPlus;
}
double UnaryPlus::evaluate(EvaluationContext& ctx) {
    return m_ptr->evaluate(ctx);
}

void UnaryPlus::optimize(std::unique_ptr<ASTNode>& thisRef) {
    m_ptr->optimize(m_ptr);
    if (m_ptr->getType() == Type::UnaryPlus ||
        m_ptr->getType() == Type::Parameter) {
        thisRef.reset(this->releaseInput());
    }
}

void UnaryPlus::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

ASTNode::Type UnaryMinus::getType() {
    return Type::UnaryMinus;
}
double UnaryMinus::evaluate(EvaluationContext& ctx) {
    return -m_ptr->evaluate(ctx);
}
void UnaryMinus::optimize(std::unique_ptr<ASTNode>& thisRef) {
    m_ptr->optimize(m_ptr);
    switch (m_ptr->getType()) {
        case Type::Constant: {
            double constValue = static_cast<Constant*>(m_ptr.get())->getValue();
            double negatedValue = -constValue;
            thisRef = std::make_unique<Constant>(negatedValue);
            break;
        }
        case Type::UnaryMinus: {
            ASTNode* grandChildPtr = static_cast<UnaryASTNode*>(m_ptr.get())->releaseInput();
            thisRef.reset(grandChildPtr);
            break;
        }
        case Type::Subtract: {
            Subtract* child = static_cast<Subtract*>(m_ptr.get());
            std::unique_ptr<ASTNode> prevLeftChild(child->releaseLeft());
            std::unique_ptr<ASTNode> prevRightChild(child->releaseRight());
            if (prevLeftChild->getType() == Type::UnaryMinus) {
                std::unique_ptr<ASTNode> prevLeftChild2(static_cast<UnaryASTNode*>(prevLeftChild.get())->releaseInput());
                thisRef = std::make_unique<Add>(std::move(prevRightChild), std::move(prevLeftChild2));
            } else {
                thisRef = std::make_unique<Subtract>(std::move(prevRightChild), std::move(prevLeftChild));
            }
            break;
        }
        default:
            break;
    }
}
void UnaryMinus::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

BinaryASTNode::BinaryASTNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right) : m_left(std::move(left)), m_right(std::move(right)) {
}

ASTNode& BinaryASTNode::getLeft() {
    return *m_left;
}

ASTNode& BinaryASTNode::getRight() {
    return *m_right;
}

ASTNode* BinaryASTNode::releaseLeft() {
    return m_left.release();
}

ASTNode* BinaryASTNode::releaseRight() {
    return m_right.release();
}

ASTNode::Type Add::getType() {
    return Type::Add;
}
double Add::evaluate(EvaluationContext& ctx) {
    return this->getLeft().evaluate(ctx) + this->getRight().evaluate(ctx);
}
void Add::optimize(std::unique_ptr<ASTNode>& thisRef) {
    m_left->optimize(m_left);
    m_right->optimize(m_right);
    if (m_left->getType() == Type::Constant &&
        m_right->getType() == Type::Constant) {
        double prev_left = static_cast<Constant*>(m_left.get())->getValue();
        double prev_right = static_cast<Constant*>(m_right.get())->getValue();

        thisRef = std::make_unique<Constant>(prev_left + prev_right);
    } else if (m_left->getType() == Type::Constant) {
        double prev_left = static_cast<Constant*>(m_left.get())->getValue();
        if (prev_left == 0.0) {
            thisRef.reset(this->releaseRight());
        }

    } else if (m_right->getType() == Type::Constant) {
        double prev_right = static_cast<Constant*>(m_right.get())->getValue();
        if (prev_right == 0.0) {
            thisRef.reset(this->releaseLeft());
        }
    } else if (m_left->getType() == Type::UnaryMinus) {
        std::unique_ptr<ASTNode> prevLeftChild(static_cast<UnaryASTNode*>(m_left.get())->releaseInput());
        std::unique_ptr<ASTNode> prevRightChild(releaseRight());
        thisRef = std::make_unique<Subtract>(std::move(prevRightChild), std::move(prevLeftChild));

    } else if (m_right->getType() == Type::UnaryMinus) {
        std::unique_ptr<ASTNode> prevLeftChild(releaseLeft());
        std::unique_ptr<ASTNode> prevRightChild(static_cast<UnaryASTNode*>(m_right.get())->releaseInput());

        thisRef = std::make_unique<Subtract>(std::move(prevLeftChild), std::move(prevRightChild));
    }
}
void Add::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}
ASTNode::Type Subtract::getType() {
    return Type::Subtract;
}
double Subtract::evaluate(EvaluationContext& ctx) {
    return this->getLeft().evaluate(ctx) - this->getRight().evaluate(ctx);
}
void Subtract::optimize(std::unique_ptr<ASTNode>& thisRef) {
    m_left->optimize(m_left);
    m_right->optimize(m_right);
    if (m_left->getType() == Type::Constant &&
        m_right->getType() == Type::Constant) {
        double prev_left = static_cast<Constant*>(m_left.get())->getValue();
        double prev_right = static_cast<Constant*>(m_right.get())->getValue();

        thisRef = std::make_unique<Constant>(prev_left - prev_right);
    } else if (m_left->getType() == Type::Constant) {
        double prev_left = static_cast<Constant*>(m_left.get())->getValue();
        if (prev_left == 0.0) {
            std::unique_ptr<ASTNode> prevRightChild(releaseRight());
            thisRef = std::make_unique<UnaryMinus>(std::move(prevRightChild));
        }

    } else if (m_right->getType() == Type::Constant) {
        double prev_right = static_cast<Constant*>(m_right.get())->getValue();
        if (prev_right == 0.0) {
            thisRef.reset(this->releaseLeft());
        }
    } else if (m_right->getType() == Type::UnaryMinus) {
        std::unique_ptr<ASTNode> prevLeftChild(releaseLeft());
        std::unique_ptr<ASTNode> prevRightChild(static_cast<UnaryASTNode*>(m_right.get())->releaseInput());
        thisRef = std::make_unique<Add>(std::move(prevLeftChild), std::move(prevRightChild));
    }
}
void Subtract::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}
ASTNode::Type Multiply::getType() {
    return Type::Multiply;
}
double Multiply::evaluate(EvaluationContext& ctx) {
    return this->getLeft().evaluate(ctx) * this->getRight().evaluate(ctx);
}
void Multiply::optimize(std::unique_ptr<ASTNode>& thisRef) {
    m_left->optimize(m_left);
    m_right->optimize(m_right);
    if (m_left->getType() == Type::Constant &&
        m_right->getType() == Type::Constant) {
        double prev_left = static_cast<Constant*>(m_left.get())->getValue();
        double prev_right = static_cast<Constant*>(m_right.get())->getValue();

        thisRef = std::make_unique<Constant>(prev_left * prev_right);
    } else if (m_left->getType() == Type::Constant) {
        double prev_left = static_cast<Constant*>(m_left.get())->getValue();
        if (prev_left == 0.0) {
            thisRef = std::make_unique<Constant>(0);
        } else if (prev_left == 1.0) {
            thisRef.reset(this->releaseRight());
        }

    } else if (m_right->getType() == Type::Constant) {
        double prev_right = static_cast<Constant*>(m_right.get())->getValue();
        if (prev_right == 0.0) {
            thisRef = std::make_unique<Constant>(0);
        } else if (prev_right == 1.0) {
            thisRef.reset(this->releaseLeft());
        }

    } else if (m_right->getType() == Type::UnaryMinus &&
               m_left->getType() == Type::UnaryMinus) {
        std::unique_ptr<ASTNode> prevLeftChild(static_cast<UnaryASTNode*>(m_left.get())->releaseInput());
        std::unique_ptr<ASTNode> prevRightChild(static_cast<UnaryASTNode*>(m_right.get())->releaseInput());
        thisRef = std::make_unique<Multiply>(std::move(prevLeftChild), std::move(prevRightChild));
    }
}
void Multiply::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}
ASTNode::Type Divide::getType() {
    return Type::Divide;
}
double Divide::evaluate(EvaluationContext& ctx) {
    return this->getLeft().evaluate(ctx) / this->getRight().evaluate(ctx);
}
void Divide::optimize(std::unique_ptr<ASTNode>& thisRef) {
    m_left->optimize(m_left);
    m_right->optimize(m_right);
    if (m_left->getType() == Type::Constant &&
        m_right->getType() == Type::Constant) {
        double prev_left = static_cast<Constant*>(m_left.get())->getValue();
        double prev_right = static_cast<Constant*>(m_right.get())->getValue();

        thisRef = std::make_unique<Constant>(prev_left / prev_right);
    } else if (m_left->getType() == Type::Constant) {
        double prev_left = static_cast<Constant*>(m_left.get())->getValue();
        if (prev_left == 0.0) {
            thisRef = std::make_unique<Constant>(0);
        }

    } else if (m_right->getType() == Type::Constant) {
        double prev_right = static_cast<Constant*>(m_right.get())->getValue();
        if (prev_right == 1.0) {
            thisRef.reset(this->releaseLeft());
        } else {
            std::unique_ptr<ASTNode> prevLeftChild(releaseLeft());
            auto new_right = std::make_unique<Constant>(1 / prev_right);
            thisRef = std::make_unique<Multiply>(std::move(prevLeftChild), std::move(new_right));
        }

    } else if (m_right->getType() == Type::UnaryMinus &&
               m_left->getType() == Type::UnaryMinus) {
        std::unique_ptr<ASTNode> prevLeftChild(static_cast<UnaryASTNode*>(m_left.get())->releaseInput());
        std::unique_ptr<ASTNode> prevRightChild(static_cast<UnaryASTNode*>(m_right.get())->releaseInput());
        thisRef = std::make_unique<Divide>(std::move(prevLeftChild), std::move(prevRightChild));
    }
}
void Divide::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}
ASTNode::Type Power::getType() {
    return Type::Power;
}
double Power::evaluate(EvaluationContext& ctx) {
    return std::pow(this->getLeft().evaluate(ctx), this->getRight().evaluate(ctx));
}
void Power::optimize(std::unique_ptr<ASTNode>& thisRef) {
    m_left->optimize(m_left);
    m_right->optimize(m_right);
    if (m_left->getType() == Type::Constant &&
        m_right->getType() == Type::Constant) {
        double prev_left = static_cast<Constant*>(m_left.get())->getValue();
        double prev_right = static_cast<Constant*>(m_right.get())->getValue();

        thisRef = std::make_unique<Constant>(std::pow(prev_left, prev_right));
    } else if (m_left->getType() == Type::Constant) {
        double prev_left = static_cast<Constant*>(m_left.get())->getValue();
        if (prev_left == 0.0) {
            thisRef = std::make_unique<Constant>(0.0);
        } else if (prev_left == 1.0) {
            thisRef = std::make_unique<Constant>(1.0);
        }

    } else if (m_right->getType() == Type::Constant) {
        double prev_right = static_cast<Constant*>(m_right.get())->getValue();
        if (prev_right == 1.0) {
            thisRef.reset(this->releaseLeft());
        } else if (prev_right == 0.0) {
            thisRef = std::make_unique<Constant>(1.0);

        } else if (prev_right == -1.0) {
            std::unique_ptr<ASTNode> prevLeftChild(releaseLeft());
            auto new_left = std::make_unique<Constant>(1);
            thisRef = std::make_unique<Divide>(std::move(new_left), std::move(prevLeftChild));
        }

    } else if (m_right->getType() == Type::UnaryMinus &&
               m_left->getType() == Type::UnaryMinus) {
        std::unique_ptr<ASTNode> prevLeftChild(static_cast<UnaryASTNode*>(m_left.get())->releaseInput());
        std::unique_ptr<ASTNode> prevRightChild(static_cast<UnaryASTNode*>(m_right.get())->releaseInput());
        thisRef = std::make_unique<Divide>(std::move(prevLeftChild), std::move(prevRightChild));
    }
}
void Power::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}
Constant::Constant(double value) : m_double(value) {
}
double Constant::getValue() {
    return m_double;
}

ASTNode::Type Constant::getType() {
    return Type::Constant;
}
double Constant::evaluate(EvaluationContext& ctx) {
    (void) ctx; //suppressing compiler unused parameter warnings
    return getValue();
}
void Constant::optimize(std::unique_ptr<ASTNode>& thisRef) {
    //nothing to be done in here
    (void) thisRef; //suppressing compiler unused parameter warnings
}
void Constant::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}
Parameter::Parameter(size_t idx) : m_idx(idx) {
}
size_t Parameter::getIndex() {
    return m_idx;
}

ASTNode::Type Parameter::getType() {
    return Type::Parameter;
}

double Parameter::evaluate(EvaluationContext& ctx) {
    return ctx.getParameter(m_idx);
}
void Parameter::optimize(std::unique_ptr<ASTNode>& thisRef) {
    //nothing to be done in here
    (void) thisRef; //suppressing compiler unused parameter warnings
}
void Parameter::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}
} // namespace ast
//---------------------------------------------------------------------------
