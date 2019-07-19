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

#define fp(func) &Parser::_parse_##func
#define req_up(func) _unit_parse(fp(func), false)
#define opt_up(func) _unit_parse(fp(func), true)

#define check_parse_named(seq, some_req_seq_parse) \
	const auto seq = some_req_seq_parse; \
	if (just_test()) \
	{ \
		return seq.check(); \
	}
#define check_parse_anon(some_req_seq_parse) \
	if (just_test()) \
	{ \
		return some_req_seq_parse.check(); \
	}
#define simple_parse_named(seq, some_req_seq_parse) \
	check_parse_named(seq, some_req_seq_parse) \
	to_check.exec(); \
	return true;
#define simple_parse_anon(some_req_seq_parse) \
	check_parse_anon(some_req_seq_parse) \
	some_req_seq_parse.exec(); \
	return true;

//using FuncVec = std::vector<decltype(fp(parse_program))>;
using std::move;
using Child = ast::NodeBase::Child;

auto Parser::parse_program() -> ParseRet
{
	//const FuncVec func_vec({fp(_parse_package), fp(_parse_module)});

	//while (_opt_parse(this, func_vec))
	//{
	//	_ast_root->append(move(_pop_ast_child()));
	//}

	//check_parse_named(seq, _opt_or_parse(req_up(package),
	//	req_up(module)));
	const auto seq = _opt_or_parse(req_up(package),
		req_up(module));

	while (seq.check())
	{
		seq.exec();
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

auto Parser::_parse_kw_if() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwIf);
	return true;
}
auto Parser::_parse_kw_else() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwElse);
	return true;
}
auto Parser::_parse_kw_for() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwFor);
	return true;
}
auto Parser::_parse_kw_generate() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwGenerate);
	return true;
}
auto Parser::_parse_kw_package() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPackage);
	return true;
}
auto Parser::_parse_kw_port() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPort);
	return true;
}
auto Parser::_parse_kw_proc() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwProc);
	return true;
}
auto Parser::_parse_kw_func() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwFunc);
	return true;
}
auto Parser::_parse_kw_task() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwTask);
	return true;
}
auto Parser::_parse_kw_module() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwModule);
	return true;
}
auto Parser::_parse_kw_const() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwConst);
	return true;
}
auto Parser::_parse_kw_using() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUsing);
	return true;
}
auto Parser::_parse_kw_while() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwWhile);
	return true;
}
auto Parser::_parse_kw_switch() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwitch);
	return true;
}
auto Parser::_parse_kw_switchz() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwitchz);
	return true;
}
auto Parser::_parse_kw_case() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwCase);
	return true;
}
auto Parser::_parse_kw_default() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwDefault);
	return true;
}
auto Parser::_parse_kw_packed() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPacked);
	return true;
}
auto Parser::_parse_kw_class() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwClass);
	return true;
}
auto Parser::_parse_kw_virtual() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwVirtual);
	return true;
}
auto Parser::_parse_kw_extends() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwExtends);
	return true;
}
auto Parser::_parse_kw_public() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPublic);
	return true;
}
auto Parser::_parse_kw_protected() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwProtected);
	return true;
}
auto Parser::_parse_kw_private() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPrivate);
	return true;
}
auto Parser::_parse_kw_enum() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwEnum);
	return true;
}
auto Parser::_parse_kw_assign() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAssign);
	return true;
}
auto Parser::_parse_kw_initial() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInitial);
	return true;
}
auto Parser::_parse_kw_always_comb() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysComb);
	return true;
}
auto Parser::_parse_kw_always_blk() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysBlk);
	return true;
}
auto Parser::_parse_kw_always_ff() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysFf);
	return true;
}
auto Parser::_parse_kw_posedge() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPosedge);
	return true;
}
auto Parser::_parse_kw_negedge() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwNegedge);
	return true;
}
auto Parser::_parse_kw_inst() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInst);
	return true;
}
auto Parser::_parse_kw_input() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInput);
	return true;
}
auto Parser::_parse_kw_output() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwOutput);
	return true;
}
auto Parser::_parse_kw_bidir() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwBidir);
	return true;
}
auto Parser::_parse_kw_type() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwType);
	return true;
}
auto Parser::_parse_kw_uwire() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUwire);
	return true;
}
auto Parser::_parse_kw_swire() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwire);
	return true;
}
auto Parser::_parse_kw_ubit() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUbit);
	return true;
}
auto Parser::_parse_kw_sbit() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSbit);
	return true;
}
auto Parser::_parse_kw_void() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwVoid);
	return true;
}
auto Parser::_parse_kw_auto() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAuto);
	return true;
}
auto Parser::_parse_kw_ubyte() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUbyte);
	return true;
}
auto Parser::_parse_kw_sbyte() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSbyte);
	return true;
}
auto Parser::_parse_kw_ushortint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUshortint);
	return true;
}
auto Parser::_parse_kw_sshortint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSshortint);
	return true;
}
auto Parser::_parse_kw_uint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUint);
	return true;
}
auto Parser::_parse_kw_sint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSint);
	return true;
}
auto Parser::_parse_kw_ulongint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUlongint);
	return true;
}
auto Parser::_parse_kw_slongint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSlongint);
	return true;
}
auto Parser::_parse_kw_typeof() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwTypeof);
	return true;
}

