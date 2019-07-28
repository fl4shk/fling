#ifndef src_parser_class_hpp
#define src_parser_class_hpp

// src/parser_class.hpp

#include "misc_includes.hpp"
#include "lexer_class.hpp"
#include "err_warn_base_class.hpp"
#include "ast_node_classes.hpp"
#include "parser_base_class.hpp"

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
	ParseRet parse_program();

private:		// functions
	ParseRet _parse_kw_if();
	ParseRet _parse_kw_else();
	ParseRet _parse_kw_for();
	ParseRet _parse_kw_generate();
	ParseRet _parse_kw_package();
	ParseRet _parse_kw_port();
	ParseRet _parse_kw_proc();
	ParseRet _parse_kw_func();
	ParseRet _parse_kw_task();
	ParseRet _parse_kw_module();
	ParseRet _parse_kw_const();
	ParseRet _parse_kw_range();
	ParseRet _parse_kw_cat();
	ParseRet _parse_kw_repl();
	ParseRet _parse_kw_using();
	ParseRet _parse_kw_while();
	ParseRet _parse_kw_switch();
	ParseRet _parse_kw_switchz();
	ParseRet _parse_kw_case();
	ParseRet _parse_kw_default();
	ParseRet _parse_kw_return();
	ParseRet _parse_kw_packed();
	ParseRet _parse_kw_class();
	ParseRet _parse_kw_virtual();
	ParseRet _parse_kw_extends();
	ParseRet _parse_kw_public();
	ParseRet _parse_kw_protected();
	ParseRet _parse_kw_private();
	ParseRet _parse_kw_enum();
	ParseRet _parse_kw_union();
	ParseRet _parse_kw_assign();
	ParseRet _parse_kw_initial();
	ParseRet _parse_kw_always_comb();
	ParseRet _parse_kw_always_blk();
	ParseRet _parse_kw_always_ff();
	ParseRet _parse_kw_posedge();
	ParseRet _parse_kw_negedge();
	ParseRet _parse_kw_inst();
	ParseRet _parse_kw_input();
	ParseRet _parse_kw_output();
	ParseRet _parse_kw_bidir();
	ParseRet _parse_kw_type();
	ParseRet _parse_kw_uwire();
	ParseRet _parse_kw_swire();
	ParseRet _parse_kw_ubit();
	ParseRet _parse_kw_sbit();
	ParseRet _parse_kw_void();
	ParseRet _parse_kw_auto();
	ParseRet _parse_kw_ubyte();
	ParseRet _parse_kw_sbyte();
	ParseRet _parse_kw_ushortint();
	ParseRet _parse_kw_sshortint();
	ParseRet _parse_kw_uint();
	ParseRet _parse_kw_sint();
	ParseRet _parse_kw_ulongint();
	ParseRet _parse_kw_slongint();
	ParseRet _parse_kw_typeof();

	ParseRet _parse_punct_lparen();
	ParseRet _parse_punct_rparen();
	ParseRet _parse_punct_lbracket();
	ParseRet _parse_punct_rbracket();
	ParseRet _parse_punct_lbrace();
	ParseRet _parse_punct_rbrace();
	ParseRet _parse_punct_comma();
	ParseRet _parse_punct_semicolon();
	ParseRet _parse_punct_colon();
	ParseRet _parse_punct_apostrophe();
	ParseRet _parse_punct_assign();
	ParseRet _parse_punct_member_access();
	ParseRet _parse_punct_scope_access();

	ParseRet _parse_header_if();
	ParseRet _parse_header_else_if();
	ParseRet _parse_header_else();
	ParseRet _parse_header_for();

	ParseRet _parse_header_generate_if();
	ParseRet _parse_header_else_generate_if();
	ParseRet _parse_header_else_generate();
	ParseRet _parse_header_generate_for();

	ParseRet _parse_package();
	ParseRet _parse_scope_package();

	ParseRet _parse_generate_package();
	ParseRet _parse_generate_package_if();
	ParseRet _parse_generate_package_for();

	ParseRet _parse_member_callable_prefix();

	ParseRet _parse_contents_modproc();
	ParseRet _parse_proc();
	ParseRet _parse_module();

	ParseRet _parse_scope_modproc();
	ParseRet _parse_generate_modproc();
	ParseRet _parse_generate_modproc_if();
	ParseRet _parse_generate_modproc_for();

	ParseRet _parse_decl_callable();
	ParseRet _parse_contents_func_task();
	ParseRet _parse_func();
	ParseRet _parse_task();

	ParseRet _parse_scope_behav();
	ParseRet _parse_inner_scope_behav();

	ParseRet _parse_generate_behav();
	ParseRet _parse_generate_behav_if();
	ParseRet _parse_generate_behav_for();

	ParseRet _parse_const();
	ParseRet _parse_one_const();
	ParseRet _parse_var();
	ParseRet _parse_one_var();
	ParseRet _parse_using();

	ParseRet _parse_stmt_assign();
	ParseRet _parse_stmt_if();
	ParseRet _parse_stmt_for();
	ParseRet _parse_stmt_while();
	ParseRet _parse_stmt_switch();
	ParseRet _parse_stmt_switchz();
	ParseRet _parse_scope_switch();
	ParseRet _parse_stmt_case();
	ParseRet _parse_stmt_default();
	ParseRet _parse_stmt_return();

	ParseRet _parse_decl_cstm_type();
	ParseRet _parse_class();
	ParseRet _parse_extends();

	ParseRet _parse_scope_class();
	ParseRet _parse_member_callable();
	ParseRet _parse_generate_class();
	ParseRet _parse_generate_class_if();
	ParseRet _parse_generate_class_for();
	ParseRet _parse_member_access_label();

	ParseRet _parse_enum();
	ParseRet _parse_union();

	ParseRet _parse_hardware_block();
	ParseRet _parse_cont_assign();
	ParseRet _parse_initial();
	ParseRet _parse_always_comb();
	ParseRet _parse_always_blk();
	ParseRet _parse_always_ff();
	ParseRet _parse_edge_list();
	ParseRet _parse_posedge_inst();
	ParseRet _parse_negedge_inst();

	ParseRet _parse_inst();

	ParseRet _parse_param_list();
	ParseRet _parse_param_sublist();
	ParseRet _parse_arg_list();
	ParseRet _parse_arg_sublist();
	ParseRet _parse_arg_port_sublist();
	ParseRet _parse_pararg_var_sublist();
	ParseRet _parse_pararg_type_sublist();
	ParseRet _parse_param_module_sublist();
	ParseRet _parse_pararg_ident_equals_typename_sublist();
	ParseRet _parse_param_inst_list();
	ParseRet _parse_arg_inst_list();

	ParseRet _parse_pos_pararg_inst_list();
	ParseRet _parse_named_pararg_inst_list();

	ParseRet _parse_typename();
	ParseRet _parse_param_possible_typename();
	ParseRet _parse_no_param_possible_typename();
	ParseRet _parse_typeof();
	ParseRet _parse_type_range();
	ParseRet _parse_range_suffix();

	ParseRet _parse_expr();
	ParseRet _parse_inner_expr();
	ParseRet _parse_op_logical();

	ParseRet _parse_expr_logical();
	ParseRet _parse_inner_expr_logical();
	ParseRet _parse_op_compare();

	ParseRet _parse_expr_compare();
	ParseRet _parse_inner_expr_compare();
	ParseRet _parse_op_plus_minus();

	ParseRet _parse_expr_add_sub();
	ParseRet _parse_inner_expr_add_sub();
	ParseRet _parse_op_mul_div_mod_etc();

	ParseRet _parse_expr_mul_div_mod_etc();
	ParseRet _parse_inner_expr_mul_div_mod_etc();
	ParseRet _parse_op_unary();

	ParseRet _parse_dollar_global_clock();
	ParseRet _parse_dollar_pow_expr();
	ParseRet _parse_num_expr();
	ParseRet _parse_raw_num();
	ParseRet _parse_const_str();

	ParseRet _parse_expr_pre_dollar_func_of_one();
	ParseRet _parse_expr_post_dollar_func_of_one();
	ParseRet _parse_dollar_func_of_one();
	ParseRet _parse_expr_cat();
	ParseRet _parse_expr_repl();

	ParseRet _parse_ident_etc();
	ParseRet _parse_ident_member_access();
	ParseRet _parse_ident_scope_access();
	ParseRet _parse_ident_non_member_scope_access();
	ParseRet _parse_ident_call();
	ParseRet _parse_ident_no_param_overloaded_call();
	ParseRet _parse_ident_param_member_overloaded_call();
	ParseRet _parse_ident_terminal();
	ParseRet _parse_ident();

	//bool _parse_generate_any_if(ParseFunc parse_scope_func);
	//bool _parse_generate_any_for(ParseFunc parse_scope_func);
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

	ParseRet _parse_generate_any_if(const string& parse_scope_func_str,
		ParseFunc parse_scope_func);
	ParseRet _parse_generate_any_for(const string& parse_scope_func_str,
		ParseFunc parse_scope_func);


	template<typename AstNodeScopeType>
	ParseRet _parse_any_scope(const string& scope_type_str,
		const TheSeqParse& list_seq);

	// pop after exec()
	inline ast::NodeBase::Child _pexec(const TheSeqParse& seq)
	{
		seq.exec();
		return _pop_ast_child();
	}

	inline bool _list_pexec(NodeList& list, const TheSeqParse& list_seq)
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
