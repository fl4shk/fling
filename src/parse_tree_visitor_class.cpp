#include "parse_tree_visitor_class.hpp"
#include "general_allocator_class.hpp"
#include "expression_builder_class.hpp"

#include <sstream>



#define ANY_JUST_ACCEPT_BASIC(arg) \
	arg->accept(this)

#define ANY_JUST_ACCEPT_LOOPED(iter, arg) \
	for (auto iter : arg) \
	{ \
		ANY_JUST_ACCEPT_BASIC(iter); \
	}

#define ANY_ACCEPT_IF_BASIC(arg) \
	if (arg) \
	{ \
		ANY_JUST_ACCEPT_BASIC(arg); \
	}


#define TOK_TO_DUPPED_STR(arg) \
	dup_str(arg->toString())

#define ANY_PUSH_TOK_IF(arg) \
	if (arg) \
	{ \
		_stacks.push_str(TOK_TO_DUPPED_STR(arg)); \
	}

#define DEBUG_EXPR(func, context) \
	printout("ParseTreeVisitor::", #func, "():  ", #context, ":  ", \
		!!ctx->context(), "\n")


namespace frost_hdl
{

typedef ParseTreeVisitor::VisitorRetType VisitorRetType;

ParseTreeVisitor::ParseTreeVisitor
	(ListParsedSrcCode&& s_list_parsed_src_code)
	: _list_parsed_src_code(std::move(s_list_parsed_src_code))
{
	//_program_ctx = parser.program();
}
ParseTreeVisitor::~ParseTreeVisitor()
{
}

int ParseTreeVisitor::run()
{
	while (pass() < Pass::Done)
	{
		//visitProgram(_program_ctx);
		for (const auto& parsed_src_code : _list_parsed_src_code)
		{
			//_curr_parsed_src_code = &parsed_src_code;
			_curr_filename = parsed_src_code->filename();
			//printout("*_curr_filename:  ", *_curr_filename, "\n");
			visitProgram(parsed_src_code->parser()->program());
		}

		if (_needs_another_subpass)
		{
			_needs_another_subpass = false;

			set_subpass(subpass() + static_cast<decltype(_subpass)>(1));

			if (subpass() >= MAX_SUBPASS)
			{
				_err(nullptr, sconcat("Too many subpasses (", 
					MAX_SUBPASS, " or more)"));
			}

			reparse();

			continue;
		}

		reparse();
		set_pass(static_cast<Pass>(static_cast<PassUint>
			(pass()) + static_cast<PassUint>(1)));
		set_subpass(0);
	}

	for (const auto& package_iter
		: _frost_program.frost_package_table.table())
	{
		printout("package \"", *package_iter.first, "\":\n");
		for (const auto& symbol_iter
			: package_iter.second->symbol_table().table())
		{
			const auto& symbol = symbol_iter.second;

			symbol->value()->full_evaluate_if_constant();

			printout(*symbol->ident(), " ",
				symbol->value()->value().convert_to_bignum(), " ",
				symbol->value()->value().size(), "\n");
		}
	}

	return 0;
}

void ParseTreeVisitor::reparse()
{
	// ...This is a HORRIBLE solution to a problem I don't know the
	// actual cause of.
	//for (size_t i=0; i<_list_parsed_src_code.size(); ++i)
	for (auto& parsed_src_code : _list_parsed_src_code)
	{
		//*_list_parsed_src_code.at(i) = ParsedSrcCode
		//	(*_list_parsed_src_code.at(i)->filename());
		*parsed_src_code = ParsedSrcCode(*parsed_src_code->filename());
	}
}

// Basically just "module", "interface", and "package" declarations.
// There are no other things permitted at global scope.
VisitorRetType ParseTreeVisitor::visitProgram
	(Parser::ProgramContext *ctx)
{
	if (in_package_pass())
	{
		ANY_JUST_ACCEPT_LOOPED(iter, ctx->declPackage());
	}

	//else if (in_interface_pass())
	//{
	//	ANY_JUST_ACCEPT_LOOPED(iter, ctx->declInterface());
	//}

	else if (in_module_pass())
	{
		ANY_JUST_ACCEPT_LOOPED(iter, ctx->declModule());
	}

	// else if (pass() == Pass::Done)
	else
	{
		_err(ctx, "ParseTreeVisitor::visitProgram():  Eek!");
	}

	return nullptr;
}




// Variable declaration stuff
VisitorRetType ParseTreeVisitor::visitLhsTypeName
	(Parser::LhsTypeNameContext *ctx)
{
	ANY_ACCEPT_IF_BASIC(ctx->lhsBuiltinTypeName())
	//else ANY_ACCEPT_IF_BASIC(ctx->lhsUnscopedCstmTypeName())
	//else ANY_ACCEPT_IF_BASIC(ctx->lhsScopedCstmTypeName())
	else
	{
		_err(ctx, "ParseTreeVisitor::visitLhsTypeName():  Eek!");
	}
	return nullptr;
}

VisitorRetType ParseTreeVisitor::visitLhsBuiltinTypeName
	(Parser::LhsBuiltinTypeNameContext *ctx)
{
	// only call this when pass() == Pass::ListModuleIdentifiers

	Expression* s_left_dim_expr = nullptr;
	if (ctx->expr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->expr());
		s_left_dim_expr = _stacks.pop_expr();

		//// Helpful warning
		//if (static_cast<BigNum>(s_left_dim_expr->value())
		//	< static_cast<BigNum>(0))
		//{
		//	_warn(ctx, "Dimensions of vector are signed and evaluate to less"
		//		" than zero.  They will be treated as an unsigned value."
		//		"  This is might not be what you want.");
		//}

		if (!s_left_dim_expr->is_constant())
		{
			_err(ctx->expr(), "Vectors must have constant dimensions.");
		}
	}

