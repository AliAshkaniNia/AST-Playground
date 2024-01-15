#include "lib/EvaluationContext.hpp"
//---------------------------------------------------------------------------
namespace ast {
void EvaluationContext::pushParameter(double value) {
    m_values.push_back(value);
}
double EvaluationContext::getParameter(size_t idx) {
    //no need to do bound checking as stated in the requirements
    return m_values.at(idx);
}

} // namespace ast
//---------------------------------------------------------------------------
