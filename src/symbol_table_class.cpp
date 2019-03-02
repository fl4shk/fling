#include "symbol_table_class.hpp"

namespace frost_hdl
{


Symbol::Symbol(SavedString s_ident, bool s_is_constant,
	HdlType* s_hdl_type, Expression* s_starting_value_expr)
{
	_ident = s_ident;
	_is_constant = s_is_constant;
	_hdl_type = s_hdl_type;
	_starting_value_expr = s_starting_value_expr;
}



} // namespace frost_hdl
