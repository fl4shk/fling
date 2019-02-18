#include "expression_classes.hpp"

namespace frost_hdl
{

typedef Expression::OpStr OpStr;
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

bool Expression::_has_only_constant_children() const
{
	if (is_leaf())
	{
		return false;
	}

	for (size_t i=0; i<num_children(); ++i)
	{
		if (!_children.at(i)->is_constant())
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

//void ExprLogAnd::evaluate()
//{
//	set_size(1);
//	set_value(_left_child()->value() && _right_child()->value());
//}
//OpStr ExprLogAnd::op_str() const
//{
//	return dup_str("&&");
//}


//ExprBinOpBitAsr::ExprBinOpBitAsr(Expression* left_child,
//	Expression* right_child)
//	: ExprBaseBinOp(left_child, right_child)
//{
//	right_child->set_is_self_determined(true);
//}
//
//void ExprBinOpBitAsr::evaluate()
//{
//}

} // namespace frost_hdl