auto Parser::_parse_punct_lparen() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::LParen);
	return true;
}
auto Parser::_parse_punct_rparen() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::RParen);
	return true;
}
auto Parser::_parse_punct_lbracket() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::LBracket);
	return true;
}
auto Parser::_parse_punct_rbracket() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::RBracket);
	return true;
}
auto Parser::_parse_punct_lbrace() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::LBrace);
	return true;
}
auto Parser::_parse_punct_rbrace() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::RBrace);
	return true;
}
auto Parser::_parse_punct_comma() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::Comma);
	return true;
}
auto Parser::_parse_punct_semicolon() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::Semicolon);
	return true;
}
auto Parser::_parse_punct_colon() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::Colon);
	return true;
}
auto Parser::_parse_punct_assign() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::Assign);
	return true;
}
auto Parser::_parse_punct_member_access() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::MemberAccess);
	return true;
}
auto Parser::_parse_punct_scope_access() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::ScopeAccess);
	return true;
}

auto Parser::_parse_header_if() -> ParseRet
{
	simple_parse_anon(_req_seq_parse(req_up(kw_if),
		req_up(punct_lparen), req_up(expr),
		req_up(punct_rparen)))
}
auto Parser::_parse_header_else_if() -> ParseRet
{
	simple_parse_anon(_req_seq_parse(req_up(kw_else),
		req_up(header_if)))
}
auto Parser::_parse_header_else() -> ParseRet
{
	simple_parse_anon(_req_seq_parse(req_up(kw_else)));
}
auto Parser::_parse_header_for() -> ParseRet
{
	simple_parse_anon(_req_seq_parse(req_up(kw_for),
		req_up(punct_lparen), req_up(ident),
		req_up(punct_colon), req_up(expr),
		req_up(punct_rparen)))
}

auto Parser::_parse_header_generate_if() -> ParseRet
{
	simple_parse_anon(_req_seq_parse(req_up(kw_generate),
		req_up(header_if)))
}
auto Parser::_parse_header_else_generate_if() -> ParseRet
{
	simple_parse_anon(_req_seq_parse(req_up(kw_else),
		req_up(header_generate_if)))
}
auto Parser::_parse_header_else_generate() -> ParseRet
{
	simple_parse_anon(_req_seq_parse(req_up(kw_else),
		req_up(kw_generate)))
}
auto Parser::_parse_header_generate_for() -> ParseRet
{
	check_parse_named(to_check, _req_seq_parse(req_up(kw_generate),
		opt_up(ident), req_up(header_for)))
}

auto Parser::_parse_package() -> ParseRet
{
	//CHECK_PREFIXED_ONE_TOK(Tok::KwPackage);
	//const auto src_code_chunk = _lexer().src_code_chunk();

	if (just_test())
	{
		return req_up(kw_package).check();
	}

	auto ident = _get_req_parse(fp(ident));
	auto scope = _get_req_parse(fp(scope_package));
	_push_ast_child(NodePackage(src_code_chunk, move(ident), move(scope)));

	return true;
}
auto Parser::_parse_scope_package() -> ParseRet
{
	NodeScopePackage to_push(_lexer().src_code_chunk());

	const auto list_seq = _opt_or_parse(req_up(generate_package),
		req_up(package), req_up(module), req_up(const), req_up(using),
		req_up(decl_callable), req_up(decl_cstm_type));
	check_parse_anon(_req_seq_parse(req_up(punct_lbrace), list_seq))

	req_up(punct_lbrace).exec();

	while (list_seq.check())
	{
		list_seq.exec();
		to_push.append(_pop_ast_child());
	}

	const auto end = req_up(punct_rbrace);
	if (!end.check())
	{
		_unexpected();
	}
	end.exec();

	_push_ast_child(move(to_push));

	return true;
}

