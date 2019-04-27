#include "symbol_class.hpp"


namespace frost_hdl
{


//Symbol::Symbol()
//{
//}

Symbol::Symbol()
{
}

Symbol::Symbol(FrostProgramNode* s_lhs_type_name_fpn,
	FrostProgramNode* s_ident_fpn, FrostProgramNode* s_arr_size_fpn)
	: _lhs_type_name_fpn(s_lhs_type_name_fpn), _ident_fpn(s_ident_fpn),
	_arr_size_fpn(s_arr_size_fpn)
{
}

Symbol::Symbol(FrostProgramNode* s_lhs_type_name_fpn,
	FrostProgramNode* s_ident_fpn, FrostProgramNode* s_arr_size_fpn,
	FrostLhsType* s_frost_lhs_type)
	: Symbol(s_lhs_type_name_fpn, s_ident_fpn, s_arr_size_fpn)
{
	_frost_lhs_type = s_frost_lhs_type;
}

Symbol::~Symbol()
{
}

} // namespace frost_hdl
