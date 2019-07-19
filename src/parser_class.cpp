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
using Child = ast::NodeBase::Child;

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

bool Parser::_parse_kw_if()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwIf);
	return true;
}
bool Parser::_parse_kw_else()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwElse);
	return true;
}
bool Parser::_parse_kw_for()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwFor);
	return true;
}
bool Parser::_parse_kw_generate()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwGenerate);
	return true;
}
bool Parser::_parse_kw_package()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPackage);
	return true;
}
bool Parser::_parse_kw_proc()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwProc);
	return true;
}
bool Parser::_parse_kw_func()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwFunc);
	return true;
}
bool Parser::_parse_kw_task()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwTask);
	return true;
}
bool Parser::_parse_kw_module()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwModule);
	return true;
}
bool Parser::_parse_kw_const()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwConst);
	return true;
}
bool Parser::_parse_kw_using()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUsing);
	return true;
}
bool Parser::_parse_kw_while()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwWhile);
	return true;
}
bool Parser::_parse_kw_switch()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwitch);
	return true;
}
bool Parser::_parse_kw_switchz()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwitchz);
	return true;
}
bool Parser::_parse_kw_case()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwCase);
	return true;
}
bool Parser::_parse_kw_default()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwDefault);
	return true;
}
bool Parser::_parse_kw_packed()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPacked);
	return true;
}
bool Parser::_parse_kw_class()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwClass);
	return true;
}
bool Parser::_parse_kw_virtual()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwVirtual);
	return true;
}
bool Parser::_parse_kw_extends()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwExtends);
	return true;
}
bool Parser::_parse_kw_public()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPublic);
	return true;
}
bool Parser::_parse_kw_protected()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwProtected);
	return true;
}
bool Parser::_parse_kw_private()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPrivate);
	return true;
}
bool Parser::_parse_kw_enum()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwEnum);
	return true;
}
bool Parser::_parse_kw_assign()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAssign);
	return true;
}
bool Parser::_parse_kw_initial()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInitial);
	return true;
}
bool Parser::_parse_kw_always_comb()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysComb);
	return true;
}
bool Parser::_parse_kw_always_blk()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysBlk);
	return true;
}
bool Parser::_parse_kw_always_ff()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysFf);
	return true;
}
bool Parser::_parse_kw_posedge()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPosedge);
	return true;
}
bool Parser::_parse_kw_negedge()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwNegedge);
	return true;
}
bool Parser::_parse_kw_inst()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInst);
	return true;
}
bool Parser::_parse_kw_input()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInput);
	return true;
}
bool Parser::_parse_kw_output()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwOutput);
	return true;
}
bool Parser::_parse_kw_bidir()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwBidir);
	return true;
}
bool Parser::_parse_kw_type()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwType);
	return true;
}
bool Parser::_parse_kw_uwire()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUwire);
	return true;
}
bool Parser::_parse_kw_swire()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwire);
	return true;
}
bool Parser::_parse_kw_ubit()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUbit);
	return true;
}
bool Parser::_parse_kw_sbit()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSbit);
	return true;
}
bool Parser::_parse_kw_void()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwVoid);
	return true;
}
bool Parser::_parse_kw_auto()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAuto);
	return true;
}
bool Parser::_parse_kw_ubyte()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUbyte);
	return true;
}
bool Parser::_parse_kw_sbyte()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSbyte);
	return true;
}
bool Parser::_parse_kw_ushortint()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUshortint);
	return true;
}
bool Parser::_parse_kw_sshortint()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSshortint);
	return true;
}
bool Parser::_parse_kw_uint()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUint);
	return true;
}
bool Parser::_parse_kw_sint()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSint);
	return true;
}
bool Parser::_parse_kw_ulongint()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUlongint);
	return true;
}
bool Parser::_parse_kw_slongint()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSlongint);
	return true;
}
bool Parser::_parse_kw_typeof()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwTypeof);
	return true;
}

bool Parser::_parse_punct_lparen()
{
	CHECK_PREFIXED_ONE_TOK(Tok::LParen);
	return true;
}
bool Parser::_parse_punct_rparen()
{
	CHECK_PREFIXED_ONE_TOK(Tok::RParen);
	return true;
}
bool Parser::_parse_punct_lbracket()
{
	CHECK_PREFIXED_ONE_TOK(Tok::LBracket);
	return true;
}
bool Parser::_parse_punct_rbracket()
{
	CHECK_PREFIXED_ONE_TOK(Tok::RBracket);
	return true;
}
bool Parser::_parse_punct_lbrace()
{
	CHECK_PREFIXED_ONE_TOK(Tok::LBrace);
	return true;
}
bool Parser::_parse_punct_rbrace()
{
	CHECK_PREFIXED_ONE_TOK(Tok::RBrace);
	return true;
}
bool Parser::_parse_punct_comma()
{
	CHECK_PREFIXED_ONE_TOK(Tok::Comma);
	return true;
}
bool Parser::_parse_punct_semicolon()
{
	CHECK_PREFIXED_ONE_TOK(Tok::Semicolon);
	return true;
}
bool Parser::_parse_punct_colon()
{
	CHECK_PREFIXED_ONE_TOK(Tok::Colon);
	return true;
}
bool Parser::_parse_punct_assign()
{
	CHECK_PREFIXED_ONE_TOK(Tok::Assign);
	return true;
}
bool Parser::_parse_punct_member_access()
{
	CHECK_PREFIXED_ONE_TOK(Tok::MemberAccess);
	return true;
}
bool Parser::_parse_punct_scope_access()
{
	CHECK_PREFIXED_ONE_TOK(Tok::ScopeAccess);
	return true;
}

