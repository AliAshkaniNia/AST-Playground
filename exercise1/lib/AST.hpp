#ifndef H_lib_AST
#define H_lib_AST
//---------------------------------------------------------------------------
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
};
//---------------------------------------------------------------------------
} // namespace ast
//---------------------------------------------------------------------------
#endif
