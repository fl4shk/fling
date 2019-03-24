#include "symbol_table_class.hpp"
//#include "expression_classes.hpp"
#include "general_allocator_class.hpp"
#include "expression_builder_class.hpp"

namespace frost_hdl
{

// For when we don't know the "Symbol"'s type yet.
Symbol::Symbol(const SrcCodePos& s_src_code_pos, SavedString s_ident,
	PortType s_port_type)
{
	_src_code_pos = s_src_code_pos;
	_ident = s_ident;
	_port_type = s_port_type;
	_frost_full_type = nullptr;
	_is_constant = false;
	_value = nullptr;
}

// Non-constant scalar or array constructor
Symbol::Symbol(const SrcCodePos& s_src_code_pos, SavedString s_ident,
	PortType s_port_type, FrostFullType* s_frost_full_type)
{
	_src_code_pos = s_src_code_pos;
	_ident = s_ident;
	_port_type = s_port_type;
	_frost_full_type = s_frost_full_type;
	_is_constant = false;
	_value = nullptr;
}

// Constant scalar constructor
Symbol::Symbol(const SrcCodePos& s_src_code_pos, SavedString s_ident,
	PortType s_port_type, FrostFullType* s_frost_full_type,
	Expression* s_value)
{
	_src_code_pos = s_src_code_pos;
	_ident = s_ident;
	_port_type = s_port_type;
	_is_constant = true;
	_frost_full_type = s_frost_full_type;
	_value = s_value;
	//_value_exprs = std::move(s_value_exprs);
	//_right_dim_expr = ExpressionBuilder::make_expr_hc_num
	//	(_value_exprs.size());
}

bool Symbol::has_default_value() const
{
	//if (_value_exprs.size() == 0)
	//{
	//	return false;
	//}

	//for (const auto& iter : _value_exprs)
	//{
	//	if (iter == nullptr)
	//	{
	//		return false;
	//	}
	//}

	//return true;

	return (_value != nullptr);
}

//bool Symbol::becomes_wire() const
//{
//	return ((_init_block_context != nullptr)
//		&& (_driver_block_context != nullptr)
//		&& (_driver_block_context->table.front()->driver_type()
//		== FrostStatement::DriverType::ContAssign));
//}

} // namespace frost_hdl
