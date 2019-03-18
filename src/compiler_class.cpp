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

Compiler::Compiler(Parser& parser)
{
	_program_ctx = parser.program();
}
Compiler::~Compiler()
{
}

int Compiler::run()
{
	while (pass() < Pass::Done)
	{
		visitProgram(_program_ctx);
		set_pass(static_cast<Pass>(static_cast<PassUint>(pass())
			+ static_cast<PassUint>(1)));
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

	switch (pass())
	{
	//case Pass::FrostListPackages:
	//case Pass::FrostExpandPackages:
	//	ANY_JUST_ACCEPT_LOOPED(subprogram, ctx->declPackage());
	//	break;

	//case Pass::FrostListInterfaces:
	//case Pass::FrostExpandInterfaces:
	//	ANY_JUST_ACCEPT_LOOPED(subprogram, ctx->declInterface());
	//	break;

	case Pass::FrostListModules:
	case Pass::FrostExpandModules:
		ANY_JUST_ACCEPT_LOOPED(subprogram, ctx->declModule());
		break;

	case Pass::Done:
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
	// only call this when pass() == Pass::FrostListModules

	Expression* s_left_dim_expr = nullptr;
	if (ctx->expr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->expr());
		s_left_dim_expr = _stacks.pop_expr();
	}

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
		_err(ctx, "Vectors must have constant dimensions.");
	}

	// "ctx->TokKwUnsigned()" is only for those who want to be pedantic.

	// Need some way to make the name unique!
	// Also, how do I handle cases where I don't know the values of named
	// constants yet?
	_stacks.push_lhs_type(save_frost_lhs_type(FrostLhsType(SrcCodePos(ctx),
		dup_str("builtin::logic"), (ctx->TokKwSigned() != nullptr),
		s_left_dim_expr)));
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

	// [ expr ]
	if (ctx->expr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->expr());

		auto s_right_dim_expr = _stacks.get_top_expr();

		if (!s_right_dim_expr->is_constant())
		{
			_err(ctx, "Arrays must have constant dimensions.");
		}

		_stacks.push_small_num(static_cast<SmallNum>
			(ScalarOrArray::Array));
	}
	// no [ expr ]
	else
	{
		_stacks.push_small_num(static_cast<SmallNum>
			(ScalarOrArray::Scalar));
	}

	return nullptr;
}

// List of (local?) variables
VisitorRetType Compiler::visitDeclVarList
	(Parser::DeclVarListContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->lhsTypeName());
	auto frost_lhs_type = _stacks.pop_lhs_type();

	for (auto iter : ctx->declNoLhsTypeVar())
	{
		ANY_JUST_ACCEPT_BASIC(iter);

		auto ident = _stacks.pop_str();

		const ScalarOrArray scalar_or_array = static_cast<ScalarOrArray>
			(_stacks.pop_small_num());

		switch (scalar_or_array)
		{
		case ScalarOrArray::Scalar:
			break;

		case ScalarOrArray::Array:
			break;

		default:
			_err(ctx, "Compiler::visitDeclVarList():  Eek!");
			break;
		}
	}

	return nullptr;
}

// For now, port vars can't be arrays.  Perhaps things will actually stay
// that way (such that arrays on ports *must* be in "splitvar" "struct"s)
VisitorRetType Compiler::visitDeclPortVarList
	(Parser::DeclPortVarListContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->lhsTypeName());

	for (auto iter : ctx->identName())
	{
		ANY_JUST_ACCEPT_BASIC(iter);
	}


	return nullptr;
}

VisitorRetType Compiler::visitDeclPortInputVarList
	(Parser::DeclPortInputVarListContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitDeclPortOutputVarList
	(Parser::DeclPortOutputVarListContext *ctx)
{
	return nullptr;
}
VisitorRetType Compiler::visitDeclPortInoutVarList
	(Parser::DeclPortInoutVarListContext *ctx)
{
	return nullptr;
}


// "module" stuff
VisitorRetType Compiler::visitDeclModule(Parser::DeclModuleContext *ctx)
{
	if (pass() == Pass::FrostListModules)
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		auto ident_name = _stacks.pop_str();

		if (_frost_program().frost_module_table.contains(ident_name))
		{
			_err(ctx, sconcat("Duplicate module called \"", *ident_name,
				"\""));
		}

		_frost_program().curr_frost_module = save_frost_module(FrostModule
			(SrcCodePos(ctx), ident_name));

		// Process ports of this module
		ANY_JUST_ACCEPT_LOOPED(port_list, ctx->declPortInputVarList())
		ANY_JUST_ACCEPT_LOOPED(port_list, ctx->declPortOutputVarList())
		ANY_JUST_ACCEPT_LOOPED(port_list, ctx->declPortInoutVarList())

		_frost_program().frost_module_table.insert_or_assign
			(_frost_program().curr_frost_module);
	}
	else if (pass() == Pass::FrostExpandModules)
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		auto ident_name = _stacks.pop_str();
	}
	else
	{
		_err(ctx, "Compiler::visitDeclModule():  Eek!");
	}


	return nullptr;
}

