#include "symbol_class.hpp"
#include "frost_program_node_class.hpp"
#include "frost_full_type_class.hpp"


namespace frost_hdl
{


Symbol::Symbol()
{
}

Symbol::Symbol(SavedString s_ident, FrostProgramNode* s_var_decl_fpn)
	: _ident(s_ident), _var_decl_fpn(s_var_decl_fpn)
{
}

Symbol::~Symbol()
{
}

//FrostFullType Symbol::frost_full_type() const
//{
//	return FrostFullType();
//}

} // namespace frost_hdl
