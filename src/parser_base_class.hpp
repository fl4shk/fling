#ifndef src_parser_base_class_hpp
#define src_parser_base_class_hpp

// src/parser_base_class.hpp

#include "misc_includes.hpp"
#include "lexer_base_class.hpp"

namespace frost_hdl
{

template<typename LexerType>
class ParserBase
{
public:		// types
	using TokType = typename LexerType::TokType;
	using LexerState = typename LexerType::State;
	using TokToStringMap = std::map<TokType, string>;

protected:		// variables
	bool _just_test = false;
	size_t _curr_file_index = 0;
	std::vector<string> _filename_vec;
	std::vector<string*> _text_vec;
	std::vector<LexerType> _lexer_vec;
public:		// functions
	ParserBase(std::vector<string>&& s_filename_vec)
		: _filename_vec(std::move(s_filename_vec))
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ParserBase)
	virtual ~ParserBase()
	{
	}

	inline auto lex_tok() const
	{
		return _lexer().tok();
	}
	inline const auto& lex_s() const
	{
		return _lexer().s();
	}
	inline auto lex_src_code_chunk() const
	{
		return _lexer().src_code_chunk();
	}
	inline bool cmp_lex_tok(TokType tok) const
	{
		return (lex_tok() == tok);
	}

	GEN_GETTER_BY_VAL(curr_file_index)
	GEN_GETTER_BY_VAL(just_test)

protected:		// functions
	const LexerType& _lexer() const
	{
		return _lexer_vec.at(curr_file_index());
	}
	LexerType& _lexer()
	{
		return _lexer_vec.at(curr_file_index());
	}

	const std::vector<LexerState> _next_n_tokens(bool affect_lexer,
		size_t n)
	{
		std::vector<LexerState> ret;

		LexerType temp_lexer(_lexer());

		auto* lexer = (!affect_lexer) ? &_lexer() : &temp_lexer;

		for (size_t i=0; i<n; ++i)
		{
			ret.push_back(lexer->state());
			_next_tok(lexer);
		}

		return ret;
	}

	inline auto _next_tok(LexerType* lexer=nullptr)
	{
		if (lexer == nullptr)
		{
			return _lexer().next_tok(just_test());
		}
		else // if (lexer != nullptr)
		{
			return lexer->next_tok(just_test());
		}
	}

	template<typename FirstFuncType, typename... RemFuncTypes>
	bool _do_parse(FirstFuncType&& first_func, RemFuncTypes&&... rem_funcs)
	{
		_just_test = false;
		if (std::mem_fn(first_func)(*this))
		{
			_just_test = true;
			std::mem_fn(first_func)(*this);

			return true;
		}
		else if constexpr (sizeof...(rem_funcs) != 0)
		{
			return _do_parse(rem_funcs...);
		}

		return false;
	}

	//inline void _syntax_error(const string& msg) const
	//{
	//	lex_src_code_chunk().syntax_error(msg);
	//}
	template<typename... ArgTypes>
	inline void _err(ArgTypes&&... args) const
	{
		lex_src_code_chunk().err(sconcat(args...));
	}
	template<typename... ArgTypes>
	inline void _warn(ArgTypes&&... args) const
	{
		lex_src_code_chunk().warn(sconcat(args...));
	}

	string _msg_for_expect(TokType tok,
		const TokToStringMap& some_tok_ident_map) const
	{
		return sconcat("Expected token ", some_tok_ident_map.at(tok),
			".  Have token ", some_tok_ident_map.at(lex_tok()),
			" and string ", lex_s());
	}
	void _expect(TokType tok, const TokToStringMap& some_tok_ident_map)
	{
		if (!cmp_lex_tok(tok))
		{
			_err(_msg_for_expect(tok, some_tok_ident_map));
		}
		_next_tok();
	}
	void _unexpected(const TokToStringMap& some_tok_ident_map)
	{
		_err("Unexpected token ", some_tok_ident_map.at(lex_tok()),
			".  Have string ", lex_s());
	}
	bool _to_next_in_list(TokType end, TokType separator,
		const TokToStringMap& some_tok_ident_map)
	{
		if (cmp_lex_tok(end))
		{
			_next_tok();
			return false;
		}
		else if (cmp_lex_tok(separator))
		{
			_next_tok();
			return true;
		}
		else
		{
			_unexpected(some_tok_ident_map);
		}
	}
};

} // namespace frost_hdl


#endif		// src_parser_base_class_hpp
