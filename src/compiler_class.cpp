#include "compiler_class.hpp"
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



namespace frost_hdl
{

typedef Compiler::VisitorRetType VisitorRetType;

Compiler::Compiler(ListParsedSrcCode&& s_list_parsed_src_code)
	: _list_parsed_src_code(std::move(s_list_parsed_src_code))
{
	//_program_ctx = parser.program();
}
Compiler::~Compiler()
{
}

int Compiler::run()
{
	while (parse_pass() < ParsePass::Done)
	{
		//visitProgram(_program_ctx);
		for (const auto& parsed_src_code : _list_parsed_src_code)
		{
			//_curr_parsed_src_code = &parsed_src_code;
			_curr_filename = parsed_src_code->filename();
			//printout("*_curr_filename:  ", *_curr_filename, "\n");
			visitProgram(parsed_src_code->parser()->program());
		}

		// ...This is a HORRIBLE solution to a problem I don't know the
		// actual cause of.
		//for (size_t i=0; i<_list_parsed_src_code.size(); ++i)
		for (auto& parsed_src_code : _list_parsed_src_code)
		{
			//*_list_parsed_src_code.at(i) = ParsedSrcCode
			//	(*_list_parsed_src_code.at(i)->filename());
			*parsed_src_code = ParsedSrcCode(*parsed_src_code->filename());
		}
		set_parse_pass(static_cast<ParsePass>(static_cast<PassUint>
			(parse_pass()) + static_cast<PassUint>(1)));
		set_subpass(0);
	}

	return 0;
}


// Basically just "module" and "package" declarations.  There are no other
// things at global scope.
VisitorRetType Compiler::visitProgram(Parser::ProgramContext *ctx)
{

	//if (_in_frost_package_pass())
	//{
	//	//for (auto subprogram : ctx->declPackage())
	//	//{
	//	//	ANY_JUST_ACCEPT_BASIC(subprogram);
	//	//}
	//}
	//else if (_in_frost_module_pass())
	//{
	//}


	switch (parse_pass())
	{
	case ParsePass::FrostListPackages:
	case ParsePass::FrostConstructRawPackages:
		ANY_JUST_ACCEPT_LOOPED(subprogram, ctx->declPackage());
		break;

	case ParsePass::FrostListModules:
	case ParsePass::FrostConstructRawModules:
		ANY_JUST_ACCEPT_LOOPED(subprogram, ctx->declModule());
		break;

	//case ParsePass::Done:
	default:
		_err(ctx, "Compiler::visitProgram():  Eek!");
		break;
	}

	return nullptr;
}




// Variable declaration stuff
VisitorRetType Compiler::visitLhsTypeName
	(Parser::LhsTypeNameContext *ctx)
{
	ANY_ACCEPT_IF_BASIC(ctx->lhsBuiltinTypeName())
	//else ANY_ACCEPT_IF_BASIC(ctx->lhsUnscopedCstmTypeName())
	//else ANY_ACCEPT_IF_BASIC(ctx->lhsScopedCstmTypeName())
	else
	{
		_err(ctx, "Compiler::visitLhsTypeName():  Eek!");
	}
	return nullptr;
}

VisitorRetType Compiler::visitLhsBuiltinTypeName
	(Parser::LhsBuiltinTypeNameContext *ctx)
{
	// only call this when parse_pass() == ParsePass::FrostListModules

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

	std::string s_ident = "logic";

	if (ctx->TokKwSigned() != nullptr)
	{
		s_ident += " signed";
	}

	if (s_left_dim_expr != nullptr)
	{
		//// Need some way to make the name unique!  Also, how do I handle
		//// cases where I don't know the values of named constants yet?
		s_ident += *construct_initial_type_ident_from_dim(dup_str(s_ident),
			s_left_dim_expr);
	}


	// "ctx->TokKwUnsigned()" is only for those who want to be pedantic.

	_stacks.push_lhs_type(save_frost_lhs_type(FrostLhsType
		(_make_src_code_pos(ctx), dup_str(s_ident),
		(ctx->TokKwSigned() != nullptr), s_left_dim_expr)));
	return nullptr;
}

// custom type name from the current scope, be it a module or a package.
// (FUTURE)
VisitorRetType Compiler::visitLhsUnscopedCstmTypeName
	(Parser::LhsUnscopedCstmTypeNameContext *ctx)
{
	return nullptr;
}

// custom type name from a package.
// (FUTURE)
VisitorRetType Compiler::visitLhsScopedCstmTypeName
	(Parser::LhsScopedCstmTypeNameContext *ctx)
{
	return nullptr;
}

// Array dimensions go here
VisitorRetType Compiler::visitDeclNoLhsTypeVar
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
VisitorRetType Compiler::visitDeclVarList
	(Parser::DeclVarListContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->lhsTypeName());
	auto s_frost_lhs_type = _stacks.pop_lhs_type();

