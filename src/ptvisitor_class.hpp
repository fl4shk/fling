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

//#include "ptvisitor/list_for_gen_stack_defines.hpp"

//namespace frost_hdl
//{
//
//// Parse tree visitor
//class PTVisitor : public FrostHdlGrammarVisitor, public ErrWarnBase
//{
//public:		// types
//	typedef FrostHdlGrammarParser Parser;
//
//	typedef std::vector<std::unique_ptr<ParsedSrcCode>> ListParsedSrcCode;
//
//
//	typedef antlrcpp::Any VisitorRetType;
//
//	// Please excuse me calling something with "max" in its name "Small".
//	// In comparison to "BigNum"s, these actually *can be* small.
//	typedef uintmax_t SmallNum;
//
//	enum class ScalarOrArray : SmallNum
//	{
//		Scalar,
//		Array,
//	};
//
//	enum class ModuleOrInterface : SmallNum
//	{
//		Module,
//		Interface,
//	};
//
//	typedef uintmax_t PassUint;
//
//
//private:		// variables
//	//Parser::ProgramContext* _program_ctx = nullptr;
//
//
//	//ParsedSrcCode* _curr_parsed_src_code;
//	ListParsedSrcCode _list_parsed_src_code;
//
//	//Pass _pass = static_cast<Pass>(0);
//
//	// For when a pass needs multiple sub-passes.
//	//PassUint _subpass = 0;
//
//	//static constexpr PassUint MAX_SUBPASS = static_cast<PassUint>(1024)
//	//	* static_cast<PassUint>(1024);
//	//static constexpr PassUint MAX_SUBPASS = static_cast<PassUint>(1024);
//	//static constexpr PassUint MAX_SUBPASS = static_cast<PassUint>(8);
//
//	//bool _needs_another_subpass = false;
//
//public:		// functions
//	PTVisitor(ListParsedSrcCode&& s_list_parsed_src_code);
//	virtual ~PTVisitor();
//	int run();
//
//
//private:		// functions
//	//GEN_GETTER_AND_SETTER_BY_VAL(pass)
//	//GEN_GETTER_AND_SETTER_BY_VAL(subpass)
//
//private:		// visitor functions
//	VisitorRetType visitProgram
//		(Parser::ProgramContext *ctx);
//
//
//	// Variable declaration stuff
//	VisitorRetType visitLhsTypeName
//		(Parser::LhsTypeNameContext *ctx);
//
//	VisitorRetType visitLhsBuiltinTypeName
//		(Parser::LhsBuiltinTypeNameContext *ctx);
//
//	// custom type name from the current scope, be it a module or a
//	// package.
//	// (FUTURE)
//	VisitorRetType visitLhsUnscopedCstmTypeName
//		(Parser::LhsUnscopedCstmTypeNameContext *ctx);
//	// custom type name from a package.
//	// (FUTURE)
//	VisitorRetType visitLhsScopedCstmTypeName
//		(Parser::LhsScopedCstmTypeNameContext *ctx);
//
//
//	// Array dimensions go here
//	VisitorRetType visitDeclNoLhsTypeVar
//		(Parser::DeclNoLhsTypeVarContext *ctx);
//
//	// List of local variables
//	VisitorRetType visitDeclVarList
//		(Parser::DeclVarListContext *ctx);
//
//	VisitorRetType visitModuleStmtInstantiateModule
//		(Parser::ModuleStmtInstantiateModuleContext *ctx);
//	VisitorRetType visitInstantiateModuleParameterConnectionList
//		(Parser::InstantiateModuleParameterConnectionListContext *ctx);
//	VisitorRetType visitInstantiateModuleConnectionList
//		(Parser::InstantiateModuleConnectionListContext *ctx);
//
//
//	VisitorRetType visitGenerateBlockInModule
//		(Parser::GenerateBlockInModuleContext *ctx);
//	VisitorRetType visitGenerateBlockAnyHeader
//		(Parser::GenerateBlockAnyHeaderContext *ctx);
//	VisitorRetType visitGenerateBlockHeaderForLoop
//		(Parser::GenerateBlockHeaderForLoopContext *ctx);
//	VisitorRetType visitGenerateBlockHeaderIf
//		(Parser::GenerateBlockHeaderIfContext *ctx);
//	VisitorRetType visitPseudoFuncCallRange
//		(Parser::PseudoFuncCallRangeContext *ctx);
//
//	VisitorRetType visitStmtBehavHeaderForLoop
//		(Parser::StmtBehavHeaderForLoopContext *ctx);
//	VisitorRetType visitStmtBehavHeaderIf
//		(Parser::StmtBehavHeaderIfContext *ctx);
//	VisitorRetType visitStmtBehavHeaderElseif
//		(Parser::StmtBehavHeaderElseifContext *ctx);
//	VisitorRetType visitStmtBehavHeaderElse
//		(Parser::StmtBehavHeaderElseContext *ctx);
//
//	VisitorRetType visitDeclNoKwLocalparam
//		(Parser::DeclNoKwLocalparamContext *ctx);
//	VisitorRetType visitDeclLocalparamList
//		(Parser::DeclLocalparamListContext *ctx);
//
//	// "package" stuff
//	VisitorRetType visitDeclPackage
//		(Parser::DeclPackageContext *ctx);
//	VisitorRetType visitInsidePackage
//		(Parser::InsidePackageContext *ctx);
//
//	// Port vars can be arrays!
//	VisitorRetType visitDeclOnePortVar
//		(Parser::DeclOnePortVarContext *ctx);
//	VisitorRetType visitDeclPortVarList
//		(Parser::DeclPortVarListContext *ctx);
//
//	VisitorRetType visitDeclPortDirectionalVarList
//		(Parser::DeclPortDirectionalVarListContext *ctx);
//
//	// "parameter" stuff
//	VisitorRetType visitDeclParameterVar
//		(Parser::DeclParameterVarContext *ctx);
//	VisitorRetType visitDeclParameterVarList
//		(Parser::DeclParameterVarListContext *ctx);
//
//	// "module" stuff
//	VisitorRetType visitDeclModule
//		(Parser::DeclModuleContext *ctx);
//
//	VisitorRetType visitModuleScope
//		(Parser::ModuleScopeContext *ctx);
//
//	VisitorRetType visitModuleStmtContAssign
//		(Parser::ModuleStmtContAssignContext *ctx);
//	//VisitorRetType visitModuleStmtBehavBlock
//	//	(Parser::ModuleStmtBehavBlockContext *ctx);
//
//	// Expression parsing
//	VisitorRetType visitExpr
//		(Parser::ExprContext *ctx);
//
//	VisitorRetType visitExprLogical
//		(Parser::ExprLogicalContext *ctx);
//	VisitorRetType visitExprCompare
//		(Parser::ExprCompareContext *ctx);
//
//	VisitorRetType visitExprAddSub
//		(Parser::ExprAddSubContext *ctx);
//	VisitorRetType visitExprMulDivModEtc
//		(Parser::ExprMulDivModEtcContext *ctx);
//
//
//	VisitorRetType visitExprPlusUnary
//		(Parser::ExprPlusUnaryContext *ctx);
//	VisitorRetType visitExprMinusUnary
//		(Parser::ExprMinusUnaryContext *ctx);
//	VisitorRetType visitExprLogNot
//		(Parser::ExprLogNotContext *ctx);
//	VisitorRetType visitExprBitNot
//		(Parser::ExprBitNotContext *ctx);
//	VisitorRetType visitExprCastUnsgn
//		(Parser::ExprCastUnsgnContext *ctx);
//	VisitorRetType visitExprCastSgn
//		(Parser::ExprCastSgnContext *ctx);
//	VisitorRetType visitExprClog2
//		(Parser::ExprClog2Context *ctx);
//
//	VisitorRetType visitNumExpr
//		(Parser::NumExprContext *ctx);
//
//	VisitorRetType visitRawNumExpr
//		(Parser::RawNumExprContext *ctx);
//	VisitorRetType visitRawSizedNumExpr
//		(Parser::RawSizedNumExprContext *ctx);
//	VisitorRetType visitIdentSizedNumExpr
//		(Parser::IdentSizedNumExprContext *ctx);
//
//
//	VisitorRetType visitIdentExpr
//		(Parser::IdentExprContext *ctx);
//	VisitorRetType visitPureIdent
//		(Parser::PureIdentContext *ctx);
//	//VisitorRetType visitMemberAccessIdentExpr
//	//	(Parser::MemberAccessIdentExprContext *ctx);
//	VisitorRetType visitNonSlicedPureIdentExpr
//		(Parser::NonSlicedPureIdentExprContext *ctx);
//	VisitorRetType visitSlicedPureIdentExpr
//		(Parser::SlicedPureIdentExprContext *ctx);
//
//
//	VisitorRetType visitSliceWithOne
//		(Parser::SliceWithOneContext *ctx);
//	VisitorRetType visitSliceWithRange
//		(Parser::SliceWithRangeContext *ctx);
//	VisitorRetType visitSliceWithAny
//		(Parser::SliceWithAnyContext *ctx);
//
//	VisitorRetType visitIdentConcatExpr
//		(Parser::IdentConcatExprContext *ctx);
//
//
//	VisitorRetType visitIdentName
//		(Parser::IdentNameContext *ctx);
//	VisitorRetType visitScopedIdentName
//		(Parser::ScopedIdentNameContext *ctx);
//private:		// functions
//};
//
//} // namespace frost_hdl

#undef LIST_FOR_GEN_STACK

#endif		// src_ptvisitor_class_hpp
