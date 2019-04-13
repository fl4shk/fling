#include "../parse_tree_visitor_class.hpp"
#include "../general_allocator_class.hpp"
#include "../expression_builder_class.hpp"
#include <sstream>

#include "dot_cpp_defines.hpp"


namespace frost_hdl
{

// Array dimensions go here
auto ParseTreeVisitor::visitDeclNoLhsTypeVar
	(Parser::DeclNoLhsTypeVarContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->identName());

	// array
	if (ctx->expr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->expr());

		auto s_right_dim_expr = _stacks.get_top_expr();

		if (!s_right_dim_expr->is_constant())
		{
			_err(ctx->expr(), "Arrays must have constant dimensions.");
			//_in_scope_thing()->in_scope_err(_make_src_code_pos
			//	(ctx->expr()), "Arrays must have constant dimensions.");
		}

		_stacks.push_small_num(static_cast<SmallNum>
			(ScalarOrArray::Array));
	}
	// scalar
	else
	{
		_stacks.push_small_num(static_cast<SmallNum>
			(ScalarOrArray::Scalar));
	}

	return nullptr;
}

// List of local variables
auto ParseTreeVisitor::visitDeclVarList
	(Parser::DeclVarListContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->lhsTypeName());
	auto s_frost_lhs_type = _stacks.pop_lhs_type();

	for (auto iter : ctx->declNoLhsTypeVar())
	{
		const SrcCodePos s_src_code_pos(_make_src_code_pos(iter));
		//auto module = _frost_program.curr_frost_module;
		auto module_scope = _stacks.get_top_module_scope();

		ANY_JUST_ACCEPT_BASIC(iter);
		auto s_ident = _stacks.pop_str();

		if (module_scope->contains_symbol(s_ident))
		{
			auto&& errwarn_string = module_scope->find_symbol(s_ident)
				->src_code_pos().convert_to_errwarn_string();
			//_err(s_src_code_pos, sconcat("Module \"", *module_scope
			//	->ident(), "\" already contains a symbol with identifier ",
			//	"\"", *s_ident, "\" at ", errwarn_string, "."));
			//module_scope->in_scope_err(_make_src_code_pos(iter), sconcat
			//	("This scope already contains a symbol called \"",
			//	*s_ident, "\", defined at ", errwarn_string, "."));
			_err(iter, sconcat("This scope already contains a symbol ",
				"called \"", *s_ident, "\", defined at ", errwarn_string,
				"."));
		}

		const ScalarOrArray scalar_or_array = static_cast<ScalarOrArray>
			(_stacks.pop_small_num());

		Expression* s_right_dim_expr = nullptr;

		switch (scalar_or_array)
		{
		case ScalarOrArray::Scalar:
			break;

		case ScalarOrArray::Array:
			s_right_dim_expr = _stacks.pop_expr();
			break;

		default:
			_err(ctx, "ParseTreeVisitor::visitDeclVarList():  Eek!");
			break;
		}


		auto s_frost_full_type = save_frost_full_type(FrostFullType
			(s_src_code_pos, s_frost_lhs_type, s_right_dim_expr));

		module_scope->local_symbol_table.insert_or_assign(save_symbol
			(Symbol(s_src_code_pos, s_ident, Symbol::PortType::NonPort,
			s_frost_full_type)));
	}

	return nullptr;
}

