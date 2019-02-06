#ifndef src_compiler_class_hpp
#define src_compiler_class_hpp

// src/compiler_class.hpp

#include "misc_includes.hpp"
#include "ANTLRErrorListener.h"
#include "gen_src/CompilerGrammarLexer.h"
#include "gen_src/CompilerGrammarParser.h"
#include "gen_src/CompilerGrammarVisitor.h"

//#include "symbol_table_class.hpp"
//#include "expr_chunk_class.hpp"

namespace frost_hdl
{

class Compiler : public CompilerGrammarVisitor
{
public:		// typedefs
	typedef antlr4::ParserRuleContext ParserRuleContext;
	typedef antlrcpp::Any VisitorRetType;

	typedef CompilerGrammarParser Parser;

private:		// variables


	//SymbolTable __sym_tbl;


	////std::stack<BigNum*> __num_stack;
	//std::stack<s64> __scope_child_num_stack;
	//std::stack<std::string*> __str_stack;
	//std::stack<ExprChunk> __expr_chunk_stack;


	Parser::ProgramContext* __program_ctx;
	int __pass;

	//ScopedTableNode<Symbol>* __curr_scope_node = nullptr;
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


	// In addition to module declarations, "subProgram" includes things
	// like struct definitions and packages, too.
	VisitorRetType visitSubProgram
		(Parser::SubProgramContext *ctx);



	// declarations
	VisitorRetType visitDeclModule
		(Parser::DeclModuleContext *ctx);

	VisitorRetType visitDeclVar
		(Parser::DeclVarContext *ctx);





	VisitorRetType visitModuleInsides
		(Parser::ModuleInsidesContext *ctx);


	// initial behavioral block
	VisitorRetType visitModuleStmtInitial
		(Parser::ModuleStmtInitialContext *ctx);

	// always_comb behavioral block
	VisitorRetType visitModuleStmtAlwaysComb
		(Parser::ModuleStmtAlwaysCombContext *ctx);

	// always_seq behavioral block
	VisitorRetType visitModuleStmtAlwaysSeq
		(Parser::ModuleStmtAlwaysSeqContext *ctx);

	VisitorRetType visitScopedListStmtBehavioral
		(Parser::ScopedListStmtBehavioralContext *ctx);

	VisitorRetType visitListStmtBehavioral
		(Parser::ListStmtBehavioralContext *ctx);

	VisitorRetType visitStmtBehavioral
		(Parser::StmtBehavioralContext *ctx);

	VisitorRetType visitStmtBehavAssign
		(Parser::StmtBehavAssignContext *ctx);

	//VisitorRetType visitStmtBehavIf
	//	(Parser::StmtBehavIfCon *ctx);


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


	VisitorRetType visitSlice
		(Parser::SliceContext *ctx);

private:		// functions
	//inline void push_expr_chunk(ExprChunk to_push)
	//{
	//	__expr_chunk_stack.push(to_push);
	//}
	//inline auto get_top_expr_chunk()
	//{
	//	return __expr_chunk_stack.top();
	//}
	//inline auto pop_expr_chunk()
	//{
	//	auto ret = __expr_chunk_stack.top();
	//	__expr_chunk_stack.pop();
	//	return ret;
	//}
	//inline void push_scope_child_num(s64 to_push)
	//{
	//	__scope_child_num_stack.push(to_push);
	//}
	//inline auto get_top_scope_child_num()
	//{
	//	return __scope_child_num_stack.top();
	//}
	//inline auto pop_scope_child_num()
	//{
	//	auto ret = __scope_child_num_stack.top();
	//	__scope_child_num_stack.pop();
	//	return ret;
	//}

	//inline void push_str(std::string* to_push)
	//{
	//	__str_stack.push(to_push);
	//}
	//inline auto get_top_str()
	//{
	//	return __str_stack.top();
	//}
	//inline auto pop_str()
	//{
	//	auto ret = __str_stack.top();
	//	__str_stack.pop();
	//	return ret;
	//}

	//GEN_GETTER_BY_REF(sym_tbl);
};

} // namespace frost_hdl

#endif		// src_compiler_class_hpp
