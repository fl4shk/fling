#include "ptvisitor_class.hpp"
//#include "general_allocator_class.hpp"
//#include "expression_builder_class.hpp"

#include <sstream>
#include "ptvisitor/dot_cpp_defines.hpp"

//#include "ptvisitor/list_for_gen_stack_defines.hpp"



namespace frost_hdl
{

//typedef PTVisitor::VisitorRetType VisitorRetType;

#define AST_CHILD(type) \
	_push_ast_child_back(_stacks.get_top_ast_node(), ctx, \
	AstNodeType::type)

#define WSTACKS_AST_CHILD(type) \
	with_stacks_ast_node(this, AST_CHILD(type)->data.get())

PTVisitor::PTVisitor(ListParsedSrcCode&& s_list_parsed_src_code)
	: _list_parsed_src_code(std::move(s_list_parsed_src_code))
{
	_ast.reset(new AstNode(SrcCodeChunk("<dummy>", "<dummy>", 9001, 9001),
		AstNodeType::Program));
}
PTVisitor::~PTVisitor()
{
}

int PTVisitor::run()
{
	for (const auto& parsed_src_code : _list_parsed_src_code)
	{
		_curr_filename = parsed_src_code->filename();

		visitProgram(parsed_src_code->parser()->program());
	}

	return 0;
}

auto PTVisitor::visitProgram
	(Parser::ProgramContext *ctx)
	-> VisitorRetType
{
	with(program, with_stacks_ast_node(this, _ast.get()))
	{
		ANY_JUST_ACCEPT_LOOPED(iter, ctx->declPackage())
		//ANY_JUST_ACCEPT_LOOPED(iter, ctx->declInterface())
		ANY_JUST_ACCEPT_LOOPED(iter, ctx->declModule())
	}

	return nullptr;
}

auto PTVisitor::visitLhsTypeName
	(Parser::LhsTypeNameContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitLhsBuiltinTypeName
	(Parser::LhsBuiltinTypeNameContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitLhsCstmTypeName
	(Parser::LhsCstmTypeNameContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}


// Array dimensions go here
auto PTVisitor::visitDeclNoLhsTypeVar
	(Parser::DeclNoLhsTypeVarContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

// List of local variables.
// (FUTURE:  The current scope's type will be important once custom
// types are added in.)
auto PTVisitor::visitDeclVarList
	(Parser::DeclVarListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitDeclNoKwLocalparam
	(Parser::DeclNoKwLocalparamContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitDeclLocalparamList
	(Parser::DeclLocalparamListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

// `struct` stuff
auto PTVisitor::visitDeclStruct
	(Parser::DeclStructContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitInsideStruct
	(Parser::InsideStructContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

// `package` stuff
auto PTVisitor::visitDeclPackage
	(Parser::DeclPackageContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitInsidePackage
	(Parser::InsidePackageContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

// Port vars can be arrays!
auto PTVisitor::visitDeclPortVarInst
	(Parser::DeclPortVarInstContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitDeclPortVarList
	(Parser::DeclPortVarListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitDeclPortDirVarList
	(Parser::DeclPortDirVarListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitDeclTaskfuncArgDirVarList
	(Parser::DeclTaskfuncArgDirVarListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}


auto PTVisitor::visitDeclPortInterfaceVarInst
	(Parser::DeclPortInterfaceVarInstContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitDeclPortInterfaceVarList
	(Parser::DeclPortInterfaceVarListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitDeclPortList
	(Parser::DeclPortListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

// `parameter` stuff
auto PTVisitor::visitDeclParameterVarInst
	(Parser::DeclParameterVarInstContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitDeclParameterVarList
	(Parser::DeclParameterVarListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitDeclParameterTypeInst
	(Parser::DeclParameterTypeInstContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitDeclParameterTypeList
	(Parser::DeclParameterTypeListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitDeclParameterList
	(Parser::DeclParameterListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

// `interface` stuff
auto PTVisitor::visitDeclInterface
	(Parser::DeclInterfaceContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitInsideInterface
	(Parser::InsideInterfaceContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

// `module` stuff
auto PTVisitor::visitDeclModule
	(Parser::DeclModuleContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}



auto PTVisitor::visitInsideModule
	(Parser::InsideModuleContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitModuleStmtContAssign
	(Parser::ModuleStmtContAssignContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitModuleStmtInstModule
	(Parser::ModuleStmtInstModuleContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitInstParameterList
	(Parser::InstParameterListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitInstModuleConnectionList
	(Parser::InstModuleConnectionListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

// generate block (that is) in (a) module
// As of writing this comment, the only other place where `generate` can
// appear is inside of an interface.
auto PTVisitor::visitGenerateBlockInModule
	(Parser::GenerateBlockInModuleContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}


auto PTVisitor::visitGenerateBlockAnyHeader
	(Parser::GenerateBlockAnyHeaderContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitGenerateBlockHeaderForLoop
	(Parser::GenerateBlockHeaderForLoopContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitGenerateBlockHeaderIf
	(Parser::GenerateBlockHeaderIfContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitPseudoFuncCallRange
	(Parser::PseudoFuncCallRangeContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
//auto PTVisitor::visitGenerateBlockInInterface
//	(Parser::GenerateBlockInInterfaceCon *ctx)
//	-> VisitorRetType
//{
//	return nullptr;
//}

// Behavioral code statement "headers"
auto PTVisitor::visitStmtBehavHeaderForLoop
	(Parser::StmtBehavHeaderForLoopContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitStmtBehavHeaderIf
	(Parser::StmtBehavHeaderIfContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitStmtBehavHeaderElseif
	(Parser::StmtBehavHeaderElseifContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
// This is boring, but I put it in here for consistency's sake.
auto PTVisitor::visitStmtBehavHeaderElse
	(Parser::StmtBehavHeaderElseContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

//auto PTVisitor::visitStmtChunkBehavIf
//	(Parser::StmtChunkBehavIfCon *ctx)
//	-> VisitorRetType
//{
//	return nullptr;
//}
//auto PTVisitor::visitStmtChunkBehavElseif
//	(Parser::StmtChunkBehavElseifCon *ctx)
//	-> VisitorRetType
//{
//	return nullptr;
//}
//auto PTVisitor::visitStmtChunkBehavElse
//	(Parser::StmtChunkBehavElseCon *ctx)
//	-> VisitorRetType
//{
//	return nullptr;
//}
//auto PTVisitor::visitStmtBehavIfElseChain
//	(Parser::StmtBehavIfElseChainCon *ctx)
//	-> VisitorRetType
//{
//	return nullptr;
//}



// Expression parsing
// (avoid left-recursion)
auto PTVisitor::visitExpr
	(Parser::ExprContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitExprLogical
	(Parser::ExprLogicalContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitExprCompare
	(Parser::ExprCompareContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitExprAddSub
	(Parser::ExprAddSubContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitExprMulDivModEtc
	(Parser::ExprMulDivModEtcContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}



auto PTVisitor::visitExprPlusUnary
	(Parser::ExprPlusUnaryContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitExprMinusUnary
	(Parser::ExprMinusUnaryContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitExprLogNot
	(Parser::ExprLogNotContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitExprBitNot
	(Parser::ExprBitNotContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitExprCastUnsgn
	(Parser::ExprCastUnsgnContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitExprCastSgn
	(Parser::ExprCastSgnContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitExprClog2
	(Parser::ExprClog2Context *ctx)
	-> VisitorRetType
{
	return nullptr;
}
//auto PTVisitor::visitExprPow
//	(Parser::ExprPowCon *ctx)
//	-> VisitorRetType
//{
//	return nullptr;
//}


auto PTVisitor::visitNumExpr
	(Parser::NumExprContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

// I have no interest in octal numbers, at least for now.
auto PTVisitor::visitRawNumExpr
	(Parser::RawNumExprContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

// Yes, this is done with the parser instead of the lexer.
//
// That is very strange, Bobbeh.
//
// It allows you to do things like
//
// 0x3        ' 9
//
// Also, signed hard-coded numbers are *not* properly handled here, so
// you are forced to do `$sgn(...)` instead of `...'s...`.  The lexer
// would have to be more heavily involved here if signed, hard-coded
// numbers were to be allowed with Verilog-style syntax.
auto PTVisitor::visitRawSizedNumExpr
	(Parser::RawSizedNumExprContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

// This permits using a constant to indicate the width of a hard-coded
// number, permitting shorter Frost HDL source code in some situations.
auto PTVisitor::visitIdentSizedNumExpr
	(Parser::IdentSizedNumExprContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}



auto PTVisitor::visitSliceWithOne
	(Parser::SliceWithOneContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitSliceWithRange
	(Parser::SliceWithRangeContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitSliceWithAny
	(Parser::SliceWithAnyContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}


auto PTVisitor::visitIdentPure
	(Parser::IdentPureContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitIdentExpr
	(Parser::IdentExprContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitIdentAccess
	(Parser::IdentAccessContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitIdentConcatExpr
	(Parser::IdentConcatExprContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitIdentName
	(Parser::IdentNameContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitIdentScope
	(Parser::IdentScopeContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}


} // namespace frost_hdl

#undef LIST_FOR_GEN_STACK
#undef AST_CHILD
#undef WSTACKS_AST_CHILD
