#include "parser_class.hpp"

namespace frost_hdl
{
using namespace ast;

Parser::Parser(vector<string>&& s_filename_vec)
	: ParserBase<Lexer>(std::move(s_filename_vec))
{
	_ast_root.reset(new NodeProgram(SrcCodeChunk()));
}
Parser::~Parser()
{
}

#define fp(func) &Parser::_parse_##func
#define runitp(func) _unit_parse(#func, fp(func), false)
#define ounitp(func) _unit_parse(#func, fp(func), true)
#define one_req_seqp(func) _req_seq_parse(runitp(func))
#define one_opt_seqp(func) _opt_seq_parse(ounitp(func))
#define basic_one_opt_parse(func) _one_opt_parse(one_req_seqp(func))

#define check_parse_named(seq, some_req_seq_parse) \
	const auto seq = some_req_seq_parse; \
	if (just_test()) \
	{ \
		return _check_for_just_test(seq); \
	}

#define check_parse_anon(some_req_seq_parse) \
	if (just_test()) \
	{ \
		return _check_for_just_test(some_req_seq_parse); \
	}

#define simple_seq_parse_named(seq, some_req_seq_parse) \
	check_parse_named(seq, some_req_seq_parse) \
	/* const auto first_invalid = seq.first_invalid(); */ \
	/* if (!std::holds_alternative<bool>(first_invalid.one_inst)) */ \
	/* { */ \
	/* 	_unexpected(*first_invalid.parse_ret); */ \
	/* } */ \
	seq.exec(); \

#define simple_seq_parse_anon(some_req_seq_parse) \
	check_parse_anon(some_req_seq_parse) \
	/* const auto first_invalid = some_req_seq_parse.first_invalid(); */ \
	/* if (!std::holds_alternative<bool>(first_invalid.one_inst)) */ \
	/* { */ \
	/* 	_unexpected(*first_invalid.parse_ret); */ \
	/* } */ \
	some_req_seq_parse.exec(); \

//using FuncVec = vector<decltype(fp(parse_program))>;
using std::move;
using Child = ast::NodeBase::Child;

auto Parser::parse_program() -> ParseRet
{
	//const FuncVec func_vec({fp(_parse_package), fp(_parse_module)});

	//while (_opt_parse(this, func_vec))
	//{
	//	_ast_root->append(move(_pop_ast_child()));
	//}

	//check_parse_named(seq, _opt_or_parse(runitp(package),
	//	runitp(module)));

	auto ret = _dup_lex_state();

	const auto seq = _opt_or_parse(runitp(package),
		runitp(module));

	while (seq.check())
	{
		seq.exec();
		_ast_root->append(_pop_ast_child());
	}

	return ret;
}

#define CHECK_PREFIXED_ONE_TOK(one_tok) \
	if (just_test()) \
	{ \
		if (_check_prefixed_tok_seq(one_tok)) \
		{ \
			return _dup_lex_state(); \
		} \
		else \
		{ \
			return ParseRet(nullptr); \
		} \
	} \
	auto ret = _dup_lex_state(); \
	_expect(one_tok); \
	return ret

#define CHECK_PREFIXED_TOK_SEQ(left, right) \
	if (just_test()) \
	{ \
		if (_check_prefixed_tok_seq(left, right)) \
		{ \
			return _dup_lex_state(); \
		} \
		else \
		{ \
			return ParseRet(nullptr); \
		} \
	} \
	auto ret = _dup_lex_state(); \
	_check_prefixed_tok_seq(left, right); \
	_next_lss_tokens(); \
	return ret

auto Parser::_parse_kw_if() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwIf);
}
auto Parser::_parse_kw_else() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwElse);
}
auto Parser::_parse_kw_for() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwFor);
}
auto Parser::_parse_kw_generate() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwGenerate);
}
auto Parser::_parse_kw_package() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPackage);
}
auto Parser::_parse_kw_port() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPort);
}
auto Parser::_parse_kw_proc() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwProc);
}
auto Parser::_parse_kw_func() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwFunc);
}
auto Parser::_parse_kw_task() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwTask);
}
auto Parser::_parse_kw_module() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwModule);
}
auto Parser::_parse_kw_const() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwConst);
}
auto Parser::_parse_kw_using() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUsing);
}
auto Parser::_parse_kw_while() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwWhile);
}
auto Parser::_parse_kw_switch() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwitch);
}
auto Parser::_parse_kw_switchz() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwitchz);
}
auto Parser::_parse_kw_case() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwCase);
}
auto Parser::_parse_kw_default() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwDefault);
}
auto Parser::_parse_kw_packed() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPacked);
}
auto Parser::_parse_kw_class() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwClass);
}
auto Parser::_parse_kw_virtual() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwVirtual);
}
auto Parser::_parse_kw_extends() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwExtends);
}
auto Parser::_parse_kw_public() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPublic);
}
auto Parser::_parse_kw_protected() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwProtected);
}
auto Parser::_parse_kw_private() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPrivate);
}
auto Parser::_parse_kw_enum() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwEnum);
}
auto Parser::_parse_kw_assign() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAssign);
}
auto Parser::_parse_kw_initial() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInitial);
}
auto Parser::_parse_kw_always_comb() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysComb);
}
auto Parser::_parse_kw_always_blk() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysBlk);
}
auto Parser::_parse_kw_always_ff() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysFf);
}
auto Parser::_parse_kw_posedge() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPosedge);
}
auto Parser::_parse_kw_negedge() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwNegedge);
}
auto Parser::_parse_kw_inst() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInst);
}
auto Parser::_parse_kw_input() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInput);
}
auto Parser::_parse_kw_output() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwOutput);
}
auto Parser::_parse_kw_bidir() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwBidir);
}
auto Parser::_parse_kw_type() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwType);
}
auto Parser::_parse_kw_uwire() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUwire);
}
auto Parser::_parse_kw_swire() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwire);
}
auto Parser::_parse_kw_ubit() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUbit);
}
auto Parser::_parse_kw_sbit() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSbit);
}
auto Parser::_parse_kw_void() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwVoid);
}
auto Parser::_parse_kw_auto() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAuto);
}
auto Parser::_parse_kw_ubyte() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUbyte);
}
auto Parser::_parse_kw_sbyte() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSbyte);
}
auto Parser::_parse_kw_ushortint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUshortint);
}
auto Parser::_parse_kw_sshortint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSshortint);
}
auto Parser::_parse_kw_uint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUint);
}
auto Parser::_parse_kw_sint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSint);
}
auto Parser::_parse_kw_ulongint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUlongint);
}
auto Parser::_parse_kw_slongint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSlongint);
}
auto Parser::_parse_kw_typeof() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwTypeof);
}

