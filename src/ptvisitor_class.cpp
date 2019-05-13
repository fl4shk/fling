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


// Variable declaration stuff
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

// List of local variables
auto PTVisitor::visitDeclVarList
	(Parser::DeclVarListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitModuleStmtInstantiateModule
	(Parser::ModuleStmtInstantiateModuleContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitInstantiateModuleParameterConnectionList
	(Parser::InstantiateModuleParameterConnectionListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitInstantiateModuleConnectionList
	(Parser::InstantiateModuleConnectionListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}


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
auto PTVisitor::visitStmtBehavHeaderElse
	(Parser::StmtBehavHeaderElseContext *ctx)
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
	with(localparam_var_list, WSTACKS_AST_CHILD(LocalparamVarList))
	{
		ANY_ACCEPT_IF_BASIC(ctx->lhsTypeName())
		ANY_JUST_ACCEPT_LOOPED(iter, ctx->declNoKwLocalparam())
	}

	return nullptr;
}

// `package` stuff
auto PTVisitor::visitDeclPackage
	(Parser::DeclPackageContext *ctx)
	-> VisitorRetType
{
	with(package, WSTACKS_AST_CHILD(Package))
	{
		// The model is different this time.
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		ANY_JUST_ACCEPT_BASIC(ctx->insidePackage());
	}

	return nullptr;
}
auto PTVisitor::visitInsidePackage
	(Parser::InsidePackageContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_LOOPED(iter, ctx->declLocalparamList())
	ANY_JUST_ACCEPT_LOOPED(iter, ctx->declStruct())
	return nullptr;
}

// Port vars can be arrays!
auto PTVisitor::visitDeclOnePortVar
	(Parser::DeclOnePortVarContext *ctx)
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

auto PTVisitor::visitDeclPortDirectionalVarList
	(Parser::DeclPortDirectionalVarListContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitDeclTaskfuncArgDirectionalVarList
	(Parser::DeclTaskfuncArgDirectionalVarListContext *ctx)
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

// `parameter` stuff
auto PTVisitor::visitDeclParameterVar
	(Parser::DeclParameterVarContext *ctx)
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
auto PTVisitor::visitOuterDeclParameterVarList
	(Parser::OuterDeclParameterVarListContext *ctx)
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

auto PTVisitor::visitModuleScope
	(Parser::ModuleScopeContext *ctx)
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
//auto PTVisitor::visitModuleStmtBehavBlock
//	(Parser::ModuleStmtBehavBlockContext *ctx)
//	-> VisitorRetType
//{
//	return nullptr;
//}

// Expression parsing
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

auto PTVisitor::visitNumExpr
	(Parser::NumExprContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitRawNumExpr
	(Parser::RawNumExprContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto PTVisitor::visitRawSizedNumExpr
	(Parser::RawSizedNumExprContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
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
	AST_CHILD(IdentName);

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
