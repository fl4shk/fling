#include "symbol_class.hpp"
#include "frost_program_node_class.hpp"
#include "frost_full_type_class.hpp"


namespace frost_hdl
{


//Symbol::Symbol()
//{
//}

Symbol::Symbol()
{
}

Symbol::Symbol(FrostProgramNode* s_lhs_type_name_fpn,
	FrostProgramNode* s_ident_fpn, FrostProgramNode* s_arr_size_fpn,
	ParametersFpnVec&& s_parameters_fpn_vec)
	: _lhs_type_name_fpn(s_lhs_type_name_fpn), _ident_fpn(s_ident_fpn),
	_arr_size_fpn(s_arr_size_fpn),
	_parameters_fpn_vec(s_parameters_fpn_vec)
{
}

Symbol::~Symbol()
{
}

SavedString Symbol::ident() const
{
	return _ident_fpn->ident();
}

FrostFullType Symbol::frost_full_type() const
{
}

} // namespace frost_hdl
