#ifndef H_lib_ASTVisitor
#define H_lib_ASTVisitor
//---------------------------------------------------------------------------
namespace ast {

class UnaryPlus;
class UnaryMinus;
class Add;
class Subtract;
class Multiply;
class Divide;
class Power;
class Constant;
class Parameter;

class ASTVisitor
{
private:
    /* data */
public:
    virtual void visit( UnaryPlus&) = 0;
    virtual void visit( UnaryMinus&) = 0;
    virtual void visit( Add&) = 0;
    virtual void visit( Subtract&) = 0;
    virtual void visit( Multiply&) = 0;
    virtual void visit( Divide&) = 0;
    virtual void visit( Power&) = 0;
    virtual void visit( Constant&) = 0;
    virtual void visit( Parameter&) = 0;
    ~ASTVisitor() = default;
};
} // namespace ast
//---------------------------------------------------------------------------
#endif
