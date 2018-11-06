#ifndef src_compiler_class_hpp
#define src_compiler_class_hpp

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


	SymbolTable ___sym_tbl;


	//std::stack<BigNum*> ___num_stack;
	std::stack<s64> ___scope_child_num_stack;
	std::stack<std::string*> ___str_stack;
	std::stack<ExprChunk> ___expr_chunk_stack;


	Parser::ProgramContext* ___program_ctx;
	int ___pass;

	ScopedTableNode<Symbol>* ___curr_scope_node = nullptr;
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
			//printerr("Error in file \"", *___file_name, "\", on line ",
			//	line, ", position ", pos_in_line, ":  ", msg, "\n");
			printerr("Error on line ", line, ", position ", pos_in_line, 
				":  ", msg, "\n");
		}
		exit(1);
	}
	inline void err(const std::string& msg)
	{
		//printerr("Error in file \"", *___file_name, "\":  ", msg, "\n");
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
			//printerr("Error in file \"", *___file_name, "\", on line ",
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
		___expr_chunk_stack.push(to_push);
	}
	inline auto get_top_expr_chunk()
	{
		return ___expr_chunk_stack.top();
	}
	inline auto pop_expr_chunk()
	{
		auto ret = ___expr_chunk_stack.top();
		___expr_chunk_stack.pop();
		return ret;
	}
	inline void push_scope_child_num(s64 to_push)
	{
		___scope_child_num_stack.push(to_push);
	}
	inline auto get_top_scope_child_num()
	{
		return ___scope_child_num_stack.top();
	}
	inline auto pop_scope_child_num()
	{
		auto ret = ___scope_child_num_stack.top();
		___scope_child_num_stack.pop();
		return ret;
	}

	inline void push_str(std::string* to_push)
	{
		___str_stack.push(to_push);
	}
	inline auto get_top_str()
	{
		return ___str_stack.top();
	}
	inline auto pop_str()
	{
		auto ret = ___str_stack.top();
		___str_stack.pop();
		return ret;
	}

	gen_getter_by_ref(sym_tbl);
};

} // namespace frost_hdl

#endif		// src_compiler_class_hpp
