#ifndef src_lexer_class_hpp
#define src_lexer_class_hpp

// src/lexer_class.hpp

#include "misc_includes.hpp"
#include "tok_enum.hpp"
#include "src_code_chunk_class.hpp"
#include "lexer_base_class.hpp"

namespace frost_hdl
{

class Lexer final : public LexerBase<Tok>
{
public:		// functions
	Lexer(const string& s_filename, string* s_text);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Lexer)
	~Lexer();

	Tok next_tok(bool just_test);
	inline auto src_code_chunk(State* state=nullptr) const
	{
		return LexerBase<Tok>::src_code_chunk<SrcCodeChunk>(state);
	}

private:		// functions
	void _inner_next_tok();
};

} // namespace frost_hdl


#endif		// src_lexer_class_hpp
