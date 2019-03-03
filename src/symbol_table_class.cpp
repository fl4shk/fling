#include "symbol_table_class.hpp"
//#include "expression_classes.hpp"
#include "general_allocator_class.hpp"
#include "expression_builder_class.hpp"

namespace frost_hdl
{

//Symbol::Symbol(SavedString s_ident, bool s_is_constant,
//	HdlType* s_hdl_type, Dimension s_right_dim_expr)
//{
//}
//
//Symbol::Symbol(SavedString s_ident, bool s_is_constant,
//	HdlType* s_hdl_type, ValueExprs&& s_value_exprs)
//{
//	_ident = s_ident;
//	_is_constant = s_is_constant;
//	_hdl_type = s_hdl_type;
//	_value_exprs = std::move(s_value_expr);
//	_right_dim_expr = ExpressionBuilder::make_expr_hc_num
//		(_value_exprs.size(), (sizeof(_value_exprs.size()) * sizeof(u8)),
//		false);
//}

// Scalar constructors
// Non-constant scalar constructor
Symbol::Symbol(SavedString s_ident, HdlType* s_hdl_type)
{
	_ident = s_ident;
	_hdl_type = s_hdl_type;
	_is_constant = false;
	_right_dim_expr = nullptr;
}

// Constant scalar constructor, or non-constant array constructor
Symbol::Symbol(SavedString s_ident, HdlType* s_hdl_type,
	bool s_is_array, Expression* two_uses)
{
	if (!s_is_array)
	{
		_ident = s_ident;
		_hdl_type = s_hdl_type;
		_is_constant = true;
		_right_dim_expr = nullptr;
		_value_exprs.push_back(two_uses);
	}
	else // if (s_is_array)
	{
		_ident = s_ident;
		_is_constant = false;
		_hdl_type = s_hdl_type;
		_right_dim_expr = two_uses;
	}
}

// Constant array constructor
Symbol::Symbol(SavedString s_ident, HdlType* s_hdl_type,
	ValueExprs&& s_value_exprs)
{
	_ident = s_ident;
	_is_constant = true;
	_hdl_type = s_hdl_type;
	_value_exprs = std::move(s_value_exprs);
	_right_dim_expr = ExpressionBuilder::make_expr_hc_num
		(_value_exprs.size());
}

bool Symbol::has_default_value() const
{
	for (const auto& iter : _value_exprs)
	{
		if (iter == nullptr)
		{
			return false;
		}
	}
	return true;
}

} // namespace frost_hdl
