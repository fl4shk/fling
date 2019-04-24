#include "../expression_class.hpp"
#include "../symbol_class.hpp"
#include "expr_hard_coded_num_classes.hpp"
#include "dot_cpp_defines.hpp"

namespace frost_hdl
{

ExprIdentSizedHardCodedNum::ExprIdentSizedHardCodedNum
	(const SrcCodePos& s_src_code_pos, Expression* s_size_expr,
	const BigNum& s_temp_value)
	: Expression(s_src_code_pos)
{
	_size_expr = s_size_expr;
	_temp_value = s_temp_value;
	set_handles_value_set_size(true);
}
void ExprIdentSizedHardCodedNum::_inner_finish_init_value()
{
	_set_value(ExprNum(_temp_value, _starting_length(), false));
}
size_t ExprIdentSizedHardCodedNum::_starting_length() const
{
	return static_cast<BigNum>(_size_expr->symbol()->value()->value())
		.get_ui();
}

} // namespace frost_hdl
