#include "../expression_class.hpp"
#include "expr_bin_op_classes.hpp"
#include "dot_cpp_defines.hpp"

namespace frost_hdl
{

ExprBaseBinOp::ExprBaseBinOp(const SrcCodePos& s_src_code_pos,
	Expression* left_child, Expression* right_child)
	: Expression(s_src_code_pos)
{
	_set_children(left_child, right_child);
}

} // namespace frost_hdl
