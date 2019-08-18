#include "pt_visitor_class.hpp"
#include <variant>

namespace frost_hdl
{

PtVisitor::PtVisitor()
{
	#include "list_of_parse_tree_nodes_define.hpp"
	#define X(node) \
		_func_map[#node] = &PtVisitor::_visit_##node;
	LIST_OF_PARSE_TREE_NODES(X)
	#undef X
	#undef LIST_OF_PARSE_TREE_NODES
}

void PtVisitor::_accept(ParseTree* tree)
{
	tree->ident()
}

using std::holds_alternative;
using std::get;
#define ha std::holds_alternative

void PtVisitor::_visit_program(ParseTree* tree)
{
}
void PtVisitor::_visit_program_item(ParseTree* tree)
{
}
void PtVisitor::_visit_header_if(ParseTree* tree)
{
}
void PtVisitor::_visit_header_else_if(ParseTree* tree)
{
}
void PtVisitor::_visit_header_else(ParseTree* tree)
{
}
void PtVisitor::_visit_header_for(ParseTree* tree)
{
}
void PtVisitor::_visit_header_generate_if(ParseTree* tree)
{
}
void PtVisitor::_visit_header_else_generate_if(ParseTree* tree)
{
}
void PtVisitor::_visit_header_else_generate(ParseTree* tree)
{
}
void PtVisitor::_visit_header_generate_for(ParseTree* tree)
{
}
void PtVisitor::_visit_package(ParseTree* tree)
{
}
void PtVisitor::_visit_scope_package(ParseTree* tree)
{
}
void PtVisitor::_visit_scope_package_item(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_package(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_package_if(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_package_else_if(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_package_else(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_package_for(ParseTree* tree)
{
}
void PtVisitor::_visit_member_callable_prefix(ParseTree* tree)
{
}
void PtVisitor::_visit_non_ref_member_callable_prefix(ParseTree* tree)
{
}
void PtVisitor::_visit_kw_const(ParseTree* tree)
{
}
void PtVisitor::_visit_kw_virtual(ParseTree* tree)
{
}
void PtVisitor::_visit_kw_static(ParseTree* tree)
{
}
void PtVisitor::_visit_kw_ref(ParseTree* tree)
{
}
void PtVisitor::_visit_contents_modproc(ParseTree* tree)
{
}
void PtVisitor::_visit_proc(ParseTree* tree)
{
}
void PtVisitor::_visit_module(ParseTree* tree)
{
}
void PtVisitor::_visit_proc_ident_etc(ParseTree* tree)
{
}
void PtVisitor::_visit_kw_port(ParseTree* tree)
{
}
void PtVisitor::_visit_scope_modproc(ParseTree* tree)
{
}
void PtVisitor::_visit_scope_modproc_item(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_modproc(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_modproc_if(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_modproc_else_if(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_modproc_else(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_modproc_for(ParseTree* tree)
{
}
void PtVisitor::_visit_decl_callable(ParseTree* tree)
{
}
void PtVisitor::_visit_contents_func_task(ParseTree* tree)
{
}
void PtVisitor::_visit_func(ParseTree* tree)
{
}
void PtVisitor::_visit_func_task_ident_etc(ParseTree* tree)
{
}
void PtVisitor::_visit_task(ParseTree* tree)
{
}
void PtVisitor::_visit_scope_behav(ParseTree* tree)
{
}
void PtVisitor::_visit_scope_behav_item(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_behav(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_behav_if(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_behav_else_if(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_behav_else(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_behav_for(ParseTree* tree)
{
}
void PtVisitor::_visit_const(ParseTree* tree)
{
}
void PtVisitor::_visit_one_const(ParseTree* tree)
{
}
void PtVisitor::_visit_var(ParseTree* tree)
{
}
void PtVisitor::_visit_one_var(ParseTree* tree)
{
}
void PtVisitor::_visit_using(ParseTree* tree)
{
}
void PtVisitor::_visit_assign_stmt(ParseTree* tree)
{
}
void PtVisitor::_visit_if_stmt(ParseTree* tree)
{
}
void PtVisitor::_visit_stmt_else_if(ParseTree* tree)
{
}
void PtVisitor::_visit_stmt_else(ParseTree* tree)
{
}
void PtVisitor::_visit_for_stmt(ParseTree* tree)
{
}
void PtVisitor::_visit_while_stmt(ParseTree* tree)
{
}
void PtVisitor::_visit_switch_stmt(ParseTree* tree)
{
}
void PtVisitor::_visit_switchz_stmt(ParseTree* tree)
{
}
void PtVisitor::_visit_scope_switch(ParseTree* tree)
{
}
void PtVisitor::_visit_scope_switch_item(ParseTree* tree)
{
}
void PtVisitor::_visit_expr_case_item(ParseTree* tree)
{
}
void PtVisitor::_visit_default_case_item(ParseTree* tree)
{
}
void PtVisitor::_visit_return_stmt(ParseTree* tree)
{
}
void PtVisitor::_visit_dollar_resize_stmt(ParseTree* tree)
{
}
void PtVisitor::_visit_decl_cstm_type(ParseTree* tree)
{
}
void PtVisitor::_visit_class(ParseTree* tree)
{
}
void PtVisitor::_visit_extends(ParseTree* tree)
{
}
void PtVisitor::_visit_scope_class(ParseTree* tree)
{
}
void PtVisitor::_visit_scope_class_item(ParseTree* tree)
{
}
void PtVisitor::_visit_modport(ParseTree* tree)
{
}
void PtVisitor::_visit_inner_modport(ParseTree* tree)
{
}
void PtVisitor::_visit_member_callable(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_class(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_class_if(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_class_else_if(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_class_else(ParseTree* tree)
{
}
void PtVisitor::_visit_generate_class_for(ParseTree* tree)
{
}
void PtVisitor::_visit_member_access_label(ParseTree* tree)
{
}
void PtVisitor::_visit_enum(ParseTree* tree)
{
}
void PtVisitor::_visit_union(ParseTree* tree)
{
}
void PtVisitor::_visit_hardware_block(ParseTree* tree)
{
}
void PtVisitor::_visit_cont_assign(ParseTree* tree)
{
}
void PtVisitor::_visit_initial(ParseTree* tree)
{
}
void PtVisitor::_visit_always_comb(ParseTree* tree)
{
}
void PtVisitor::_visit_always_blk(ParseTree* tree)
{
}
void PtVisitor::_visit_always_ff(ParseTree* tree)
{
}
void PtVisitor::_visit_dff(ParseTree* tree)
{
}
void PtVisitor::_visit_edge_list(ParseTree* tree)
{
}
void PtVisitor::_visit_edge_list_item(ParseTree* tree)
{
}
void PtVisitor::_visit_posedge_inst(ParseTree* tree)
{
}
void PtVisitor::_visit_negedge_inst(ParseTree* tree)
{
}
void PtVisitor::_visit_inst(ParseTree* tree)
{
}
void PtVisitor::_visit_param_list(ParseTree* tree)
{
}
void PtVisitor::_visit_param_sublist(ParseTree* tree)
{
}
void PtVisitor::_visit_arg_list(ParseTree* tree)
{
}
void PtVisitor::_visit_arg_sublist(ParseTree* tree)
{
}
void PtVisitor::_visit_arg_port_sublist(ParseTree* tree)
{
}
void PtVisitor::_visit_pararg_var_sublist(ParseTree* tree)
{
}
void PtVisitor::_visit_pararg_var_sublist_item(ParseTree* tree)
{
}
void PtVisitor::_visit_pararg_type_sublist(ParseTree* tree)
{
}
void PtVisitor::_visit_param_module_sublist(ParseTree* tree)
{
}
void PtVisitor::_visit_pararg_ident_equals_typename_sublist
	(ParseTree* tree)
{
}
void PtVisitor::_visit_pararg_ident_equals_typename_sublist_item
	(ParseTree* tree)
{
}
void PtVisitor::_visit_param_inst_list(ParseTree* tree)
{
}
void PtVisitor::_visit_arg_inst_list(ParseTree* tree)
{
}
void PtVisitor::_visit_pos_pararg_inst_list(ParseTree* tree)
{
}
void PtVisitor::_visit_named_pararg_inst_list(ParseTree* tree)
{
}
void PtVisitor::_visit_named_pararg_inst_list_item(ParseTree* tree)
{
}
void PtVisitor::_visit_typename(ParseTree* tree)
{
}
void PtVisitor::_visit_param_possible_typename(ParseTree* tree)
{
}
void PtVisitor::_visit_no_param_possible_typename(ParseTree* tree)
{
}
void PtVisitor::_visit_typeof(ParseTree* tree)
{
}
void PtVisitor::_visit_type_range(ParseTree* tree)
{
}
void PtVisitor::_visit_range_suffix(ParseTree* tree)
{
}
void PtVisitor::_visit_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_logical_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_logical_expr_first_choice(ParseTree* tree)
{
}
void PtVisitor::_visit_compare_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_compare_expr_first_choice(ParseTree* tree)
{
}
void PtVisitor::_visit_add_sub_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_add_sub_expr_first_choice(ParseTree* tree)
{
}
void PtVisitor::_visit_mul_div_mod_etc_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_unary_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_paren_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_dollar_global_clock(ParseTree* tree)
{
}
void PtVisitor::_visit_dollar_pow_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_num_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_raw_num(ParseTree* tree)
{
}
void PtVisitor::_visit_const_str(ParseTree* tree)
{
}
void PtVisitor::_visit_pre_dollar_func_of_one_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_post_dollar_func_of_one_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_expr_dollar_func_of_one(ParseTree* tree)
{
}
void PtVisitor::_visit_pre_dollar_func_of_one_valid_lhs_expr
	(ParseTree* tree)
{
}
void PtVisitor::_visit_post_dollar_func_of_one_valid_lhs_expr
	(ParseTree* tree)
{
}
void PtVisitor::_visit_cat_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_valid_lhs_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_repl_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_ident_etc(ParseTree* tree)
{
}
void PtVisitor::_visit_ident_member_access(ParseTree* tree)
{
}
void PtVisitor::_visit_ident_scope_access(ParseTree* tree)
{
}
void PtVisitor::_visit_ident_non_member_scope_access(ParseTree* tree)
{
}
void PtVisitor::_visit_ident_call(ParseTree* tree)
{
}
void PtVisitor::_visit_ident_no_param_overloaded_call(ParseTree* tree)
{
}
void PtVisitor::_visit_ident_param_member_overloaded_call(ParseTree* tree)
{
}
void PtVisitor::_visit_ident_terminal(ParseTree* tree)
{
}
void PtVisitor::_visit_any_range_suffix(ParseTree* tree)
{
}
void PtVisitor::_visit_ident(ParseTree* tree)
{
}

} // namespace frost_hdl
