#ifndef src_lexer_class_hpp
#define src_lexer_class_hpp

// src/lexer_class.hpp

#include "misc_includes.hpp"
#include "tok_enum.hpp"

namespace frost_hdl
{

class Lexer final
{
private:		// variables
	string* _text = nullptr;
	Tok _tok = Tok::Comment;
	string _s;
	int _c;
	BigNum _n;
	size_t _x = 0, _line_num = 1, _pos_in_line = 0;

public:		// functions
	Lexer(string* s_text);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Lexer)
	~Lexer();

	Tok next_tok();


	GEN_GETTER_BY_VAL(text)
	GEN_GETTER_BY_VAL(tok)
	GEN_GETTER_BY_CON_REF(s)
	GEN_GETTER_BY_VAL(c)
	GEN_GETTER_BY_CON_REF(n)
	GEN_GETTER_BY_VAL(x)
	GEN_GETTER_BY_VAL(line_num)
	GEN_GETTER_BY_VAL(pos_in_line)

private:		// functions
	void _set_tok(Tok n_tok, bool perf_next_char);
	int _next_char(); 
	void _eat_whitespace();
	void _inner_next_tok();

	template<typename... RemArgTypes>
	bool _set_kw_tok(Tok n_tok, const string& to_check,
		RemArgTypes&&...  rem_args)
	{
		if (s() == to_check)
		{
			_set_tok(n_tok, false);
			return true;
		}
		else if constexpr (sizeof...(rem_args) > 0)
		{
			return _set_kw_tok(rem_args...);
		}
		return false;
	}
};

} // namespace frost_hdl


#endif		// src_lexer_class_hpp