auto ParseTreeVisitor::visitDeclNoKwLocalparam
	(Parser::DeclNoKwLocalparamContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->identName());
	auto s_ident = _stacks.pop_str();


	const SrcCodePos s_src_code_pos(_make_src_code_pos(ctx));

	if ((pass() == Pass::ListPackageInnerDecl)
		// || (pass() == Pass::ListInterfaceInnerDecl)
		|| (pass() == Pass::ListModuleInnerDecl))
	{
		SymbolTable* symbol_table = nullptr;

		// Error checking
		if (_in_package_pass())
		{
			auto package = _frost_program.curr_frost_package;

			if (package->symbol_table().contains(s_ident))
			{
				auto&& errwarn_string = package->symbol_table().at(s_ident)
					->src_code_pos().convert_to_errwarn_string();
				//package->in_scope_err(s_src_code_pos, sconcat
				//	("This package already has a localparam called \"", 
				//	*s_ident,  "\", defined at ",
				//	errwarn_string, "."));
				_err(s_src_code_pos, sconcat ("This package already has ",
					"a localparam called \"", *s_ident,  "\", defined at ",
					errwarn_string, "."));
			}

			symbol_table = &package->symbol_table();
		}
		//else if (_in_interface_pass())
		//{
		//	auto interface = _frost_program.curr_frost_interface;

		//	if (interface->symbol_table().contains(s_ident))
		//	{
		//		auto&& errwarn_string = interface->symbol_table()
		//			.at(s_ident)->src_code_pos()
		//			.convert_to_errwarn_string();
		//		interface->in_scope_err(s_src_code_pos, sconcat
		//			("This interface already has a localparam called \"", 
		//			*s_ident,  "\", defined at ",
		//			errwarn_string, "."));
		//	}

		//	symbol_table = &interface->symbol_table();
		//}
		else if (_in_module_pass())
		{
			//auto module = _frost_program.curr_frost_module;
			auto module_scope = _stacks.get_top_module_scope();

			if (module_scope->contains_symbol(s_ident))
			{
				auto&& errwarn_string = module_scope->find_symbol(s_ident)
					->src_code_pos().convert_to_errwarn_string();
				//module_scope->in_scope_err(s_src_code_pos, sconcat("This ",
				//	"scope already has a symbol called \"", *s_ident, 
				//	"\", defined at ", errwarn_string, "."));
				_err(s_src_code_pos, sconcat("This scope already has a ",
					"symbol called \"", *s_ident, "\", defined at ",
					errwarn_string, "."));
			}

			symbol_table = &module_scope->local_symbol_table;
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitDeclNoKwLocalparam():  "
				"InnerDecl pass() Eek!");
		}

		//symbol_table->insert_or_assign(save_symbol(Symbol(s_src_code_pos,
		//	s_ident, Symbol::PortType::NonPort)));
		symbol_table->insert_or_assign(save_symbol(Symbol(s_src_code_pos,
			s_ident)));
	}
	else if ((pass() == Pass::FinishRawPackageConstruct)
		//|| (pass() == Pass::FinishRawInterfaceConstruct)
		|| (pass() == Pass::FinishRawModuleConstruct))
	{
		ANY_JUST_ACCEPT_BASIC(ctx->expr());
		auto s_value = _stacks.pop_expr();

		Symbol* existing_symbol = nullptr;

		auto package = _frost_program.curr_frost_package;
		//auto interface = _frost_program.curr_frost_interface;
		//auto module = _frost_program.curr_frost_module;
		auto module_scope = _stacks.get_top_module_scope();

		if (_in_package_pass())
		{
			existing_symbol = package->symbol_table().at(s_ident);
		}
		//else if (_in_interface_pass())
		//{
		//	existing_symbol = interface->symbol_table().at(s_ident);
		//}
		else if (_in_module_pass())
		{
			existing_symbol = module_scope->local_symbol_table.at(s_ident);
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitDeclNoKwLocalparam():  "
				"FinishRaw...Construct pass() Eek!");
		}


		if (s_value->references_symbol(existing_symbol))
		{
			//_in_scope_thing()->in_scope_err(existing_symbol
			//	->src_code_pos(), sconcat("localparam with identifier \"",
			//	*s_ident, "\" is defined in terms of itself."));
			_err(existing_symbol->src_code_pos(), sconcat("localparam ",
				"with identifier \"", *s_ident, "\" is defined in terms ",
				"of itself."));
		}

		if (!s_value->is_constant())
		{
			//_in_scope_thing()->in_scope_err(existing_symbol
			//	->src_code_pos(), sconcat("localparam with identifier \"",
			//	*s_ident, "\" is not constant."));
			_err(existing_symbol->src_code_pos(), sconcat("localparam ",
				"with identifier \"", *s_ident, "\" is not constant."));
		}

		// Actually insert the value
		*existing_symbol = Symbol(existing_symbol->src_code_pos(),
			existing_symbol->ident(), s_value);


		//if (!s_value->defined_in_terms_of_any_incomplete_symbol())
		//{
		//	auto s_left_dim_expr = ExpressionBuilder::make_expr_hc_num
		//		(_make_src_code_pos(ctx->expr()),
		//		s_value->value().size());

		//	// This forcibly makes "localparam"s be vectors, but that's
		//	// not such a big deal (given that "localparam"s are always
		//	// built-in types), is it?
		//	auto s_frost_lhs_type = save_frost_lhs_type(FrostLhsType
		//		(s_src_code_pos, FrostLhsType
		//		::construct_initial_builtin_type_ident
		//		(s_value->value().is_signed(), s_left_dim_expr),
		//		s_value->value().is_signed(), s_left_dim_expr));

		//	// "localparam"s are never arrays.
		//	auto s_frost_full_type = save_frost_full_type(FrostFullType
		//		(s_src_code_pos, s_frost_lhs_type));

		//	// Actually insert the value
		//	*existing_symbol = Symbol(existing_symbol->src_code_pos(),
		//		existing_symbol->ident(), existing_symbol->port_type(),
		//		s_frost_full_type, s_value);
		//}
		//else
		//{
		//	_needs_another_subpass = true;
		//}
	}
	else
	{
		_err(ctx, "ParseTreeVisitor::visitDeclNoKwLocalparam():  "
			"invalid pass() Eek!");
	}

	return nullptr;
}
auto ParseTreeVisitor::visitDeclLocalparamList
	(Parser::DeclLocalparamListContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_LOOPED(decl_no_kw_localparam_iter,
		ctx->declNoKwLocalparam())
	return nullptr;
}

