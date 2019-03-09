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

#define ANY_PUSH_TOK_IF(arg) \
	if (arg) \
	{ \
		push_str(dup_str(arg->toString())); \
	}

namespace frost_hdl
{

Compiler::Compiler(Parser& parser)
{
	_program_ctx = parser.program();
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


// In addition to module declarations, "subProgram" includes things
// like struct definitions and packages, too.
Compiler::VisitorRetType Compiler::visitSubProgram
	(Parser::SubProgramContext *ctx)
{
	return nullptr;
}



// declarations
Compiler::VisitorRetType Compiler::visitDeclModule
	(Parser::DeclModuleContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitDeclVar
	(Parser::DeclVarContext *ctx)
{
	return nullptr;
}





Compiler::VisitorRetType Compiler::visitModuleInsides
	(Parser::ModuleInsidesContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitModuleStmtAssign
	(Parser::ModuleStmtAssignContext *ctx)
{
	return nullptr;
}


//// initial behavioral block
//Compiler::VisitorRetType Compiler::visitModuleStmtInitial
//	(Parser::ModuleStmtInitialContext *ctx)
//{
//	return nullptr;
//}
//
//// always_comb behavioral block
//Compiler::VisitorRetType Compiler::visitModuleStmtAlwaysComb
//	(Parser::ModuleStmtAlwaysCombContext *ctx)
//{
//	return nullptr;
//}
//
//// always_seq behavioral block
//Compiler::VisitorRetType Compiler::visitModuleStmtAlwaysSeq
//	(Parser::ModuleStmtAlwaysSeqContext *ctx)
//{
//	return nullptr;
//}
//
//Compiler::VisitorRetType Compiler::visitScopedListStmtBehavioral
//	(Parser::ScopedListStmtBehavioralContext *ctx)
//{
//	return nullptr;
//}
//
//Compiler::VisitorRetType Compiler::visitListStmtBehavioral
//	(Parser::ListStmtBehavioralContext *ctx)
//{
//	return nullptr;
//}
//
//Compiler::VisitorRetType Compiler::visitStmtBehavioral
//	(Parser::StmtBehavioralContext *ctx)
//{
//	return nullptr;
//}
//
//Compiler::VisitorRetType Compiler::visitStmtBehavAssign
//	(Parser::StmtBehavAssignContext *ctx)
//{
//	return nullptr;
//}
//
////Compiler::VisitorRetType Compiler::visitStmtBehavIf
////	(Parser::StmtBehavIfCon *ctx)
////{
////	return nullptr;
////}


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

// For now, only support sliced identifiers.
Compiler::VisitorRetType Compiler::visitIdentSliced
	(Parser::IdentSlicedContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitIdentConcatExpr
	(Parser::IdentConcatExprContext *ctx)
{
	return nullptr;
}
Compiler::VisitorRetType Compiler::visitListIdentExpr
	(Parser::ListIdentExprContext *ctx)
{
	return nullptr;
}

Compiler::VisitorRetType Compiler::visitSlice
	(Parser::SliceContext *ctx)
{
	return nullptr;
}


Compiler::VisitorRetType Compiler::visitInnerSliceOne
	(Parser::InnerSliceOneContext *ctx)
{
	return nullptr;
}
Compiler::VisitorRetType Compiler::visitInnerSliceTwo
	(Parser::InnerSliceTwoContext *ctx)
{
	return nullptr;
}

} // namespace frost_hdl