auto Parser::_parse_punct_lparen() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::LParen);
}
auto Parser::_parse_punct_rparen() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::RParen);
}
auto Parser::_parse_punct_lbracket() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::LBracket);
}
auto Parser::_parse_punct_rbracket() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::RBracket);
}
auto Parser::_parse_punct_lbrace() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::LBrace);
}
auto Parser::_parse_punct_rbrace() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::RBrace);
}
auto Parser::_parse_punct_comma() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::Comma);
}
auto Parser::_parse_punct_semicolon() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::Semicolon);
}
auto Parser::_parse_punct_colon() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::Colon);
}
auto Parser::_parse_punct_assign() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::Assign);
}
auto Parser::_parse_punct_member_access() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::MemberAccess);
}
auto Parser::_parse_punct_scope_access() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::ScopeAccess);
}

auto Parser::_parse_header_if() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(runitp(kw_if),
		runitp(punct_lparen), runitp(expr), runitp(punct_rparen)));
	return ret;
}
auto Parser::_parse_header_else_if() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(runitp(kw_else),
		runitp(header_if)))
	return ret;
}
auto Parser::_parse_header_else() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(runitp(kw_else)));
	return ret;
}
auto Parser::_parse_header_for() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(runitp(kw_for),
		runitp(punct_lparen), runitp(ident), runitp(punct_colon),
		runitp(expr), runitp(punct_rparen)))
	return ret;
}

auto Parser::_parse_header_generate_if() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(runitp(kw_generate),
		runitp(header_if)))
	return ret;
}
auto Parser::_parse_header_else_generate_if() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(runitp(kw_else),
		runitp(header_generate_if)))
	return ret;
}
auto Parser::_parse_header_else_generate() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(runitp(kw_else),
		runitp(kw_generate)))
	return ret;
}
auto Parser::_parse_header_generate_for() -> ParseRet
{
	auto ret = _dup_lex_state();
	check_parse_anon(_req_seq_parse(runitp(kw_generate), ounitp(ident),
		runitp(header_for)))
	
	one_req_seqp(kw_generate).exec();
	_push_num(basic_one_opt_parse(ident));
	one_req_seqp(header_for).exec();

	return ret;
}

