#ifndef src_ptvisitor_class_hpp
#define src_ptvisitor_class_hpp

// src/ptvisitor_class.hpp

#include "misc_includes.hpp"
#include "parsed_src_code_class.hpp"

#include "err_warn_base_class.hpp"

//#include "table_types.hpp"
//#include "frost_program_class.hpp"
//#include "pseudo_func_call_range_class.hpp"
//#include "generate_block_header_classes.hpp"

#include "ast_node_class.hpp"
#include "ast_builder_class.hpp"


namespace frost_hdl
{

// Parse tree visitor
class PTVisitor final : public FrostHdlGrammarVisitor, public ErrWarnBase
{
public:		// types
	typedef FrostHdlGrammarParser Parser;

	typedef std::vector<std::unique_ptr<ParsedSrcCode>> ListParsedSrcCode;

	typedef antlrcpp::Any VisitorRetType;

	typedef uintmax_t SmallNum;


private:		// variables
	ListParsedSrcCode _list_parsed_src_code;
	AstNode::Child _ast;

	#include "ptvisitor/list_for_gen_stack_defines.hpp"
	#include "gen_stacks_stuff.hpp"
	#undef LIST_FOR_GEN_STACK

public:		// functions
	PTVisitor(ListParsedSrcCode&& s_list_parsed_src_code);
	~PTVisitor();
	int run();


private:		// functions

private:		// visitor functions
	VisitorRetType visitProgram
		(Parser::ProgramContext *ctx);


	// Variable declaration stuff
	VisitorRetType visitLhsTypeName
		(Parser::LhsTypeNameContext *ctx);

	VisitorRetType visitLhsBuiltinTypeName
		(Parser::LhsBuiltinTypeNameContext *ctx);

	VisitorRetType visitLhsCstmTypeName
		(Parser::LhsCstmTypeNameContext *ctx);


	// Array dimensions go here
	VisitorRetType visitDeclNoLhsTypeVar
		(Parser::DeclNoLhsTypeVarContext *ctx);

	// List of local variables
	VisitorRetType visitDeclVarList
		(Parser::DeclVarListContext *ctx);

	VisitorRetType visitModuleStmtInstantiateModule
		(Parser::ModuleStmtInstantiateModuleContext *ctx);
	VisitorRetType visitInstantiateModuleParameterConnectionList
		(Parser::InstantiateModuleParameterConnectionListContext *ctx);
	VisitorRetType visitInstantiateModuleConnectionList
		(Parser::InstantiateModuleConnectionListContext *ctx);


	VisitorRetType visitGenerateBlockInModule
		(Parser::GenerateBlockInModuleContext *ctx);
	VisitorRetType visitGenerateBlockAnyHeader
		(Parser::GenerateBlockAnyHeaderContext *ctx);
	VisitorRetType visitGenerateBlockHeaderForLoop
		(Parser::GenerateBlockHeaderForLoopContext *ctx);
	VisitorRetType visitGenerateBlockHeaderIf
		(Parser::GenerateBlockHeaderIfContext *ctx);
	VisitorRetType visitPseudoFuncCallRange
		(Parser::PseudoFuncCallRangeContext *ctx);

	VisitorRetType visitStmtBehavHeaderForLoop
		(Parser::StmtBehavHeaderForLoopContext *ctx);
	VisitorRetType visitStmtBehavHeaderIf
		(Parser::StmtBehavHeaderIfContext *ctx);
	VisitorRetType visitStmtBehavHeaderElseif
		(Parser::StmtBehavHeaderElseifContext *ctx);
	VisitorRetType visitStmtBehavHeaderElse
		(Parser::StmtBehavHeaderElseContext *ctx);

	VisitorRetType visitDeclNoKwLocalparam
		(Parser::DeclNoKwLocalparamContext *ctx);
	VisitorRetType visitDeclLocalparamList
		(Parser::DeclLocalparamListContext *ctx);

