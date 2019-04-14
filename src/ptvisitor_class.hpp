#ifndef src_ptvisitor_class_hpp
#define src_ptvisitor_class_hpp

// src/ptvisitor_class.hpp

#include "misc_includes.hpp"
#include "parsed_src_code_class.hpp"

#include "table_types.hpp"
#include "frost_program_class.hpp"
#include "pseudo_func_call_range_class.hpp"

namespace frost_hdl
{

// Parse tree visitor
class PTVisitor : public FrostHdlGrammarVisitor
{
public:		// types
	typedef FrostHdlGrammarParser Parser;

	typedef std::vector<std::unique_ptr<ParsedSrcCode>> ListParsedSrcCode;


	typedef antlr4::ParserRuleContext ParserRuleContext;

	typedef antlrcpp::Any VisitorRetType;

	// Please excuse me calling something with "max" in its name "Small".
	// In comparison to "BigNum"s, these actually *can be* small.
	typedef uintmax_t SmallNum;

	enum class ScalarOrArray : SmallNum
	{
		Scalar,
		Array
	};

	typedef uintmax_t PassUint;

	// Passes where we walk the parse tree.  Some semantic analysis is done
	// here, so long as said semantic analysis does not need to actually
	// evaluate constant expressions.
	enum class Pass : PassUint
	{
		// List "package" names.
		ListPackageIdentifiers,

		// Add named things to the symbol tables and type tables and stuff
		ListPackageInnerDecl,

		// Construct raw "package"s, such that their "param"s are not
		// yet evaluated
		FinishRawPackageConstruct,

		//ListInterfaceIdentifiers,
		//// Add named things to the symbol tables and type tables and stuff
		//ListInterfaceInnerDecl,
		//FinishRawInterfaceConstruct,


		// List "module"s, their "param"s, and their ports.
		// (FUTURE:  Add "interface" "modport" stuff here.)
		ListModuleIdentifiers,

		// Add named things to the symbol tables and type tables and stuff
		ListModuleInnerDecl,

		// Construct raw modules (such that "param"s are not yet
		// evaluated)
		FinishRawModuleConstruct,


		Done,
	};

private:		// variables

	//X(stack_type, ret_type, whateverfix)
	#define LIST_FOR_GEN_STACK(X) \
		X(BigNum, const BigNum&, big_num) \
		X(SmallNum, SmallNum, small_num) \
		X(SavedString, SavedString, str) \
		X(SrcCodePos, SrcCodePos, src_code_pos) \
		X(Expression*, Expression*, expr) \
		X(Symbol*, Symbol*, sym) \
		X(FrostLhsType*, FrostLhsType*, lhs_type) \
		X(FrostFullType*, FrostFullType*, full_type) \
		X(FrostStatementTable::Node*, FrostStatementTable::Node*, \
			statement_table_node) \
		X(ModuleScope*, ModuleScope*, module_scope) \
		X(InterfaceScope*, InterfaceScope*, interface_scope) \

	class Stacks
	{
	private:		// variables
		#define GEN_STACK(stack_type, dummy, whateverfix) \
			std::stack<stack_type> _##whateverfix##_inner_stack; 

		LIST_FOR_GEN_STACK(GEN_STACK)
		#undef GEN_STACK

	public:		// functions
		#define GEN_STACK_FUNCS(dummy, ret_type, whateverfix) \
			inline void push_##whateverfix(ret_type to_push) \
			{ \
				_##whateverfix##_inner_stack.push(to_push); \
			} \
			inline auto get_top_##whateverfix() \
			{ \
				return _##whateverfix##_inner_stack.top(); \
			} \
			inline auto pop_##whateverfix() \
			{ \
				auto ret = _##whateverfix##_inner_stack.top(); \
				_##whateverfix##_inner_stack.pop(); \
				return ret; \
			} \
			inline const auto& whateverfix##_inner_stack() const \
			{ \
				return _##whateverfix##_inner_stack; \
			}

