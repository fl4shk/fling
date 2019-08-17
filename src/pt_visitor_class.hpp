#ifndef src_pt_visitor_class_hpp
#define src_pt_visitor_class_hpp

// src/pt_visitor_class.hpp

#include "misc_includes.hpp"
#include "parse_tree_class.hpp"
#include "ast_node_main_classes.hpp"

namespace frost_hdl
{

class PtVisitor final
{
private:		// variables
	ParseTree* _pt_root = nullptr;
	ast::NodeBase::Child _ast_root;

	#define LIST_FOR_GEN_STACK(X) \
		X(BigNum, const BigNum&, num) \
		X(string, string, str) \
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
	inline PtVisitor() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(PtVisitor);
	inline ~PtVisitor() = default;

	GEN_GETTER_AND_SETTER_BY_VAL(pt_root)

	void run();

	GEN_GETTER_BY_REF(ast_root)

private:		// functions
	void _accept(ParseTree* tree);

	void _visit_program(ParseTree* tree);
	void _visit_program_item(ParseTree* tree);
	void _visit_header_if(ParseTree* tree);
	void _visit_header_else_if(ParseTree* tree);
	void _visit_header_else(ParseTree* tree);
	void _visit_header_for(ParseTree* tree);
	void _visit_header_generate_if(ParseTree* tree);
	void _visit_header_else_generate_if(ParseTree* tree);
	void _visit_header_else_generate(ParseTree* tree);
	void _visit_package(ParseTree* tree);
	void _visit_scope_package(ParseTree* tree);
	void _visit_scope_package_item(ParseTree* tree);
	void _visit_generate_package(ParseTree* tree);
	void _visit_generate_package_if(ParseTree* tree);
	void _visit_generate_package_else_if(ParseTree* tree);
	void _visit_generate_package_for(ParseTree* tree);
	void _visit_member_callable_prefix(ParseTree* tree);
	void _visit_non_ref_member_callable_prefix(ParseTree* tree);
	void _visit_kw_const(ParseTree* tree);
	void _visit_kw_virtual(ParseTree* tree);
	void _visit_kw_static(ParseTree* tree);
	void _visit_kw_ref(ParseTree* tree);
	void _visit_contents_modproc(ParseTree* tree);
	void _visit_proc(ParseTree* tree);
	void _visit_module(ParseTree* tree);
	void _visit_proc_ident_etc(ParseTree* tree);
	void _visit_kw_port(ParseTree* tree);
	void _visit_scope_modproc(ParseTree* tree);
	void _visit_scope_modproc_item(ParseTree* tree);
	void _visit_generate_modproc(ParseTree* tree);
	void _visit_generate_modproc_if(ParseTree* tree);
	void _visit_generate_modproc_else_if(ParseTree* tree);
	void _visit_generate_modproc_else(ParseTree* tree);
	void _visit_generate_modproc_for(ParseTree* tree);
	void _visit_decl_callable(ParseTree* tree);
	void _visit_contents_func_task(ParseTree* tree);
	void _visit_func(ParseTree* tree);
	void _visit_func_task_ident_etc(ParseTree* tree);
	void _visit_task(ParseTree* tree);
	void _visit_scope_behav(ParseTree* tree);
	void _visit_scope_behav_item(ParseTree* tree);
	void _visit_generate_behav(ParseTree* tree);
	void _visit_generate_behav_if(ParseTree* tree);
	void _visit_generate_behav_else_if(ParseTree* tree);
	void _visit_generate_behav_else(ParseTree* tree);
	void _visit_generate_behav_for(ParseTree* tree);
	void _visit_const(ParseTree* tree);
	void _visit_one_const(ParseTree* tree);
	void _visit_var(ParseTree* tree);
	void _visit_one_var(ParseTree* tree);
	void _visit_using(ParseTree* tree);
	void _visit_assign_stmt(ParseTree* tree);
	void _visit_if_stmt(ParseTree* tree);
	void _visit_stmt_else_if(ParseTree* tree);
	void _visit_stmt_else(ParseTree* tree);
	void _visit_for_stmt(ParseTree* tree);
	void _visit_while_stmt(ParseTree* tree);
	void _visit_switch_stmt(ParseTree* tree);
	void _visit_switchz_stmt(ParseTree* tree);
	void _visit_scope_switch(ParseTree* tree);
	void _visit_scope_switch_item(ParseTree* tree);
	void _visit_expr_case_item(ParseTree* tree);
	void _visit_default_case_item(ParseTree* tree);
	void _visit_return_stmt(ParseTree* tree);
	void _visit_dollar_resize_stmt(ParseTree* tree);
	void _visit_decl_cstm_type(ParseTree* tree);
	void _visit_class(ParseTree* tree);
	void _visit_extends(ParseTree* tree);
	void _visit_scope_class(ParseTree* tree);
	void _visit_scope_class_item(ParseTree* tree);
	void _visit_modport(ParseTree* tree);
	void _visit_inner_modport(ParseTree* tree);
	void _visit_member_callable(ParseTree* tree);
	void _visit_generate_class(ParseTree* tree);
	void _visit_generate_class_if(ParseTree* tree);
	void _visit_generate_class_else_if(ParseTree* tree);
	void _visit_generate_class_else(ParseTree* tree);
	void _visit_generate_class_for(ParseTree* tree);
	void _visit_member_access_label(ParseTree* tree);
	void _visit_enum(ParseTree* tree);
	void _visit_union(ParseTree* tree);
	void _visit_hardware_block(ParseTree* tree);
	void _visit_cont_assign(ParseTree* tree);
	void _visit_initial(ParseTree* tree);
	void _visit_always_comb(ParseTree* tree);
	void _visit_always_blk(ParseTree* tree);
	void _visit_always_ff(ParseTree* tree);
	void _visit_dff(ParseTree* tree);
	void _visit_edge_list(ParseTree* tree);
	void _visit_edge_list_item(ParseTree* tree);
	void _visit_posedge_inst(ParseTree* tree);
	void _visit_negedge_inst(ParseTree* tree);
	void _visit_inst(ParseTree* tree);
	void _visit_param_list(ParseTree* tree);
	void _visit_param_sublist(ParseTree* tree);
	void _visit_arg_list(ParseTree* tree);
	void _visit_arg_sublist(ParseTree* tree);
	void _visit_arg_port_sublist(ParseTree* tree);
	void _visit_pararg_var_sublist(ParseTree* tree);
	void _visit_pararg_var_sublist_item(ParseTree* tree);
	void _visit_pararg_type_sublist(ParseTree* tree);
	void _visit_param_module_sublist(ParseTree* tree);
	void _visit_pararg_ident_equals_typename_sublist(ParseTree* tree);
	void _visit_pararg_ident_equals_typename_sublist_item(ParseTree* tree);
	void _visit_param_inst_list(ParseTree* tree);
	void _visit_arg_inst_list(ParseTree* tree);
	void _visit_pos_pararg_inst_list(ParseTree* tree);
	void _visit_named_pararg_inst_list(ParseTree* tree);
	void _visit_named_pararg_inst_list_item(ParseTree* tree);
	void _visit_typename(ParseTree* tree);
	void _visit_param_possible_typename(ParseTree* tree);
	void _visit_no_param_possible_typename(ParseTree* tree);
	void _visit_typeof(ParseTree* tree);
	void _visit_type_range(ParseTree* tree);
	void _visit_range_suffix(ParseTree* tree);
	void _visit_expr(ParseTree* tree);
	void _visit_logical_expr(ParseTree* tree);
	void _visit_logical_expr_first_choice(ParseTree* tree);
	void _visit_compare_expr(ParseTree* tree);
	void _visit_compare_expr_first_choice(ParseTree* tree);
	void _visit_add_sub_expr(ParseTree* tree);
	void _visit_add_sub_expr_first_choice(ParseTree* tree);
	void _visit_mul_div_mod_etc_expr(ParseTree* tree);
	void _visit_unary_expr(ParseTree* tree);
	void _visit_paren_expr(ParseTree* tree);
	void _visit_dollar_global_clock(ParseTree* tree);
	void _visit_dollar_pow_expr(ParseTree* tree);
	void _visit_num_expr(ParseTree* tree);
	void _visit_raw_num(ParseTree* tree);
	void _visit_const_str(ParseTree* tree);
	void _visit_pre_dollar_func_of_one_expr(ParseTree* tree);
	void _visit_post_dollar_func_of_one_expr(ParseTree* tree);
	void _visit_expr_dollar_func_of_one(ParseTree* tree);
	void _visit_pre_dollar_func_of_one_valid_lhs_expr(ParseTree* tree);
	void _visit_post_dollar_func_of_one_valid_lhs_expr(ParseTree* tree);
	void _visit_pre_dollar_func_of_one_valid_lhs_expr(ParseTree* tree);
	void _visit_post_dollar_func_of_one_valid_lhs_expr(ParseTree* tree);
	void _visit_cat_expr(ParseTree* tree);
	void _visit_valid_lhs_expr(ParseTree* tree);
	void _visit_repl_expr(ParseTree* tree);
	void _visit_ident_etc(ParseTree* tree);
	void _visit_ident_member_access(ParseTree* tree);
	void _visit_ident_scope_access(ParseTree* tree);
	void _visit_ident_non_member_scope_access(ParseTree* tree);
	void _visit_ident_call(ParseTree* tree);
	void _visit_ident_no_param_overloaded_call(ParseTree* tree);
	void _visit_ident_param_member_overloaded_call(ParseTree* tree);
	void _visit_ident_terminal(ParseTree* tree);
	void _visit_any_range_suffix(ParseTree* tree);
	void _visit_ident(ParseTree* tree);

};


} // namespace frost_hdl

#endif		// src_pt_visitor_class_hpp
