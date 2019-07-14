#include "parser_class.hpp"

namespace frost_hdl
{
using namespace ast;

Parser::Parser(std::vector<string>&& s_filename_vec)
	: ParserBase<Lexer>(std::move(s_filename_vec))
{
	_ast.reset(new NodeList(SrcCodeChunk()));
}
Parser::~Parser()
{
}

#define fp(func) &Parser::func

using FuncVec = std::vector<decltype(fp(_parse_program))>;

bool Parser::_parse_program()
{
	const FuncVec func_vec({fp(_parse_package), fp(_parse_module)});

	if (just_test())
	{
		return _check_parse(this, func_vec);
	}

	_req_parse_loop(this, func_vec);

	return true;
}

bool Parser::_parse_header_if()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_header_else_if()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_header_else()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_header_for()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_header_generate_if()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_header_else_generate_if()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_header_else_generate()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_header_generate_for()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_package()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_scope_package()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_generate_package()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_generate_package_if()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_generate_package_for()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_callable_member_prefix()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_contents_modproc()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_proc()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_module()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_scope_modproc()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_generate_modproc()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_generate_modproc_if()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_generate_modproc_for()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_decl_callable()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_contents_func_task()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_func()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_task()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_scope_behav()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_inner_scope_behav()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_generate_behav()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_generate_behav_if()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_generate_behav_for()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_const()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_var()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_using()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_stmt_assign()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_stmt_if()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_stmt_for()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_stmt_while()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_stmt_switch()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_stmt_switchz()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_scope_switch()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_decl_cstm_type()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_class()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_extends()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_scope_class()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_generate_class()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_generate_class_if()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_generate_class_for()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_member_access_label()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_enum()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_hardware_block()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_cont_assign()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_initial()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_always_comb()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_always_blk()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_always_ff()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_edge_list()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_posedge_inst()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_negedge_inst()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_inst()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_param_list()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_param_sublist()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_arg_list()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_arg_sublist()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_arg_port_sublist()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_pararg_var_sublist()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_pararg_type_sublist()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_param_module_sublist()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_ident_equals_typename_sublist()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_param_inst_list()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_pos_pararg_inst_list()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_named_pararg_inst_list()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_typename()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_param_possible_typename()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_no_param_possible_typename()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_typeof()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_expr()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_inner_expr()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_expr_logical()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_inner_expr_logical()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_expr_compare()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_inner_expr_compare()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_expr_add_sub()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_inner_expr_add_sub()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_expr_mul_div_mod_etc()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_inner_expr_mul_div_mod_etc()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_dollar_global_clock()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_dollar_pow_expr()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_const_str()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_ident_etc()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_ident_etc_pre_dollar_func()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_ident_etc_post_dollar_func()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

bool Parser::_parse_inner_ident_etc()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_ident_terminal()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_ident_member_access()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_ident()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_ident_bracket()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_ident_call()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_ident_no_param_overloaded_call()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}
bool Parser::_parse_ident_param_overloaded_call()
{
	if (just_test())
	{
	}
	_next_lss_tokens();

	return true;
}

#undef FUNC_VEC
#undef fp

} // namespace frost_hdl