auto Parser::_parse_package() -> ParseRet
{
	//CHECK_PREFIXED_ONE_TOK(Tok::KwPackage);
	//const auto src_code_chunk = _lexer().src_code_chunk();

	auto ret = _dup_lex_state();

	check_parse_named(check_seq, one_req_seqp(kw_package))
	check_seq.exec();

	auto ident = _get_req_parse(fp(ident));
	auto scope = _get_req_parse(fp(scope_package));
	_push_ast_child(NodePackage(_ls_src_code_chunk(ret), move(ident),
		move(scope)));
	return ret;

}
auto Parser::_parse_scope_package() -> ParseRet
{
	return _parse_any_scope<NodeScopePackage>("package",
		_req_or_parse(runitp(generate_package),
		runitp(package), runitp(module), runitp(const), runitp(using),
		runitp(decl_callable), runitp(decl_cstm_type)));
}

auto Parser::_parse_generate_package() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_or_parse(runitp(generate_package_if),
		runitp(generate_package_for)))
	return ret;
}
auto Parser::_parse_generate_package_if() -> ParseRet
{
	return _parse_generate_any_if("scope_package", fp(scope_package));
}
auto Parser::_parse_generate_package_for() -> ParseRet
{
	return _parse_generate_any_for("scope_package", fp(scope_package));
}

auto Parser::_parse_callable_member_prefix() -> ParseRet
{
	auto ret = _dup_lex_state();

	const auto vec = _next_n_tokens(3, false);

	TokSet found_set;

	const TokSet search_set({Tok::KwConst, Tok::KwVirtual, Tok::KwStatic});

	for (size_t i=0; i<vec.size(); ++i)
	{
		if (search_set.count(vec.at(i).tok()))
		{
			if (found_set.count(vec.at(i).tok()))
			{
				_lexer().src_code_chunk(ret.get()).err(sconcat
					("Duplicate callable member prefix \"",
					tok_ident_map.at(vec.at(i).tok()), "\""));
			}
			found_set.insert(vec.at(i).tok());
		}
		else
		{
			break;
		}
	}

	if (just_test())
	{
		if (found_set.size() != 0)
		{
			return ret;
		}
		else
		{
			return ParseRet(nullptr);
		}
	}

	_next_n_tokens(found_set.size(), true);
	for (const auto& iter : found_set)
	{
		_push_tok(iter);
	}
	_push_num(found_set.size());

	return ret;
}

auto Parser::_parse_contents_modproc() -> ParseRet
{
	auto ret = _dup_lex_state();

	const auto opt_seq = one_opt_seqp(param_list);
	const auto req_seq = _req_seq_parse(runitp(arg_list),
		runitp(scope_modproc));

	check_parse_anon(_req_seq_parse(opt_seq, req_seq))

	_push_num(_one_opt_parse(opt_seq));
	req_seq.exec();

	return ret;
}
auto Parser::_parse_proc() -> ParseRet
{
	auto ret = _dup_lex_state();

	check_parse_named(start_seq, one_req_seqp(kw_proc))
	start_seq.exec();

	//const auto or_seq = _req_or_parse(runitp(ident), runitp(kw_port),
	//	runitp(const_str));

	Child s_ident_or_op(nullptr);
	bool s_is_port = false;

	if (const auto seq_ident = one_req_seqp(ident); seq_ident.check())
	{
		s_ident_or_op = _pexec(seq_ident);
	}
	else if (const auto seq_port = one_req_seqp(kw_port); seq_port.check())
	{
		seq_port.exec();
		s_is_port = true;
	}
	else if (const auto seq_const_str = one_req_seqp(const_str);
		seq_const_str.check())
	{
		s_ident_or_op = _pexec(seq_const_str);
	}

	one_req_seqp(contents_modproc).exec();

	auto s_stmt_list = _pop_ast_child();
	auto s_arg_list = _pop_ast_child();

	Child s_param_list;

	if (_pop_num())
	{
		s_param_list = _pop_ast_child();
	}

	_push_ast_child(NodeDeclProc(_ls_src_code_chunk(ret), s_is_port,
		move(s_param_list), move(s_arg_list), move(s_ident_or_op),
		move(s_stmt_list)));
	return ret;
}
auto Parser::_parse_module() -> ParseRet
{
	auto ret = _dup_lex_state();

	check_parse_named(seq, _req_seq_parse(runitp(kw_module),
		runitp(ident), runitp(contents_modproc)))
	seq.exec();

	auto s_scope = _pop_ast_child();
	auto s_port_list = _pop_ast_child();

	Child s_param_list;

	if (_pop_num())
	{
		s_param_list = _pop_ast_child();
	}

	auto s_ident = _pop_ast_child();

	_push_ast_child(NodeModule(_ls_src_code_chunk(ret), move(s_ident),
		move(s_param_list), move(s_port_list), move(s_scope)));
	return ret;
}