bool Parser::_parse_header_if()
{
	//CHECK_PREFIXED_ONE_TOK(Tok::KwIf);

	//_expect(Tok::LParen);
	//_parse_expr();
	//_expect(Tok::RParen);

	return true;
}
bool Parser::_parse_header_else_if()
{
	return true;
}
bool Parser::_parse_header_else()
{
	return true;
}
bool Parser::_parse_header_for()
{
	return true;
}

bool Parser::_parse_header_generate_if()
{
	return true;
}
bool Parser::_parse_header_else_generate_if()
{
	return true;
}
bool Parser::_parse_header_else_generate()
{
	return true;
}
bool Parser::_parse_header_generate_for()
{
	return true;
}

bool Parser::_parse_package()
{
	//CHECK_PREFIXED_ONE_TOK(Tok::KwPackage);
	//const auto src_code_chunk = _lexer().src_code_chunk();

	//auto ident = _get_req_parse(fp(_parse_ident));
	//auto scope = _get_req_parse(fp(_parse_scope_package));
	//_push_ast_child(NodePackage(src_code_chunk, move(ident), move(scope)));

	return true;
}
bool Parser::_parse_scope_package()
{
	//CHECK_PREFIXED_ONE_TOK(Tok::LBrace);

	//NodeScopePackage to_push(_lexer().src_code_chunk());

	//while (_opt_parse(fp(_parse_generate_package),
	//	fp(_parse_package), fp(_parse_module), fp(_parse_const),
	//	fp(_parse_using), fp(_parse_decl_callable),
	//	fp(_parse_decl_cstm_type)))
	//{
	//	to_push.append(_pop_ast_child());
	//}
	//_push_ast_child(move(to_push));

	//_expect(Tok::RBrace);

	return true;
}

bool Parser::_parse_generate_package()
{
	RUN_ONE_FUNC(FuncVec({fp(_parse_generate_package_if),
		fp(_parse_generate_package_for)}));

	return true;
}
bool Parser::_parse_generate_package_if()
{
	return _parse_generate_any_if(fp(_parse_scope_package));
}
bool Parser::_parse_generate_package_for()
{
	return _parse_generate_any_for(fp(_parse_scope_package));
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
bool Parser::_parse_kw_port()
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
bool Parser::_parse_op_logical()
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
bool Parser::_parse_op_compare()
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
bool Parser::_parse_op_plus_minus()
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
bool Parser::_parse_op_mul_div_mod_etc()
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
bool Parser::_parse_op_unary()
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
bool Parser::_parse_expr_pre_dollar_func()
{
	return true;
}
bool Parser::_parse_expr_post_dollar_func()
{
	return true;
}
bool Parser::_parse_dollar_func_of_one()
{
	return true;
}

bool Parser::_parse_ident_etc()
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
bool Parser::_parse_ident_scope_access()
{
	return true;;
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
bool Parser::_parse_ident_param_member_overloaded_call()
{
	return true;
}
bool Parser::_parse_ident_param_scope_overloaded_call()
{
	return true;
}

//bool Parser::_parse_generate_any_if(bool (Parser::* parse_scope_func)())
//{
//	RUN_ONE_FUNC(fp(_parse_header_generate_if));
//
//	NodeStmtGenerateIf to_push(_lexer().src_code_chunk(), _pop_ast_child(),
//		Child(nullptr), Child(nullptr));
//	NodeBase* which_to_push = &to_push;
//
//	bool found = false;
//	while (_check_parse(fp(_parse_header_else_generate_if)))
//	{
//		_req_parse(fp(_parse_header_else_generate_if));
//
//		found = true;
//	}
//
//	return true;
//}
//bool Parser::_parse_generate_any_for(bool (Parser::* parse_scope_func)())
//{
//	return true;
//}

#undef FUNC_VEC
#undef fp
#undef CHECK_PREFIXED_ONE_TOK
#undef CHECK_PREFIXED_TOK_SEQ
#undef RUN_ONE_FUNC

} // namespace frost_hdl