	for (auto iter : ctx->declNoLhsTypeVar())
	{
		const SrcCodePos s_src_code_pos(_make_src_code_pos(iter));
		auto module = _frost_program().curr_frost_module;

		ANY_JUST_ACCEPT_BASIC(iter);
		auto s_ident = _stacks.pop_str();

		if (module->contains_symbol(s_ident))
		{
			auto&& errwarn_string = module->find_symbol(s_ident)
				->src_code_pos().convert_to_errwarn_string();
			_err(s_src_code_pos, sconcat("Module \"", *module->ident(),
				"\" already contains a symbol with identifier \"",
				*s_ident, "\" at ", errwarn_string, "."));
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
			_err(ctx, "Compiler::visitDeclVarList():  Eek!");
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
VisitorRetType Compiler::visitDeclNoKwLocalparam
	(Parser::DeclNoKwLocalparamContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->identName());
	auto s_ident = _stacks.pop_str();


	if (parse_pass() == ParsePass::FrostConstructRawPackages)
	{
		auto package = _frost_program().curr_frost_package;

		if (package->symbol_table().contains(s_ident))
		{
			auto&& errwarn_string = package->symbol_table().at(s_ident)
				->src_code_pos().convert_to_errwarn_string();
			//_err(ctx, sconcat("Duplicate localparam called \"", *s_ident,
			//	"\" in package \"", *package->ident(), "\", defined at ",
			//	errwarn_string));
			package->in_scope_err(sconcat("This package already has a ",
				"localparam called \"", *s_ident,  "\", defined at ",
				errwarn_string, "."));
		}
	}
	//else if (parse_pass() == ParsePass::FrostConstructRawInterfaces)
	//{
	//}
	else if (parse_pass() == ParsePass::FrostConstructRawModules)
	{
		auto module = _frost_program().curr_frost_module;

		if (module->contains_symbol(s_ident))
		{
			auto&& errwarn_string = module->find_symbol(s_ident)
				->src_code_pos().convert_to_errwarn_string();
			//module->find_symbol(s_ident)->src_code_pos().in_scope_err
			//	(module, "test");
			module->in_scope_err(sconcat("This module already has a ",
				"symbol called \"", *s_ident, "\", defined at ",
				errwarn_string, "."));
		}
	}
	else
	{
		_err(ctx, "Compiler::visitDeclNoKwLocalparam():  Eek!");
	}
	return nullptr;
}
VisitorRetType Compiler::visitDeclLocalparamList
	(Parser::DeclLocalparamListContext *ctx)
{
	ANY_JUST_ACCEPT_LOOPED(decl_no_kw_localparam_iter,
		ctx->declNoKwLocalparam())
	return nullptr;
}
// "package" stuff
VisitorRetType Compiler::visitDeclPackage
	(Parser::DeclPackageContext *ctx)
{
	if (parse_pass() == ParsePass::FrostListPackages)
	{
	}
	else if (parse_pass() == ParsePass::FrostConstructRawPackages)
	{
	}
	else
	{
		_err(ctx, "Compiler::visitDeclPackage():  Eek!");
	}
	return nullptr;
}
VisitorRetType Compiler::visitInsidePackage
	(Parser::InsidePackageContext *ctx)
{
	return nullptr;
}

// For now, port vars can't be arrays.  Perhaps things will actually stay
// that way (such that arrays on ports *must* be in "splitvar" "struct"s)
VisitorRetType Compiler::visitDeclPortVarList
	(Parser::DeclPortVarListContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->lhsTypeName());

	_stacks.push_small_num(ctx->identName().size());

	for (auto iter : ctx->identName())
	{
		ANY_JUST_ACCEPT_BASIC(iter);
		_stacks.push_src_code_pos(_make_src_code_pos(iter));
	}


	return nullptr;
}


VisitorRetType Compiler::visitDeclPortDirectionalVarList
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
		_err(ctx, "Compiler::visitDeclPortDirectionalVarList():  Eek!");
	}

	for (size_t i=0; i<num_ident_names; ++i)
	{
		_insert_module_port_var(_stacks.pop_src_code_pos(),
			_stacks.pop_str(), s_port_type, frost_lhs_type);
	}

	return nullptr;
}

