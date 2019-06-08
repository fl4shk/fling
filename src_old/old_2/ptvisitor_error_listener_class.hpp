#ifndef src_ptvisitor_error_listener_class_hpp
#define src_ptvisitor_error_listener_class_hpp

// src/ptvisitor_error_listener_class_hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include <ANTLRErrorListener.h>
//#include "general_allocator_class.hpp"

namespace frost_hdl
{

class PTVisitorErrorListener : public antlr4::ANTLRErrorListener
{
private:		// variables
	Ident _filename;

public:		// functions
	PTVisitorErrorListener(const Ident& s_filename);
	virtual ~PTVisitorErrorListener();

	void syntaxError(antlr4::Recognizer *recognizer, 
		antlr4::Token *offendingSymbol, size_t line, 
		size_t charPositionInLine, const Ident &msg, 
		std::exception_ptr e);
	void reportAmbiguity(antlr4::Parser *recognizer, 
		const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex, 
		bool exact, const antlrcpp::BitSet &ambigAlts, 
		antlr4::atn::ATNConfigSet *configs);
	
	void reportAttemptingFullContext(antlr4::Parser *recognizer, 
		const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
		const antlrcpp::BitSet &conflictingAlts, 
		antlr4::atn::ATNConfigSet *configs);

	void reportContextSensitivity(antlr4::Parser *recognizer, 
		const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
		size_t prediction, antlr4::atn::ATNConfigSet *configs);
};

} // namespace frost_hdl

#endif		// src_ptvisitor_error_listener_class_hpp
