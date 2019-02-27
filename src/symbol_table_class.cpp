#include "symbol_table_class.hpp"

namespace frost_hdl
{


Symbol::Symbol(SavedString s_ident, HdlType* s_hdl_type)
{
	_ident = s_ident;
	_value = nullptr;
}

Symbol::Symbol(SavedString s_ident, HdlType* s_hdl_type, ExprNum* s_value)
{
	_ident = s_ident;
	_hdl_type = s_hdl_type;
	_value = s_value;
}



} // namespace frost_hdl
