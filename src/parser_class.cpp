#include "parser_class.hpp"

namespace frost_hdl
{
using namespace ast;

Parser::Parser(std::vector<string>&& s_filename_vec)
	: ParserBase<Lexer>(std::move(s_filename_vec))
{
	_ast_root.reset(new NodeProgram(SrcCodeChunk()));
}
Parser::~Parser()
{
}

#define fp(func) &Parser::func

using FuncVec = std::vector<decltype(fp(parse_program))>;
using std::move;

bool Parser::parse_program()
{
	const FuncVec func_vec({fp(_parse_package), fp(_parse_module)});

	while (_opt_parse(this, func_vec))
	{
		_ast_root->append(move(_pop_ast_child()));
	}

	return true;
}

#define CHECK_PREFIXED_ONE_TOK(one_tok) \
	if (just_test()) \
	{ \
		return _check_prefixed_tok_seq(one_tok); \
	} \
	_next_lss_tokens()

#define CHECK_PREFIXED_TOK_SEQ(left, right) \
	if (just_test()) \
	{ \
		return _check_prefixed_tok_seq(left, right); \
	} \
	_next_lss_tokens()

bool Parser::_parse_header_if()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwIf);

	_expect(Tok::LParen);
	_parse_expr();
	_expect(Tok::RParen);

	return true;
}
bool Parser::_parse_header_else_if()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwElse);

	_parse_header_if();

	return true;
}
bool Parser::_parse_header_else()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwElse);

	return true;
}
bool Parser::_parse_header_for()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwFor);

	_expect(Tok::LParen);
	_parse_ident();
	_expect(Tok::Colon);
	_parse_expr();
	_expect(Tok::RParen);

	return true;
}

bool Parser::_parse_header_generate_if()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwGenerate);

	_parse_header_if();

	return true;
}
bool Parser::_parse_header_else_generate_if()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwElse);

	_parse_header_generate_if();

	return true;
}
bool Parser::_parse_header_else_generate()
{
	CHECK_PREFIXED_TOK_SEQ(TokSet({Tok::KwElse}), Tok::KwGenerate);
	return true;
}
bool Parser::_parse_header_generate_for()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwGenerate);

	_push_num(_opt_parse(fp(_parse_ident)));

	_parse_header_for();

	return true;
}

bool Parser::_parse_package()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPackage);
	const auto src_code_chunk = _lexer().src_code_chunk();

	auto ident = _get_req_parse(fp(_parse_ident));
	auto scope = _get_req_parse(fp(_parse_scope_package));
	_push_ast_child(NodePackage(src_code_chunk, move(ident), move(scope)));

	return true;
}
bool Parser::_parse_scope_package()
{
	return true;
}

bool Parser::_parse_generate_package()
{
	return true;
}
bool Parser::_parse_generate_package_if()
{
	return true;
}
bool Parser::_parse_generate_package_for()
{
	return true;
}

bool Parser::_parse_callable_member_prefix()
{
	return true;
}

bool Parser::_parse_contents_modproc()
{
	return true;
}
bool Parser::_parse_proc()
{
	return true;
}
bool Parser::_parse_module()
{
	return true;
}

bool Parser::_parse_scope_modproc()
{
	return true;
}
bool Parser::_parse_generate_modproc()
{
	return true;
}
bool Parser::_parse_generate_modproc_if()
{
	return true;
}
bool Parser::_parse_generate_modproc_for()
{
	return true;
}

bool Parser::_parse_decl_callable()
{
	return true;
}
bool Parser::_parse_contents_func_task()
{
	return true;
}
bool Parser::_parse_func()
{
	return true;
}
bool Parser::_parse_task()
{
	return true;
}

bool Parser::_parse_scope_behav()
{
	return true;
}
bool Parser::_parse_inner_scope_behav()
{
	return true;
}

bool Parser::_parse_generate_behav()
{
	return true;
}
bool Parser::_parse_generate_behav_if()
{
	return true;
}
bool Parser::_parse_generate_behav_for()
{
	return true;
}

bool Parser::_parse_const()
{
	return true;
}
bool Parser::_parse_var()
{
	return true;
}
bool Parser::_parse_using()
{
	return true;
}