auto Parser::_parse_scope_modproc() -> ParseRet
{
	return _parse_any_scope<NodeScopeModproc>("scope_modproc",
		_req_seq_parse(runitp(generate_modproc), runitp(module),
		runitp(const), runitp(var), runitp(using), runitp(decl_callable),
		runitp(decl_cstm_type), runitp(hardware_block)));
}
auto Parser::_parse_generate_modproc() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_or_parse(runitp(generate_modproc_if),
		runitp(generate_modproc_for)))
	return ret;
}
auto Parser::_parse_generate_modproc_if() -> ParseRet
{
	return _parse_generate_any_if("scope_modproc", fp(scope_modproc));
}
auto Parser::_parse_generate_modproc_for() -> ParseRet
{
	return _parse_generate_any_for("scope_package", fp(scope_package));
}

auto Parser::_parse_decl_callable() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_or_parse(runitp(func), runitp(task),
		runitp(proc)))
	return ret;
}
auto Parser::_parse_contents_func_task() -> ParseRet
{
	auto ret = _dup_lex_state();

	const auto opt_seq = one_opt_seqp(param_list);
	const auto req_seq = _req_seq_parse(runitp(arg_list),
		runitp(scope_behav));

	check_parse_anon(_req_seq_parse(opt_seq, req_seq))

	_push_num(_one_opt_parse(opt_seq));
	req_seq.exec();

	return ret;
}
auto Parser::_parse_func() -> ParseRet
{
	auto ret = _dup_lex_state();

	simple_seq_parse_anon(one_req_seqp(kw_func))

	auto s_the_typename = _pexec(one_req_seqp(typename));
	auto s_ident_or_op = _pexec(_req_or_parse(runitp(ident),
		runitp(const_str)));

	one_req_seqp(contents_func_task).exec();
	auto s_stmt_list = _pop_ast_child();
	auto s_arg_list = _pop_ast_child();

	Child s_param_list;

	if (_pop_num())
	{
		s_param_list = _pop_ast_child();
	}

	_push_ast_child(NodeDeclFunc(_ls_src_code_chunk(ret),
		move(s_the_typename), move(s_param_list), move(s_arg_list),
		move(s_ident_or_op), move(s_stmt_list)));
	return ret;
}
auto Parser::_parse_task() -> ParseRet
{
	auto ret = _dup_lex_state();

	simple_seq_parse_anon(one_req_seqp(kw_task))

	auto s_ident_or_op = _pexec(_req_or_parse(runitp(ident),
		runitp(const_str)));

	one_req_seqp(contents_func_task).exec();
	auto s_stmt_list = _pop_ast_child();
	auto s_arg_list = _pop_ast_child();

	Child s_param_list;

	if (_pop_num())
	{
		s_param_list = _pop_ast_child();
	}

	_push_ast_child(NodeDeclTask(_ls_src_code_chunk(ret),
		move(s_param_list), move(s_arg_list), move(s_ident_or_op),
		move(s_stmt_list)));
	return ret;
}

auto Parser::_parse_scope_behav() -> ParseRet
{
	return _parse_any_scope<NodeScopeBehav>("behavioral",
		one_req_seqp(inner_scope_behav));
}
auto Parser::_parse_inner_scope_behav() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_or_parse(runitp(generate_behav),
		runitp(const), runitp(var), runitp(using), runitp(stmt_assign),
		runitp(stmt_if), runitp(stmt_for), runitp(stmt_while),
		runitp(stmt_switch), runitp(stmt_switchz), runitp(ident_etc),
		runitp(decl_cstm_type), runitp(scope_behav)))
	return ret;
}

