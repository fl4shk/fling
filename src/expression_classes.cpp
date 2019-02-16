#include "expression_classes.hpp"

namespace frost_hdl
{

typedef Expression::OpStr OpStr;
//typedef Expression::MemberName MemberName;
//typedef Expression::Category Category;

Expression::Expression()
{
	for (auto& iter : _children)
	{
		iter = nullptr;
	}

	_ident = nullptr;
	//_value = nullptr;
	//_size = nullptr;
	_is_constant = false;
}


void Expression::evaluate()
{
	//set_value(0);
}
OpStr Expression::op_str() const
{
	return dup_str("INVALID_EXPRESSION");
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
	_is_constant = _has_only_constant_children(only_child);

	// We do this regardless of whether or not this expression is constant.
	evaluate();
}

ExprBaseBinOp::ExprBaseBinOp(Expression* left_child,
	Expression* right_child)
{
	_is_constant = _has_only_constant_children(left_child, right_child);

	// We do this regardless of whether or not this expression is constant.
	evaluate();
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



} // namespace frost_hdl