bool Parser::_parse_stmt_assign()
{
	return true;
}
bool Parser::_parse_stmt_if()
{
	return true;
}
bool Parser::_parse_stmt_for()
{
	return true;
}
bool Parser::_parse_stmt_while()
{
	return true;
}
bool Parser::_parse_stmt_switch()
{
	return true;
}
bool Parser::_parse_stmt_switchz()
{
	return true;
}
bool Parser::_parse_scope_switch()
{
	return true;
}

bool Parser::_parse_decl_cstm_type()
{
	return true;
}
bool Parser::_parse_class()
{
	return true;
}
bool Parser::_parse_extends()
{
	return true;
}

bool Parser::_parse_scope_class()
{
	return true;
}
bool Parser::_parse_generate_class()
{
	return true;
}
bool Parser::_parse_generate_class_if()
{
	return true;
}
bool Parser::_parse_generate_class_for()
{
	return true;
}
bool Parser::_parse_member_access_label()
{
	return true;
}

bool Parser::_parse_enum()
{
	return true;
}

bool Parser::_parse_hardware_block()
{
	return true;
}
bool Parser::_parse_cont_assign()
{
	return true;
}
bool Parser::_parse_initial()
{
	return true;
}
bool Parser::_parse_always_comb()
{
	return true;
}
bool Parser::_parse_always_blk()
{
	return true;
}
bool Parser::_parse_always_ff()
{
	return true;
}
bool Parser::_parse_edge_list()
{
	return true;
}
bool Parser::_parse_posedge_inst()
{
	return true;
}
bool Parser::_parse_negedge_inst()
{
	return true;
}

bool Parser::_parse_inst()
{
	return true;
}

bool Parser::_parse_param_list()
{
	return true;
}
bool Parser::_parse_param_sublist()
{
	return true;
}
bool Parser::_parse_arg_list()
{
	return true;
}
bool Parser::_parse_arg_sublist()
{
	return true;
}
bool Parser::_parse_arg_port_sublist()
{
	return true;
}
bool Parser::_parse_pararg_var_sublist()
{
	return true;
}
bool Parser::_parse_pararg_type_sublist()
{
	return true;
}
bool Parser::_parse_param_module_sublist()
{
	return true;
}
bool Parser::_parse_ident_equals_typename_sublist()
{
	return true;
}
bool Parser::_parse_param_inst_list()
{
	return true;
}

bool Parser::_parse_pos_pararg_inst_list()
{
	return true;
}
bool Parser::_parse_named_pararg_inst_list()
{
	return true;
}

bool Parser::_parse_typename()
{
	return true;
}
bool Parser::_parse_param_possible_typename()
{
	return true;
}
bool Parser::_parse_no_param_possible_typename()
{
	return true;
}
bool Parser::_parse_typeof()
{
	return true;
}

bool Parser::_parse_expr()
{
	return true;
}
bool Parser::_parse_inner_expr()
{
	return true;
}

bool Parser::_parse_expr_logical()
{
	return true;
}
bool Parser::_parse_inner_expr_logical()
{
	return true;
}

bool Parser::_parse_expr_compare()
{
	return true;
}
bool Parser::_parse_inner_expr_compare()
{
	return true;
}

bool Parser::_parse_expr_add_sub()
{
	return true;
}
bool Parser::_parse_inner_expr_add_sub()
{
	return true;
}

bool Parser::_parse_expr_mul_div_mod_etc()
{
	return true;
}
bool Parser::_parse_inner_expr_mul_div_mod_etc()
{
	return true;
}

bool Parser::_parse_dollar_global_clock()
{
	return true;
}
bool Parser::_parse_dollar_pow_expr()
{
	return true;
}
bool Parser::_parse_const_str()
{
	return true;
}

bool Parser::_parse_ident_etc()
{
	return true;
}
bool Parser::_parse_ident_etc_pre_dollar_func()
{
	return true;
}
bool Parser::_parse_ident_etc_post_dollar_func()
{
	return true;
}

bool Parser::_parse_inner_ident_etc()
{
	return true;
}
bool Parser::_parse_ident_terminal()
{
	return true;
}
bool Parser::_parse_ident_member_access()
{
	return true;
}
bool Parser::_parse_ident()
{
	return true;
}
bool Parser::_parse_ident_bracket()
{
	return true;
}
bool Parser::_parse_ident_call()
{
	return true;
}
bool Parser::_parse_ident_no_param_overloaded_call()
{
	return true;
}
bool Parser::_parse_ident_param_overloaded_call()
{
	return true;
}

#undef FUNC_VEC
#undef fp

} // namespace frost_hdl