	auto s_ident = FrostLhsType::construct_initial_builtin_type_ident
		((ctx->TokKwSigned() != nullptr), s_left_dim_expr);


	// "ctx->TokKwUnsigned()" is only for those who want to be pedantic.

	_stacks.push_lhs_type(save_frost_lhs_type(FrostLhsType
		(_make_src_code_pos(ctx), s_ident,
		(ctx->TokKwSigned() != nullptr), s_left_dim_expr)));
	return nullptr;
}

// custom type name from the current scope, be it a module or a package.
// (FUTURE)
VisitorRetType ParseTreeVisitor::visitLhsUnscopedCstmTypeName
	(Parser::LhsUnscopedCstmTypeNameContext *ctx)
{
	return nullptr;
}

// custom type name from a package.
// (FUTURE)
VisitorRetType ParseTreeVisitor::visitLhsScopedCstmTypeName
	(Parser::LhsScopedCstmTypeNameContext *ctx)
{
	return nullptr;
}

// Array dimensions go here
VisitorRetType ParseTreeVisitor::visitDeclNoLhsTypeVar
	(Parser::DeclNoLhsTypeVarContext *ctx)
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
VisitorRetType ParseTreeVisitor::visitDeclVarList
	(Parser::DeclVarListContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->lhsTypeName());
	auto s_frost_lhs_type = _stacks.pop_lhs_type();

	for (auto iter : ctx->declNoLhsTypeVar())
	{
		const SrcCodePos s_src_code_pos(_make_src_code_pos(iter));
		auto module = _frost_program.curr_frost_module;

		ANY_JUST_ACCEPT_BASIC(iter);
		auto s_ident = _stacks.pop_str();

		if (module->contains_symbol(s_ident))
		{
			auto&& errwarn_string = module->find_symbol(s_ident)
				->src_code_pos().convert_to_errwarn_string();
			//_err(s_src_code_pos, sconcat("Module \"", *module->ident(),
			//	"\" already contains a symbol with identifier \"",
			//	*s_ident, "\" at ", errwarn_string, "."));
			module->in_scope_err(_make_src_code_pos(iter), sconcat("This ",
				"module already contains a symbol called \"", *s_ident, 
				"\", deifned at ", errwarn_string, "."));
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

		module->local_symbol_table().insert_or_assign(save_symbol(Symbol
			(s_src_code_pos, s_ident, Symbol::PortType::NonPort,
			s_frost_full_type)));
	}

	return nullptr;
}
VisitorRetType ParseTreeVisitor::visitDeclNoKwLocalparam
	(Parser::DeclNoKwLocalparamContext *ctx)
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
		if (in_package_pass())
		{
			auto package = _frost_program.curr_frost_package;

			if (package->symbol_table().contains(s_ident))
			{
				auto&& errwarn_string = package->symbol_table().at(s_ident)
					->src_code_pos().convert_to_errwarn_string();
				package->in_scope_err(s_src_code_pos, sconcat
					("This package already has a localparam called \"", 
					*s_ident,  "\", defined at ",
					errwarn_string, "."));
			}

			symbol_table = &package->symbol_table();
		}
		//else if (in_interface_pass())
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
		else if (in_module_pass())
		{
			auto module = _frost_program.curr_frost_module;

			if (module->contains_symbol(s_ident))
			{
				auto&& errwarn_string = module->find_symbol(s_ident)
					->src_code_pos().convert_to_errwarn_string();
				module->in_scope_err(s_src_code_pos, sconcat("This ",
					"module already has a symbol called \"", *s_ident, 
					"\", defined at ", errwarn_string, "."));
			}

			symbol_table = &module->local_symbol_table();
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitDeclNoKwLocalparam():  "
				"InnerDecl pass() Eek!");
		}

		symbol_table->insert_or_assign(save_symbol(Symbol(s_src_code_pos,
			s_ident, Symbol::PortType::NonPort)));
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
		auto module = _frost_program.curr_frost_module;

		if (in_package_pass())
		{
			existing_symbol = package->symbol_table().at(s_ident);
		}
		//else if (in_interface_pass())
		//{
		//	existing_symbol = interface->symbol_table().at(s_ident);
		//}
		else if (in_module_pass())
		{
			existing_symbol = module->local_symbol_table().at(s_ident);
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitDeclNoKwLocalparam():  "
				"FinishRaw...Construct pass() Eek!");
		}

		// The error messages should make what this does clear...
		if (s_value->references_symbol(existing_symbol))
		{
			if (in_package_pass())
			{
				package->in_scope_err(existing_symbol->src_code_pos(),
					sconcat("localparam with identifier \"",
					*s_ident, "\" is defined in terms of itself."));
			}
			//else if (in_interface_pass())
			//{
			//	interface->in_scope_err(existing_symbol->src_code_pos(),
			//		sconcat("localparam with identifier \"",
			//		*s_ident, "\" is defined in terms of itself."));
			//}
			else if (in_module_pass())
			{
				module->in_scope_err(existing_symbol->src_code_pos(),
					sconcat("localparam with identifier \"",
					*s_ident, "\" is defined in terms of itself."));
			}
			else
			{
				_err(ctx, "ParseTreeVisitor"
					"::visitDeclNoKwLocalparam():  "
					"references_symbol() pass() Eek!");
			}
		}


		if (!s_value->defined_in_terms_of_any_incomplete_symbol())
		{
			auto s_left_dim_expr = ExpressionBuilder::make_expr_hc_num
				(_make_src_code_pos(ctx->expr()),
				s_value->value().size());

			// This forcibly makes "localparam"s be vectors, but that's
			// not such a big deal (given that "localparam"s are always
			// built-in types), is it?
			auto s_frost_lhs_type = save_frost_lhs_type(FrostLhsType
				(s_src_code_pos, FrostLhsType
				::construct_initial_builtin_type_ident
				(s_value->value().is_signed(), s_left_dim_expr),
				s_value->value().is_signed(), s_left_dim_expr));

			// "localparam"s are never arrays.
			auto s_frost_full_type = save_frost_full_type(FrostFullType
				(s_src_code_pos, s_frost_lhs_type));

			// Actually insert the value
			*existing_symbol = Symbol(existing_symbol->src_code_pos(),
				existing_symbol->ident(), existing_symbol->port_type(),
				s_frost_full_type, s_value);
		}
		else
		{
			_needs_another_subpass = true;
		}
	}
	else
	{
		_err(ctx, "ParseTreeVisitor::visitDeclNoKwLocalparam():  "
			"invalid pass() Eek!");
	}

	return nullptr;
}
VisitorRetType ParseTreeVisitor::visitDeclLocalparamList
	(Parser::DeclLocalparamListContext *ctx)
{
	ANY_JUST_ACCEPT_LOOPED(decl_no_kw_localparam_iter,
		ctx->declNoKwLocalparam())
	return nullptr;
}
// "package" stuff
VisitorRetType ParseTreeVisitor::visitDeclPackage
	(Parser::DeclPackageContext *ctx)
{
	if (pass() == Pass::ListPackageIdentifiers)
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		auto s_ident = _stacks.pop_str();

		auto& frost_package_table = _frost_program.frost_package_table;
		auto& curr_frost_package = _frost_program.curr_frost_package;

		if (frost_package_table.contains(s_ident))
		{
			_err(ctx, sconcat("Duplicate package called \"", *s_ident,
				"\", previously declared at ", frost_package_table.at
				(s_ident)->src_code_pos().convert_to_errwarn_string(),
				"."));
		}

		curr_frost_package = save_frost_package(FrostPackage
			(_make_src_code_pos(ctx), s_ident));

		frost_package_table.insert_or_assign(curr_frost_package);
	}
	else if ((pass() == Pass::ListPackageInnerDecl)
		|| (pass() == Pass::FinishRawPackageConstruct))
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		_frost_program.curr_frost_package
			= _frost_program.frost_package_table.at(_stacks.pop_str());

		ANY_JUST_ACCEPT_BASIC(ctx->insidePackage());
	}
	else
	{
		_err(ctx, "ParseTreeVisitor::visitDeclPackage():  Eek!");
	}
	return nullptr;
}
VisitorRetType ParseTreeVisitor::visitInsidePackage
	(Parser::InsidePackageContext *ctx)
{
	ANY_JUST_ACCEPT_LOOPED(decl_localparam_list_iter,
		ctx->declLocalparamList())

	//ANY_JUST_ACCEPT_BASIC(ctx->declStruct())
	////ANY_JUST_ACCEPT_BASIC(ctx->declClass())
	//ANY_JUST_ACCEPT_BASIC(ctx->declEnum())
	//ANY_JUST_ACCEPT_BASIC(ctx->declFunction())
	//ANY_JUST_ACCEPT_BASIC(ctx->declTypedef())

	return nullptr;
}

