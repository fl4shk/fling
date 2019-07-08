#ifndef src_parser_class_hpp
#define src_parser_class_hpp

// src/parser_class.hpp

#include "misc_includes.hpp"
#include "lexer_class.hpp"
#include "err_warn_base_class.hpp"
#include "ast_node_classes.hpp"

namespace frost_hdl
{

class Parser final : public ParserBase<Lexer>
{
public:		// types
	using Base = ParserBase<Lexer>;
	using TokSet = ast::NodeBase::TokSet;

private:		// variables
	unique_ptr<ast::NodeBase> _ast;

public:		// functions
	Parser(std::vector<string>&& s_filename_vec);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Parser)
	~Parser();

private:		// functions
	inline std::string _msg_for_expect(Tok tok,
		const LexerState& lex_state) const
	{
		return Base::_msg_for_expect(tok, tok_ident_map, lex_state);
	}
	inline void _expect(Tok tok, const LexerState& lex_state)
	{
		Base::_expect(tok, tok_ident_map, lex_state);
	}
	inline void _expect(Tok tok)
	{
		_expect(tok, _lexer().state());
	}
	inline auto _wexpect(TokType tok, Lexer* lexer=nullptr)
	{
		return Base::_wexpect(tok, tok_ident_map, lexer);
	}
	inline void _unexpected(const LexerState& lex_state)
	{
		Base::_unexpected(tok_ident_map, lex_state);
	}
	inline void _unexpected()
	{
		_unexpected(_lexer().state());
	}
	inline void _unexpected(Lexer* lexer)
	{
		Base::_unexpected(tok_ident_map, lexer);
	}
	inline bool _to_next_in_list(Tok end, Tok separator=Tok::Comma)
	{
		return Base::_to_next_in_list(end, separator, tok_ident_map);
	}
	inline void _next_lss_tokens()
	{
		Base::_next_lss_tokens(tok_ident_map);
	}
	bool _check_prefixed_tok_seq(const TokSet& prefix_set, Tok end)
	{
		return Base::_check_prefixed_tok_seq(prefix_set, end);
	}
	bool _check_prefixed_tok_seq(Tok end)
	{
		return Base::_check_prefixed_tok_seq(TokSet(), end);
	}
	inline auto _lex_tok() const
	{
		return _lexer().tok();
	}
	inline void _next_tok()
	{
		_lexer().next_tok();
	}
	template<typename FirstFuncType, typename... RemFuncTypes>
	bool _opt_parse(FirstFuncType&& first_func,
		RemFuncTypes&&... rem_funcs)
	{
		return Base::_opt_parse(this, first_func, rem_funcs...);
	}
	template<typename FirstFuncType, typename... RemFuncTypes>
	void _req_parse(FirstFuncType&& first_func,
		RemFuncTypes&&... rem_funcs)
	{
		Base::_req_parse(this, first_func, rem_funcs...);
	}


	bool _parse_package();

	// Modules, classes, constants, functions, tasks, processes, and other
	// packages.
	bool _parse_package_scope();

	bool _parse_module();
	bool _parse_module_scope();
	bool _parse_enum();
	bool _parse_enum_scope();
	bool _parse_union();
	bool _parse_union_scope();

	bool _parse_class();
	bool _parse_extends();
	bool _parse_class_scope();
	bool _parse_using();

	bool _parse_proc();
	bool _parse_func();
	bool _parse_task();

	bool _parse_param_list();
	bool _parse_arg_list();
};

} // namespace frost_hdl


#endif		// src_parser_class_hpp
