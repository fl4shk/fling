#include "expression_classes.hpp"

namespace frost_hdl
{

Expression::Expression()
{
	for (auto& iter : _children)
	{
		iter = nullptr;
	}

	_value = 0;
	_size = 0;
	_is_constant = false;
}

Expression::~Expression()
{
}

bool Expression::_any_children_are_constant() const
{
	for (size_t i=0; i<num_children(); ++i)
	{
		if (_children.at(i)->is_constant())
		{
			return true;
		}
	}

	return false;
}

ExprLogAnd::ExprLogAnd(Expression* left, Expression* right)
{
	ASM_COMMENT("_set_children(left, right)");

	_set_children(left, right);
}

} // namespace frost_hdl