// For now, port vars can't be arrays.  Perhaps things will actually stay
// that way (such that arrays on ports *must* be in "splitvar" "struct"s)
VisitorRetType ParseTreeVisitor::visitDeclPortVarList
	(Parser::DeclPortVarListContext *ctx)
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


VisitorRetType ParseTreeVisitor::visitDeclPortDirectionalVarList
	(Parser::DeclPortDirectionalVarListContext *ctx)
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
	else if (ctx->TokKwInout())
	{
		s_port_type = Symbol::PortType::Inout;
	}
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
VisitorRetType ParseTreeVisitor::visitDeclParameterVar
	(Parser::DeclParameterVarContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->identName());
	auto s_ident = _stacks.pop_str();

	auto module = _frost_program.curr_frost_module;

	if (module->contains_symbol(s_ident))
	{
		auto&& errwarn_string = module->find_symbol(s_ident)
			->src_code_pos().convert_to_errwarn_string();
		module->in_scope_err(_make_src_code_pos(ctx), sconcat("This ",
			"module already has a parameter called \"", *s_ident, "\", ",
			"defined at ", errwarn_string, "."));
	}

	Expression* s_value = nullptr;

	if (ctx->expr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->expr());
		s_value = _stacks.pop_expr();
	}

	// Don't even bother with trying to figure out the "FrostFullType" yet.
	// That will be done during un-"parameter"ization. 
	module->parameter_symbol_table().insert_or_assign(save_symbol(Symbol
		(_make_src_code_pos(ctx), s_ident, Symbol::PortType::NonPort,
		nullptr, s_value)));

	return nullptr;
}
VisitorRetType ParseTreeVisitor::visitDeclParameterVarList
	(Parser::DeclParameterVarListContext *ctx)
{
	ANY_JUST_ACCEPT_LOOPED(iter, ctx->declParameterVar());
	return nullptr;
}

