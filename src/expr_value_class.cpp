#include "expr_value_class.hpp"

namespace frost_hdl
{

ExprValue::ExprValue()
{
	make_hold_expr_num();
}
ExprValue::ExprValue(const string& s_ident)
	: ExprValue()
{
	_ident = s_ident;
}
ExprValue::ExprValue(string&& s_ident)
	: ExprValue()
{
	_ident = std::move(s_ident);
}
ExprValue::~ExprValue()
{
}

} // namespace frost_hdl