		LIST_FOR_GEN_STACK(GEN_STACK_FUNCS)
		#undef GEN_STACK_FUNCS

	} _stacks;

	#undef LIST_FOR_GEN_STACK



	//Parser::ProgramContext* _program_ctx = nullptr;


	//ParsedSrcCode* _curr_parsed_src_code;
	SavedString _curr_filename = nullptr;
	ListParsedSrcCode _list_parsed_src_code;

	Pass _pass = static_cast<Pass>(0);

	// For when a pass needs multiple sub-passes.
	PassUint _subpass = 0;

	static constexpr PassUint MAX_SUBPASS = static_cast<PassUint>(1024)
		* static_cast<PassUint>(1024);
	//static constexpr PassUint MAX_SUBPASS = static_cast<PassUint>(1024);
	//static constexpr PassUint MAX_SUBPASS = static_cast<PassUint>(8);

	//bool _needs_another_subpass = false;

	//MoveOnlyPrevCurrPair<FrostProgram> _frost_program;
	FrostProgram _frost_program;



public:		// functions
	PTVisitor(ListParsedSrcCode&& s_list_parsed_src_code);
	virtual ~PTVisitor();
	int run();


private:		// functions
	inline void _err(antlr4::ParserRuleContext* ctx,
		const std::string& msg)
	{
		if (ctx == nullptr)
		{
			printerr("Error:  ", msg, "\n");
		}
		else
		{
			//auto tok = ctx->getStart();
			//const size_t line = tok->getLine();
			//const size_t pos_in_line = tok->getCharPositionInLine();
			////printerr("Error in file \"", *_filename, "\", on line ",
			////	line, ", position ", pos_in_line, ":  ", msg, "\n");
			//printerr("Error on line ", line, ", position ", pos_in_line, 
			//	":  ", msg, "\n");
			_err(_make_src_code_pos(ctx), msg);
		}
		exit(1);
	}
	inline void _err(const SrcCodePos& src_code_pos,
		const std::string& msg)
	{
		//_err(src_code_pos.ctx(), msg);
		src_code_pos.err(msg);
	}
	inline void _err(const std::string& msg)
	{
		//printerr("Error in file \"", *_filename, "\":  ", msg, "\n");
		printerr("Error:  ", msg, "\n");
		exit(1);
	}
	inline void _warn(ParserRuleContext* ctx, const std::string& msg)
	{
		if (ctx == nullptr)
		{
			printerr("Warning:  ", msg, "\n");
		}
		else
		{
			//auto tok = ctx->getStart();
			//const size_t line = tok->getLine();
			//const size_t pos_in_line = tok->getCharPositionInLine();
			////printerr("Error in file \"", *_filename, "\", on line ",
			////	line, ", position ", pos_in_line, ":  ", msg, "\n");
			//printerr("Warning on line ", line, ", position ", pos_in_line, 
			//	":  ", msg, "\n");
			_warn(_make_src_code_pos(ctx), msg);
		}
	}
	inline void _warn(const SrcCodePos& src_code_pos,
		const std::string& msg)
	{
		//_warn(src_code_pos.ctx(), msg);
		src_code_pos.warn(msg);
	}
	inline void _warn(const std::string& msg)
	{
		printerr("Warning:  ", msg, "\n");
	}

	//static inline const BigNum _default_hard_coded_num_size()
	//{
	//	return BigNum(32);
	//}

	inline bool _in_package_pass() const
	{
		return ((pass() >= Pass::ListPackageIdentifiers)
			&& (pass() <= Pass::FinishRawPackageConstruct));
	}
	//inline bool _in_interface_pass() const
	//{
	//	return ((pass() >= Pass::ListInterfaceIdentifiers)
	//		&& (pass() <= Pass::FinishRawInterfaceConstruct));
	//}
	inline bool _in_module_pass() const
	{
		return ((pass() >= Pass::ListModuleIdentifiers)
			&& (pass() <= Pass::FinishRawModuleConstruct));
	}