// "module" stuff
VisitorRetType ParseTreeVisitor::visitDeclModule
	(Parser::DeclModuleContext *ctx)
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

		// Process "parameter"s of this module.
		ANY_ACCEPT_IF_BASIC(ctx->declParameterVarList())

		// Process ports of this module
		ANY_JUST_ACCEPT_LOOPED(port_list_iter,
			ctx->declPortDirectionalVarList())

		frost_module_table.insert_or_assign(curr_frost_module);
	}
	else if ((pass() == Pass::ListModuleInnerDecl)
		|| (pass() == Pass::FinishRawModuleConstruct))
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		_frost_program.curr_frost_module
			= _frost_program.frost_module_table.at(_stacks.pop_str());

		ANY_JUST_ACCEPT_BASIC(ctx->insideModule());
	}
	else
	{
		_err(ctx, "ParseTreeVisitor::visitDeclModule():  Eek!");
	}


	return nullptr;
}

VisitorRetType ParseTreeVisitor::visitInsideModule
	(Parser::InsideModuleContext *ctx)
{
	ANY_JUST_ACCEPT_LOOPED(decl_localparam_list_iter,
		ctx->declLocalparamList())

	if (pass() == Pass::ListModuleInnerDecl)
	{
		ANY_JUST_ACCEPT_LOOPED(decl_var_list_iter, ctx->declVarList())
	}

	// Only process these other things AFTER we know about declared
	// variables and stuff.
	else if (pass() == Pass::FinishRawModuleConstruct)
	{
		ANY_JUST_ACCEPT_LOOPED(module_stmt_cont_assign_iter,
			ctx->moduleStmtContAssign())
		//ANY_JUST_ACCEPT_LOOPED(module_stmt_initial_iter,
		//	ctx->moduleStmtBehavBlock())
	}

	return nullptr;
}