// For now, port vars can't be arrays.  This will change.
auto ParseTreeVisitor::visitDeclPortVarList
	(Parser::DeclPortVarListContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->lhsTypeName());

	// How many port variables are in this particular list?
	_stacks.push_small_num(ctx->identName().size());

	for (auto iter : ctx->identName())
	{
		ANY_JUST_ACCEPT_BASIC(iter);
		_stacks.push_src_code_pos(_make_src_code_pos(iter));
	}


	return nullptr;
}


auto ParseTreeVisitor::visitDeclPortDirectionalVarList
	(Parser::DeclPortDirectionalVarListContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->declPortVarList());

	auto frost_lhs_type = _stacks.pop_lhs_type();

	const size_t num_ident_names = _stacks.pop_small_num();

	Symbol::PortType s_port_type;

	if (ctx->TokKwInput())
	{
		s_port_type = Symbol::PortType::Input;
	}
	else if (ctx->TokKwOutput())
	{
		s_port_type = Symbol::PortType::Output;
	}
	//else if (ctx->TokKwInout())
	//{
	//	s_port_type = Symbol::PortType::Inout;
	//}
	else
	{
		_err(ctx, "ParseTreeVisitor::visitDeclPortDirectionalVarList():  "
			"Eek!");
	}

	for (size_t i=0; i<num_ident_names; ++i)
	{
		_insert_module_port_var(_stacks.pop_src_code_pos(),
			_stacks.pop_str(), s_port_type, frost_lhs_type);
	}

	return nullptr;
}

// "parameter" stuff
auto ParseTreeVisitor::visitDeclParameterVar
	(Parser::DeclParameterVarContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->identName());
	auto s_ident = _stacks.pop_str();

	auto module = _frost_program.curr_frost_module;

	if (module->contains_symbol_in_top_scope(s_ident))
	{
		auto&& errwarn_string = module->find_symbol_in_top_scope(s_ident)
			->src_code_pos().convert_to_errwarn_string();
		//module->in_scope_err(_make_src_code_pos(ctx), sconcat("This ",
		//	"module already has a parameter called \"", *s_ident, "\", ",
		//	"defined at ", errwarn_string, "."));
		_err(ctx, sconcat("This module already has a parameter called \"",
			*s_ident, "\", defined at ", errwarn_string, "."));
	}

	Expression* s_value = nullptr;

	if (ctx->expr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->expr());
		s_value = _stacks.pop_expr();
	}

	// Don't even bother with trying to figure out the "FrostFullType" yet.
	// That will be done during un-"parameter"ization. 
	//module->parameter_symbol_table().insert_or_assign(save_symbol(Symbol
	//	(_make_src_code_pos(ctx), s_ident, Symbol::PortType::NonPort,
	//	nullptr, s_value)));
	module->parameter_symbol_table().insert_or_assign(save_symbol(Symbol
		(_make_src_code_pos(ctx), s_ident, s_value)));

	return nullptr;
}
auto ParseTreeVisitor::visitDeclParameterVarList
	(Parser::DeclParameterVarListContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_LOOPED(iter, ctx->declParameterVar());
	return nullptr;
}
} // namespace frost_hdl