// "module" stuff
VisitorRetType Compiler::visitDeclModule
	(Parser::DeclModuleContext *ctx)
{
	if (parse_pass() == ParsePass::FrostListModules)
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		auto s_ident = _stacks.pop_str();

		if (_frost_program().frost_module_table.contains(s_ident))
		{
			_err(ctx, sconcat("Duplicate module called \"", *s_ident,
				"\"."));
		}

		_frost_program().curr_frost_module = save_frost_module(FrostModule
			(_make_src_code_pos(ctx), s_ident));

		// Process ports of this module
		ANY_JUST_ACCEPT_LOOPED(port_list,
			ctx->declPortDirectionalVarList())

		_frost_program().frost_module_table.insert_or_assign
			(_frost_program().curr_frost_module);
	}
	else if (parse_pass() == ParsePass::FrostConstructRawModules)
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		_frost_program().curr_frost_module
			= _frost_program().frost_module_table.at(_stacks.pop_str());

		ANY_JUST_ACCEPT_BASIC(ctx->insideModule());
	}
	else
	{
		_err(ctx, "Compiler::visitDeclModule():  Eek!");
	}


	return nullptr;
}

VisitorRetType Compiler::visitInsideModule
	(Parser::InsideModuleContext *ctx)
{
	ANY_JUST_ACCEPT_LOOPED(decl_localparam_list_iter,
		ctx->declLocalparamList())
	ANY_JUST_ACCEPT_LOOPED(decl_var_list_iter, ctx->declVarList())

	ANY_JUST_ACCEPT_LOOPED(stmt_assign_iter, ctx->moduleStmtContAssign())

	return nullptr;
}

VisitorRetType Compiler::visitModuleStmtContAssign
	(Parser::ModuleStmtContAssignContext *ctx)
{
	auto module = _frost_program().curr_frost_module;

	ANY_JUST_ACCEPT_BASIC(ctx->identExpr());
	auto s_lhs_expr = _stacks.pop_expr();

	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	auto s_rhs_expr = _stacks.pop_expr();

	typedef Expression::LhsCategory ExprLhsCategory;

	auto s_frost_statement = save_frost_statement(FrostStmtContAssign
		(s_lhs_expr, s_rhs_expr));

	switch (s_lhs_expr->lhs_category())
	{
	case ExprLhsCategory::None:
		_err(ctx, "Compiler::visitModuleStmtContAssign():  lhs None Eek!");
		break;

	case ExprLhsCategory::NonSliced:
		break;

	case ExprLhsCategory::Sliced:
		_err(ctx, "Compiler::visitModuleStmtContAssign():  "
			"Sliced not implemented Eek!");
		break;

	case ExprLhsCategory::Concat:
		_err(ctx, "Compiler::visitModuleStmtContAssign():  "
			"Concat not implemented Eek!");
		break;

	default:
		_err(ctx, "Compiler::visitModuleStmtContAssign():  lhs default "
			"Eek!");
		break;
	}


	return nullptr;
}

// Expression parsing
VisitorRetType Compiler::visitExpr
	(Parser::ExprContext *ctx)
{
	if (ctx->TokOpLogical())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->expr());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprLogical());
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
			_err(ctx, "Compiler::visitExpr():  Eek!");
		}
	}
	else
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprLogical());
	}
	return nullptr;
}

VisitorRetType Compiler::visitExprLogical
	(Parser::ExprLogicalContext *ctx)
{
	if (ctx->TokOpCompare())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprLogical());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
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
			_err(ctx, "Compiler::visitExprLogical():  Eek!");
		}
	}
	else
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
	}
	return nullptr;
}
VisitorRetType Compiler::visitExprCompare
	(Parser::ExprCompareContext *ctx)
{
	if (ctx->TokPlus())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
		auto right = _stacks.pop_expr();

		_stacks.push_expr(ExpressionBuilder::make_expr_binop
			<ExprBinOpPlus>(_make_src_code_pos(ctx), left, right));
	}
	else if (ctx->TokMinus())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
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

