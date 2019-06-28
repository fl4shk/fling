#ifndef src_lexer_base_class_hpp
#define src_lexer_base_class_hpp

// src/lexer_base_class.hpp

#include "misc_includes.hpp"
#include "src_code_chunk_class.hpp"

namespace frost_hdl
{

template<typename _TokType>
class LexerBase
{
public:		// types
	using TokType = _TokType;

	class State
	{
	public:		// variables
		TokType tok;
		string s;
		int c;
		BigNum n;
		size_t x = 0, line_num = 1, pos_in_line = 0;

	public:		// functions
		State()
		{
		}
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(State)
		~State()
		{
		}
	};

protected:		// variables
	string _filename;
	string* _text = nullptr;
	State _state;

public:		// functions
	inline LexerBase(const string& s_filename, string* s_text,
		TokType done_tok, TokType comment_tok)
		: _filename(s_filename), _text(s_text)
	{
		_next_tok_no_test(done_tok, comment_tok);
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(LexerBase)
	virtual ~LexerBase()
	{
	}


	inline auto src_code_chunk() const
	{
		return SrcCodeChunk(filename(), "", line_num(), pos_in_line());
	}

	inline decltype(_state.tok) tok() const
	{
		return _state.tok;
	}
	inline const decltype(_state.s)& s() const
	{
		return _state.s;
	}
	inline decltype(_state.c) c() const
	{
		return _state.c;
	}
	inline const decltype(_state.n) n() const
	{
		return _state.n;
	}
	inline decltype(_state.x) x() const
	{
		return _state.x;
	}
	inline decltype(_state.line_num) line_num() const
	{
		return _state.line_num;
	}
	inline decltype(_state.pos_in_line) pos_in_line() const
	{
		return _state.pos_in_line;
	}
	GEN_GETTER_BY_CON_REF(filename)
	GEN_GETTER_BY_VAL(text)
	GEN_GETTER_BY_CON_REF(state)

protected:		// functions
	TokType _next_tok_no_test(TokType done_tok, TokType comment_tok)
	{
		do
		{
			_eat_whitespace();

			if (c() == EOF)
			{
				_set_tok(done_tok, false);
			}
			else
			{
				_inner_next_tok();
			}
		} while (tok() == comment_tok);

		return tok();
	}
	int _next_char()
	{
		if (x() < text()->size())
		{
			_state.c = text()->at(_state.x++);

			++_state.pos_in_line;

			if (c() == '\n')
			{
				++_state.line_num;
				_state.pos_in_line = 1;
			}

			return c();
		}
		else
		{
			return EOF;
		}
	}
	void _eat_whitespace()
	{
		while (isspace(c()))
		{
			_next_char();
		}
	}
	void _set_tok(TokType n_tok, bool perf_next_char)
	{
		_state.tok = n_tok;

		if (perf_next_char)
		{
			_next_char();
		}
	}

	virtual void _inner_next_tok() = 0;

	inline bool _set_kw_tok
		(const std::map<TokType, string>& some_tok_ident_map)
	{
		for (const auto& iter : some_tok_ident_map)
		{
			if (s() == iter.second)
			{
				_set_tok(iter.first, false);
				return true;
			}
		}
		return false;
	}
};

} // namespace frost_hdl


#endif		// src_lexer_base_class_hpp
