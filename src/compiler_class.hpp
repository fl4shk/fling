#ifndef src__slash__compiler_class_hpp
#define src__slash__compiler_class_hpp

// src/compiler_class.hpp

#include "misc_includes.hpp"
#include "ANTLRErrorListener.h"
#include "gen_src/CompilerGrammarLexer.h"
#include "gen_src/CompilerGrammarParser.h"
#include "gen_src/CompilerGrammarVisitor.h"

#include "symbol_table_classes.hpp"

//class Compiler : public CompilerGrammarVisitor
class Compiler
{
public:		// typedefs
	typedef antlr4::ParserRuleContext ParserRuleContext;

private:		// variables


	SymbolTable __sym_tbl;


	std::stack<BigNum*> __num_stack;
	std::stack<s64> __scope_child_num_stack;
	std::stack<std::string*> __str_stack;


	CompilerGrammarParser::ProgramContext* __program_ctx;
	int __pass;

	ScopedTableNode<Symbol>* __curr_scope_node = nullptr;
public:		// functions
	Compiler(CompilerGrammarParser& parser);
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
	antlrcpp::Any visitProgram
		(CompilerGrammarParser::ProgramContext *ctx);

	// program:
	antlrcpp::Any visitSubProgram
		(CompilerGrammarParser::SubProgramContext *ctx);

	// Declarations
	// subProgram
	antlrcpp::Any visitDeclModule
		(CompilerGrammarParser::DeclModuleContext *ctx);

private:		// functions
	inline void push_num(BigNum* to_push)
	{
		__num_stack.push(to_push);
	}
	inline auto get_top_num()
	{
		return __num_stack.top();
	}
	inline auto pop_num()
	{
		auto ret = __num_stack.top();
		__num_stack.pop();
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


#endif		// src__slash__compiler_class_hpp
