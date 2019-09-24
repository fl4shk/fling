#include "../expression_class.hpp"
#include "expr_ternary_class.hpp"
#include "dot_cpp_defines.hpp"

namespace frost_hdl
{

ExprTernary::ExprTernary(const SrcCodePos& s_src_code_pos,
	Expression* condition_child, Expression* when_true_child,
	Expression* when_false_child)
	: Expression(s_src_code_pos)
{
	_set_children(condition_child, when_true_child, when_false_child);
	//_value.set_size(_starting_length());
	//_value.set_is_signed(_when_true_child_value().is_signed()
	//	&& _when_false_child_value().is_signed());
	set_handles_children_eval(true);
}

void ExprTernary::_evaluate()
{
	_condition_child()->inner_full_evaluate();

	if (static_cast<BigNum>(_condition_child_value()))
	{
		_when_true_child()->inner_full_evaluate();
		//_value.copy_from_bignum(static_cast<BigNum>
		//	(_when_true_child_value()));
		_value = _when_true_child_value();
	}
	else // if (!static_cast<BigNum>(_condition_child_value()))
	{
		_when_false_child()->inner_full_evaluate();
		_value = _when_false_child_value();
	}
}

} // namespace frost_hdl
