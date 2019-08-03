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
	friend Base;

	using TokSet = ast::NodeBase::TokSet;

	using TheMultiParse = Base::MultiParse<Parser>;
	using TheUnitParse = Base::UnitParse<Parser>;
	using TheSeqParse = Base::SeqParse<Parser>;
	using ParseRet = typename TheMultiParse::ParseRet;
	using ParseFunc = typename TheMultiParse::ParseFunc;

	using MapSeqParse = Base::MapSeqParse<TheSeqParse>;

private:		// variables
	ast::NodeBase::Child _ast_root;

	#define LIST_FOR_GEN_STACK(X) \
		X(BigNum, const BigNum&, num) \
		X(Tok, Tok, tok) \
		X(string, string, str) \

	#include "gen_stacks_stuff.hpp"
	#undef LIST_FOR_GEN_STACK

	std::stack<ast::NodeBase::Child> _ast_child_stack;

	inline void _push_ast_child(ast::NodeBase::Child&& to_push)
	{
		_ast_child_stack.push(std::move(to_push));
	}
	template<typename ChildType>
	inline void _push_ast_child(ChildType&& to_push)
	{
		_push_ast_child(ast::NodeBase::Child(new ChildType(std::move
			(to_push))));
	}
	template<typename ChildType>
	inline auto _to_ast_child(ChildType&& to_convert)
	{
		return ast::NodeBase::Child(new ChildType(std::move(to_convert)));
	}
	inline auto _pop_ast_child()
	{
		auto&& ret = _ast_child_stack.top();
		_ast_child_stack.pop();
		return std::move(ret);
	}

	inline void _push_num(const BigNum& to_push)
	{
		_stacks.push_num(to_push);
	}
	inline auto _get_top_num()
	{
		return _stacks.get_top_num();
	}
	inline auto _pop_num()
	{
		return _stacks.pop_num();
	}

	inline void _push_tok(Tok to_push)
	{
		_stacks.push_tok(to_push);
	}
	inline auto _get_top_tok()
	{
		return _stacks.get_top_tok();
	}
	inline auto _pop_tok()
	{
		return _stacks.pop_tok();
	}

	inline void _push_str(const string& to_push)
	{
		_stacks.push_str(to_push);
	}
	inline auto _get_top_str()
	{
		return _stacks.get_top_str();
	}
	inline auto _pop_str()
	{
		return _stacks.pop_str();
	}


public:		// functions
	Parser(vector<string>&& s_filename_vec);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Parser)
	~Parser();

	GEN_GETTER_BY_CON_REF(ast_root)

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

public:		// functions
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
private:		// functions
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



public:		// functions
	bool parse_program();