auto Parser::_parse_generate_package() -> ParseRet
{
	return true;
}
auto Parser::_parse_generate_package_if() -> ParseRet
{
	return true;
}
auto Parser::_parse_generate_package_for() -> ParseRet
{
	return true;
}

auto Parser::_parse_callable_member_prefix() -> ParseRet
{
	return true;
}

auto Parser::_parse_contents_modproc() -> ParseRet
{
	return true;
}
auto Parser::_parse_proc() -> ParseRet
{
	return true;
}
auto Parser::_parse_module() -> ParseRet
{
	return true;
}

auto Parser::_parse_scope_modproc() -> ParseRet
{
	return true;
}
auto Parser::_parse_generate_modproc() -> ParseRet
{
	return true;
}
auto Parser::_parse_generate_modproc_if() -> ParseRet
{
	return true;
}
auto Parser::_parse_generate_modproc_for() -> ParseRet
{
	return true;
}

auto Parser::_parse_decl_callable() -> ParseRet
{
	return true;
}
auto Parser::_parse_contents_func_task() -> ParseRet
{
	return true;
}
auto Parser::_parse_func() -> ParseRet
{
	return true;
}
auto Parser::_parse_task() -> ParseRet
{
	return true;
}

auto Parser::_parse_scope_behav() -> ParseRet
{
	return true;
}
auto Parser::_parse_inner_scope_behav() -> ParseRet
{
	return true;
}

auto Parser::_parse_generate_behav() -> ParseRet
{
	return true;
}
auto Parser::_parse_generate_behav_if() -> ParseRet
{
	return true;
}
auto Parser::_parse_generate_behav_for() -> ParseRet
{
	return true;
}

auto Parser::_parse_const() -> ParseRet
{
	return true;
}
auto Parser::_parse_var() -> ParseRet
{
	return true;
}
auto Parser::_parse_using() -> ParseRet
{
	return true;
}

auto Parser::_parse_stmt_assign() -> ParseRet
{
	return true;
}
auto Parser::_parse_stmt_if() -> ParseRet
{
	return true;
}
auto Parser::_parse_stmt_for() -> ParseRet
{
	return true;
}
auto Parser::_parse_stmt_while() -> ParseRet
{
	return true;
}
auto Parser::_parse_stmt_switch() -> ParseRet
{
	return true;
}
auto Parser::_parse_stmt_switchz() -> ParseRet
{
	return true;
}
auto Parser::_parse_scope_switch() -> ParseRet
{
	return true;
}

auto Parser::_parse_decl_cstm_type() -> ParseRet
{
	return true;
}
auto Parser::_parse_class() -> ParseRet
{
	return true;
}
auto Parser::_parse_extends() -> ParseRet
{
	return true;
}

auto Parser::_parse_scope_class() -> ParseRet
{
	return true;
}
auto Parser::_parse_generate_class() -> ParseRet
{
	return true;
}
auto Parser::_parse_generate_class_if() -> ParseRet
{
	return true;
}
auto Parser::_parse_generate_class_for() -> ParseRet
{
	return true;
}
auto Parser::_parse_member_access_label() -> ParseRet
{
	return true;
}

auto Parser::_parse_enum() -> ParseRet
{
	return true;
}

auto Parser::_parse_hardware_block() -> ParseRet
{
	return true;
}
auto Parser::_parse_cont_assign() -> ParseRet
{
	return true;
}
auto Parser::_parse_initial() -> ParseRet
{
	return true;
}
auto Parser::_parse_always_comb() -> ParseRet
{
	return true;
}
auto Parser::_parse_always_blk() -> ParseRet
{
	return true;
}
auto Parser::_parse_always_ff() -> ParseRet
{
	return true;
}
auto Parser::_parse_edge_list() -> ParseRet
{
	return true;
}
auto Parser::_parse_posedge_inst() -> ParseRet
{
	return true;
}
auto Parser::_parse_negedge_inst() -> ParseRet
{
	return true;
}

auto Parser::_parse_inst() -> ParseRet
{
	return true;
}

