#include "hdl_full_type_table_class.hpp"
#include "expression_classes.hpp"

namespace frost_hdl
{

HdlFullType::HdlFullType(SavedString s_ident, HdlLhsType* s_hdl_lhs_type,
	Expression* s_right_dim_expr)
	: _ident(s_ident), _hdl_lhs_type(s_hdl_lhs_type),
	_right_dim_expr(s_right_dim_expr)
{
}

bool HdlFullType::operator == (const HdlFullType& other) const
{
	//return ((_hdl_lhs_type == other._hdl_lhs_type)
	//	&& (_right_dim_expr->value()
	//	== other._right_dim_expr->value()));

	//if ((*_hdl_lhs_type) == (*other._hdl_lhs_type))

	// The addresses of two "HdlLhsType"s *must* be the same in all cases
	// for them to be the same researcher, even for built-in "HdlLhsType"s.
	//
	// How am I going to be able to evaluate the left dimension of an
	// "HdlLhsType"?
	if (_hdl_lhs_type == other._hdl_lhs_type)
	{
		if (_right_dim_expr == other._right_dim_expr)
		{
			return true;
		}
		else if (is_array() && other.is_array()
			&& (_right_dim_expr->value()
			== other._right_dim_expr->value()))
		{
			return true;
		}
		return false;
	}
	return false;
}

size_t HdlFullType::right_dim() const
{
	return (_right_dim_expr != nullptr)
		? BigNum(_right_dim_expr->value()).get_ui() : 1;
	//return (_right_dim_expr != nullptr)
	//	? _right_dim_expr->value().convert_to_unsigned_bignum() : 1;
}

} // namespace frost_hdl
