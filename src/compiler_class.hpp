#ifndef src_compiler_class_hpp
#define src_compiler_class_hpp

// src/compiler_class.hpp

#include "misc_includes.hpp"
#include <ANTLRErrorListener.h>
#include "gen_src/CompilerGrammarLexer.h"
#include "gen_src/CompilerGrammarParser.h"
#include "gen_src/CompilerGrammarVisitor.h"


#include "frost_module_table_class.hpp"

namespace frost_hdl
{

class Compiler : public CompilerGrammarVisitor
{
public:		// types
	typedef antlr4::ParserRuleContext ParserRuleContext;

	// VisitorRetType
	typedef antlrcpp::Any VisitorRetType;

	typedef CompilerGrammarParser Parser;

	enum class Pass : uintmax_t
	{
		ListPackages,
		ExpandPackages,

		ListModules,
		ExpandModules,

		Done,
	};



private:		// variables
	std::stack<BigNum> _num_stack;
	std::stack<Expression*> _expr_stack;
	std::stack<SavedString> _str_stack;
	std::stack<Symbol*> _sym_stack;


	// Global "FrostLhsType"s
	FrostLhsTypeTable _frost_lhs_type_table;

	// Global "FrostFullType"s
	FrostFullTypeTable _frost_full_type_table;

	// "FrostModule"s are always global anyway
	FrostModuleTable _frost_module_table;
	FrostModule* _curr_frost_module = nullptr;


	Parser::ProgramContext* _program_ctx;

	Pass _pass = static_cast<Pass>(0);


	//ScopedTableNode<Symbol>* _curr_scope_node = nullptr;

public:		// functions
	Compiler(Parser& parser);
	virtual ~Compiler() = default;
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
			auto tok = ctx->getStart();
			const size_t line = tok->getLine();
			const size_t pos_in_line = tok->getCharPositionInLine();
			//printerr("Error in file \"", *_file_name, "\", on line ",
			//	line, ", position ", pos_in_line, ":  ", msg, "\n");
			printerr("Error on line ", line, ", position ", pos_in_line, 
				":  ", msg, "\n");
		}
		exit(1);
	}
	inline void _err(const std::string& msg)
	{
		//printerr("Error in file \"", *_file_name, "\":  ", msg, "\n");
		printerr("Error:  ", msg, "\n");
		exit(1);
	}
	inline void _warn(ParserRuleContext* ctx, const std::string& msg)
	{
		if (ctx == nullptr)
		{
			printerr("Error:  ", msg, "\n");
		}
		else
		{
			auto tok = ctx->getStart();
			const size_t line = tok->getLine();
			const size_t pos_in_line = tok->getCharPositionInLine();
			//printerr("Error in file \"", *_file_name, "\", on line ",
			//	line, ", position ", pos_in_line, ":  ", msg, "\n");
			printerr("Warning on line ", line, ", position ", pos_in_line, 
				":  ", msg, "\n");
		}
	}
	inline void _warn(const std::string& msg)
	{
		printerr("Warning:  ", msg, "\n");
	}

	inline bool in_package_pass() const
	{
		return ((pass() == Pass::ListPackages)
			|| (pass() == Pass::ExpandPackages));
	}
	inline bool in_module_pass() const
	{
		return ((pass() == Pass::ListModules)
			|| (pass() == Pass::ExpandModules));
	}

	GEN_GETTER_AND_SETTER_BY_VAL(pass)

private:		// visitor functions
	// In addition to module declarations, this includes things like
	// "struct" definitions and "package"s, too.
	VisitorRetType visitProgram
		(Parser::ProgramContext *ctx);


	// Variable declaration stuff
	VisitorRetType visitLhsTypeName
		(Parser::LhsTypeNameContext *ctx);


	VisitorRetType visitDeclNoLhsTypeVar
		(Parser::DeclNoLhsTypeVarContext *ctx);

	VisitorRetType visitDeclVarList
		(Parser::DeclVarListContext *ctx);

	VisitorRetType visitDeclPortVarList
		(Parser::DeclPortVarListContext *ctx);

	VisitorRetType visitDeclPortInputVarList
		(Parser::DeclPortInputVarListContext *ctx);

	VisitorRetType visitDeclPortOutputVarList
		(Parser::DeclPortOutputVarListContext *ctx);
	VisitorRetType visitDeclPortInoutVarList
		(Parser::DeclPortInoutVarListContext *ctx);


	// "module" stuff
	VisitorRetType visitDeclModule
		(Parser::DeclModuleContext *ctx);

	VisitorRetType visitModuleInsides
		(Parser::ModuleInsidesContext *ctx);

	VisitorRetType visitModuleStmtAssign
		(Parser::ModuleStmtAssignContext *ctx);

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

	VisitorRetType visitExprUnary
		(Parser::ExprUnaryContext *ctx);


	VisitorRetType visitExprBitInvert
		(Parser::ExprBitInvertContext *ctx);
	VisitorRetType visitExprNegate
		(Parser::ExprNegateContext *ctx);
	VisitorRetType visitExprLogNot
		(Parser::ExprLogNotContext *ctx);

	VisitorRetType visitNumExpr
		(Parser::NumExprContext *ctx);



	VisitorRetType visitIdentExpr
		(Parser::IdentExprContext *ctx);


	VisitorRetType visitIdentName
		(Parser::IdentNameContext *ctx);

	// For now, only support sliced identifiers.
	VisitorRetType visitIdentSliced
		(Parser::IdentSlicedContext *ctx);

	VisitorRetType visitIdentConcatExpr
		(Parser::IdentConcatExprContext *ctx);

	VisitorRetType visitListIdentExpr
		(Parser::ListIdentExprContext *ctx);



	VisitorRetType visitSlice
		(Parser::SliceContext *ctx);

	VisitorRetType visitInnerSliceOne
		(Parser::InnerSliceOneContext *ctx);

	VisitorRetType visitInnerSliceTwo
		(Parser::InnerSliceTwoContext *ctx);

private:		// functions
	inline void _push_num(const BigNum& to_push)
	{
		_num_stack.push(to_push);
	}
	inline auto _get_top_num()
	{
		return _num_stack.top();
	}
	inline auto _pop_num()
	{
		auto ret = _num_stack.top();
		_num_stack.pop();
		return ret;
	}

	inline void _push_expr(Expression* to_push)
	{
		_expr_stack.push(to_push);
	}
	inline auto _get_top_expr()
	{
		return _expr_stack.top();
	}
	inline auto _pop_expr()
	{
		auto ret = _expr_stack.top();
		_expr_stack.pop();
		return ret;
	}

	inline void _push_sym(Symbol* to_push)
	{
		_sym_stack.push(to_push);
	}
	inline auto _get_top_sym()
	{
		return _sym_stack.top();
	}
	inline auto _pop_sym()
	{
		auto ret = _sym_stack.top();
		_sym_stack.pop();
		return ret;
	}

	inline void _push_str(SavedString to_push)
	{
		_str_stack.push(to_push);
	}
	inline auto _get_top_str()
	{
		return _str_stack.top();
	}
	inline auto _pop_str()
	{
		auto ret = _str_stack.top();
		_str_stack.pop();
		return ret;
	}

};

} // namespace frost_hdl

#endif		// src_compiler_class_hpp