auto Parser::_parse_param_list() -> ParseRet
{
	return true;
}
auto Parser::_parse_param_sublist() -> ParseRet
{
	return true;
}
auto Parser::_parse_arg_list() -> ParseRet
{
	return true;
}
auto Parser::_parse_arg_sublist() -> ParseRet
{
	return true;
}
auto Parser::_parse_arg_port_sublist() -> ParseRet
{
	return true;
}
auto Parser::_parse_pararg_var_sublist() -> ParseRet
{
	return true;
}
auto Parser::_parse_pararg_type_sublist() -> ParseRet
{
	return true;
}
auto Parser::_parse_param_module_sublist() -> ParseRet
{
	return true;
}
auto Parser::_parse_ident_equals_typename_sublist() -> ParseRet
{
	return true;
}
auto Parser::_parse_param_inst_list() -> ParseRet
{
	return true;
}

auto Parser::_parse_pos_pararg_inst_list() -> ParseRet
{
	return true;
}
auto Parser::_parse_named_pararg_inst_list() -> ParseRet
{
	return true;
}

auto Parser::_parse_typename() -> ParseRet
{
	return true;
}
auto Parser::_parse_param_possible_typename() -> ParseRet
{
	return true;
}
auto Parser::_parse_no_param_possible_typename() -> ParseRet
{
	return true;
}
auto Parser::_parse_typeof() -> ParseRet
{
	return true;
}

auto Parser::_parse_expr() -> ParseRet
{
	return true;
}
auto Parser::_parse_inner_expr() -> ParseRet
{
	return true;
}
auto Parser::_parse_op_logical() -> ParseRet
{
	return true;
}

auto Parser::_parse_expr_logical() -> ParseRet
{
	return true;
}
auto Parser::_parse_inner_expr_logical() -> ParseRet
{
	return true;
}
auto Parser::_parse_op_compare() -> ParseRet
{
	return true;
}

auto Parser::_parse_expr_compare() -> ParseRet
{
	return true;
}
auto Parser::_parse_inner_expr_compare() -> ParseRet
{
	return true;
}
auto Parser::_parse_op_plus_minus() -> ParseRet
{
	return true;
}

auto Parser::_parse_expr_add_sub() -> ParseRet
{
	return true;
}
auto Parser::_parse_inner_expr_add_sub() -> ParseRet
{
	return true;
}
auto Parser::_parse_op_mul_div_mod_etc() -> ParseRet
{
	return true;
}

auto Parser::_parse_expr_mul_div_mod_etc() -> ParseRet
{
	return true;
}
auto Parser::_parse_inner_expr_mul_div_mod_etc() -> ParseRet
{
	return true;
}
auto Parser::_parse_op_unary() -> ParseRet
{
	return true;
}

auto Parser::_parse_dollar_global_clock() -> ParseRet
{
	return true;
}
auto Parser::_parse_dollar_pow_expr() -> ParseRet
{
	return true;
}
auto Parser::_parse_const_str() -> ParseRet
{
	return true;
}
auto Parser::_parse_expr_pre_dollar_func() -> ParseRet
{
	return true;
}
auto Parser::_parse_expr_post_dollar_func() -> ParseRet
{
	return true;
}
auto Parser::_parse_dollar_func_of_one() -> ParseRet
{
	return true;
}

auto Parser::_parse_ident_etc() -> ParseRet
{
	return true;
}
auto Parser::_parse_ident_terminal() -> ParseRet
{
	return true;
}
auto Parser::_parse_ident_member_access() -> ParseRet
{
	return true;
}
auto Parser::_parse_ident_scope_access() -> ParseRet
{
	return true;;
}
auto Parser::_parse_ident() -> ParseRet
{
	return true;
}
auto Parser::_parse_ident_bracket() -> ParseRet
{
	return true;
}
auto Parser::_parse_ident_call() -> ParseRet
{
	return true;
}
auto Parser::_parse_ident_no_param_overloaded_call() -> ParseRet
{
	return true;
}
auto Parser::_parse_ident_param_member_overloaded_call() -> ParseRet
{
	return true;
}
auto Parser::_parse_ident_param_scope_overloaded_call() -> ParseRet
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
#undef opt_up
#undef req_up
#undef check_parse_named
#undef check_parse_anon
#undef simple_parse_named
#undef simple_parse_anon
#undef CHECK_PREFIXED_ONE_TOK
#undef CHECK_PREFIXED_TOK_SEQ
//#undef RUN_ONE_FUNC

} // namespace frost_hdl