VisitorRetType Compiler::visitExprAddSub
	(Parser::ExprAddSubContext *ctx)
{
	if (ctx->TokOpMulDivMod())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprMulDivModEtc());
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
			_err(ctx, "Compiler::visitExprAddSub():  TokOpMulDivMod() "
				"Eek!");
		}
	}
	else if (ctx->TokOpBitwise())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprMulDivModEtc());
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
			_err(ctx, "Compiler::visitExprAddSub():  TokOpBitwise() "
				"Eek!");
		}
	}
	else
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprMulDivModEtc());
	}
	return nullptr;
}
VisitorRetType Compiler::visitExprMulDivModEtc
	(Parser::ExprMulDivModEtcContext *ctx)
{
	ANY_ACCEPT_IF_BASIC(ctx->exprUnary())
	else ANY_ACCEPT_IF_BASIC(ctx->numExpr())
	else ANY_ACCEPT_IF_BASIC(ctx->identExpr())
	else ANY_ACCEPT_IF_BASIC(ctx->expr())
	else
	{
		_err(ctx, "Compiler::visitExprMulDivModEtc():  Eek!");
	}
	return nullptr;
}

VisitorRetType Compiler::visitExprUnary
	(Parser::ExprUnaryContext *ctx)
{
	ANY_ACCEPT_IF_BASIC(ctx->exprPlusUnary())
	else ANY_ACCEPT_IF_BASIC(ctx->exprMinusUnary())
	else ANY_ACCEPT_IF_BASIC(ctx->exprLogNot())
	else ANY_ACCEPT_IF_BASIC(ctx->exprBitNot())
	else ANY_ACCEPT_IF_BASIC(ctx->exprCastUnsigned())
	else ANY_ACCEPT_IF_BASIC(ctx->exprCastSigned())
	else
	{
		_err(ctx, "Compiler::visitExprUnary():  Eek!");
	}
	return nullptr;
}


VisitorRetType Compiler::visitExprPlusUnary
	(Parser::ExprPlusUnaryContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpPlus>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
VisitorRetType Compiler::visitExprMinusUnary
	(Parser::ExprMinusUnaryContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpMinus>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
VisitorRetType Compiler::visitExprLogNot
	(Parser::ExprLogNotContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpLogNot>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
VisitorRetType Compiler::visitExprBitNot
	(Parser::ExprBitNotContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpBitNot>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
VisitorRetType Compiler::visitExprCastUnsigned
	(Parser::ExprCastUnsignedContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop
		<ExprUnOpCastUnsigned>(_make_src_code_pos(ctx),
		_stacks.pop_expr()));

	return nullptr;
}
VisitorRetType Compiler::visitExprCastSigned
	(Parser::ExprCastSignedContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop
		<ExprUnOpCastSigned>(_make_src_code_pos(ctx),
		_stacks.pop_expr()));

	return nullptr;
}

// I'm pretty sure this works.
VisitorRetType Compiler::visitNumExpr
	(Parser::NumExprContext *ctx)
{
	if (ctx->rawNumExpr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->rawNumExpr());
		const auto value = _stacks.pop_big_num();

		const auto size = _default_hard_coded_num_size();

		_stacks.push_expr(ExpressionBuilder::make_expr_hc_num
			(_make_src_code_pos(ctx), value, size.get_ui(), false));
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
		_err(ctx, "Compiler::visitNumExpr():  Eek!");
	}

	return nullptr;
}

// This needs tested!
VisitorRetType Compiler::visitRawNumExpr
	(Parser::RawNumExprContext *ctx)
{
	if (ctx->TokDecNum())
	{
		BigNum to_push(0);

		for (auto c : ctx->TokDecNum()->toString())
		{
			to_push = (to_push * 10) + (c - '0');
		}

		_stacks.push_big_num(to_push);
	}
	else if (ctx->TokHexNum())
	{
		BigNum to_push(0);

		for (auto c : ctx->TokHexNum()->toString())
		{
			if ((c >= 'A') && (c <= 'F'))
			{
				to_push = (to_push * 16) + (c - 'A' + 0xA);
			}
			else if ((c >= 'a') && (c <= 'f'))
			{
				to_push = (to_push * 16) + (c - 'a' + 0xa);
			}
			else // if ((c >= '0') && (c <= '9'))
			{
				to_push = (to_push * 16) + (c - '0' + 0x0);
			}
		}

		_stacks.push_big_num(to_push);
	}
	else if (ctx->TokBinNum())
	{
		BigNum to_push(0);

		for (auto c : ctx->TokBinNum()->toString())
		{
			to_push = (to_push * 2) + (c - '0');
		}

		_stacks.push_big_num(to_push);
	}
	else
	{
		_err(ctx, "Compiler::visitRawNumExpr():  Eek!");
	}

	return nullptr;
}
VisitorRetType Compiler::visitSizedNumExpr
	(Parser::SizedNumExprContext *ctx)
{
	ANY_JUST_ACCEPT_LOOPED(raw_num_expr, ctx->rawNumExpr())

	return nullptr;
}

VisitorRetType Compiler::visitIdentExpr
	(Parser::IdentExprContext *ctx)
{
	if (ctx->identName())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		auto ident = _stacks.pop_str();

		auto module = _frost_program().curr_frost_module;


		// Here we check to see whether or not the symbol actually exists
		// in the current scope.
		switch (parse_pass())
		{
		//case ParsePass::FrostConstructRawPackages:
		//	break;

		//case ParsePass::FrostConstructRawInterfaces:
		//	break;

		case ParsePass::FrostConstructRawModules:
			if (module->contains_symbol(ident))
			{
				_stacks.push_expr(save_expr(ExprIdentName
					(_make_src_code_pos(ctx),
					module->find_symbol(ident))));
			}
			else
			{
				_err(ctx, sconcat("Module \"", *module->ident(), "\" does",
					" not contain a symbol called \"", *ident, "\"."));
			}
			break;

		default:
			break;
		}
	}

	else if(ctx->scopedIdentName())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->scopedIdentName());
	
		const SmallNum num_scopes = _stacks.pop_small_num();

		//// The identifier of whatever is inside the package.
		//auto inner_ident = _stacks.pop_str();

		//// What package does this identifier come from?
		//auto scope_ident = _stacks.pop_str();

		//auto package = _frost_program().curr_frost_package;


		switch (parse_pass())
		{
		default:
			break;
		}
	}
	else
	{
		_err(ctx, "Compiler::visitIdentExpr():  Eek!");
	}

	return nullptr;
}


