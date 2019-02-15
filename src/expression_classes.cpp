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
	_value = nullptr;
	_size = nullptr;
	_is_constant = false;
}

Expression::~Expression()
{
}

void Expression::evaluate()
{
	_value = cstm_num_dup(0);
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

void ExprLogAnd::evaluate()
{
	set_size(1);
	set_value(_left_child()->value() && _right_child()->value());
}
OpStr ExprLogAnd::op_str() const
{
	return cstm_str_dup("&&");
}


void ExprLogOr::evaluate()
{
	set_size(1);
	set_value(_left_child()->value() || _right_child()->value());
}
OpStr ExprLogOr::op_str() const
{
	return cstm_str_dup("||");
}

void ExprCmpEq::evaluate()
{
	set_size(1);
	set_value(_left_child()->value() == _right_child()->value());
}
OpStr ExprCmpEq::op_str() const
{
	return cstm_str_dup("==");
}

void ExprCmpNe::evaluate()
{
	set_size(1);
	set_value(_left_child()->value() != _right_child()->value());
}
OpStr ExprCmpNe::op_str() const
{
	return cstm_str_dup("!=");
}

void ExprCmpLt::evaluate()
{
	set_size(1);
	set_value(_left_child()->value() < _right_child()->value());
}
OpStr ExprCmpLt::op_str() const
{
	return cstm_str_dup("<");
}

void ExprCmpGt::evaluate()
{
	set_size(1);
	set_value(_left_child()->value() > _right_child()->value());
}
OpStr ExprCmpGt::op_str() const
{
	return cstm_str_dup(">");
}

void ExprCmpLe::evaluate()
{
	set_size(1);
	set_value(_left_child()->value() <= _right_child()->value());
}
OpStr ExprCmpLe::op_str() const
{
	return cstm_str_dup("<=");
}

void ExprCmpGe::evaluate()
{
	set_size(1);
	set_value(_left_child()->value() >= _right_child()->value());
}
OpStr ExprCmpGe::op_str() const
{
	return cstm_str_dup(">=");
}

void ExprBinOpPlus::evaluate()
{
	set_size(max(_left_child()->size(), _right_child()->size()));
	set_value(_left_child()->value() + _right_child()->value());
}
OpStr ExprBinOpPlus::op_str() const
{
	return cstm_str_dup("+");
}

void ExprBinOpMinus::evaluate()
{
	set_size(max(_left_child()->size(), _right_child()->size()));
	set_value(_left_child()->value() + _right_child()->value());
}
OpStr ExprBinOpMinus::op_str() const
{
	return cstm_str_dup("-");
}

} // namespace frost_hdl
