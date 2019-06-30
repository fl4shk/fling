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

private:		// variables
	unique_ptr<ast::NodeBase> _ast;

public:		// functions
	Parser(std::vector<string>&& s_filename_vec);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Parser)
	~Parser();

private:		// functions
	inline std::string _msg_for_expect(TokType tok,
		const LexerState& lex_state) const
	{
		return Base::_msg_for_expect(tok, tok_ident_map, lex_state);
	}
	inline void _expect(TokType tok, const LexerState& lex_state)
	{
		Base::_expect(tok, tok_ident_map, lex_state);
	}
	inline void _unexpected(const LexerState& lex_state)
	{
		Base::_unexpected(tok_ident_map, lex_state);
	}
	inline void _unexpected(Lexer* lexer)
	{
		Base::_unexpected(tok_ident_map, lexer);
	}
	inline bool _to_next_in_list(TokType end, TokType separator=Tok::Comma)
	{
		return Base::_to_next_in_list(end, separator, tok_ident_map);
	}
	inline void _next_lss_tokens()
	{
		Base::_next_lss_tokens(tok_ident_map);
	}
	template<typename AstNodeType>
	bool _check_prefixed_tok_seq()
	{
		return Base::_check_prefixed_tok_seq(AstNodeType::tok_prefix_set,
			AstNodeType::end_tok);
	}

	bool _parse_decl_package();
	bool _parse_decl_module();
	bool _parse_decl_enum();
	bool _parse_decl_class();
	bool _parse_decl_union();
	bool _parse_generate();

	bool _parse_member_access_label();

	bool _parse_decl_member_func();
	bool _parse_decl_func();
	bool _parse_decl_member_task();
	bool _parse_decl_task();

	bool _parse_module_prolog();
	bool _parse_list_param();
	bool _parse_list_port();

	bool _parse_expr();
};

} // namespace frost_hdl


#endif		// src_parser_class_hpp
