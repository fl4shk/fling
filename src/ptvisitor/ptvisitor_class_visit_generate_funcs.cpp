#include "../ptvisitor_class.hpp"
#include "../general_allocator_class.hpp"
#include "../expression_builder_class.hpp"
#include <sstream>

#include "dot_cpp_defines.hpp"

#include "../frost_generate_block_classes.hpp"


namespace frost_hdl
{

auto PTVisitor::visitGenerateBlockInModule
	(Parser::GenerateBlockInModuleContext *ctx)
	-> VisitorRetType
{
	SavedString s_ident = nullptr;
	if (ctx->identName())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		s_ident = _stacks.pop_str();
	}

	ANY_JUST_ACCEPT_BASIC(ctx->generateBlockAnyHeader());

	auto curr_module_scope = _stacks.get_top_module_scope();

	curr_module_scope->frost_generate_block_table.push_back
		(save_frost_generate_block_in_module(FrostGenerateBlockInModule
		(_make_src_code_pos(ctx), s_ident, s_header)));

	_stacks.push_module_scope(&curr_module_scope
		->frost_generate_block_table.back()->module_scope());
	ANY_JUST_ACCEPT_BASIC(ctx->moduleScope());
	_stacks.pop_module_scope();

	return nullptr;
}
auto PTVisitor::visitGenerateBlockAnyHeader
	(Parser::GenerateBlockAnyHeaderContext *ctx)
	-> VisitorRetType
{
	ANY_ACCEPT_IF_BASIC(ctx->generateBlockHeaderForLoop())
	else ANY_ACCEPT_IF_BASIC(ctx->generateBlockHeaderIf())
	else
	{
		_err(ctx, "PTVisitor::visitGenerateBlockAnyHeader():  Eek!");
	}
	return nullptr;
}
auto PTVisitor::visitGenerateBlockHeaderForLoop
	(Parser::GenerateBlockHeaderForLoopContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->stmtBehavHeaderForLoop());

	return nullptr;
}
auto PTVisitor::visitGenerateBlockHeaderIf
	(Parser::GenerateBlockHeaderIfContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->stmtBehavHeaderIf());

	return nullptr;
}

auto PTVisitor::visitPseudoFuncCallRange
	(Parser::PseudoFuncCallRangeContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

} // namespace frost_hdl
