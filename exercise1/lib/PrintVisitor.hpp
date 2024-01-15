#ifndef H_lib_PrintVisitor
#define H_lib_PrintVisitor
#include "ASTVisitor.hpp"
//---------------------------------------------------------------------------
namespace ast {
class PrintVisitor: public ASTVisitor
{
public:

    void visit( UnaryPlus&) override;
    void visit( UnaryMinus&) override;
    void visit( Add&) override;
    void visit( Subtract&) override;
    void visit( Multiply&) override;
    void visit( Divide&) override;
    void visit( Power&) override;
    void visit( Constant&) override;
    void visit( Parameter&) override;
};
} // namespace ast
//---------------------------------------------------------------------------
#endif
