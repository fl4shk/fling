#include "compiler_class.hpp"
#include "general_allocator_class.hpp"

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
		_push_str(TOK_TO_DUPPED_STR(arg)); \
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
	// Temporary initialization of "Pass::ListModules".
	set_pass(Pass::ListModules);


	while (pass() < Pass::Done)
	{
		visitProgram(_program_ctx);
		set_pass(static_cast<Pass>(static_cast<uintmax_t>(pass())
			+ static_cast<uintmax_t>(1)));
	}

	return 0;
}


// In addition to module declarations, this includes things like "struct"
// definitions and "package"s, too.
VisitorRetType Compiler::visitProgram(Parser::ProgramContext *ctx)
{
	//if ((pass() == Pass::ListModules) || (pass() == Pass::ExpandModules))

	if (in_package_pass())
	{
		//for (auto subprogram : ctx->declPackage())
		//{
		//	ANY_JUST_ACCEPT_BASIC(subprogram);
		//}
	}
	else if (in_module_pass())
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
	if (pass() == Pass::ListModules)
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		auto ident_name = _pop_str();

		if (_frost_module_table.contains(ident_name))
		{
			_err(ctx, sconcat("Duplicate module called \"", *ident_name,
				"\""));
		}

		_curr_frost_module = save_frost_module(FrostModule(ident_name));

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

		_frost_module_table.insert_or_assign(_curr_frost_module);
	}
	else if (pass() == Pass::ExpandModules)
	{
		//ANY_JUST_ACCEPT_BASIC(ctx->identName());
		//auto ident_name = _pop_str();
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
	return nullptr;
}


VisitorRetType Compiler::visitIdentExpr
	(Parser::IdentExprContext *ctx)
{
	return nullptr;
}


VisitorRetType Compiler::visitIdentName
	(Parser::IdentNameContext *ctx)
{
	_push_str(TOK_TO_DUPPED_STR(ctx->TokIdent()));

	return nullptr;
}

// For now, only support sliced identifiers.
VisitorRetType Compiler::visitIdentSliced
	(Parser::IdentSlicedContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitIdentConcatExpr
	(Parser::IdentConcatExprContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitListIdentExpr
	(Parser::ListIdentExprContext *ctx)
{
	return nullptr;
}



VisitorRetType Compiler::visitSlice
	(Parser::SliceContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitInnerSliceOne
	(Parser::InnerSliceOneContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitInnerSliceTwo
	(Parser::InnerSliceTwoContext *ctx)
{
	return nullptr;
}


} // namespace frost_hdl
