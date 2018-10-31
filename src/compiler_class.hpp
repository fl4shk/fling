#ifndef src__slash__compiler_class_hpp
#define src__slash__compiler_class_hpp

// src/compiler_class.hpp

#include "misc_includes.hpp"
#include "ANTLRErrorListener.h"
#include "gen_src/CompilerGrammarLexer.h"
#include "gen_src/CompilerGrammarParser.h"
#include "gen_src/CompilerGrammarVisitor.h"

#include "symbol_table_classes.hpp"
#include "expr_chunk_class.hpp"

namespace frost_hdl
{

class Compiler : public CompilerGrammarVisitor
{
public:		// typedefs
	typedef antlr4::ParserRuleContext ParserRuleContext;
	typedef antlrcpp::Any VisitorRetType;

	typedef CompilerGrammarParser Parser;

private:		// variables


	SymbolTable __sym_tbl;


	//std::stack<BigNum*> __num_stack;
	std::stack<s64> __scope_child_num_stack;
	std::stack<std::string*> __str_stack;
	std::stack<ExprChunk> __expr_chunk_stack;


	Parser::ProgramContext* __program_ctx;
	int __pass;

	ScopedTableNode<Symbol>* __curr_scope_node = nullptr;
public:		// functions
	Compiler(Parser& parser);
	virtual ~Compiler();
	int run();

private:		// functions
	inline void err(antlr4::ParserRuleContext* ctx, 
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
			//printerr("Error in file \"", *__file_name, "\", on line ",
			//	line, ", position ", pos_in_line, ":  ", msg, "\n");
			printerr("Error on line ", line, ", position ", pos_in_line, 
				":  ", msg, "\n");
		}
		exit(1);
	}
	inline void err(const std::string& msg)
	{
		//printerr("Error in file \"", *__file_name, "\":  ", msg, "\n");
		printerr("Error:  ", msg, "\n");
		exit(1);
	}
	inline void warn(ParserRuleContext* ctx, const std::string& msg)
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
			//printerr("Error in file \"", *__file_name, "\", on line ",
			//	line, ", position ", pos_in_line, ":  ", msg, "\n");
			printerr("Warning on line ", line, ", position ", pos_in_line, 
				":  ", msg, "\n");
		}
	}
	inline void warn(const std::string& msg)
	{
		printerr("Warning:  ", msg, "\n");
	}

private:		// visitor functions
	VisitorRetType visitProgram
		(Parser::ProgramContext *ctx);

	// program:
	VisitorRetType visitSubProgram
		(Parser::SubProgramContext *ctx);

	// Declarations
	// subProgram
	VisitorRetType visitDeclModule
		(Parser::DeclModuleContext *ctx);

	VisitorRetType visitDeclStruct
		(Parser::DeclStructContext *ctx);

	VisitorRetType visitDeclVarList
		(Parser::DeclVarListContext *ctx);

	VisitorRetType visitDeclParameters
		(Parser::DeclParametersContext *ctx);

	VisitorRetType visitTypeName
		(Parser::TypeNameContext *ctx);

	VisitorRetType visitSlice
		(Parser::SliceContext *ctx);

	VisitorRetType visitScopedOuterStatements
		(Parser::ScopedOuterStatementsContext *ctx);

	// Outer statements
	VisitorRetType visitOuterStatement
		(Parser::OuterStatementContext *ctx);

	// outerStmtAssign
	VisitorRetType visitListIdentNames
		(Parser::ListIdentNamesContext *ctx);

	VisitorRetType visitMultiListModulePorts
		(Parser::MultiListModulePortsContext *ctx);

	VisitorRetType visitListModulePorts
		(Parser::ListModulePortsContext *ctx);

	VisitorRetType visitListPortParams
		(Parser::ListPortParamsContext *ctx);

	VisitorRetType visitPortParam
		(Parser::PortParamContext *ctx);

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
	VisitorRetType visitIdentSliced
		(Parser::IdentSlicedContext *ctx);

private:		// functions
	inline void push_expr_chunk(ExprChunk to_push)
	{
		__expr_chunk_stack.push(to_push);
	}
	inline auto get_top_expr_chunk()
	{
		return __expr_chunk_stack.top();
	}
	inline auto pop_expr_chunk()
	{
		auto ret = __expr_chunk_stack.top();
		__expr_chunk_stack.pop();
		return ret;
	}
	inline void push_scope_child_num(s64 to_push)
	{
		__scope_child_num_stack.push(to_push);
	}
	inline auto get_top_scope_child_num()
	{
		return __scope_child_num_stack.top();
	}
	inline auto pop_scope_child_num()
	{
		auto ret = __scope_child_num_stack.top();
		__scope_child_num_stack.pop();
		return ret;
	}

	inline void push_str(std::string* to_push)
	{
		__str_stack.push(to_push);
	}
	inline auto get_top_str()
	{
		return __str_stack.top();
	}
	inline auto pop_str()
	{
		auto ret = __str_stack.top();
		__str_stack.pop();
		return ret;
	}

	gen_getter_by_ref(sym_tbl);
};

} // namespace frost_hdl

#endif		// src__slash__compiler_class_hpp
