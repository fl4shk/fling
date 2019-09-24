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
	inline auto _push_ast_child_back(AstNode* parent,
		ParserRuleContext* ctx, AstNodeType s_type) const
	{
		return parent->push_child_back(_make_src_code_chunk(ctx), s_type);
	}

private:		// visitor functions
	VisitorRetType visitProgram
		(Parser::ProgramContext *ctx);

	VisitorRetType visitLhsTypeName
		(Parser::LhsTypeNameContext *ctx);

	VisitorRetType visitLhsBuiltinTypeName
		(Parser::LhsBuiltinTypeNameContext *ctx);

	VisitorRetType visitLhsCstmTypeName
		(Parser::LhsCstmTypeNameContext *ctx);


	// Array dimensions go here
	VisitorRetType visitDeclNoLhsTypeVar
		(Parser::DeclNoLhsTypeVarContext *ctx);

	// List of local variables.
	// (FUTURE:  The current scope's type will be important once custom
	// types are added in.)
	VisitorRetType visitDeclVarList
		(Parser::DeclVarListContext *ctx);

	VisitorRetType visitDeclNoKwLocalparam
		(Parser::DeclNoKwLocalparamContext *ctx);

	VisitorRetType visitDeclLocalparamList
		(Parser::DeclLocalparamListContext *ctx);

	// `struct` stuff
	VisitorRetType visitDeclStruct
		(Parser::DeclStructContext *ctx);

	VisitorRetType visitInsideStruct
		(Parser::InsideStructContext *ctx);

	// `package` stuff
	VisitorRetType visitDeclPackage
		(Parser::DeclPackageContext *ctx);

	VisitorRetType visitInsidePackage
		(Parser::InsidePackageContext *ctx);

	// Port vars can be arrays!
	VisitorRetType visitDeclPortVarInst
		(Parser::DeclPortVarInstContext *ctx);

	VisitorRetType visitDeclPortVarList
		(Parser::DeclPortVarListContext *ctx);

	VisitorRetType visitDeclPortDirVarList
		(Parser::DeclPortDirVarListContext *ctx);
	VisitorRetType visitDeclTaskfuncArgDirVarList
		(Parser::DeclTaskfuncArgDirVarListContext *ctx);

	VisitorRetType visitDeclPortInterfaceVarInst
		(Parser::DeclPortInterfaceVarInstContext *ctx);

	VisitorRetType visitDeclPortInterfaceVarList
		(Parser::DeclPortInterfaceVarListContext *ctx);

	VisitorRetType visitDeclPortList
		(Parser::DeclPortListContext *ctx);


	// `parameter` stuff
	VisitorRetType visitDeclParameterVarInst
		(Parser::DeclParameterVarInstContext *ctx);
	VisitorRetType visitDeclParameterVarList
		(Parser::DeclParameterVarListContext *ctx);

	VisitorRetType visitDeclParameterTypeInst
		(Parser::DeclParameterTypeInstContext *ctx);
	VisitorRetType visitDeclParameterTypeList
		(Parser::DeclParameterTypeListContext *ctx);
	VisitorRetType visitDeclParameterList
		(Parser::DeclParameterListContext *ctx);

	// `interface` stuff
	VisitorRetType visitDeclInterface
		(Parser::DeclInterfaceContext *ctx);
	VisitorRetType visitInsideInterface
		(Parser::InsideInterfaceContext *ctx);

	// `module` stuff
	VisitorRetType visitDeclModule
		(Parser::DeclModuleContext *ctx);



	VisitorRetType visitInsideModule
		(Parser::InsideModuleContext *ctx);

	VisitorRetType visitModuleStmtContAssign
		(Parser::ModuleStmtContAssignContext *ctx);

	VisitorRetType visitModuleStmtInstModule
		(Parser::ModuleStmtInstModuleContext *ctx);

	VisitorRetType visitInstParameterList
		(Parser::InstParameterListContext *ctx);
	VisitorRetType visitInstModuleConnectionList
		(Parser::InstModuleConnectionListContext *ctx);

	// generate block (that is) in (a) module
	// As of writing this comment, the only other place where `generate` can
	// appear is inside of an interface.
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
	//VisitorRetType visitGenerateBlockInInterface
	//	(Parser::GenerateBlockInInterfaceCon *ctx);

	// Behavioral code statement "headers"
	VisitorRetType visitStmtBehavHeaderForLoop
		(Parser::StmtBehavHeaderForLoopContext *ctx);

	VisitorRetType visitStmtBehavHeaderIf
		(Parser::StmtBehavHeaderIfContext *ctx);
	VisitorRetType visitStmtBehavHeaderElseif
		(Parser::StmtBehavHeaderElseifContext *ctx);
	// This is boring, but I put it in here for consistency's sake.
	VisitorRetType visitStmtBehavHeaderElse
		(Parser::StmtBehavHeaderElseContext *ctx);

	//VisitorRetType visitStmtChunkBehavIf
	//	(Parser::StmtChunkBehavIfCon *ctx);
	//VisitorRetType visitStmtChunkBehavElseif
	//	(Parser::StmtChunkBehavElseifCon *ctx);
	//VisitorRetType visitStmtChunkBehavElse
	//	(Parser::StmtChunkBehavElseCon *ctx);
	//VisitorRetType visitStmtBehavIfElseChain
	//	(Parser::StmtBehavIfElseChainCon *ctx);



	// Expression parsing
	// (avoid left-recursion)
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
	//VisitorRetType visitExprPow
	//	(Parser::ExprPowCon *ctx);


	VisitorRetType visitNumExpr
		(Parser::NumExprContext *ctx);

	// I have no interest in octal numbers, at least for now.
	VisitorRetType visitRawNumExpr
		(Parser::RawNumExprContext *ctx);

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
	VisitorRetType visitRawSizedNumExpr
		(Parser::RawSizedNumExprContext *ctx);

	// This permits using a constant to indicate the width of a hard-coded
	// number, permitting shorter Frost HDL source code in some situations.
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

	VisitorRetType visitIdentAccess
		(Parser::IdentAccessContext *ctx);

	VisitorRetType visitIdentConcatExpr
		(Parser::IdentConcatExprContext *ctx);

	VisitorRetType visitIdentName
		(Parser::IdentNameContext *ctx);

	VisitorRetType visitIdentScope
		(Parser::IdentScopeContext *ctx);
};

} // namespace frost_hdl


#endif		// src_ptvisitor_class_hpp
