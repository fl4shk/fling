#include "symbol_table_class.hpp"
//#include "expression_classes.hpp"
#include "general_allocator_class.hpp"
#include "expression_builder_class.hpp"

namespace frost_hdl
{


// Non-constant scalar or array constructor
Symbol::Symbol(SavedString s_ident, PortType s_port_type,
	HdlFullType* s_hdl_full_type)
{
	_ident = s_ident;
	_port_type = s_port_type;
	_hdl_full_type = s_hdl_full_type;
	_is_constant = false;
}

	// Constant scalar or array constructor
Symbol::Symbol(SavedString s_ident, PortType s_port_type,
	HdlFullType* s_hdl_full_type, ValueExprs&& s_value_exprs)
{
	_ident = s_ident;
	_port_type = s_port_type;
	_is_constant = true;
	_hdl_full_type = s_hdl_full_type;
	_value_exprs = std::move(s_value_exprs);
	//_right_dim_expr = ExpressionBuilder::make_expr_hc_num
	//	(_value_exprs.size());
}

bool Symbol::has_default_value() const
{
	if (_value_exprs.size() == 0)
	{
		return false;
	}

	for (const auto& iter : _value_exprs)
	{
		if (iter == nullptr)
		{
			return false;
		}
	}

	return true;
}

bool Symbol::becomes_wire() const
{
	return ((_init_block_context != nullptr)
		&& (_driver_block_context != nullptr)
		&& (_driver_block_context->table.front()->driver_type()
		== HdlStatement::DriverType::ContAssign));
}

} // namespace frost_hdl
