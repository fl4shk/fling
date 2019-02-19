#include "expression_classes.hpp"

namespace frost_hdl
{

//typedef Expression::OpStr OpStr;
//typedef Expression::Type ExprType;

Expression::Expression()
{
	for (auto& iter : _children)
	{
		iter = nullptr;
	}

	_ident = nullptr;
	set_is_self_determined(false);

}


void Expression::evaluate()
{
	set_value(ExprNum(0, 1, false));
}

//OpStr Expression::op_str() const
//{
//	return dup_str("INVALID_EXPRESSION");
//}

bool Expression::_children_affect_length() const
{
	return true;
}
size_t Expression::_starting_length() const
{
	return 0;
}

bool Expression::_is_always_constant() const
{
	return false;
}

bool Expression::_has_any_unsigned_non_self_determined_children() const
{
	for (const auto& child : _children)
	{
		if ((!child->value().is_signed())
			&& (!child->is_self_determined()))
		{
			return true;
		}
	}

	return false;
}

bool Expression::_has_only_constant_children() const
{
	if (is_leaf())
	{
		return false;
	}

	for (const auto& child : _children)
	{
		if (!child->is_constant())
		{
			return false;
		}
	}

	return true;
}

ExprBaseUnOp::ExprBaseUnOp(Expression* only_child)
{
	_set_children(only_child);
}

ExprBaseBinOp::ExprBaseBinOp(Expression* left_child,
	Expression* right_child)
{
	_set_children(left_child, right_child);
}

void ExprBinOpBitLsl::evaluate()
{

	for (BigNum i=0; i<BigNum(_right_child_value()); ++i)
	{
		set_value(ExprNum(BigNum(value()) * 2, value().size(),
			value().is_signed()));
	}
}

void ExprBinOpBitLsr::evaluate()
{
}

void ExprBinOpBitAsr::evaluate()
{
}

} // namespace frost_hdl
