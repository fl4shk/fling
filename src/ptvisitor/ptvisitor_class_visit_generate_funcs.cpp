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


	auto module_scope = _stacks.get_top_module_scope();
	module_scope->frost_generate_block_table.push_back
		(save_frost_generate_block_in_module(FrostGenerateBlockInModule
		(_make_src_code_pos(ctx), s_ident)));

	auto curr_generate_block = module_scope->frost_generate_block_table
		.back();

	with(inner_module_scope, with_stacks_module_scope(this,
		&curr_generate_block->module_scope()))
	{
		//_stacks.push_module_scope(&curr_generate_block->module_scope());

		with(top_level_context, with_stacks_small_num(this, SmallNum
			(ModuleOrInterface::Module)))
		{
			if (std::holds_alternative<FrostModule*>(module_scope
				->parent()))
			{
				curr_generate_block->set_parent(std::get
					<FrostModule*>(module_scope->parent()));
			}
			else if (std::holds_alternative<FrostGenerateBlockInModule*>
				(module_scope->parent()))
			{
				curr_generate_block->set_parent(std::get
					<FrostGenerateBlockInModule*>(module_scope->parent()));
			}
			else
			{
				_err(ctx, "PTVisitor::visitGenerateBlockInModule():"
					"  Eek!");
			}

			// The header is accept()ed AFTER creating a new
			// FrostGenerateBlockInModule so that the local_symbol_table
			// can be where the iterator variable of a generate for loop is
			// placed.
			ANY_JUST_ACCEPT_BASIC(ctx->generateBlockAnyHeader());
			curr_generate_block->set_header(_stacks
				.pop_any_generate_block_header());
		}

		// Lastly, go into the scope
		ANY_JUST_ACCEPT_BASIC(ctx->moduleScope());
		//_stacks.pop_module_scope();
	}

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
	const auto s_src_code_pos = _stacks.pop_src_code_pos();

	auto s_ident = _stacks.pop_str();

	const auto s_pseudo_func_call_range = _stacks
		.pop_pseudo_func_call_range();

	//// "generate for" iterator variables are forcibly signed.
	//auto s_frost_lhs_type = save_frost_lhs_type(FrostLhsType
	//	(s_src_code_pos, FrostLhsType
	//	::construct_initial_builtin_type_ident(true,
	//	s_pseudo_func_call_range), true, s_pseudo_func_call_range));
	auto s_frost_lhs_type = _make_for_loop_iter_lhs_type(s_src_code_pos);


	auto s_frost_full_type = save_frost_full_type(FrostFullType
		(s_src_code_pos, s_frost_lhs_type, nullptr));

	auto s_iter_sym = save_symbol(Symbol(s_src_code_pos, s_ident,
		Symbol::PortType::NonPort, s_frost_full_type));

	if (static_cast<ModuleOrInterface>(_stacks.get_top_small_num())
		== ModuleOrInterface::Module)
	{
		// This gives us the ModuleScope of the current generate block
		_stacks.get_top_module_scope()->local_symbol_table.insert_or_assign
			(s_iter_sym);
	}
	else if (static_cast<ModuleOrInterface>(_stacks.get_top_small_num())
		== ModuleOrInterface::Interface)
	{
		//_stacks.get_top_interface_scope()->local_symbol_table
		//	.insert_or_assign(s_iter_sym);
		_err(ctx, "PTVisitor::visitGenerateBlockHeaderForLoop():  You "
			"forgot to implement the case for interfaces!");
	}
	else
	{
		_err(ctx, "PTVisitor::visitGenerateBlockHeaderForLoop():  Eek!");
	}

	_stacks.push_any_generate_block_header(GenerateBlockHeaderFor
		(s_iter_sym, s_pseudo_func_call_range));

	return nullptr;
}
auto PTVisitor::visitGenerateBlockHeaderIf
	(Parser::GenerateBlockHeaderIfContext *ctx)
	-> VisitorRetType
{
	// Dead simple
	ANY_JUST_ACCEPT_BASIC(ctx->stmtBehavHeaderIf());
	_stacks.push_any_generate_block_header(GenerateBlockHeaderIf(_stacks
		.pop_expr()));

	return nullptr;
}

auto PTVisitor::visitPseudoFuncCallRange
	(Parser::PseudoFuncCallRangeContext *ctx)
	-> VisitorRetType
{
	const auto num_exprs = ctx->expr().size();

	ANY_JUST_ACCEPT_LOOPED(expr_iter, ctx->expr())

	if (num_exprs == 1)
	{
		// range(whatever) -> range(0, whatever - 1)
		auto whatever = _stacks.pop_expr();

		//if (whatever->value().is_signed())
		//{
		//	_err(whatever->src_code_pos(), "Signed argument not supported "
		//		"in one-argument range");
		//}

		auto s_left = ExpressionBuilder::make_expr_hc_num_from_expr_num
			(whatever->src_code_pos(), ExprNum(BigNum(0), false));

		// Rarely is this kind of thing actually needed, but dang, it sure
		// is nice to be able to just construct expressions like this from
		// the parser.
		auto one = ExpressionBuilder::make_expr_hc_num_from_expr_num
			(whatever->src_code_pos(), ExprNum(BigNum(1), false));
		auto s_right = ExpressionBuilder::make_expr_binop<ExprBinOpMinus>
			(whatever->src_code_pos(), whatever, one);

		// TODO:  I hope there are no bugs caused by a dependence on
		// thinking I can know some_expr->is_signed() in PTVisitor....
		_stacks.push_pseudo_func_call_range(PseudoFuncCallRange(s_left,
			s_right));
	}
	else if (num_exprs == 2)
	{
		// range(left, right)
		// Dead simple.
		auto s_right = _stacks.pop_expr();
		auto s_left = _stacks.pop_expr();

		//if (s_left->is_signed() != s_right->is_signed())
		//{
		//	_err(s_left, "Left and right expressions of range have "
		//		"mismatched signedness");
		//}
		_stacks.push_pseudo_func_call_range(PseudoFuncCallRange(s_left,
			s_right));
	}
	// Range with an increment of some sort; this may come later.  It may
	// be unnecessary for "generate for" since "generate if" exists (though
	// still potentially useful for "generate for"), but for behavioral
	// code inside an "initial" or "always_<whatever>" block, it might
	// still be useful.
	// ("generate while" might be a good idea to add.)
	//else if (num_exprs == 3)
	//{
	//}
	else
	{
		_err(ctx, "PTVisitor::visitPseudoFuncCallRange():  Eek!");
	}

	return nullptr;
}

} // namespace frost_hdl
