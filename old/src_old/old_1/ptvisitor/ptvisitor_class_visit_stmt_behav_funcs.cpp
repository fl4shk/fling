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
	const auto s_src_code_pos = _make_src_code_pos(ctx->identName());

	auto s_frost_lhs_type = _make_for_loop_iter_lhs_type(s_src_code_pos);
	_stacks.push_full_type(save_frost_full_type(FrostFullType
		(s_src_code_pos, s_frost_lhs_type, nullptr)));

	_stacks.push_src_code_pos(s_src_code_pos);

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
auto PTVisitor::visitStmtBehavHeaderElseif
	(Parser::StmtBehavHeaderElseifContext *ctx)
	-> VisitorRetType
{
	// This is simple
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	return nullptr;
}
auto PTVisitor::visitStmtBehavHeaderElse
	(Parser::StmtBehavHeaderElseContext *ctx)
	-> VisitorRetType
{
	// This time I actually *don't* want to do anything else here.
	return nullptr;
};


} // namespace frost_hdl