VisitorRetType Compiler::visitModuleInsides
	(Parser::ModuleInsidesContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitModuleStmtAssign
	(Parser::ModuleStmtAssignContext *ctx)
{
	return nullptr;
}

// Expression parsing
VisitorRetType Compiler::visitExpr
	(Parser::ExprContext *ctx)
{
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
				<ExprBinOpCmpEq>(left, right));
		}
		else if (tok == dup_str("!"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpNe>(left, right));
		}
		else if (tok == dup_str("<"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpLt>(left, right));
		}
		else if (tok == dup_str(">"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpGt>(left, right));
		}
		else if (tok == dup_str("<="))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpLe>(left, right));
		}
		else if (tok == dup_str(">="))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpGe>(left, right));
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
			<ExprBinOpPlus>(left, right));
	}
	else if (ctx->TokMinus())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
		auto right = _stacks.pop_expr();

		_stacks.push_expr(ExpressionBuilder::make_expr_binop
			<ExprBinOpMinus>(left, right));
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
				<ExprBinOpMul>(left, right));
		}
		else if (tok == dup_str("/"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpDiv>(left, right));
		}
		else if (tok == dup_str("%"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpMod>(left, right));
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

		auto tok = TOK_TO_DUPPED_STR(ctx->TokOpMulDivMod());

		if (tok == dup_str("&"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitAnd>(left, right));
		}
		else if (tok == dup_str("|"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitOr>(left, right));
		}
		else if (tok == dup_str("^"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitXor>(left, right));
		}
		else if (tok == dup_str("<<"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitLsl>(left, right));
		}
		else if (tok == dup_str(">>"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitLsr>(left, right));
		}
		else if (tok == dup_str(">>>"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitAsr>(left, right));
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
		(_stacks.pop_expr()));

	return nullptr;
}
VisitorRetType Compiler::visitExprMinusUnary
	(Parser::ExprMinusUnaryContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpMinus>
		(_stacks.pop_expr()));

	return nullptr;
}
VisitorRetType Compiler::visitExprLogNot
	(Parser::ExprLogNotContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpLogNot>
		(_stacks.pop_expr()));

	return nullptr;
}
VisitorRetType Compiler::visitExprBitNot
	(Parser::ExprBitNotContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpBitNot>
		(_stacks.pop_expr()));

	return nullptr;
}

VisitorRetType Compiler::visitNumExpr
	(Parser::NumExprContext *ctx)
{
	if (ctx->rawNumExpr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->rawNumExpr());
		const auto value = _stacks.pop_big_num();

		const auto size = _default_hard_coded_num_size();

		return ExpressionBuilder::make_expr_hc_num(value, size.get_ui(),
			false);
	}
	else if (ctx->sizedNumExpr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->sizedNumExpr());
		const auto value = _stacks.pop_big_num();
		const auto size = _stacks.pop_big_num();

		return ExpressionBuilder::make_expr_hc_num(value, size.get_ui(),
			false);
	}
	else
	{
		_err(ctx, "Compiler::visitNumExpr():  Eek!");
	}

	return nullptr;
}

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
	ANY_ACCEPT_IF_BASIC(ctx->identName())
	else ANY_ACCEPT_IF_BASIC(ctx->scopedIdentName())
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

	return nullptr;
}

VisitorRetType Compiler::visitScopedIdentName
	(Parser::ScopedIdentNameContext *ctx)
{
	ANY_JUST_ACCEPT_LOOPED(iter, ctx->identName());

	return nullptr;
}

} // namespace frost_hdl
