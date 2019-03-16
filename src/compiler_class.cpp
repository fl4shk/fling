#include "compiler_class.hpp"
#include "general_allocator_class.hpp"
#include "expression_builder_class.hpp"

#include <sstream>



#define ANY_JUST_ACCEPT_BASIC(arg) \
	arg->accept(this)

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

int Compiler::run()
{
	//// Temporary initialization of "Pass::FrostListModules".
	//set_pass(Pass::FrostListModules);


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
	//else
	if (_in_frost_module_pass())
	{
		for (auto subprogram : ctx->declModule())
		{
			ANY_JUST_ACCEPT_BASIC(subprogram);
		}
	}

	return nullptr;
}




// Variable declaration stuff
VisitorRetType Compiler::visitLhsTypeName
	(Parser::LhsTypeNameContext *ctx)
{
	ANY_ACCEPT_IF_BASIC(ctx->lhsBuiltinTypeName())
	//else ANY_ACCEPT_IF_BASIC(ctx->lhsUnscopedTypeName())
	//else ANY_ACCEPT_IF_BASIC(ctx->lhsScopedTypeName())
	else
	{
		_err(ctx, "Compiler::visitLhsTypeName():  Eek!");
	}
	return nullptr;
}

VisitorRetType Compiler::visitLhsBuiltinTypeName
	(Parser::LhsBuiltinTypeNameContext *ctx)
{
	return nullptr;
}

// Future
VisitorRetType Compiler::visitLhsUnscopedTypeName
	(Parser::LhsUnscopedTypeNameContext *ctx)
{
	return nullptr;
}

// Future
VisitorRetType Compiler::visitLhsScopedTypeName
	(Parser::LhsScopedTypeNameContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitDeclNoLhsTypeVar
	(Parser::DeclNoLhsTypeVarContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitDeclVarList
	(Parser::DeclVarListContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitDeclPortVarList
	(Parser::DeclPortVarListContext *ctx)
{
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

		if (_frost_program.frost_module_table.contains(ident_name))
		{
			_err(ctx, sconcat("Duplicate module called \"", *ident_name,
				"\""));
		}

		_frost_program.curr_frost_module = save_frost_module(FrostModule
			(ident_name));

		// Process ports of this module
		for (auto port_list : ctx->declPortInputVarList())
		{
			ANY_JUST_ACCEPT_BASIC(port_list);
		}
		for (auto port_list : ctx->declPortOutputVarList())
		{
			ANY_JUST_ACCEPT_BASIC(port_list);
		}
		for (auto port_list : ctx->declPortInoutVarList())
		{
			ANY_JUST_ACCEPT_BASIC(port_list);
		}

		_frost_program.frost_module_table.insert_or_assign
			(_frost_program.curr_frost_module);
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
	return nullptr;
}
VisitorRetType Compiler::visitExprCompare
	(Parser::ExprCompareContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitExprAddSub
	(Parser::ExprAddSubContext *ctx)
{
	return nullptr;
}
VisitorRetType Compiler::visitExprMulDivModEtc
	(Parser::ExprMulDivModEtcContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitExprUnary
	(Parser::ExprUnaryContext *ctx)
{
	return nullptr;
}


VisitorRetType Compiler::visitExprBitInvert
	(Parser::ExprBitInvertContext *ctx)
{
	return nullptr;
}
VisitorRetType Compiler::visitExprNegate
	(Parser::ExprNegateContext *ctx)
{
	return nullptr;
}
VisitorRetType Compiler::visitExprLogNot
	(Parser::ExprLogNotContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitNumExpr
	(Parser::NumExprContext *ctx)
{
	if (ctx->rawNumExpr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->rawNumExpr());
		const auto value = _stacks.pop_num();

		const auto size = _default_hard_coded_num_size();

		return ExpressionBuilder::make_expr_hc_num(value, size.get_ui(),
			false);
	}
	else if (ctx->sizedNumExpr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->sizedNumExpr());
		const auto value = _stacks.pop_num();
		const auto size = _stacks.pop_num();

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

		_stacks.push_num(to_push);
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

		_stacks.push_num(to_push);
	}
	else if (ctx->TokBinNum())
	{
		BigNum to_push(0);

		for (auto c : ctx->TokBinNum()->toString())
		{
			to_push = (to_push * 2) + (c - '0');
		}

		_stacks.push_num(to_push);
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
	for (auto raw_num_expr : ctx->rawNumExpr())
	{
		ANY_JUST_ACCEPT_BASIC(raw_num_expr);
	}
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
	for (auto iter : ctx->identName())
	{
		ANY_JUST_ACCEPT_BASIC(iter);
	}

	return nullptr;
}

} // namespace frost_hdl
