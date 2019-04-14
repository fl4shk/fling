#include "../ptvisitor_class.hpp"
#include "../general_allocator_class.hpp"
#include "../expression_builder_class.hpp"
#include <sstream>

#include "dot_cpp_defines.hpp"


namespace frost_hdl
{

// "module" stuff
auto PTVisitor::visitDeclModule
	(Parser::DeclModuleContext *ctx)
	-> VisitorRetType
{
	if (pass() == Pass::ListModuleIdentifiers)
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		auto s_ident = _stacks.pop_str();

		auto& frost_module_table = _frost_program.frost_module_table;
		auto& curr_frost_module = _frost_program.curr_frost_module;

		if (frost_module_table.contains(s_ident))
		{
			_err(ctx, sconcat("Duplicate module called \"", *s_ident,
				"\", previously declared at ", frost_module_table.at
				(s_ident)->src_code_pos().convert_to_errwarn_string(),
				"."));
		}


		curr_frost_module = save_frost_module(FrostModule
			(_make_src_code_pos(ctx), s_ident));

		curr_frost_module->module_scope() = ModuleScope(curr_frost_module);

		_stacks.push_module_scope(&curr_frost_module->module_scope());

		// Process "parameter"s of this module.
		ANY_ACCEPT_IF_BASIC(ctx->declParameterVarList())

		// Process ports of this module
		ANY_JUST_ACCEPT_LOOPED(port_list_iter,
			ctx->declPortDirectionalVarList())

		frost_module_table.insert_or_assign(curr_frost_module);

		_stacks.pop_module_scope();
	}
	else if ((pass() == Pass::ListModuleInnerDecl)
		|| (pass() == Pass::FinishRawModuleConstruct))
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		auto& curr_frost_module = _frost_program.curr_frost_module;

		curr_frost_module = _frost_program.frost_module_table.at(_stacks
			.pop_str());

		_stacks.push_module_scope(&curr_frost_module->module_scope());
		ANY_JUST_ACCEPT_BASIC(ctx->moduleScope());
		_stacks.pop_module_scope();
	}
	else
	{
		_err(ctx, "PTVisitor::visitDeclModule():  Eek!");
	}


	return nullptr;
}

auto PTVisitor::visitModuleScope
	(Parser::ModuleScopeContext *ctx)
	-> VisitorRetType
{
	//if (_stacks.module_scope_inner_stack().size() == 0)
	//{
	//	auto module = _frost_program.curr_frost_module;
	//}

	//ANY_JUST_ACCEPT_LOOPED(decl_localparam_list_iter,
	//	ctx->declLocalparamList())

	if (pass() == Pass::ListModuleInnerDecl)
	{
		ANY_JUST_ACCEPT_LOOPED(decl_localparam_list_iter,
			ctx->declLocalparamList())

		ANY_JUST_ACCEPT_LOOPED(decl_var_list_iter, ctx->declVarList())

		// Do this AFTER the others.
		ANY_JUST_ACCEPT_LOOPED(generate_block_in_module_iter,
			ctx->generateBlockInModule())
	}

	// Only process these other things AFTER we know about declared
	// variables and stuff.
	else if (pass() == Pass::FinishRawModuleConstruct)
	{
		ANY_JUST_ACCEPT_LOOPED(module_stmt_cont_assign_iter,
			ctx->moduleStmtContAssign())
		//ANY_JUST_ACCEPT_LOOPED(module_stmt_behav_block_iter,
		//	ctx->moduleStmtBehavBlock())
		//ANY_JUST_ACCEPT_LOOPED(module_stmt_instantiate_module_iter,
		//	ctx->moduleStmtInstantiateModule())
	}

	return nullptr;
}

auto PTVisitor::visitModuleStmtContAssign
	(Parser::ModuleStmtContAssignContext *ctx)
	-> VisitorRetType
{
	//auto module = _frost_program.curr_frost_module;
	auto module_scope = _stacks.get_top_module_scope();

	ANY_JUST_ACCEPT_BASIC(ctx->identExpr());
	auto s_lhs_expr = _stacks.pop_expr();

	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	auto s_rhs_expr = _stacks.pop_expr();


	//typedef Expression::LhsCategory ExprLhsCategory;

	//auto s_frost_statement = save_frost_statement(FrostStmtContAssign
	//	(s_lhs_expr, s_rhs_expr));

	// For continuous assignments in particular, there's no need to use
	// "_stacks" to keep track of the statement scoping top node.
	module_scope->frost_statement_table.insert(module_scope
		->frost_statement_table.next_top_node(), FrostStmtContAssign
		(_make_src_code_pos(ctx), s_lhs_expr, s_rhs_expr));


	return nullptr;
}
//auto visitModuleStmtBehavBlock
//	(Parser::ModuleStmtBehavBlockContext *ctx)
//	-> VisitorRetType
//{
//	return nullptr;
//}
auto PTVisitor::visitModuleStmtInstantiateModule
	(Parser::ModuleStmtInstantiateModuleContext *ctx)
	-> VisitorRetType
{
	_err(ctx, "PTVisitor::visitModuleStmtInstantiateModule():  "
		"not implemented Eek!");
	//ANY_JUST_ACCEPT_BASIC(ctx->identName());
	//auto ident = _stacks.pop_str();

	//if (ctx->instantiateModulePortsList())
	//{
	//	ANY_ACCEPT_IF_BASIC(ctx->instantiateModulePortsList());
	//}
	//else // if (!ctx->instantiateModulePortsList())
	//{
	//}

	return nullptr;
}
auto PTVisitor::visitInstantiateModulePortsList
	(Parser::InstantiateModulePortsListContext *ctx)
	-> VisitorRetType
{
	_err(ctx, "PTVisitor::visitInstantiateModulePortsList():  "
		"not implemented Eek!");
	return nullptr;
}

} // namespace frost_hdl
