#include "pt_visitor_class.hpp"

namespace frost_hdl
{

void PtVisitor::_accept(ParseTree* tree)
{
	if (tree->ident() == "program")
	{
		_visit_program(tree);
	}
	else if (tree->ident() == "program_item")
	{
		_visit_program_item(tree);
	}
	else if (tree->ident() == "header_if")
	{
		_visit_header_if(tree);
	}
	else if (tree->ident() == "header_else_if")
	{
		_visit_header_else_if(tree);
	}
	else if (tree->ident() == "header_else")
	{
		_visit_header_else(tree);
	}
	else if (tree->ident() == "header_for")
	{
		_visit_header_for(tree);
	}
	else if (tree->ident() == "header_generate_if")
	{
		_visit_header_generate_if(tree);
	}
	else if (tree->ident() == "header_else_generate_if")
	{
		_visit_header_else_generate_if(tree);
	}
	else if (tree->ident() == "header_else_generate")
	{
		_visit_header_else_generate(tree);
	}
	else if (tree->ident() == "header_generate_for")
	{
		_visit_header_generate_for(tree);
	}
	else if (tree->ident() == "package")
	{
		_visit_package(tree);
	}
	else if (tree->ident() == "scope_package")
	{
		_visit_scope_package(tree);
	}
	else if (tree->ident() == "scope_package_item")
	{
		_visit_scope_package_item(tree);
	}
	else if (tree->ident() == "generate_package")
	{
		_visit_generate_package(tree);
	}
	else if (tree->ident() == "generate_package_if")
	{
		_visit_generate_package_if(tree);
	}
	else if (tree->ident() == "generate_package_else_if")
	{
		_visit_generate_package_else_if(tree);
	}
	else if (tree->ident() == "generate_package_else")
	{
		_visit_generate_package_else(tree);
	}
	else if (tree->ident() == "generate_package_for")
	{
		_visit_generate_package_for(tree);
	}
	else if (tree->ident() == "member_callable_prefix")
	{
		_visit_member_callable_prefix(tree);
	}
	else if (tree->ident() == "non_ref_member_callable_prefix")
	{
		_visit_non_ref_member_callable_prefix(tree);
	}
	else if (tree->ident() == "kw_const")
	{
		_visit_kw_const(tree);
	}
	else if (tree->ident() == "kw_virtual")
	{
		_visit_kw_virtual(tree);
	}
	else if (tree->ident() == "kw_static")
	{
		_visit_kw_static(tree);
	}
	else if (tree->ident() == "kw_ref")
	{
		_visit_kw_ref(tree);
	}
	else if (tree->ident() == "contents_modproc")
	{
		_visit_contents_modproc(tree);
	}
	else if (tree->ident() == "proc")
	{
		_visit_proc(tree);
	}
	else if (tree->ident() == "module")
	{
		_visit_module(tree);
	}
	else if (tree->ident() == "proc_ident_etc")
	{
		_visit_proc_ident_etc(tree);
	}
	else if (tree->ident() == "kw_port")
	{
		_visit_kw_port(tree);
	}
	else if (tree->ident() == "scope_modproc")
	{
		_visit_scope_modproc(tree);
	}
	else if (tree->ident() == "scope_modproc_item")
	{
		_visit_scope_modproc_item(tree);
	}
	else if (tree->ident() == "generate_modproc")
	{
		_visit_generate_modproc(tree);
	}
	else if (tree->ident() == "generate_modproc_if")
	{
		_visit_generate_modproc_if(tree);
	}
	else if (tree->ident() == "generate_modproc_else_if")
	{
		_visit_generate_modproc_else_if(tree);
	}
	else if (tree->ident() == "generate_modproc_else")
	{
		_visit_generate_modproc_else(tree);
	}
	else if (tree->ident() == "generate_modproc_for")
	{
		_visit_generate_modproc_for(tree);
	}
	else if (tree->ident() == "decl_callable")
	{
		_visit_decl_callable(tree);
	}
	else if (tree->ident() == "contents_func_task")
	{
		_visit_contents_func_task(tree);
	}
	else if (tree->ident() == "func")
	{
		_visit_func(tree);
	}
	else if (tree->ident() == "func_task_ident_etc")
	{
		_visit_func_task_ident_etc(tree);
	}
	else if (tree->ident() == "task")
	{
		_visit_task(tree);
	}
	else if (tree->ident() == "scope_behav")
	{
		_visit_scope_behav(tree);
	}
	else if (tree->ident() == "scope_behav_item")
	{
		_visit_scope_behav_item(tree);
	}
	else if (tree->ident() == "generate_behav")
	{
		_visit_generate_behav(tree);
	}
	else if (tree->ident() == "generate_behav_if")
	{
		_visit_generate_behav_if(tree);
	}
	else if (tree->ident() == "generate_behav_else_if")
	{
		_visit_generate_behav_else_if(tree);
	}
	else if (tree->ident() == "generate_behav_else")
	{
		_visit_generate_behav_else(tree);
	}
	else if (tree->ident() == "generate_behav_for")
	{
		_visit_generate_behav_for(tree);
	}
	else if (tree->ident() == "const")
	{
		_visit_const(tree);
	}
	else if (tree->ident() == "one_const")
	{
		_visit_one_const(tree);
	}
	else if (tree->ident() == "var")
	{
		_visit_var(tree);
	}
	else if (tree->ident() == "one_var")
	{
		_visit_one_var(tree);
	}
	else if (tree->ident() == "using")
	{
		_visit_using(tree);
	}
	else if (tree->ident() == "assign_stmt")
	{
		_visit_assign_stmt(tree);
	}
	else if (tree->ident() == "if_stmt")
	{
		_visit_if_stmt(tree);
	}
	else if (tree->ident() == "stmt_else_if")
	{
		_visit_stmt_else_if(tree);
	}
	else if (tree->ident() == "stmt_else")
	{
		_visit_stmt_else(tree);
	}
	else if (tree->ident() == "for_stmt")
	{
		_visit_for_stmt(tree);
	}
	else if (tree->ident() == "while_stmt")
	{
		_visit_while_stmt(tree);
	}
	else if (tree->ident() == "switch_stmt")
	{
		_visit_switch_stmt(tree);
	}
	else if (tree->ident() == "switchz_stmt")
	{
		_visit_switchz_stmt(tree);
	}
	else if (tree->ident() == "scope_switch")
	{
		_visit_scope_switch(tree);
	}
	else if (tree->ident() == "scope_switch_item")
	{
		_visit_scope_switch_item(tree);
	}
	else if (tree->ident() == "expr_case_item")
	{
		_visit_expr_case_item(tree);
	}
	else if (tree->ident() == "default_case_item")
	{
		_visit_default_case_item(tree);
	}
	else if (tree->ident() == "return_stmt")
	{
		_visit_return_stmt(tree);
	}
	else if (tree->ident() == "dollar_resize_stmt")
	{
		_visit_dollar_resize_stmt(tree);
	}
	else if (tree->ident() == "decl_cstm_type")
	{
		_visit_decl_cstm_type(tree);
	}
	else if (tree->ident() == "class")
	{
		_visit_class(tree);
	}
	else if (tree->ident() == "extends")
	{
		_visit_extends(tree);
	}
	else if (tree->ident() == "scope_class")
	{
		_visit_scope_class(tree);
	}
	else if (tree->ident() == "scope_class_item")
	{
		_visit_scope_class_item(tree);
	}
	else if (tree->ident() == "modport")
	{
		_visit_modport(tree);
	}
	else if (tree->ident() == "inner_modport")
	{
		_visit_inner_modport(tree);
	}
	else if (tree->ident() == "member_callable")
	{
		_visit_member_callable(tree);
	}
	else if (tree->ident() == "generate_class")
	{
		_visit_generate_class(tree);
	}
	else if (tree->ident() == "generate_class_if")
	{
		_visit_generate_class_if(tree);
	}
	else if (tree->ident() == "generate_class_else_if")
	{
		_visit_generate_class_else_if(tree);
	}
	else if (tree->ident() == "generate_class_else")
	{
		_visit_generate_class_else(tree);
	}
	else if (tree->ident() == "generate_class_for")
	{
		_visit_generate_class_for(tree);
	}
	else if (tree->ident() == "member_access_label")
	{
		_visit_member_access_label(tree);
	}
	else if (tree->ident() == "enum")
	{
		_visit_enum(tree);
	}
	else if (tree->ident() == "union")
	{
		_visit_union(tree);
	}
	else if (tree->ident() == "hardware_block")
	{
		_visit_hardware_block(tree);
	}
	else if (tree->ident() == "cont_assign")
	{
		_visit_cont_assign(tree);
	}
	else if (tree->ident() == "initial")
	{
		_visit_initial(tree);
	}
	else if (tree->ident() == "always_comb")
	{
		_visit_always_comb(tree);
	}
	else if (tree->ident() == "always_blk")
	{
		_visit_always_blk(tree);
	}
	else if (tree->ident() == "always_ff")
	{
		_visit_always_ff(tree);
	}
	else if (tree->ident() == "dff")
	{
		_visit_dff(tree);
	}
	else if (tree->ident() == "edge_list")
	{
		_visit_edge_list(tree);
	}
	else if (tree->ident() == "edge_list_item")
	{
		_visit_edge_list_item(tree);
	}
	else if (tree->ident() == "posedge_inst")
	{
		_visit_posedge_inst(tree);
	}
	else if (tree->ident() == "negedge_inst")
	{
		_visit_negedge_inst(tree);
	}
	else if (tree->ident() == "inst")
	{
		_visit_inst(tree);
	}
	else if (tree->ident() == "param_list")
	{
		_visit_param_list(tree);
	}
	else if (tree->ident() == "param_sublist")
	{
		_visit_param_sublist(tree);
	}
	else if (tree->ident() == "arg_list")
	{
		_visit_arg_list(tree);
	}
	else if (tree->ident() == "arg_sublist")
	{
		_visit_arg_sublist(tree);
	}
	else if (tree->ident() == "arg_port_sublist")
	{
		_visit_arg_port_sublist(tree);
	}
	else if (tree->ident() == "pararg_var_sublist")
	{
		_visit_pararg_var_sublist(tree);
	}
	else if (tree->ident() == "pararg_var_sublist_item")
	{
		_visit_pararg_var_sublist_item(tree);
	}
	else if (tree->ident() == "pararg_type_sublist")
	{
		_visit_pararg_type_sublist(tree);
	}
	else if (tree->ident() == "param_module_sublist")
	{
		_visit_param_module_sublist(tree);
	}
	else if (tree->ident() == "pararg_ident_equals_typename_sublist")
	{
		_visit_pararg_ident_equals_typename_sublist(tree);
	}
	else if (tree->ident() == "pararg_ident_equals_typename_sublist_item")
	{
		_visit_pararg_ident_equals_typename_sublist_item(tree);
	}
	else if (tree->ident() == "param_inst_list")
	{
		_visit_param_inst_list(tree);
	}
	else if (tree->ident() == "arg_inst_list")
	{
		_visit_arg_inst_list(tree);
	}
	else if (tree->ident() == "pos_pararg_inst_list")
	{
		_visit_pos_pararg_inst_list(tree);
	}
	else if (tree->ident() == "named_pararg_inst_list")
	{
		_visit_named_pararg_inst_list(tree);
	}
	else if (tree->ident() == "named_pararg_inst_list_item")
	{
		_visit_named_pararg_inst_list_item(tree);
	}
	else if (tree->ident() == "typename")
	{
		_visit_typename(tree);
	}
	else if (tree->ident() == "param_possible_typename")
	{
		_visit_param_possible_typename(tree);
	}
	else if (tree->ident() == "no_param_possible_typename")
	{
		_visit_no_param_possible_typename(tree);
	}
	else if (tree->ident() == "typeof")
	{
		_visit_typeof(tree);
	}
	else if (tree->ident() == "type_range")
	{
		_visit_type_range(tree);
	}
	else if (tree->ident() == "range_suffix")
	{
		_visit_range_suffix(tree);
	}
	else if (tree->ident() == "expr")
	{
		_visit_expr(tree);
	}
	else if (tree->ident() == "logical_expr")
	{
		_visit_logical_expr(tree);
	}
	else if (tree->ident() == "logical_expr_first_choice")
	{
		_visit_logical_expr_first_choice(tree);
	}
	else if (tree->ident() == "compare_expr")
	{
		_visit_compare_expr(tree);
	}
	else if (tree->ident() == "compare_expr_first_choice")
	{
		_visit_compare_expr_first_choice(tree);
	}
	else if (tree->ident() == "add_sub_expr")
	{
		_visit_add_sub_expr(tree);
	}
	else if (tree->ident() == "add_sub_expr_first_choice")
	{
		_visit_add_sub_expr_first_choice(tree);
	}
	else if (tree->ident() == "mul_div_mod_etc_expr")
	{
		_visit_mul_div_mod_etc_expr(tree);
	}
	else if (tree->ident() == "unary_expr")
	{
		_visit_unary_expr(tree);
	}
	else if (tree->ident() == "paren_expr")
	{
		_visit_paren_expr(tree);
	}
	else if (tree->ident() == "dollar_global_clock")
	{
		_visit_dollar_global_clock(tree);
	}
	else if (tree->ident() == "dollar_pow_expr")
	{
		_visit_dollar_pow_expr(tree);
	}
	else if (tree->ident() == "num_expr")
	{
		_visit_num_expr(tree);
	}
	else if (tree->ident() == "raw_num")
	{
		_visit_raw_num(tree);
	}
	else if (tree->ident() == "const_str")
	{
		_visit_const_str(tree);
	}
	else if (tree->ident() == "pre_dollar_func_of_one_expr")
	{
		_visit_pre_dollar_func_of_one_expr(tree);
	}
	else if (tree->ident() == "post_dollar_func_of_one_expr")
	{
		_visit_post_dollar_func_of_one_expr(tree);
	}
	else if (tree->ident() == "expr_dollar_func_of_one")
	{
		_visit_expr_dollar_func_of_one(tree);
	}
	else if (tree->ident() == "pre_dollar_func_of_one_valid_lhs_expr")
	{
		_visit_pre_dollar_func_of_one_valid_lhs_expr(tree);
	}
	else if (tree->ident() == "post_dollar_func_of_one_valid_lhs_expr")
	{
		_visit_post_dollar_func_of_one_valid_lhs_expr(tree);
	}
	else if (tree->ident() == "pre_dollar_func_of_one_valid_lhs_expr")
	{
		_visit_pre_dollar_func_of_one_valid_lhs_expr(tree);
	}
	else if (tree->ident() == "post_dollar_func_of_one_valid_lhs_expr")
	{
		_visit_post_dollar_func_of_one_valid_lhs_expr(tree);
	}
	else if (tree->ident() == "cat_expr")
	{
		_visit_cat_expr(tree);
	}
	else if (tree->ident() == "valid_lhs_expr")
	{
		_visit_valid_lhs_expr(tree);
	}
	else if (tree->ident() == "repl_expr")
	{
		_visit_repl_expr(tree);
	}
	else if (tree->ident() == "ident_etc")
	{
		_visit_ident_etc(tree);
	}
	else if (tree->ident() == "ident_member_access")
	{
		_visit_ident_member_access(tree);
	}
	else if (tree->ident() == "ident_scope_access")
	{
		_visit_ident_scope_access(tree);
	}
	else if (tree->ident() == "ident_non_member_scope_access")
	{
		_visit_ident_non_member_scope_access(tree);
	}
	else if (tree->ident() == "ident_call")
	{
		_visit_ident_call(tree);
	}
	else if (tree->ident() == "ident_no_param_overloaded_call")
	{
		_visit_ident_no_param_overloaded_call(tree);
	}
	else if (tree->ident() == "ident_param_member_overloaded_call")
	{
		_visit_ident_param_member_overloaded_call(tree);
	}
	else if (tree->ident() == "ident_terminal")
	{
		_visit_ident_terminal(tree);
	}
	else if (tree->ident() == "any_range_suffix")
	{
		_visit_any_range_suffix(tree);
	}
	else if (tree->ident() == "ident")
	{
		_visit_ident(tree);
	}
}

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
void PtVisitor::_visit_pararg_ident_equals_typename_sublist(ParseTree* tree)
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
void PtVisitor::_visit_pre_dollar_func_of_one_valid_lhs_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_post_dollar_func_of_one_valid_lhs_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_pre_dollar_func_of_one_valid_lhs_expr(ParseTree* tree)
{
}
void PtVisitor::_visit_post_dollar_func_of_one_valid_lhs_expr(ParseTree* tree)
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