VisitorRetType ParseTreeVisitor::visitModuleStmtContAssign
	(Parser::ModuleStmtContAssignContext *ctx)
{
	auto module = _frost_program.curr_frost_module;

	ANY_JUST_ACCEPT_BASIC(ctx->identExpr());
	auto s_lhs_expr = _stacks.pop_expr();

	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	auto s_rhs_expr = _stacks.pop_expr();


	//typedef Expression::LhsCategory ExprLhsCategory;

	//auto s_frost_statement = save_frost_statement(FrostStmtContAssign
	//	(s_lhs_expr, s_rhs_expr));

	// For continuous assignments in particular, there's no need to use
	// "_stacks" to keep track of the statement scoping top node.
	module->frost_statement_table().insert(module->frost_statement_table()
		.next_top_node(), FrostStmtContAssign(s_lhs_expr, s_rhs_expr));


	return nullptr;
}
//VisitorRetType visitModuleStmtBehavBlock
//	(Parser::ModuleStmtBehavBlockContext *ctx)
//{
//	return nullptr;
//}

// Expression parsing
VisitorRetType ParseTreeVisitor::visitExpr
	(Parser::ExprContext *ctx)
{
	if (ctx->TokOpLogical())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprLogical());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->expr());
		auto right = _stacks.pop_expr();

		auto tok = TOK_TO_DUPPED_STR(ctx->TokOpLogical());

		if (tok == dup_str("&&"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpLogAnd>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("||"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpLogOr>(_make_src_code_pos(ctx), left, right));
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitExpr():  Eek!");
		}
	}
	else
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprLogical());
	}
	return nullptr;
}

VisitorRetType ParseTreeVisitor::visitExprLogical
	(Parser::ExprLogicalContext *ctx)
{
	if (ctx->TokOpCompare())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprLogical());
		auto right = _stacks.pop_expr();

		auto tok = TOK_TO_DUPPED_STR(ctx->TokOpCompare());

		if (tok == dup_str("=="))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpEq>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("!="))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpNe>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("<"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpLt>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str(">"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpGt>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("<="))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpLe>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str(">="))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpGe>(_make_src_code_pos(ctx), left, right));
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitExprLogical():  Eek!");
		}
	}
	else
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
	}
	return nullptr;
}
VisitorRetType ParseTreeVisitor::visitExprCompare
	(Parser::ExprCompareContext *ctx)
{
	//DEBUG_EXPR(visitExprCompare, TokPlus);
	//DEBUG_EXPR(visitExprCompare, TokMinus);
	//printout("\n\n");


	if (ctx->TokPlus())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
		auto right = _stacks.pop_expr();

		_stacks.push_expr(ExpressionBuilder::make_expr_binop
			<ExprBinOpPlus>(_make_src_code_pos(ctx), left, right));
	}
	else if (ctx->TokMinus())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
		auto right = _stacks.pop_expr();

		_stacks.push_expr(ExpressionBuilder::make_expr_binop
			<ExprBinOpMinus>(_make_src_code_pos(ctx), left, right));
	}
	else
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
	}
	return nullptr;
}

VisitorRetType ParseTreeVisitor::visitExprAddSub
	(Parser::ExprAddSubContext *ctx)
{
	if (ctx->TokOpMulDivMod())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprMulDivModEtc());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
		auto right = _stacks.pop_expr();

		auto tok = TOK_TO_DUPPED_STR(ctx->TokOpMulDivMod());

		if (tok == dup_str("*"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpMul>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("/"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpDiv>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("%"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpMod>(_make_src_code_pos(ctx), left, right));
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitExprAddSub():  "
				"TokOpMulDivMod() "
				"Eek!");
		}
	}
	else if (ctx->TokOpBitwise())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprMulDivModEtc());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
		auto right = _stacks.pop_expr();

		auto tok = TOK_TO_DUPPED_STR(ctx->TokOpBitwise());

		if (tok == dup_str("&"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitAnd>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("|"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitOr>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("^"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitXor>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("<<"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitLsl>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str(">>"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitLsr>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str(">>>"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitAsr>(_make_src_code_pos(ctx), left, right));
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitExprAddSub():  "
				"TokOpBitwise() Eek!");
		}
	}
	else
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprMulDivModEtc());
	}
	return nullptr;
}
VisitorRetType ParseTreeVisitor::visitExprMulDivModEtc
	(Parser::ExprMulDivModEtcContext *ctx)
{
	//DEBUG_EXPR(visitExprMulDivModEtc, exprUnary);
	//DEBUG_EXPR(visitExprMulDivModEtc, numExpr);
	//DEBUG_EXPR(visitExprMulDivModEtc, identExpr);
	//DEBUG_EXPR(visitExprMulDivModEtc, expr);
	//printout("\n\n");

	ANY_ACCEPT_IF_BASIC(ctx->exprUnary())
	else ANY_ACCEPT_IF_BASIC(ctx->numExpr())
	else ANY_ACCEPT_IF_BASIC(ctx->identExpr())
	else ANY_ACCEPT_IF_BASIC(ctx->expr())
	else
	{
		_err(ctx, "ParseTreeVisitor::visitExprMulDivModEtc():  Eek!");
	}
	return nullptr;
}

