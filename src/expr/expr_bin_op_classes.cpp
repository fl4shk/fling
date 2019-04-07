#include "../expression_class.hpp"
#include "expr_bin_op_classes.hpp"
#include "dot_cpp_defines.hpp"

namespace frost_hdl
{

void ExprBinOpBitLsl::_evaluate()
{
	_value.perf_lsl(_left_child_value(), _right_child_value());
}

void ExprBinOpBitLsr::_evaluate()
{
	_value.perf_lsr(_left_child_value(), _right_child_value());
}

void ExprBinOpBitAsr::_evaluate()
{
	_value.perf_asr(_left_child_value(), _right_child_value());
}

ExprBaseBinOp::ExprBaseBinOp(const SrcCodePos& s_src_code_pos,
	Expression* left_child, Expression* right_child)
	: Expression(s_src_code_pos)
{
	_set_children(left_child, right_child);
}

} // namespace frost_hdl
