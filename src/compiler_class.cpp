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
	//case Pass::FrostConstructRawPackages:
	//	ANY_JUST_ACCEPT_LOOPED(subprogram, ctx->declPackage());
	//	break;

	case Pass::FrostListModules:
	case Pass::FrostConstructRawModules:
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

	_stacks.push_lhs_type(save_frost_lhs_type(FrostLhsType(SrcCodePos(ctx),
		dup_str(s_ident), (ctx->TokKwSigned() != nullptr),
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

// List of local variables
VisitorRetType Compiler::visitDeclVarList
	(Parser::DeclVarListContext *ctx)
{
	//ANY_JUST_ACCEPT_BASIC(ctx->lhsTypeName());
	//auto frost_lhs_type = _stacks.pop_lhs_type();

	//for (auto iter : ctx->declNoLhsTypeVar())
	//{
	//	ANY_JUST_ACCEPT_BASIC(iter);

	//	auto ident = _stacks.pop_str();

	//	const ScalarOrArray scalar_or_array = static_cast<ScalarOrArray>
	//		(_stacks.pop_small_num());

	//	switch (scalar_or_array)
	//	{
	//	case ScalarOrArray::Scalar:
	//		break;

	//	case ScalarOrArray::Array:
	//		break;

	//	default:
	//		_err(ctx, "Compiler::visitDeclVarList():  Eek!");
	//		break;
	//	}
	//}

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
	}


	return nullptr;
}

VisitorRetType Compiler::visitDeclPortInputVarList
	(Parser::DeclPortInputVarListContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->declPortVarList());

	auto frost_lhs_type = _stacks.pop_lhs_type();

	const size_t num_ident_names = _stacks.pop_small_num();

	for (size_t i=0; i<num_ident_names; ++i)
	{
		_insert_module_port_var(ctx, _stacks.pop_str(),
			Symbol::PortType::Input, frost_lhs_type);
	}

	return nullptr;
}
VisitorRetType Compiler::visitDeclPortOutputVarList
	(Parser::DeclPortOutputVarListContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->declPortVarList());

	auto frost_lhs_type = _stacks.pop_lhs_type();

	const size_t num_ident_names = _stacks.pop_small_num();

	for (size_t i=0; i<num_ident_names; ++i)
	{
		_insert_module_port_var(ctx, _stacks.pop_str(),
			Symbol::PortType::Output, frost_lhs_type);
	}

	return nullptr;
}
VisitorRetType Compiler::visitDeclPortInoutVarList
	(Parser::DeclPortInoutVarListContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->declPortVarList());

	auto frost_lhs_type = _stacks.pop_lhs_type();

	const size_t num_ident_names = _stacks.pop_small_num();

	for (size_t i=0; i<num_ident_names; ++i)
	{
		_insert_module_port_var(ctx, _stacks.pop_str(),
			Symbol::PortType::Inout, frost_lhs_type);
	}

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
	else if (pass() == Pass::FrostConstructRawModules)
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
				<ExprBinOpLogAnd>(SrcCodePos(ctx), left, right));
		}
		else if (tok == dup_str("||"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpLogOr>(SrcCodePos(ctx), left, right));
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
				<ExprBinOpCmpEq>(SrcCodePos(ctx), left, right));
		}
		else if (tok == dup_str("!"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpNe>(SrcCodePos(ctx), left, right));
		}
		else if (tok == dup_str("<"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpLt>(SrcCodePos(ctx), left, right));
		}
		else if (tok == dup_str(">"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpGt>(SrcCodePos(ctx), left, right));
		}
		else if (tok == dup_str("<="))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpLe>(SrcCodePos(ctx), left, right));
		}
		else if (tok == dup_str(">="))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpGe>(SrcCodePos(ctx), left, right));
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
			<ExprBinOpPlus>(SrcCodePos(ctx), left, right));
	}
	else if (ctx->TokMinus())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
		auto right = _stacks.pop_expr();

		_stacks.push_expr(ExpressionBuilder::make_expr_binop
			<ExprBinOpMinus>(SrcCodePos(ctx), left, right));
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
				<ExprBinOpMul>(SrcCodePos(ctx), left, right));
		}
		else if (tok == dup_str("/"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpDiv>(SrcCodePos(ctx), left, right));
		}
		else if (tok == dup_str("%"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpMod>(SrcCodePos(ctx), left, right));
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
				<ExprBinOpBitAnd>(SrcCodePos(ctx), left, right));
		}
		else if (tok == dup_str("|"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitOr>(SrcCodePos(ctx), left, right));
		}
		else if (tok == dup_str("^"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitXor>(SrcCodePos(ctx), left, right));
		}
		else if (tok == dup_str("<<"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitLsl>(SrcCodePos(ctx), left, right));
		}
		else if (tok == dup_str(">>"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitLsr>(SrcCodePos(ctx), left, right));
		}
		else if (tok == dup_str(">>>"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitAsr>(SrcCodePos(ctx), left, right));
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
		(SrcCodePos(ctx), _stacks.pop_expr()));

	return nullptr;
}
VisitorRetType Compiler::visitExprMinusUnary
	(Parser::ExprMinusUnaryContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpMinus>
		(SrcCodePos(ctx), _stacks.pop_expr()));

	return nullptr;
}
VisitorRetType Compiler::visitExprLogNot
	(Parser::ExprLogNotContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpLogNot>
		(SrcCodePos(ctx), _stacks.pop_expr()));

	return nullptr;
}
VisitorRetType Compiler::visitExprBitNot
	(Parser::ExprBitNotContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpBitNot>
		(SrcCodePos(ctx), _stacks.pop_expr()));

	return nullptr;
}
VisitorRetType Compiler::visitExprCastUnsigned
	(Parser::ExprCastUnsignedContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop
		<ExprUnOpCastUnsigned>(SrcCodePos(ctx), _stacks.pop_expr()));

	return nullptr;
}
VisitorRetType Compiler::visitExprCastSigned
	(Parser::ExprCastSignedContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop
		<ExprUnOpCastSigned>(SrcCodePos(ctx), _stacks.pop_expr()));

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

		return ExpressionBuilder::make_expr_hc_num(SrcCodePos(ctx), value,
			size.get_ui(), false);
	}
	else if (ctx->sizedNumExpr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->sizedNumExpr());
		const auto value = _stacks.pop_big_num();
		const auto size = _stacks.pop_big_num();

		return ExpressionBuilder::make_expr_hc_num(SrcCodePos(ctx), value,
			size.get_ui(), false);
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
	if (ctx->identName())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		auto ident = _stacks.pop_str();

		Symbol* s_symbol = nullptr;

		Expression* to_push = nullptr;

		switch (pass())
		{
		//case Pass::FrostConstructRawPackages:
		//	break;


		//case Pass::FrostListModules:
		case Pass::FrostConstructRawModules:
			if (_frost_program().curr_frost_module->contains_symbol(ident))
			{
				//save_expr(ExprIdentName(_frost_program().curr_frost_module
			}
			break;

		default:
			break;
		}
	}

	//else if(ctx->scopedIdentName())
	//{
	//	ANY_JUST_ACCEPT_BASIC(ctx->scopedIdentName());

	//	// The identifier of whatever is inside the package.
	//	auto inner_ident = _stacks.pop_str();

	//	// What package does this identifier come from?
	//	auto scope_ident = _stacks.pop_str();
	//}
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
	ANY_JUST_ACCEPT_LOOPED(iter, ctx->identName())
	return nullptr;
}

void Compiler::_insert_module_port_var(antlr4::ParserRuleContext* ctx,
	SavedString s_ident, Symbol::PortType s_port_type,
	FrostLhsType* s_frost_lhs_type)
{
	auto module = _frost_program().curr_frost_module;

	if (module->contains_symbol(s_ident))
	{
		_err(ctx, sconcat("Module \"", module->ident(), 
			"\" already has a port variable with identifier \"", s_ident,
			"\"."));
	}

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
		_err(ctx, "Compiler::_insert_module_port_var():  Eek!");
		break;
	}

	auto s_frost_full_type = save_frost_full_type(FrostFullType
		(SrcCodePos(ctx), s_frost_lhs_type));

	symbol_table->insert_or_assign(save_symbol(Symbol(SrcCodePos(ctx),
		s_ident, s_port_type, s_frost_full_type)));
}

} // namespace frost_hdl