VisitorRetType ParseTreeVisitor::visitExprUnary
	(Parser::ExprUnaryContext *ctx)
{
	//DEBUG_EXPR(visitExprUnary, exprPlusUnary);;
	//DEBUG_EXPR(visitExprUnary, exprMinusUnary);
	//DEBUG_EXPR(visitExprUnary, exprLogNot);
	//DEBUG_EXPR(visitExprUnary, exprBitNot);
	//DEBUG_EXPR(visitExprUnary, exprCastUnsigned);
	//DEBUG_EXPR(visitExprUnary, exprCastSigned);
	//printout("\n\n");

	ANY_ACCEPT_IF_BASIC(ctx->exprPlusUnary())
	else ANY_ACCEPT_IF_BASIC(ctx->exprMinusUnary())
	else ANY_ACCEPT_IF_BASIC(ctx->exprLogNot())
	else ANY_ACCEPT_IF_BASIC(ctx->exprBitNot())
	else ANY_ACCEPT_IF_BASIC(ctx->exprCastUnsigned())
	else ANY_ACCEPT_IF_BASIC(ctx->exprCastSigned())
	else
	{
		_err(ctx, "ParseTreeVisitor::visitExprUnary():  Eek!");
	}
	return nullptr;
}


VisitorRetType ParseTreeVisitor::visitExprPlusUnary
	(Parser::ExprPlusUnaryContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpPlus>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
VisitorRetType ParseTreeVisitor::visitExprMinusUnary
	(Parser::ExprMinusUnaryContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpMinus>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
VisitorRetType ParseTreeVisitor::visitExprLogNot
	(Parser::ExprLogNotContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpLogNot>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
VisitorRetType ParseTreeVisitor::visitExprBitNot
	(Parser::ExprBitNotContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpBitNot>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
VisitorRetType ParseTreeVisitor::visitExprCastUnsigned
	(Parser::ExprCastUnsignedContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop
		<ExprUnOpCastUnsigned>(_make_src_code_pos(ctx),
		_stacks.pop_expr()));

	return nullptr;
}
VisitorRetType ParseTreeVisitor::visitExprCastSigned
	(Parser::ExprCastSignedContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop
		<ExprUnOpCastSigned>(_make_src_code_pos(ctx),
		_stacks.pop_expr()));

	return nullptr;
}

// I'm pretty sure this works.
VisitorRetType ParseTreeVisitor::visitNumExpr
	(Parser::NumExprContext *ctx)
{
	if (ctx->rawNumExpr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->rawNumExpr());
		const auto s_data = _stacks.pop_big_num();

		_stacks.push_expr(ExpressionBuilder::make_expr_hc_num_from_expr_num
			(_make_src_code_pos(ctx), ExprNum(s_data, false)));
	}
	else if (ctx->sizedNumExpr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->sizedNumExpr());
		const auto value = _stacks.pop_big_num();
		const auto size = _stacks.pop_big_num();

		_stacks.push_expr(ExpressionBuilder::make_expr_hc_num
			(_make_src_code_pos(ctx), value, size.get_ui(), false));
	}
	else
	{
		_err(ctx, "ParseTreeVisitor::visitNumExpr():  Eek!");
	}

	return nullptr;
}

// I'm pretty sure this works.
VisitorRetType ParseTreeVisitor::visitRawNumExpr
	(Parser::RawNumExprContext *ctx)
{
	BigNum to_push(0);
	if (ctx->TokDecNum())
	{
		for (auto c : ctx->TokDecNum()->toString())
		{
			to_push = (to_push * 10) + (c - '0');
		}

		_stacks.push_big_num(to_push);
	}
	else if (ctx->TokHexNum())
	{
		const auto& as_string = ctx->TokHexNum()->toString();
		for (size_t i=0; i<as_string.size(); ++i)
		{
			if (i < 2)
			{
				continue;
			}

			const auto c = as_string.at(i);
			if ((c >= 'A') && (c <= 'F'))
			{
				to_push = (to_push * 0x10) + (c - 'A' + 0xA);
			}
			else if ((c >= 'a') && (c <= 'f'))
			{
				to_push = (to_push * 0x10) + (c - 'a' + 0xa);
			}
			else // if ((c >= '0') && (c <= '9'))
			{
				to_push = (to_push * 0x10) + (c - '0' + 0x0);
			}
		}

		_stacks.push_big_num(to_push);
	}
	else if (ctx->TokBinNum())
	{
		const auto& as_string = ctx->TokBinNum()->toString();
		for (size_t i=0; i<as_string.size(); ++i)
		{
			if (i < 2)
			{
				continue;
			}

			const auto c = as_string.at(i);
			to_push = (to_push * 0b10) + (c - '0');
		}

		_stacks.push_big_num(to_push);
	}
	else
	{
		_err(ctx, "ParseTreeVisitor::visitRawNumExpr():  Eek!");
	}

	return nullptr;
}
VisitorRetType ParseTreeVisitor::visitSizedNumExpr
	(Parser::SizedNumExprContext *ctx)
{
	ANY_JUST_ACCEPT_LOOPED(raw_num_expr, ctx->rawNumExpr())

	return nullptr;
}

