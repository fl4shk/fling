#ifndef src_lexer_class_hpp
#define src_lexer_class_hpp

// src/lexer_class.hpp

#include "misc_includes.hpp"
#include "tok_enum.hpp"
#include "src_code_chunk_class.hpp"

namespace frost_hdl
{

class Lexer final : public LexerBase<Tok>
{
public:		// types
	using TwoStates = typename LexerBase<Tok>::TwoStates;
public:		// functions
	Lexer(const string& s_filename, string* s_text);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Lexer)
	~Lexer();

	void next_tok();
	inline auto src_code_chunk(const TwoStates* two_states=nullptr) const
	{
		return LexerBase<Tok>::src_code_chunk<SrcCodeChunk>(two_states);
	}

private:		// functions
	void _inner_next_tok();
};

} // namespace frost_hdl


#endif		// src_lexer_class_hpp