VisitorRetType Compiler::visitIdentName
	(Parser::IdentNameContext *ctx)
{
	_stacks.push_str(TOK_TO_DUPPED_STR(ctx->TokIdent()));
	//auto ident = TOK_TO_DUPPED_STR(ctx->TokIdent());

	return nullptr;
}

VisitorRetType Compiler::visitScopedIdentName
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


void Compiler::_insert_module_port_var(const SrcCodePos& s_src_code_pos,
	SavedString s_ident, Symbol::PortType s_port_type,
	FrostLhsType* s_frost_lhs_type)
{
	// Call this ONLY if (parse_pass() == Compiler::ParsePass
	// ::FrostListModules)
	if (parse_pass() != Compiler::ParsePass::FrostListModules)
	{
		_err(s_src_code_pos, "Compiler::_insert_module_port_var():  "
			"parse_pass() Eek!");
	}

	// I am lazy.
	auto module = _frost_program().curr_frost_module;

	if (module->contains_symbol(s_ident))
	{
		auto&& errwarn_string = module->find_symbol(s_ident)
			->src_code_pos().convert_to_errwarn_string();
		//if (module->parameter_vars().contains(s_ident))
		//{
		//	//_err(s_src_code_pos, sconcat("Module \"", *module->ident(),
		//	//	"\" already has a parameter with identifier \"", *s_ident,
		//	//	"\", defined at ", errwarn_string, "."));
		//}
		//else // if (not a parameter)
		//{
		//	//_err(s_src_code_pos, sconcat("Module \"", *module->ident(),
		//	//	"\" already has a port variable with identifier \"",
		//	//	*s_ident, "\", defined at ", errwarn_string, "."));
		//}
		module->in_scope_err(sconcat("This module already has a symbol ",
			"called \"", *s_ident, "\", defined at ", errwarn_string,
			"."));
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
		_err(s_src_code_pos, "Compiler::_insert_module_port_var():  "
			"PortType Eek!");
		break;
	}

	// Ports can't be arrays.
	auto s_frost_full_type = save_frost_full_type(FrostFullType
		(s_src_code_pos, s_frost_lhs_type));

	symbol_table->insert_or_assign(save_symbol(Symbol(s_src_code_pos,
		s_ident, s_port_type, s_frost_full_type)));
}

} // namespace frost_hdl