VisitorRetType ParseTreeVisitor::visitIdentExpr
	(Parser::IdentExprContext *ctx)
{
	if (ctx->identName())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		auto ident = _stacks.pop_str();


		// Here we check to see whether or not the symbol actually exists
		// in the current scope.

		if (in_package_pass())
		{
			auto package = _frost_program.curr_frost_package;
			if (package->symbol_table().contains(ident))
			{
				auto symbol = package->symbol_table().at(ident);

				if (!symbol->is_incomplete())
				{
					_stacks.push_expr(save_expr(ExprIdentName
						(_make_src_code_pos(ctx), symbol)));
				}
				else // if (symbol->is_incomplete())
				{
					_stacks.push_expr(save_expr(ExprSubpassIdentName
						(_make_src_code_pos(ctx), symbol)));
				}
			}
			else
			{
				package->in_scope_err(_make_src_code_pos(ctx), sconcat
					("Unknown symbol called \"", *ident, "\" at this ",
					"point."));
			}
		}

		//else if (in_interface_pass())
		//{
		//	auto interface = _frost_program.curr_frost_interface;
		//	if (interface->symbol_table().contains(ident))
		//	{
		//		auto symbol = interface->symbol_table().at(ident);

		//		if (!symbol->is_incomplete())
		//		{
		//			_stacks.push_expr(save_expr(ExprIdentName
		//				(_make_src_code_pos(ctx), symbol)));
		//		}
		//		else // if (symbol->is_incomplete())
		//		{
		//			_stacks.push_expr(save_expr(ExprSubpassIdentName
		//				(_make_src_code_pos(ctx), symbol)));
		//		}
		//	}
		//	else
		//	{
		//		interface->in_scope_err(_make_src_code_pos(ctx), sconcat
		//			("Unknown symbol called \"", *ident, "\" at this ",
		//			"point."));
		//	}
		//}

		else if (in_module_pass())
		{
			auto module = _frost_program.curr_frost_module;
			if (module->contains_symbol(ident))
			{
				auto symbol = module->find_symbol(ident);

				if (!symbol->is_incomplete())
				{
					_stacks.push_expr(save_expr(ExprIdentName
						(_make_src_code_pos(ctx), symbol)));
				}
				else // if (symbol->is_incomplete())
				{
					_stacks.push_expr(save_expr(ExprSubpassIdentName
						(_make_src_code_pos(ctx), symbol)));
				}
			}
			else
			{
				module->in_scope_err(_make_src_code_pos(ctx), sconcat
					("Unknown symbol called \"", *ident, "\" at this ",
					"point."));
			}
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitIdentExpr():  identName() "
				"pass() Eek!");
		}
	}

	else if (ctx->scopedIdentName())
	{
		//_err(ctx, "ParseTreeVisitor::visitIdentExpr():  "
		//	"scopedIdentName() not implemented Eek!");
		ANY_JUST_ACCEPT_BASIC(ctx->scopedIdentName());
	
		const auto num_scopes = _stacks.pop_small_num();

		if (num_scopes == 2)
		{
			auto most_inner_ident = _stacks.pop_str();
			auto which_scope = _stacks.pop_str();

			// Local enums come before packages because local symbols
			// override global ones.  Perhaps a warning should be spat out
			// if a local symbol overrides a global one?
			auto& frost_package_table = _frost_program.frost_package_table;

			InScopeErrWarnBase<SrcCodePos>* in_scope_thing = nullptr;

			if (in_package_pass())
			{
				in_scope_thing = _frost_program.curr_frost_package;
			}
			//else if (in_interface_pass())
			//{
			//	in_scope_thing = _frost_program.curr_frost_interface;
			//}
			else if (in_module_pass())
			{
				in_scope_thing = _frost_program.curr_frost_module;
			}

			if (!frost_package_table.contains(which_scope))
			{
				in_scope_thing->in_scope_err(_make_src_code_pos(ctx),
					sconcat("Unknown package called \"", *which_scope,
					"\"."));
			}

			auto package = frost_package_table.at(which_scope);

			if (!package->symbol_table().contains(most_inner_ident))
			{
				in_scope_thing->in_scope_err(_make_src_code_pos(ctx),
					sconcat("Package \"", *package->ident(), "\" does ",
					"not contain a symbol called \"", *most_inner_ident,
					"\"."));
			}

			auto symbol = package->symbol_table().at(most_inner_ident);


			if (symbol->is_incomplete())
			{
				//printout("test:  ", *symbol->ident(), "\n");
				//in_scope_thing->in_scope_warn(_make_src_code_pos(ctx),
				//	sconcat("test:  ", *symbol->ident()));
				//_needs_another_subpass = true;
				_stacks.push_expr(save_expr(ExprSubpassIdentName
					(_make_src_code_pos(ctx), symbol)));
			}
			else // if (symbol->frost_full_type() != nullptr)
			{
				_stacks.push_expr(save_expr(ExprIdentName
					(_make_src_code_pos(ctx), symbol)));
			}

			//if (symbol->frost_full_type()->frost_lhs_type()
			//	->left_dim_expr()->value() == ExprNum(BigNum(0), 1, false))
			//{
			//	//_needs_another_subpass = true;
			//	_stacks.push_expr(save_expr(ExprSubpassIdentName
			//		(_make_src_code_pos(ctx), symbol)));
			//}
			//else
			//{
			//	_stacks.push_expr(save_expr(ExprIdentName
			//		(_make_src_code_pos(ctx), symbol)));
			//}
		}
		else if (num_scopes == 3)
		{
			// This is a reference to a particular value of an enum that is
			// inside of a package.
			// Since enums aren't fully implemented yet, this is being
			// skipped for now.
			_err(ctx, "ParseTreeVisitor::visitIdentExpr():  "
				"scopedIdentName() (num_scopes == 3) not implemented "
				"Eek!");
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitIdentExpr():  "
				"scopedIdentName() num_scopes Eek!");
		}
	}
	else
	{
		_err(ctx, "ParseTreeVisitor::visitIdentExpr():  Eek!");
	}

	return nullptr;
}


