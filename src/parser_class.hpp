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

	using MultiParse = Base::MultiParse<Parser>;
	using ParseFunc = typename MultiParse::ParseFunc;

private:		// variables
	ast::NodeBase::Child _ast_root;

	#define LIST_FOR_GEN_STACK(X) \
		X(BigNum, const BigNum&, num) \
		X(Tok, Tok, tok) \

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
	//inline auto _get_top_ast_child()
	//{
	//	return _ast_child_stack.top();
	//}
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


	template<typename FirstFuncType, typename... RemFuncTypes>
	auto _check_parse(FirstFuncType&& first_func,
		RemFuncTypes&&... rem_funcs)
	{
		return Base::_check_parse(this, first_func, rem_funcs...);
	}
	template<typename FuncType>
	static auto _check_parse(Parser* self,
		const std::vector<FuncType>& func_vec)
	{
		return Base::_check_parse(self, func_vec);
	}


	template<typename FirstFuncType, typename... RemFuncTypes>
	bool _opt_parse(FirstFuncType&& first_func,
		RemFuncTypes&&... rem_funcs)
	{
		return Base::_opt_parse(this, first_func, rem_funcs...);
	}
	template<typename FuncType>
	static bool _opt_parse(Parser* self,
		const std::vector<FuncType>& func_vec)
	{
		return Base::_opt_parse(self, func_vec);
	}


	template<typename FirstFuncType, typename... RemFuncTypes>
	void _req_parse(FirstFuncType&& first_func,
		RemFuncTypes&&... rem_funcs)
	{
		Base::_req_parse(this, first_func, rem_funcs...);
	}
	template<typename FuncType>
	static void _req_parse(Parser* self,
		const std::vector<FuncType>& func_vec)
	{
		Base::_req_parse(self, func_vec);
	}
	template<typename FirstFuncType, typename... RemFuncTypes>
	auto _get_req_parse(FirstFuncType&& first_func,
		RemFuncTypes&&... rem_funcs)
	{
		Base::_req_parse(this, first_func, rem_funcs...);
		return _pop_ast_child();
	}
	template<typename FuncType>
	static auto _get_req_parse(Parser* self,
		const std::vector<FuncType>& func_vec)
	{
		Base::_req_parse(self, func_vec);
		return self->_pop_ast_child();
	}


	template<typename FirstFuncType, typename... RemFuncTypes>
	void _req_parse_loop(FirstFuncType&& first_func,
		RemFuncTypes&&... rem_funcs)
	{
		Base::_req_parse_loop(this, first_func, rem_funcs...);
	}
	template<typename FuncType>
	static void _req_parse_loop(Parser* self,
		const std::vector<FuncType>& func_vec)
	{
		Base::_req_parse_loop(self, func_vec);
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
	bool _parse_kw_using();
	bool _parse_kw_while();
	bool _parse_kw_switch();
	bool _parse_kw_switchz();
	bool _parse_kw_case();
	bool _parse_kw_default();
	bool _parse_kw_packed();
	bool _parse_kw_class();
	bool _parse_kw_virtual();
	bool _parse_kw_extends();
	bool _parse_kw_public();
	bool _parse_kw_protected();
	bool _parse_kw_private();
	bool _parse_kw_enum();
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
	bool _parse_punct_assign();
	bool _parse_punct_member_access();
	bool _parse_punct_scope_access();

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

	bool _parse_callable_member_prefix();

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
	bool _parse_var();
	bool _parse_using();

	bool _parse_stmt_assign();
	bool _parse_stmt_if();
	bool _parse_stmt_for();
	bool _parse_stmt_while();
	bool _parse_stmt_switch();
	bool _parse_stmt_switchz();
	bool _parse_scope_switch();

	bool _parse_decl_cstm_type();
	bool _parse_class();
	bool _parse_extends();

	bool _parse_scope_class();
	bool _parse_generate_class();
	bool _parse_generate_class_if();
	bool _parse_generate_class_for();
	bool _parse_member_access_label();

	bool _parse_enum();

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
	bool _parse_ident_equals_typename_sublist();
	bool _parse_param_inst_list();

	bool _parse_pos_pararg_inst_list();
	bool _parse_named_pararg_inst_list();

	bool _parse_typename();
	bool _parse_param_possible_typename();
	bool _parse_no_param_possible_typename();
	bool _parse_typeof();

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
	bool _parse_const_str();

	bool _parse_expr_pre_dollar_func();
	bool _parse_expr_post_dollar_func();
	bool _parse_dollar_func_of_one();

	bool _parse_ident_etc();
	bool _parse_ident_terminal();
	bool _parse_ident_member_access();
	bool _parse_ident_scope_access();
	bool _parse_ident();
	bool _parse_ident_bracket();
	bool _parse_ident_call();
	bool _parse_ident_no_param_overloaded_call();
	bool _parse_ident_param_member_overloaded_call();
	bool _parse_ident_param_scope_overloaded_call();

	//bool _parse_generate_any_if(ParseFunc parse_scope_func);
	//bool _parse_generate_any_for(ParseFunc parse_scope_func);
	inline auto _unit_parse(ParseFunc s_parse_func, bool s_optional=false)
	{
		return MultiParse::_unit_parse(this, s_optional, s_parse_func);
	}
	template<typename FirstArgType, typename... RemArgTypes>
	inline auto _opt_seq_parse(FirstArgType&& first_arg,
		RemArgTypes&&... rem_args)
	{
		return MultiParse::_opt_seq_parse(first_arg, rem_args...);
	}
	template<typename FirstArgType, typename... RemArgTypes>
	inline auto _req_seq_parse(FirstArgType&& first_arg,
		RemArgTypes&&... rem_args)
	{
		return MultiParse::_req_seq_parse(first_arg, rem_args...);
	}
	template<typename FirstArgType, typename... RemArgTypes>
	inline auto _opt_or_parse(FirstArgType&& first_arg,
		RemArgTypes&&... rem_args)
	{
		return MultiParse::_opt_or_parse(first_arg, rem_args...);
	}
	template<typename FirstArgType, typename... RemArgTypes>
	inline auto _req_or_parse(FirstArgType&& first_arg,
		RemArgTypes&&... rem_args)
	{
		return MultiParse::_req_or_parse(first_arg, rem_args...);
	}


};

} // namespace frost_hdl


#endif		// src_parser_class_hpp