auto Parser::_parse_generate_behav() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_or_parse(runitp(generate_behav_if),
		runitp(generate_behav_for)))
	return ret;
}
auto Parser::_parse_generate_behav_if() -> ParseRet
{
	return _parse_generate_any_if("scope_behav", fp(scope_behav));
}
auto Parser::_parse_generate_behav_for() -> ParseRet
{
	return _parse_generate_any_for("scope_behav", fp(scope_behav));
}

auto Parser::_parse_const() -> ParseRet
{
	auto ret = _dup_lex_state();

	simple_seq_parse_anon(one_req_seqp(kw_const))

	Child s_the_typename;

	if (_one_opt_parse(one_req_seqp(typename)))
	{
		s_the_typename = _pop_ast_child();
	}

	NodeIdentTermAndExtraList s_ident_term_and_extra_list
		(_ls_src_code_chunk(_dup_lex_state()));

	const auto list_seq = one_req_seqp(one_const);
	s_ident_term_and_extra_list.append(_pexec(list_seq));

	_partial_parse_any_list(s_ident_term_and_extra_list,
		_req_seq_parse(runitp(punct_comma), list_seq));

	one_req_seqp(punct_semicolon).exec();

	_push_ast_child(NodeDeclConstList(_ls_src_code_chunk(ret),
		move(s_the_typename),
		_to_ast_child(move(s_ident_term_and_extra_list))));

	return ret;
}
auto Parser::_parse_one_const() -> ParseRet
{
	auto ret = _dup_lex_state();

	simple_seq_parse_anon(_req_seq_parse(runitp(ident_terminal),
		runitp(punct_assign), runitp(expr)))
	
	auto s_expr_or_arg_inst_list = _pop_ast_child();
	auto s_ident_terminal = _pop_ast_child();

	_push_ast_child(NodeIdentTermAndExtra(_ls_src_code_chunk(ret),
		move(s_ident_terminal), move(s_expr_or_arg_inst_list)));

	return ret;
}
auto Parser::_parse_var() -> ParseRet
{
	auto ret = _dup_lex_state();

	auto s_the_typename = _pexec(one_req_seqp(typename));

	NodeIdentTermAndExtraList s_ident_term_and_extra_list
		(_ls_src_code_chunk(_dup_lex_state()));

	const auto list_seq = one_req_seqp(one_var);
	s_ident_term_and_extra_list.append(_pexec(list_seq));

	_partial_parse_any_list(s_ident_term_and_extra_list,
		_req_seq_parse(runitp(punct_comma), list_seq));

	one_req_seqp(punct_semicolon).exec();

	_push_ast_child(NodeDeclVarList(_ls_src_code_chunk(ret),
		move(s_the_typename),
		_to_ast_child(move(s_ident_term_and_extra_list))));

	return ret;
}
auto Parser::_parse_one_var() -> ParseRet
{
	auto ret = _dup_lex_state();

	simple_seq_parse_anon(_req_seq_parse(runitp(ident_terminal),
		runitp(punct_assign), runitp(expr)))
	
	auto s_expr_or_arg_inst_list = _pop_ast_child();
	auto s_ident_terminal = _pop_ast_child();

	_push_ast_child(NodeIdentTermAndExtra(_ls_src_code_chunk(ret),
		move(s_ident_terminal), move(s_expr_or_arg_inst_list)));

	return ret;
}
auto Parser::_parse_using() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_stmt_assign() -> ParseRet
{
}
auto Parser::_parse_stmt_if() -> ParseRet
{
	auto ret = _dup_lex_state();
	check_parse_named(to_check, one_req_seqp(header_if))

	NodeStmtIf to_push(_ls_src_code_chunk(ret),
		_pexec(to_check), Child(nullptr), Child(nullptr));

	NodeStmtIf* top = &to_push;

	const auto parse_scope_seq = one_req_seqp(header_if);

	to_push.set_stmt_list(_pexec(parse_scope_seq));

	const auto seq_else_if = one_req_seqp(header_else_if);

	while (seq_else_if.check())
	{
		auto temp = _dup_lex_state();
		auto cond_expr = _pexec(seq_else_if);

		auto stmt_list = _pexec(parse_scope_seq);

		NodeStmtIf next_to_push(_ls_src_code_chunk(temp),
			move(cond_expr), move(stmt_list), Child(nullptr));
		top->set_stmt_else(Child(new NodeStmtIf(move(next_to_push))));
		top = static_cast<NodeStmtIf*>(top->stmt_else().get());
	}

	const auto seq_else = one_req_seqp(header_else_generate);

	if (seq_else.check())
	{
		seq_else.exec();
		top->set_stmt_else(_pexec(parse_scope_seq));
	}

	_push_ast_child(move(to_push));

	return ret;
}
auto Parser::_parse_stmt_for() -> ParseRet
{
}
auto Parser::_parse_stmt_while() -> ParseRet
{
}
auto Parser::_parse_stmt_switch() -> ParseRet
{
}
auto Parser::_parse_stmt_switchz() -> ParseRet
{
}
auto Parser::_parse_scope_switch() -> ParseRet
{
}