VisitorRetType ParseTreeVisitor::visitIdentName
	(Parser::IdentNameContext *ctx)
{
	_stacks.push_str(TOK_TO_DUPPED_STR(ctx->TokIdent()));
	//auto ident = TOK_TO_DUPPED_STR(ctx->TokIdent());

	return nullptr;
}

VisitorRetType ParseTreeVisitor::visitScopedIdentName
	(Parser::ScopedIdentNameContext *ctx)
{
	SmallNum num_scopes = 0;
	for (auto iter : ctx->identName())
	{
		ANY_JUST_ACCEPT_BASIC(iter);
		++num_scopes;
	}

	_stacks.push_small_num(num_scopes);
	return nullptr;
}


void ParseTreeVisitor::_insert_module_port_var
	(const SrcCodePos& s_src_code_pos, SavedString s_ident,
	Symbol::PortType s_port_type, FrostLhsType* s_frost_lhs_type)
{
	// Call this ONLY if (pass() == Pass::FrostListModules)
	if (pass() != Pass::ListModuleIdentifiers)
	{
		_err(s_src_code_pos, "ParseTreeVisitor"
			"::_insert_module_port_var():  pass() Eek!");
	}

	// I am lazy.
	auto module = _frost_program.curr_frost_module;

	if (module->contains_symbol(s_ident))
	{
		auto&& errwarn_string = module->find_symbol(s_ident)
			->src_code_pos().convert_to_errwarn_string();
		module->in_scope_err(s_src_code_pos, sconcat("This module ",
			"already has a symbol called \"", *s_ident, "\", defined at ",
			errwarn_string, "."));
	}

	// Again, I am lazy.
	SymbolTable* symbol_table = nullptr;

	switch (s_port_type)
	{
	case Symbol::PortType::Input:
		symbol_table = &module->input_symbol_table();
		break;

	case Symbol::PortType::Output:
		symbol_table = &module->output_symbol_table();
		break;

	case Symbol::PortType::Inout:
		symbol_table = &module->inout_symbol_table();
		break;

	default:
		_err(s_src_code_pos, "ParseTreeVisitor"
			"::_insert_module_port_var():  PortType Eek!");
		break;
	}

	// Ports can't be arrays.
	auto s_frost_full_type = save_frost_full_type(FrostFullType
		(s_src_code_pos, s_frost_lhs_type));

	symbol_table->insert_or_assign(save_symbol(Symbol(s_src_code_pos,
		s_ident, s_port_type, s_frost_full_type)));
}

} // namespace frost_hdl
