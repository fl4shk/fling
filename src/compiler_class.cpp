#include "compiler_class.hpp"
#include "allocation_stuff.hpp"

#include <sstream>



#define ANY_JUST_ACCEPT_BASIC(arg) \
	arg->accept(this)

#define ANY_ACCEPT_IF_BASIC(arg) \
	if (arg) \
	{ \
		ANY_JUST_ACCEPT_BASIC(arg); \
	}

#define ANY_PUSH_TOK_IF(arg) \
	if (arg) \
	{ \
		push_str(cstm_strdup(arg->toString())); \
	}

namespace frost_hdl
{

Compiler::Compiler(Parser& parser)
{
	___program_ctx = parser.program();
}

Compiler::~Compiler()
{
}

int Compiler::run()
{
	return 0;
}


Compiler::VisitorRetType Compiler::visitProgram
	(Parser::ProgramContext *ctx)
{
	return nullptr;
}

// program:
Compiler::VisitorRetType Compiler::visitSubProgram
	(Parser::SubProgramContext *ctx)
{
	return nullptr;
}

// Declarations
// subProgram
Compiler::VisitorRetType Compiler::visitDeclModule
	(Parser::DeclModuleContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitDeclStruct
	(Parser::DeclStructContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitDeclVarList
	(Parser::DeclVarListContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitDeclParameters
	(Parser::DeclParametersContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitTypeName
	(Parser::TypeNameContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitSlice
	(Parser::SliceContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitScopedOuterStatements
	(Parser::ScopedOuterStatementsContext *ctx)
{
	return nullptr;
}

// Outer statements
Compiler::VisitorRetType Compiler::visitOuterStatement
	(Parser::OuterStatementContext *ctx)
{
	return nullptr;
}

// outerStmtAssign
Compiler::VisitorRetType Compiler::visitListIdentNames
	(Parser::ListIdentNamesContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitMultiListModulePorts
	(Parser::MultiListModulePortsContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitListModulePorts
	(Parser::ListModulePortsContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitListPortParams
	(Parser::ListPortParamsContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitPortParam
	(Parser::PortParamContext *ctx)
{
	return nullptr;
}

// Expression parsing
Compiler::VisitorRetType Compiler::visitExpr
	(Parser::ExprContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitExprLogical
	(Parser::ExprLogicalContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitExprCompare
	(Parser::ExprCompareContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitExprAddSub
	(Parser::ExprAddSubContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitExprMulDivModEtc
	(Parser::ExprMulDivModEtcContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitExprUnary
	(Parser::ExprUnaryContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitExprBitInvert
	(Parser::ExprBitInvertContext *ctx)
{
	return nullptr;
}
Compiler::VisitorRetType Compiler::visitExprNegate
	(Parser::ExprNegateContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitExprLogNot
	(Parser::ExprLogNotContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitNumExpr
	(Parser::NumExprContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitIdentExpr
	(Parser::IdentExprContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitIdentName
	(Parser::IdentNameContext *ctx)
{
	return nullptr;
}
Compiler::VisitorRetType Compiler::visitIdentSliced
	(Parser::IdentSlicedContext *ctx)
{
	return nullptr;
}

} // namespace frost_hdl
