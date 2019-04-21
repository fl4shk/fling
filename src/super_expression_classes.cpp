#include "super_expression_classes.hpp"

namespace frost_hdl
{

SuperExpression::SuperExpression(const SrcCodePos& s_src_code_pos)
	: HasSrcCodePosBase(s_src_code_pos)
{
}
SuperExpression::~SuperExpression()
{
}

} // namespace frost_hdl
