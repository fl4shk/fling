#ifndef src_compiler_class_hpp
#define src_compiler_class_hpp

// src/compiler_class.hpp

#include "misc_includes.hpp"
#include <ANTLRErrorListener.h>
#include "gen_src/CompilerGrammarLexer.h"
#include "gen_src/CompilerGrammarParser.h"
#include "gen_src/CompilerGrammarVisitor.h"


//#include "frost_module_table_class.hpp"
#include "frost_program_class.hpp"

namespace frost_hdl
{

class Compiler : public CompilerGrammarVisitor
{
public:		// types
	typedef antlr4::ParserRuleContext ParserRuleContext;

	typedef antlrcpp::Any VisitorRetType;
	typedef CompilerGrammarParser Parser;


	typedef uintmax_t PassUint;

	enum class Pass : PassUint
	{
		//// Passes for the initial processing of Frost HDL source code
		//FrostListPackages,
		//FrostExpandPackages,

		////FrostListInterfaces,
		////FrostExpandInterfaces,

		FrostListModules,
		FrostExpandModules,

		//// Passes for processing the output of processing Frost HDL source
		//// code

		//// Passes for generation of code in the destination HDL (most
		//// likely Verilog)

		Done,
	};


private:		// variables
	class Stacks
	{
	private:		// variables
		std::stack<BigNum> _num_stack;
		std::stack<Expression*> _expr_stack;
		std::stack<SavedString> _str_stack;
		std::stack<Symbol*> _sym_stack;

	public:		// functions
		#define GEN_STACK_FUNCS(type, whateverfix) \
			inline void push_##whateverfix(type to_push) \
			{ \
				_##whateverfix##_stack.push(to_push); \
			} \
			inline auto get_top_##whateverfix() \
			{ \
				return _##whateverfix##_stack.top(); \
			} \
			inline auto pop_##whateverfix() \
			{ \
				auto ret = _##whateverfix##_stack.top(); \
				_##whateverfix##_stack.pop(); \
				return ret; \
			}

		GEN_STACK_FUNCS(const BigNum&, num)
		GEN_STACK_FUNCS(Expression*, expr)
		GEN_STACK_FUNCS(Symbol*, sym)
		GEN_STACK_FUNCS(SavedString, str)

		#undef GEN_STACK_FUNCS

	} _stacks;



	Parser::ProgramContext* _program_ctx;

	Pass _pass = static_cast<Pass>(0);

	// For when a pass needs multiple sub-passes.
	PassUint _subpass = 0;

	FrostProgram _frost_program;


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

	static inline const BigNum _default_hard_coded_num_size()
	{
		return BigNum(32);
	}

	// "Pass"es
	//inline bool _in_frost_package_pass() const
	//{
	//	return ((pass() == Pass::FrostListPackages)
	//		|| (pass() == Pass::FrostExpandPackages));
	//}
	inline bool _in_frost_module_pass() const
	{
		return ((pass() == Pass::FrostListModules)
			|| (pass() == Pass::FrostExpandModules));
	}

	GEN_GETTER_AND_SETTER_BY_VAL(pass)

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
	VisitorRetType visitLhsUnscopedTypeName
		(Parser::LhsUnscopedTypeNameContext *ctx);
	VisitorRetType visitLhsScopedTypeName
		(Parser::LhsScopedTypeNameContext *ctx);


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

	VisitorRetType visitRawNumExpr
		(Parser::RawNumExprContext *ctx);
	VisitorRetType visitSizedNumExpr
		(Parser::SizedNumExprContext *ctx);



	VisitorRetType visitIdentExpr
		(Parser::IdentExprContext *ctx);


	VisitorRetType visitIdentName
		(Parser::IdentNameContext *ctx);
	VisitorRetType visitScopedIdentName
		(Parser::ScopedIdentNameContext *ctx);
private:		// functions

};

} // namespace frost_hdl

#endif		// src_compiler_class_hpp