	inline SrcCodePos _make_src_code_pos(ParserRuleContext* ctx) const
	{
		return SrcCodePos(_curr_filename, ctx);
	}

	void _reparse();

	//InScopeErrWarnBase<SrcCodePos>* _in_scope_thing();

	GEN_GETTER_AND_SETTER_BY_VAL(pass)
	GEN_GETTER_AND_SETTER_BY_VAL(subpass)

private:		// visitor functions
	// Basically just "module" and "package" declarations.  There are no
	// other things at global scope.
	VisitorRetType visitProgram
		(Parser::ProgramContext *ctx);


	// Variable declaration stuff
	VisitorRetType visitLhsTypeName
		(Parser::LhsTypeNameContext *ctx);

	VisitorRetType visitLhsBuiltinTypeName
		(Parser::LhsBuiltinTypeNameContext *ctx);

	// custom type name from the current scope, be it a module or a
	// package.
	// (FUTURE)
	VisitorRetType visitLhsUnscopedCstmTypeName
		(Parser::LhsUnscopedCstmTypeNameContext *ctx);
	// custom type name from a package.
	// (FUTURE)
	VisitorRetType visitLhsScopedCstmTypeName
		(Parser::LhsScopedCstmTypeNameContext *ctx);


	// Array dimensions go here
	VisitorRetType visitDeclNoLhsTypeVar
		(Parser::DeclNoLhsTypeVarContext *ctx);

	// List of local variables
	VisitorRetType visitDeclVarList
		(Parser::DeclVarListContext *ctx);

	VisitorRetType visitModuleStmtInstantiateModule
		(Parser::ModuleStmtInstantiateModuleContext *ctx);
	VisitorRetType visitInstantiateModulePortsList
		(Parser::InstantiateModulePortsListContext *ctx);


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

	VisitorRetType visitDeclNoKwLocalparam
		(Parser::DeclNoKwLocalparamContext *ctx);
	VisitorRetType visitDeclLocalparamList
		(Parser::DeclLocalparamListContext *ctx);

	// "package" stuff
	VisitorRetType visitDeclPackage
		(Parser::DeclPackageContext *ctx);
	VisitorRetType visitInsidePackage
		(Parser::InsidePackageContext *ctx);

	// For now, port vars can't be arrays.
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


	VisitorRetType visitIdentExpr
		(Parser::IdentExprContext *ctx);
	VisitorRetType visitPureIdent
		(Parser::PureIdentContext *ctx);
	//VisitorRetType visitMemberAccessIdentExpr
	//	(Parser::MemberAccessIdentExprContext *ctx);
	VisitorRetType visitNonSlicedPureIdentExpr
		(Parser::NonSlicedPureIdentExprContext *ctx);
	VisitorRetType visitSlicedPureIdentExpr
		(Parser::SlicedPureIdentExprContext *ctx);


	VisitorRetType visitSliceWithOne
		(Parser::SliceWithOneContext *ctx);
	VisitorRetType visitSliceWithRange
		(Parser::SliceWithRangeContext *ctx);
	VisitorRetType visitSliceWithAny
		(Parser::SliceWithAnyContext *ctx);

	VisitorRetType visitIdentConcatExpr
		(Parser::IdentConcatExprContext *ctx);


	VisitorRetType visitIdentName
		(Parser::IdentNameContext *ctx);
	VisitorRetType visitScopedIdentName
		(Parser::ScopedIdentNameContext *ctx);
private:		// functions
	void _insert_module_port_var(const SrcCodePos& s_src_code_pos,
		SavedString s_ident, Symbol::PortType s_port_type,
		FrostLhsType* s_frost_lhs_type);
};

} // namespace frost_hdl

#endif		// src_ptvisitor_class_hpp
