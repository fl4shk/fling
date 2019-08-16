#ifndef src_opt_as_func_arg_parser_base_class_hpp
#define src_opt_as_func_arg_parser_base_class_hpp

// src/opt_as_func_arg_parser_base_class.hpp

#include "misc_includes.hpp"

namespace frost_hdl
{

template<typename LexerType>
class OptAsFuncArgParserBase
{
public:		// types
	enum class Opt
	{
		ParseAsFarAsPossible,
		JustParse,
		Exec,
	};

	using TwoStates = typename LexerType::TwoStates;

	class ParseRet final
	{
	private:		// variables
		bool _valid = true;
		vector<TwoStates> _lex_two_states_vec;
		set<Tok> _tok_set;
	public:		// functions
		inline ParseRet() = default;
		inline ParseRet(const ParseRet& to_copy) = default;
		inline ParseRet(ParseRet&& to_move) = default;
		inline ~ParseRet() = default;
		inline ParseRet& operator = (const ParseRet& to_copy) = default;
		inline ParseRet& operator = (ParseRet&& to_move) = default;

		inline void append_lex_two_states(const TwoStates& to_append)
		{
			_lex_two_states_vec.push_back(to_append);
		}
		inline void append_tok(Tok tok)
		{
			_tok_set.insert(tok);
		}
		inline void append_tok_set(const set<Tok>& to_append_set)
		{
			for (const auto& iter : to_append_set)
			{
				_tok_set.insert(iter);
			}
		}
		inline void append_parse_ret(const ParseRet& to_append)
		{
			if (!to_append.valid())
			{
				_valid = false;
			}
			for (const auto& iter : to_append.lex_two_states_vec())
			{
				_lex_two_states_vec.push_back(iter);
			}
			for (const auto& iter : to_append.tok_set())
			{
				_tok_set.insert(iter);
			}
		}

		GEN_GETTER_AND_SETTER_BY_VAL(valid)
		GEN_GETTER_BY_CON_REF(lex_two_states_vec)
		GEN_GETTER_BY_CON_REF(tok_set)
	};

	template<typename DerivedType>
	class UnitParse
	{
	public:		// types
	};
protected:		// variables
	LexerType _lexer;

public:		// functions
protected:		// functions
};

} // namespace frost_hdl


#endif		// src_opt_as_func_arg_parser_base_class_hpp