auto Parser::_parse_decl_cstm_type() -> ParseRet
{
}
auto Parser::_parse_class() -> ParseRet
{
}
auto Parser::_parse_extends() -> ParseRet
{
}

auto Parser::_parse_scope_class() -> ParseRet
{
}
auto Parser::_parse_callable_member() -> ParseRet
{
}
auto Parser::_parse_generate_class() -> ParseRet
{
}
auto Parser::_parse_generate_class_if() -> ParseRet
{
}
auto Parser::_parse_generate_class_for() -> ParseRet
{
}
auto Parser::_parse_member_access_label() -> ParseRet
{
}

auto Parser::_parse_enum() -> ParseRet
{
}

auto Parser::_parse_hardware_block() -> ParseRet
{
}
auto Parser::_parse_cont_assign() -> ParseRet
{
}
auto Parser::_parse_initial() -> ParseRet
{
}
auto Parser::_parse_always_comb() -> ParseRet
{
}
auto Parser::_parse_always_blk() -> ParseRet
{
}
auto Parser::_parse_always_ff() -> ParseRet
{
}
auto Parser::_parse_edge_list() -> ParseRet
{
}
auto Parser::_parse_posedge_inst() -> ParseRet
{
}
auto Parser::_parse_negedge_inst() -> ParseRet
{
}

auto Parser::_parse_inst() -> ParseRet
{
}

auto Parser::_parse_param_list() -> ParseRet
{
}
auto Parser::_parse_param_sublist() -> ParseRet
{
}
auto Parser::_parse_arg_list() -> ParseRet
{
}
auto Parser::_parse_arg_sublist() -> ParseRet
{
}
auto Parser::_parse_arg_port_sublist() -> ParseRet
{
}
auto Parser::_parse_pararg_var_sublist() -> ParseRet
{
}
auto Parser::_parse_pararg_type_sublist() -> ParseRet
{
}
auto Parser::_parse_param_module_sublist() -> ParseRet
{
}
auto Parser::_parse_ident_equals_typename_sublist() -> ParseRet
{
}
auto Parser::_parse_param_inst_list() -> ParseRet
{
}

auto Parser::_parse_pos_pararg_inst_list() -> ParseRet
{
}
auto Parser::_parse_named_pararg_inst_list() -> ParseRet
{
}

auto Parser::_parse_typename() -> ParseRet
{
}
auto Parser::_parse_param_possible_typename() -> ParseRet
{
}
auto Parser::_parse_no_param_possible_typename() -> ParseRet
{
}
auto Parser::_parse_typeof() -> ParseRet
{
}

auto Parser::_parse_expr() -> ParseRet
{
}
auto Parser::_parse_inner_expr() -> ParseRet
{
}
auto Parser::_parse_op_logical() -> ParseRet
{
}

auto Parser::_parse_expr_logical() -> ParseRet
{
}
auto Parser::_parse_inner_expr_logical() -> ParseRet
{
}
auto Parser::_parse_op_compare() -> ParseRet
{
}

auto Parser::_parse_expr_compare() -> ParseRet
{
}
auto Parser::_parse_inner_expr_compare() -> ParseRet
{
}
auto Parser::_parse_op_plus_minus() -> ParseRet
{
}

auto Parser::_parse_expr_add_sub() -> ParseRet
{
}
auto Parser::_parse_inner_expr_add_sub() -> ParseRet
{
}
auto Parser::_parse_op_mul_div_mod_etc() -> ParseRet
{
}

auto Parser::_parse_expr_mul_div_mod_etc() -> ParseRet
{
}
auto Parser::_parse_inner_expr_mul_div_mod_etc() -> ParseRet
{
}
auto Parser::_parse_op_unary() -> ParseRet
{
}

