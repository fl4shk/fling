#include "../ptvisitor_class.hpp"
#include "../general_allocator_class.hpp"
#include "../expression_builder_class.hpp"
#include <sstream>

#include "dot_cpp_defines.hpp"


namespace frost_hdl
{

auto PTVisitor::visitStmtBehavHeaderForLoop
	(Parser::StmtBehavHeaderForLoopContext *ctx)
	-> VisitorRetType
{
	// This is simple
	_stacks.push_src_code_pos(_make_src_code_pos(ctx->identName()));
	ANY_JUST_ACCEPT_BASIC(ctx->identName());
	ANY_JUST_ACCEPT_BASIC(ctx->pseudoFuncCallRange());
	return nullptr;
}

auto PTVisitor::visitStmtBehavHeaderIf
	(Parser::StmtBehavHeaderIfContext *ctx)
	-> VisitorRetType
{
	// This is simple
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	return nullptr;
}

} // namespace frost_hdl
