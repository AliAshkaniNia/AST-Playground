#ifndef H_lib_EvaluationContext
#define H_lib_EvaluationContext
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
namespace ast {
class EvaluationContext {
    public:
    void pushParameter(double value);
    double getParameter(size_t idx);

    protected:
    std::vector<double> m_values;
};
} // namespace ast
//---------------------------------------------------------------------------
#endif