private:		// functions
	bool _parse_kw_if();
	bool _parse_kw_else();
	bool _parse_kw_for();
	bool _parse_kw_generate();
	bool _parse_kw_package();
	bool _parse_kw_port();
	bool _parse_kw_proc();
	bool _parse_kw_func();
	bool _parse_kw_task();
	bool _parse_kw_module();
	bool _parse_kw_const();
	bool _parse_kw_range();
	bool _parse_kw_cat();
	bool _parse_kw_repl();
	bool _parse_kw_using();
	bool _parse_kw_while();
	bool _parse_kw_switch();
	bool _parse_kw_switchz();
	bool _parse_kw_case();
	bool _parse_kw_default();
	bool _parse_kw_return();
	bool _parse_kw_packed();
	bool _parse_kw_class();
	bool _parse_kw_virtual();
	bool _parse_kw_extends();
	bool _parse_kw_public();
	bool _parse_kw_protected();
	bool _parse_kw_private();
	bool _parse_kw_enum();
	bool _parse_kw_union();
	bool _parse_kw_assign();
	bool _parse_kw_initial();
	bool _parse_kw_always_comb();
	bool _parse_kw_always_blk();
	bool _parse_kw_always_ff();
	bool _parse_kw_posedge();
	bool _parse_kw_negedge();
	bool _parse_kw_inst();
	bool _parse_kw_input();
	bool _parse_kw_output();
	bool _parse_kw_bidir();
	bool _parse_kw_type();
	bool _parse_kw_uwire();
	bool _parse_kw_swire();
	bool _parse_kw_ubit();
	bool _parse_kw_sbit();
	bool _parse_kw_void();
	bool _parse_kw_auto();
	bool _parse_kw_ubyte();
	bool _parse_kw_sbyte();
	bool _parse_kw_ushortint();
	bool _parse_kw_sshortint();
	bool _parse_kw_uint();
	bool _parse_kw_sint();
	bool _parse_kw_ulongint();
	bool _parse_kw_slongint();
	bool _parse_kw_typeof();

	bool _parse_punct_lparen();
	bool _parse_punct_rparen();
	bool _parse_punct_lbracket();
	bool _parse_punct_rbracket();
	bool _parse_punct_lbrace();
	bool _parse_punct_rbrace();
	bool _parse_punct_comma();
	bool _parse_punct_semicolon();
	bool _parse_punct_colon();
	bool _parse_punct_apostrophe();
	bool _parse_punct_assign();
	bool _parse_punct_member_access();
	bool _parse_punct_scope_access();
	bool _parse_punct_param_pack();

	bool _parse_header_if();
	bool _parse_header_else_if();
	bool _parse_header_else();
	bool _parse_header_for();

	bool _parse_header_generate_if();
	bool _parse_header_else_generate_if();
	bool _parse_header_else_generate();
	bool _parse_header_generate_for();

	bool _parse_package();
	bool _parse_scope_package();

	bool _parse_generate_package();
	bool _parse_generate_package_if();
	bool _parse_generate_package_for();

	bool _parse_member_callable_prefix();

	bool _parse_contents_modproc();
	bool _parse_proc();
	bool _parse_module();

	bool _parse_scope_modproc();
	bool _parse_generate_modproc();
	bool _parse_generate_modproc_if();
	bool _parse_generate_modproc_for();

	bool _parse_decl_callable();
	bool _parse_contents_func_task();
	bool _parse_func();
	bool _parse_task();

	bool _parse_scope_behav();
	bool _parse_inner_scope_behav();

	bool _parse_generate_behav();
	bool _parse_generate_behav_if();
	bool _parse_generate_behav_for();

	bool _parse_const();
	bool _parse_one_const();
	bool _parse_var();
	bool _parse_one_var();
	bool _parse_using();

	bool _parse_stmt_assign();
	bool _parse_stmt_if();
	bool _parse_stmt_for();
	bool _parse_stmt_while();
	bool _parse_stmt_switch();
	bool _parse_stmt_switchz();
	bool _parse_scope_switch();
	bool _parse_stmt_case();
	bool _parse_stmt_default();
	bool _parse_stmt_return();

	bool _parse_decl_cstm_type();
	bool _parse_class();
	bool _parse_extends();

	bool _parse_scope_class();
	bool _parse_member_callable();
	bool _parse_generate_class();
	bool _parse_generate_class_if();
	bool _parse_generate_class_for();
	bool _parse_member_access_label();

	bool _parse_enum();
	bool _parse_union();

	bool _parse_hardware_block();
	bool _parse_cont_assign();
	bool _parse_initial();
	bool _parse_always_comb();
	bool _parse_always_blk();
	bool _parse_always_ff();
	bool _parse_edge_list();
	bool _parse_posedge_inst();
	bool _parse_negedge_inst();

	bool _parse_inst();

	bool _parse_param_list();
	bool _parse_param_sublist();
	bool _parse_arg_list();
	bool _parse_arg_sublist();
	bool _parse_arg_port_sublist();
	bool _parse_pararg_var_sublist();
	bool _parse_pararg_type_sublist();
	bool _parse_param_module_sublist();
	bool _parse_pararg_ident_equals_typename_sublist();
	bool _parse_param_inst_list();
	bool _parse_arg_inst_list();

	bool _parse_pos_pararg_inst_list();
	bool _parse_named_pararg_inst_list();

	bool _parse_typename();
	bool _parse_param_possible_typename();
	bool _parse_no_param_possible_typename();
	bool _parse_typeof();
	bool _parse_type_range();
	bool _parse_range_suffix();

	bool _parse_expr();
	bool _parse_inner_expr();
	bool _parse_op_logical();

	bool _parse_expr_logical();
	bool _parse_inner_expr_logical();
	bool _parse_op_compare();

	bool _parse_expr_compare();
	bool _parse_inner_expr_compare();
	bool _parse_op_plus_minus();

	bool _parse_expr_add_sub();
	bool _parse_inner_expr_add_sub();
	bool _parse_op_mul_div_mod_etc();

	bool _parse_expr_mul_div_mod_etc();
	bool _parse_inner_expr_mul_div_mod_etc();
	bool _parse_op_unary();

	bool _parse_dollar_global_clock();
	bool _parse_dollar_pow_expr();
	bool _parse_num_expr();
	bool _parse_raw_num();
	bool _parse_const_str();

	bool _parse_expr_pre_dollar_func_of_one();
	bool _parse_expr_post_dollar_func_of_one();
	bool _parse_dollar_func_of_one();
	bool _parse_expr_cat();
	bool _parse_expr_repl();

	bool _parse_ident_etc();
	bool _parse_ident_member_access();
	bool _parse_ident_scope_access();
	bool _parse_ident_non_member_scope_access();
	bool _parse_ident_call();
	bool _parse_ident_no_param_overloaded_call();
	bool _parse_ident_param_member_overloaded_call();
	bool _parse_ident_terminal();
	bool _parse_ident();

	//bool _parse_generate_any_if(ParseFunc parse_scope_func);
	//bool _parse_generate_any_for(ParseFunc parse_scope_func);
	template<typename FirstArgType, typename... RemArgTypes>
	inline void _append_msp(MapSeqParse& map_seq_parse,
		const string& first_key, FirstArgType&& first_seq,
		RemArgTypes&&... rem_args)
	{
		TheMultiParse::_append_msp(map_seq_parse, first_key, first_seq,
			rem_args...);
	}

	inline auto _unit_parse(const string& s_parse_func_str,
		ParseFunc s_parse_func, bool s_optional=false)
	{
		return TheMultiParse::_unit_parse(this, s_parse_func_str,
			s_parse_func, s_optional);
	}
	template<typename FirstArgType, typename... RemArgTypes>
	inline auto _opt_seq_parse(const FirstArgType& first_arg,
		RemArgTypes&&... rem_args)
	{
		return TheMultiParse::_opt_seq_parse(this, first_arg, rem_args...);
	}
	template<typename FirstArgType, typename... RemArgTypes>
	inline auto _req_seq_parse(const FirstArgType& first_arg,
		RemArgTypes&&... rem_args)
	{
		return TheMultiParse::_req_seq_parse(this, first_arg, rem_args...);
	}
	template<typename FirstArgType, typename... RemArgTypes>
	inline auto _opt_or_parse(const FirstArgType& first_arg,
		RemArgTypes&&... rem_args)
	{
		return TheMultiParse::_opt_or_parse(this, first_arg, rem_args...);
	}
	template<typename FirstArgType, typename... RemArgTypes>
	inline auto _req_or_parse(const FirstArgType& first_arg,
		RemArgTypes&&... rem_args)
	{
		return TheMultiParse::_req_or_parse(this, first_arg, rem_args...);
	}
	template<typename FirstArgType, typename... RemArgTypes>
	inline auto _opt_list_parse(const FirstArgType& first_arg,
		RemArgTypes&&... rem_args)
	{
		return TheMultiParse::_opt_list_parse(this, first_arg,
			rem_args...);
	}
	template<typename FirstArgType, typename... RemArgTypes>
	inline auto _req_list_parse(const FirstArgType& first_arg,
		RemArgTypes&&... rem_args)
	{
		return TheMultiParse::_req_list_parse(this, first_arg,
			rem_args...);
	}

	inline SrcCodeChunk _ls_src_code_chunk(const ParseRet& lex_state) const
	{
		return _lexer().src_code_chunk(lex_state.get());
	}

	inline bool _one_opt_parse(const TheSeqParse& parse_seq,
		const string& exec_str, const string& no_exec_str)
	{
		if (parse_seq.check())
		{
			parse_seq.exec();
			_push_str(exec_str);
			return true;
		}
		else
		{
			_push_str(no_exec_str);
			return false;
		}
	}
	inline void _push_one_opt_parse(const TheSeqParse& parse_seq)
	{
		//printout("_one_opt_parse():  ", parse_seq.check(), "\n");
		if (parse_seq.check())
		{
			parse_seq.exec();
			_push_num(true);
		}
		else
		{
			_push_num(false);
		}
	}

	inline ast::NodeBase::Child _get_one_opt_parse
		(const TheSeqParse& parse_seq)
	{
		if (parse_seq.check())
		{
			parse_seq.exec();
			return _pop_ast_child();
		}
		return ast::NodeBase::Child();
	}
	inline ast::NodeBase::Child _get_ast_child_if_pop_num()
	{
		if (_pop_num())
		{
			return _pop_ast_child();
		}
		return ast::NodeBase::Child();
	}

	bool _parse_generate_any_if(const string& parse_scope_func_str,
		ParseFunc parse_scope_func);
	bool _parse_generate_any_for(const string& parse_scope_func_str,
		ParseFunc parse_scope_func);


	template<typename AstNodeScopeType>
	bool _parse_any_scope(const string& scope_type_str,
		const TheSeqParse& list_seq);

	// pop after exec()
	inline ast::NodeBase::Child _pexec(const TheSeqParse& seq)
	{
		seq.exec();
		return _pop_ast_child();
	}

	inline bool _list_pexec(ast::NodeList& list,
		const TheSeqParse& list_seq)
	{
		if (!list_seq.check())
		{
			return false;
		}

		while (list_seq.check())
		{
			list.append(_pexec(list_seq));
		}

		return true;
	}

	template<typename FirstArgType, typename... RemArgTypes>
	inline bool _check_or_tok(const LexerState& vec_front,
		FirstArgType&& first_tok, RemArgTypes&&... rem_tokens) const
	{
		if (vec_front.tok() == first_tok)
		{
			return true;
		}
		else if constexpr (sizeof...(rem_tokens) > 0)
		{
			return _check_or_tok(vec_front, rem_tokens...);
		}
		else
		{
			return false;
		}
	}

	void _finish_parse_expr_any_dollar_func_of_one
		(const SrcCodeChunk& s_src_code_chunk);

};

} // namespace frost_hdl


#endif		// src_parser_class_hpp