auto Parser::_parse_dollar_global_clock() -> ParseRet
{
}
auto Parser::_parse_dollar_pow_expr() -> ParseRet
{
}
auto Parser::_parse_const_str() -> ParseRet
{
}
auto Parser::_parse_expr_pre_dollar_func() -> ParseRet
{
}
auto Parser::_parse_expr_post_dollar_func() -> ParseRet
{
}
auto Parser::_parse_dollar_func_of_one() -> ParseRet
{
}

auto Parser::_parse_ident_etc() -> ParseRet
{
}
auto Parser::_parse_ident_terminal() -> ParseRet
{
}
auto Parser::_parse_ident_member_access() -> ParseRet
{
}
auto Parser::_parse_ident_scope_access() -> ParseRet
{
}
auto Parser::_parse_ident() -> ParseRet
{
}
auto Parser::_parse_ident_bracket() -> ParseRet
{
}
auto Parser::_parse_ident_call() -> ParseRet
{
}
auto Parser::_parse_ident_no_param_overloaded_call() -> ParseRet
{
}
auto Parser::_parse_ident_param_member_overloaded_call() -> ParseRet
{
}
auto Parser::_parse_ident_param_scope_overloaded_call() -> ParseRet
{
}

auto Parser::_parse_generate_any_if(const string& parse_scope_func_str,
	ParseFunc parse_scope_func) -> ParseRet
{
	auto ret = _dup_lex_state();
	check_parse_named(to_check, _req_seq_parse(runitp(header_generate_if)))

	NodeStmtGenerateIf to_push(_ls_src_code_chunk(ret),
		_pexec(to_check), Child(nullptr), Child(nullptr));

	NodeStmtGenerateIf* top = &to_push;

	const auto parse_scope_seq = _req_seq_parse(_unit_parse
		(parse_scope_func_str, parse_scope_func));

	to_push.set_stmt_list(_pexec(parse_scope_seq));

	const auto seq_else_if = _req_seq_parse
		(runitp(header_else_generate_if));

	while (seq_else_if.check())
	{
		auto temp = _dup_lex_state();
		auto cond_expr = _pexec(seq_else_if);

		auto stmt_list = _pexec(parse_scope_seq);

		NodeStmtGenerateIf next_to_push(_ls_src_code_chunk(temp),
			move(cond_expr), move(stmt_list), Child(nullptr));
		top->set_stmt_else(Child
			(new NodeStmtGenerateIf(move(next_to_push))));
		top = static_cast<NodeStmtGenerateIf*>(top->stmt_else().get());
	}

	const auto seq_else = _req_seq_parse(runitp(header_else_generate));

	if (seq_else.check())
	{
		seq_else.exec();
		top->set_stmt_else(_pexec(parse_scope_seq));
	}

	_push_ast_child(move(to_push));

	return ret;
}

auto Parser::_parse_generate_any_for(const string& parse_scope_func_str,
	ParseFunc parse_scope_func) -> ParseRet
{
	auto ret = _dup_lex_state();

	check_parse_named(to_check, one_req_seqp(header_generate_for))

	to_check.exec();

	auto s_items = _pop_ast_child();
	auto s_var = _pop_ast_child();

	Child s_label(nullptr);

	// Check for ident
	if (_pop_num())
	{
		s_label = _pop_ast_child();
	}

	auto s_stmt_list = _pexec(_req_seq_parse(_unit_parse
		(parse_scope_func_str, parse_scope_func)));

	_push_ast_child(NodeStmtGenerateFor(_ls_src_code_chunk(ret),
		move(s_label), move(s_var), move(s_items), move(s_stmt_list)));

	return ret;
}

template<typename AstNodeScopeType>
auto Parser::_parse_any_scope(const string& scope_type_str,
	const TheSeqParse& list_seq) -> ParseRet
{
	auto ret = _dup_lex_state();
	AstNodeScopeType to_push(_lexer().src_code_chunk());

	const auto check_seq = one_req_seqp(punct_lbrace);
	const auto end_seq = one_req_seqp(punct_rbrace);

	check_parse_anon(check_seq)

	check_seq.exec();

	if ((!_partial_parse_any_list(to_push, list_seq))
		&& (!end_seq.check()))
	{
		_lexer().src_code_chunk().err(sconcat("Unknown ", scope_type_str,
			" scope item."));
	}

	if (!end_seq.check())
	{
		_lexer().src_code_chunk().err(sconcat("Unknown ", scope_type_str,
			" scope item."));
	}

	end_seq.exec();
	_push_ast_child(move(to_push));

	return ret;
}


} // namespace frost_hdl