	// "package" stuff
	VisitorRetType visitDeclPackage
		(Parser::DeclPackageContext *ctx);
	VisitorRetType visitInsidePackage
		(Parser::InsidePackageContext *ctx);

	// Port vars can be arrays!
	VisitorRetType visitDeclOnePortVar
		(Parser::DeclOnePortVarContext *ctx);
	VisitorRetType visitDeclPortVarList
		(Parser::DeclPortVarListContext *ctx);

	VisitorRetType visitDeclPortDirectionalVarList
		(Parser::DeclPortDirectionalVarListContext *ctx);

	// "parameter" stuff
	VisitorRetType visitDeclParameterVar
		(Parser::DeclParameterVarContext *ctx);
	VisitorRetType visitDeclParameterVarList
		(Parser::DeclParameterVarListContext *ctx);

	// "module" stuff
	VisitorRetType visitDeclModule
		(Parser::DeclModuleContext *ctx);

	VisitorRetType visitModuleScope
		(Parser::ModuleScopeContext *ctx);

	VisitorRetType visitModuleStmtContAssign
		(Parser::ModuleStmtContAssignContext *ctx);
	//VisitorRetType visitModuleStmtBehavBlock
	//	(Parser::ModuleStmtBehavBlockContext *ctx);

	// Expression parsing
	VisitorRetType visitExpr
		(Parser::ExprContext *ctx);

	VisitorRetType visitExprLogical
		(Parser::ExprLogicalContext *ctx);
	VisitorRetType visitExprCompare
		(Parser::ExprCompareContext *ctx);

	VisitorRetType visitExprAddSub
		(Parser::ExprAddSubContext *ctx);
	VisitorRetType visitExprMulDivModEtc
		(Parser::ExprMulDivModEtcContext *ctx);


	VisitorRetType visitExprPlusUnary
		(Parser::ExprPlusUnaryContext *ctx);
	VisitorRetType visitExprMinusUnary
		(Parser::ExprMinusUnaryContext *ctx);
	VisitorRetType visitExprLogNot
		(Parser::ExprLogNotContext *ctx);
	VisitorRetType visitExprBitNot
		(Parser::ExprBitNotContext *ctx);
	VisitorRetType visitExprCastUnsgn
		(Parser::ExprCastUnsgnContext *ctx);
	VisitorRetType visitExprCastSgn
		(Parser::ExprCastSgnContext *ctx);
	VisitorRetType visitExprClog2
		(Parser::ExprClog2Context *ctx);

	VisitorRetType visitNumExpr
		(Parser::NumExprContext *ctx);

	VisitorRetType visitRawNumExpr
		(Parser::RawNumExprContext *ctx);
	VisitorRetType visitRawSizedNumExpr
		(Parser::RawSizedNumExprContext *ctx);
	VisitorRetType visitIdentSizedNumExpr
		(Parser::IdentSizedNumExprContext *ctx);

	
	VisitorRetType visitSliceWithOne
		(Parser::SliceWithOneContext *ctx);
	VisitorRetType visitSliceWithRange
		(Parser::SliceWithRangeContext *ctx);
	VisitorRetType visitSliceWithAny
		(Parser::SliceWithAnyContext *ctx);

	VisitorRetType visitIdentPure
		(Parser::IdentPureContext *ctx);

	VisitorRetType visitIdentExpr
		(Parser::IdentExprContext *ctx);

	VisitorRetType visitIdentInnerExpr
		(Parser::IdentInnerExprContext *ctx);
	VisitorRetType visitIdentConcatExpr
		(Parser::IdentConcatExprContext *ctx);

	VisitorRetType visitIdentName
		(Parser::IdentNameContext *ctx);
	VisitorRetType visitIdentScope
		(Parser::IdentScopeContext *ctx);
};

} // namespace frost_hdl


#endif		// src_ptvisitor_class_hpp
