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
#define named_fp(func) #func, fp(func)
#define rseqp(func) _req_seq_parse(_unit_parse(named_fp(func), false))
#define oseqp(func) _opt_seq_parse(_unit_parse(named_fp(func), false))
#define named_rseqp(func) #func, rseqp(func)
#define named_oseqp(func) #func, oseqp(func)
#define make_msp MapSeqParse map_seq_parse
#define msp(func) map_seq_parse[#func]

#define check_parse_named(seq, some_req_seq_parse) \
	const auto seq = some_req_seq_parse; \
	if (actual_just_test()) \
	{ \
		return seq.check(); \
	}

#define check_parse_anon(some_req_seq_parse) \
	if (actual_just_test()) \
	{ \
		return some_req_seq_parse.check(); \
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

#define simple_seq_parse_if_jp_anon(some_req_seq_parse) \
	check_parse_anon(some_req_seq_parse) \
	if (just_parse()) \
	{ \
		some_req_seq_parse.exec(); \
	}
#define simple_seq_parse_if_jp_named(seq, some_req_seq_parse) \
	check_parse_named(seq, some_req_seq_parse) \
	if (just_parse()) \
	{ \
		seq.exec(); \
	}

//using FuncVec = vector<decltype(fp(parse_program))>;
using std::move;
using Child = ast::NodeBase::Child;

bool Parser::parse_program()
{
	//const FuncVec func_vec({fp(_parse_package), fp(_parse_module)});

	//while (_opt_parse(this, func_vec))
	//{
	//	_ast_root->append(move(_pop_ast_child()));
	//}

	//check_parse_named(seq, _opt_or_parse(rseqp(package),
	//	rseqp(module)));
	TheSeqParse::debug = true;
	TheSeqParse::debug_tok_ident_map = &tok_ident_map;

	auto ret = _dup_lex_state();

	const auto seq = _opt_or_parse(rseqp(package), rseqp(module));

	if (!seq.check())
	{
		_ls_src_code_chunk(ret).err("Invalid program.");
	}
	while (seq.check())
	{
		seq.exec();
		_ast_root->append(_pop_ast_child());
	}

	return true;
}

#define CHECK_PREFIXED_ONE_TOK(one_tok) \
	if (actual_just_test()) \
	{ \
		return (_check_prefixed_tok_seq(one_tok)); \
	} \
	_expect(one_tok); \
	return true

bool Parser::_parse_kw_if()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwIf);
}
bool Parser::_parse_kw_else()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwElse);
}
bool Parser::_parse_kw_for()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwFor);
}
bool Parser::_parse_kw_generate()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwGenerate);
}
bool Parser::_parse_kw_package()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPackage);
}
bool Parser::_parse_kw_port()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPort);
}
bool Parser::_parse_kw_proc()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwProc);
}
bool Parser::_parse_kw_func()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwFunc);
}
bool Parser::_parse_kw_task()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwTask);
}
bool Parser::_parse_kw_module()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwModule);
}
bool Parser::_parse_kw_const()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwConst);
}
bool Parser::_parse_kw_range()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwRange);
}
bool Parser::_parse_kw_cat()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwCat);
}
bool Parser::_parse_kw_repl()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwRepl);
}
bool Parser::_parse_kw_using()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUsing);
}
bool Parser::_parse_kw_while()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwWhile);
}
bool Parser::_parse_kw_switch()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwitch);
}
bool Parser::_parse_kw_switchz()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwitchz);
}
bool Parser::_parse_kw_case()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwCase);
}
bool Parser::_parse_kw_default()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwDefault);
}
bool Parser::_parse_kw_return()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwReturn);
}
bool Parser::_parse_kw_packed()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPacked);
}
bool Parser::_parse_kw_class()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwClass);
}
bool Parser::_parse_kw_virtual()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwVirtual);
}
bool Parser::_parse_kw_extends()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwExtends);
}
bool Parser::_parse_kw_public()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPublic);
}
bool Parser::_parse_kw_protected()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwProtected);
}
bool Parser::_parse_kw_private()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPrivate);
}
bool Parser::_parse_kw_enum()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwEnum);
}
bool Parser::_parse_kw_union()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUnion);
}
bool Parser::_parse_kw_assign()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAssign);
}
bool Parser::_parse_kw_initial()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInitial);
}
bool Parser::_parse_kw_always_comb()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysComb);
}
bool Parser::_parse_kw_always_blk()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysBlk);
}
bool Parser::_parse_kw_always_ff()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysFf);
}
bool Parser::_parse_kw_posedge()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPosedge);
}
bool Parser::_parse_kw_negedge()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwNegedge);
}
bool Parser::_parse_kw_inst()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInst);
}
bool Parser::_parse_kw_input()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInput);
}
bool Parser::_parse_kw_output()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwOutput);
}
bool Parser::_parse_kw_bidir()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwBidir);
}
bool Parser::_parse_kw_type()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwType);
}
bool Parser::_parse_kw_uwire()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUwire);
}
bool Parser::_parse_kw_swire()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwire);
}
bool Parser::_parse_kw_ubit()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUbit);
}
bool Parser::_parse_kw_sbit()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSbit);
}
bool Parser::_parse_kw_void()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwVoid);
}
bool Parser::_parse_kw_auto()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAuto);
}
bool Parser::_parse_kw_ubyte()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUbyte);
}
bool Parser::_parse_kw_sbyte()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSbyte);
}
bool Parser::_parse_kw_ushortint()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUshortint);
}
bool Parser::_parse_kw_sshortint()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSshortint);
}
bool Parser::_parse_kw_uint()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUint);
}
bool Parser::_parse_kw_sint()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSint);
}
bool Parser::_parse_kw_ulongint()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUlongint);
}
bool Parser::_parse_kw_slongint()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSlongint);
}
bool Parser::_parse_kw_typeof()
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwTypeof);
}

bool Parser::_parse_punct_lparen()
{
	CHECK_PREFIXED_ONE_TOK(Tok::LParen);
}
bool Parser::_parse_punct_rparen()
{
	CHECK_PREFIXED_ONE_TOK(Tok::RParen);
}
bool Parser::_parse_punct_lbracket()
{
	CHECK_PREFIXED_ONE_TOK(Tok::LBracket);
}
bool Parser::_parse_punct_rbracket()
{
	CHECK_PREFIXED_ONE_TOK(Tok::RBracket);
}
bool Parser::_parse_punct_lbrace()
{
	CHECK_PREFIXED_ONE_TOK(Tok::LBrace);
}
bool Parser::_parse_punct_rbrace()
{
	CHECK_PREFIXED_ONE_TOK(Tok::RBrace);
}
bool Parser::_parse_punct_comma()
{
	CHECK_PREFIXED_ONE_TOK(Tok::Comma);
}
bool Parser::_parse_punct_semicolon()
{
	CHECK_PREFIXED_ONE_TOK(Tok::Semicolon);
}
bool Parser::_parse_punct_colon()
{
	CHECK_PREFIXED_ONE_TOK(Tok::Colon);
}
bool Parser::_parse_punct_apostrophe()
{
	CHECK_PREFIXED_ONE_TOK(Tok::Apostrophe);
}
bool Parser::_parse_punct_assign()
{
	CHECK_PREFIXED_ONE_TOK(Tok::Assign);
}
bool Parser::_parse_punct_member_access()
{
	CHECK_PREFIXED_ONE_TOK(Tok::MemberAccess);
}
bool Parser::_parse_punct_scope_access()
{
	CHECK_PREFIXED_ONE_TOK(Tok::ScopeAccess);
}
bool Parser::_parse_punct_param_pack()
{
	CHECK_PREFIXED_ONE_TOK(Tok::ParamPack);
}

bool Parser::_parse_header_if()
{
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_if), rseqp(punct_lparen),
		rseqp(expr), rseqp(punct_rparen)))
	return true;
}
bool Parser::_parse_header_else_if()
{
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_else), rseqp(header_if)))
	return true;
}
bool Parser::_parse_header_else()
{
	simple_seq_parse_anon(rseqp(kw_else))
	return true;
}
bool Parser::_parse_header_for()
{
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_for),
		rseqp(punct_lparen), rseqp(ident), rseqp(punct_colon),
		_req_or_parse(rseqp(expr), rseqp(type_range)),
		rseqp(punct_rparen)))
	return true;
}

bool Parser::_parse_header_generate_if()
{
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_generate),
		rseqp(header_if)))
	return true;
}
bool Parser::_parse_header_else_generate_if()
{
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_else),
		rseqp(header_generate_if)))
	return true;
}
bool Parser::_parse_header_else_generate()
{
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_else),
		rseqp(kw_generate)))
	return true;
}
bool Parser::_parse_header_generate_for()
{
	make_msp;
	_append_msp(map_seq_parse,
		named_rseqp(kw_generate),
		named_oseqp(ident),
		named_rseqp(header_for));

	simple_seq_parse_if_jp_named(seq, _req_seq_parse(msp(kw_generate),
		msp(ident), msp(header_for)))
	else
	{
		msp(kw_generate).exec();
		_push_one_opt_parse(msp(ident));
		msp(header_for).exec();
	}

	return true;
}

bool Parser::_parse_package()
{
	auto ls = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_package), rseqp(ident),
		rseqp(scope_package)))

	if (!just_parse())
	{
		auto scope_package = _pop_ast_child();
		auto ident = _pop_ast_child();
		_push_ast_child(NodePackage(_ls_src_code_chunk(ls),
			move(ident), move(scope_package)));
	}
	return true;
}
bool Parser::_parse_scope_package()
{
	return _parse_any_scope<NodeScopePackage>("scope_package",
		_req_or_parse(rseqp(generate_package), rseqp(package),
		rseqp(module), rseqp(const), rseqp(using), rseqp(decl_callable),
		rseqp(decl_cstm_type)));
}

bool Parser::_parse_generate_package()
{
	simple_seq_parse_anon(_req_or_parse(rseqp(generate_package_if),
		rseqp(generate_package_for)))
	return true;
}
bool Parser::_parse_generate_package_if()
{
	return _parse_generate_any_if(named_fp(generate_package_if));
}
bool Parser::_parse_generate_package_for()
{
	return _parse_generate_any_for(named_fp(generate_package_for));
}

bool Parser::_parse_member_callable_prefix()
{
	auto ls = _dup_lex_state();

	const auto vec = _next_n_tokens(3, false);
	bool is_const = false;
	bool is_virtual = false;
	bool is_static = false;

	bool found = true;
	for (const auto& iter : vec)
	{
		switch (iter.tok())
		{
		case Tok::KwConst:
			is_const = true;
			break;
		case Tok::KwVirtual:
			is_virtual = true;
			break;
		case Tok::KwStatic:
			is_static = true;
			break;
		default:
			found = false;
			break;
		}

		if (!found)
		{
			break;
		}
	}
	if (actual_just_test())
	{
		return (is_const || is_virtual || is_static);
	}

	size_t to_push = 0;
	if (is_const)
	{
		_next_n_tokens(1, true);
		++to_push;

		if (!just_parse())
		{
			_push_str("is_const");
		}
	}
	if (is_virtual)
	{
		_next_n_tokens(1, true);
		++to_push;

		if (!just_parse())
		{
			_push_str("is_virtual");
		}
	}
	if (is_static)
	{
		_next_n_tokens(1, true);
		++to_push;

		if (!just_parse())
		{
			_push_str("is_static");
		}
	}

	if (!just_parse())
	{
		_push_num(to_push);
	}

	return true;
}

bool Parser::_parse_contents_modproc()
{
	make_msp;
	_append_msp(map_seq_parse,
		named_oseqp(param_list),
		named_rseqp(arg_list),
		named_rseqp(scope_modproc));

	simple_seq_parse_if_jp_named(seq, _req_seq_parse(msp(param_list),
		msp(arg_list), msp(scope_modproc)))
	else
	{
		_push_one_opt_parse(msp(param_list));
		msp(arg_list).exec();
		msp(scope_modproc).exec();
	}
	return true;
}
bool Parser::_parse_proc()
{
	auto ls = _dup_lex_state();

	make_msp;
	_append_msp(map_seq_parse,
		named_rseqp(kw_proc),
		"type", _req_or_parse(rseqp(ident), rseqp(kw_port),
			rseqp(const_str)),
		named_rseqp(contents_modproc));

	simple_seq_parse_if_jp_anon(_req_seq_parse(msp(kw_proc), msp(type),
		msp(contents_modproc)))
	else
	{
		msp(kw_proc).exec();

		const auto parse_func_str = msp(type).fv_parse_func_str();
		msp(type).exec();

		Child s_ident_or_op;
		bool s_is_port = false;
		if ((parse_func_str == "ident") || (parse_func_str == "const_str"))
		{
			s_ident_or_op = _pop_ast_child();
		}
		else // if (parse_func_str == "kw_port")
		{
			s_is_port = true;
		}

		msp(contents_modproc).exec();
		auto s_scope = _pop_ast_child();
		auto s_arg_list = _pop_ast_child();
		auto s_param_list = _get_ast_child_if_pop_num();

		_push_ast_child(NodeDeclProc(_ls_src_code_chunk(ls), s_is_port,
			move(s_param_list), move(s_arg_list), move(s_ident_or_op),
			move(s_scope)));
	}
	return true;
}
bool Parser::_parse_module()
{
	auto ls = _dup_lex_state();

	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_module), rseqp(ident),
		rseqp(contents_modproc)))

	if (!just_parse())
	{
		auto s_scope = _pop_ast_child();
		auto s_arg_list = _pop_ast_child();
		auto s_param_list = _get_ast_child_if_pop_num();
		auto s_ident = _pop_ast_child();
		_push_ast_child(NodeModule(_ls_src_code_chunk(ls), move(s_ident),
			move(s_param_list), move(s_arg_list), move(s_scope)));
	}
	return true;
}

bool Parser::_parse_scope_modproc()
{
	return _parse_any_scope<NodeScopeModproc>("scope_modproc",
		_req_or_parse(rseqp(generate_modproc),
		rseqp(module), rseqp(const), rseqp(var), rseqp(using),
		rseqp(decl_callable), rseqp(decl_cstm_type),
		rseqp(hardware_block)));
}
bool Parser::_parse_generate_modproc()
{
	simple_seq_parse_anon(_req_or_parse(rseqp(generate_modproc_if),
		rseqp(generate_modproc_for)))
	return true;
}
bool Parser::_parse_generate_modproc_if()
{
	return _parse_generate_any_if(named_fp(generate_modproc_if));
}
bool Parser::_parse_generate_modproc_for()
{
	return _parse_generate_any_for(named_fp(generate_modproc_for));
}

bool Parser::_parse_decl_callable()
{
	simple_seq_parse_anon(_req_or_parse(rseqp(func), rseqp(task),
		rseqp(proc)))
	return true;
}
bool Parser::_parse_contents_func_task()
{
	make_msp;
	_append_msp(map_seq_parse,
		named_oseqp(param_list),
		named_rseqp(arg_list),
		named_rseqp(scope_behav));
	simple_seq_parse_if_jp_anon(_req_seq_parse(msp(param_list),
		msp(arg_list), msp(scope_behav)))
	else
	{
		_push_one_opt_parse(msp(param_list));
		msp(arg_list).exec();
		msp(scope_behav).exec();
	}

	return true;
}
bool Parser::_parse_func()
{
	auto ls = _dup_lex_state();
	make_msp;
	_append_msp(map_seq_parse,
		named_rseqp(kw_func),
		named_rseqp(typename),
		"ident_or_op", _req_or_parse(rseqp(ident), rseqp(const_str)),
		named_rseqp(contents_func_task));

	simple_seq_parse_if_jp_anon(_req_seq_parse(msp(kw_func), msp(typename),
		msp(ident_or_op), msp(contents_func_task)))
	else
	{
		msp(kw_func).exec();
		auto s_the_typename = _pexec(msp(typename));
		auto s_ident_or_op = _pexec(msp(ident_or_op));

		msp(contents_func_task).exec();
		auto s_scope = _pop_ast_child();
		auto s_arg_list = _pop_ast_child();
		auto s_param_list = _get_ast_child_if_pop_num();
		_push_ast_child(NodeDeclFunc(_ls_src_code_chunk(ls),
			move(s_the_typename), move(s_param_list), move(s_arg_list),
			move(s_ident_or_op), move(s_scope)));
	}

	return true;
}
bool Parser::_parse_task()
{
	auto ls = _dup_lex_state();
	make_msp;
	_append_msp(map_seq_parse,
		named_rseqp(kw_task),
		"ident_or_op", _req_or_parse(rseqp(ident), rseqp(const_str)),
		named_rseqp(contents_func_task));

	simple_seq_parse_if_jp_anon(_req_seq_parse(msp(kw_task),
		msp(ident_or_op), msp(contents_func_task)))
	else
	{
		msp(kw_task).exec();
		auto s_ident_or_op = _pexec(msp(ident_or_op));

		msp(contents_func_task).exec();
		auto s_scope = _pop_ast_child();
		auto s_arg_list = _pop_ast_child();
		auto s_param_list = _get_ast_child_if_pop_num();
		_push_ast_child(NodeDeclTask(_ls_src_code_chunk(ls),
			move(s_param_list), move(s_arg_list), move(s_ident_or_op),
			move(s_scope)));
	}

	return true;
}

bool Parser::_parse_scope_behav()
{
	return _parse_any_scope<NodeScopeBehav>("scope_behav",
		_req_or_parse(rseqp(inner_scope_behav)));
}
bool Parser::_parse_inner_scope_behav()
{
	simple_seq_parse_anon(_req_or_parse(rseqp(generate_behav),
		rseqp(const), rseqp(var), rseqp(using), rseqp(stmt_assign),
		rseqp(stmt_if), rseqp(stmt_for), rseqp(stmt_while),
		rseqp(stmt_switch), rseqp(stmt_switchz), rseqp(stmt_return),
		rseqp(ident_etc), rseqp(decl_cstm_type), rseqp(scope_behav)))
	return true;
}

bool Parser::_parse_generate_behav()
{
	simple_seq_parse_anon(_req_or_parse(rseqp(generate_behav_if),
		rseqp(generate_behav_for)))
	return true;
}
bool Parser::_parse_generate_behav_if()
{
	return _parse_generate_any_if(named_fp(generate_behav_if));
}
bool Parser::_parse_generate_behav_for()
{
	return _parse_generate_any_for(named_fp(generate_behav_for));
}

bool Parser::_parse_const()
{
	auto ls = _dup_lex_state();
	make_msp;

	_append_msp(map_seq_parse,
		named_rseqp(kw_const),
		named_oseqp(typename),
		named_rseqp(one_const),
		"list_one_const", _opt_list_parse(rseqp(punct_comma),
			rseqp(one_const)),
		named_rseqp(punct_semicolon));

	simple_seq_parse_if_jp_anon(_req_seq_parse(msp(kw_const),
		msp(typename), msp(one_const), msp(list_one_const),
		msp(punct_semicolon)))
	else
	{
		msp(kw_const).exec();
		auto s_the_typename = _get_one_opt_parse(msp(typename));

		NodeIdentTermEqualsExtraList s_ident_term_equals_extra_list
			(_ls_src_code_chunk(_dup_lex_state()));
		s_ident_term_equals_extra_list.append(_pexec(msp(one_const)));
		_list_pexec(s_ident_term_equals_extra_list, msp(list_one_const));

		msp(punct_semicolon).exec();
		_push_ast_child(NodeDeclConstList(_ls_src_code_chunk(ls),
			move(s_the_typename),
			_to_ast_child(move(s_ident_term_equals_extra_list))));
	}
	return true;
}
bool Parser::_parse_one_const()
{
	auto ls = _dup_lex_state();
	make_msp;
	_append_msp(map_seq_parse,
		named_rseqp(ident_terminal),
		named_rseqp(punct_assign),
		named_rseqp(expr));
	simple_seq_parse_if_jp_anon(_req_seq_parse(msp(ident_terminal),
		msp(punct_assign), msp(expr)))
	else
	{
		auto s_ident_terminal = _pexec(msp(ident_terminal));
		msp(punct_assign).exec();
		auto s_expr = _pexec(msp(expr));
		_push_ast_child(NodeIdentTermEqualsExtra(_ls_src_code_chunk(ls),
			move(s_ident_terminal), move(s_expr)));
	}

	return true;
}
bool Parser::_parse_var()
{
	auto ls = _dup_lex_state();
	make_msp;
	_append_msp(map_seq_parse,
		named_rseqp(typename),
		named_rseqp(one_var),
		"list", _req_list_parse(rseqp(punct_comma), rseqp(one_var)),
		named_rseqp(punct_semicolon));
	simple_seq_parse_if_jp_anon(_req_seq_parse(msp(typename),
		msp(one_var), _opt_seq_parse(msp(list)), msp(punct_semicolon)))
	else
	{
		auto s_the_typename = _pexec(msp(typename));
		auto s_first_var = _pexec(msp(one_var));

		std::vector<Child> s_rem_var_list;

		if (msp(list).check())
		{
			const auto s_list_amount = _pexec<BigNum>(s_rem_var_list);

			for (decltype(s_list_amount) i=0; i<s_list_amount; ++i)
			{
				s_rem_var_list.push_back(_pop_ast_child());
			}
		}

		msp(punct_semicolon).exec();
	}

	return true;
}
bool Parser::_parse_one_var()
{
}
bool Parser::_parse_using()
{
}

bool Parser::_parse_stmt_assign()
{
}
bool Parser::_parse_stmt_if()
{
}
bool Parser::_parse_stmt_for()
{
}
bool Parser::_parse_stmt_while()
{
}
bool Parser::_parse_stmt_switch()
{
}
bool Parser::_parse_stmt_switchz()
{
}
bool Parser::_parse_scope_switch()
{
}
bool Parser::_parse_stmt_case()
{
}
bool Parser::_parse_stmt_default()
{
}
bool Parser::_parse_stmt_return()
{
}

bool Parser::_parse_decl_cstm_type()
{
}
bool Parser::_parse_class()
{
}
bool Parser::_parse_extends()
{
}

bool Parser::_parse_scope_class()
{
}
bool Parser::_parse_member_callable()
{
}
bool Parser::_parse_generate_class()
{
}
bool Parser::_parse_generate_class_if()
{
}
bool Parser::_parse_generate_class_for()
{
}
bool Parser::_parse_member_access_label()
{
}

bool Parser::_parse_enum()
{
}
bool Parser::_parse_union()
{
}

bool Parser::_parse_hardware_block()
{
}
bool Parser::_parse_cont_assign()
{
}
bool Parser::_parse_initial()
{
}
bool Parser::_parse_always_comb()
{
}
bool Parser::_parse_always_blk()
{
}
bool Parser::_parse_always_ff()
{
}
bool Parser::_parse_edge_list()
{
}
bool Parser::_parse_posedge_inst()
{
}
bool Parser::_parse_negedge_inst()
{
}

bool Parser::_parse_inst()
{
}

bool Parser::_parse_param_list()
{
}
bool Parser::_parse_param_sublist()
{
}
bool Parser::_parse_arg_list()
{
}
bool Parser::_parse_arg_sublist()
{
}
bool Parser::_parse_arg_port_sublist()
{
}
bool Parser::_parse_pararg_var_sublist()
{
}
bool Parser::_parse_pararg_type_sublist()
{
}
bool Parser::_parse_param_module_sublist()
{
}
bool Parser::_parse_pararg_ident_equals_typename_sublist()
{
}
bool Parser::_parse_param_inst_list()
{
}
bool Parser::_parse_arg_inst_list()
{
}

bool Parser::_parse_pos_pararg_inst_list()
{
}
bool Parser::_parse_named_pararg_inst_list()
{
}

bool Parser::_parse_typename()
{
}
bool Parser::_parse_param_possible_typename()
{
}
bool Parser::_parse_no_param_possible_typename()
{
}
bool Parser::_parse_typeof()
{
}
bool Parser::_parse_type_range()
{
}
bool Parser::_parse_range_suffix()
{
}

bool Parser::_parse_expr()
{
}
bool Parser::_parse_inner_expr()
{
}
bool Parser::_parse_op_logical()
{
}

bool Parser::_parse_expr_logical()
{
}
bool Parser::_parse_inner_expr_logical()
{
}
bool Parser::_parse_op_compare()
{
}

bool Parser::_parse_expr_compare()
{
}
bool Parser::_parse_inner_expr_compare()
{
}
bool Parser::_parse_op_plus_minus()
{
}

bool Parser::_parse_expr_add_sub()
{
}
bool Parser::_parse_inner_expr_add_sub()
{
}
bool Parser::_parse_op_mul_div_mod_etc()
{
}

bool Parser::_parse_expr_mul_div_mod_etc()
{
}
bool Parser::_parse_inner_expr_mul_div_mod_etc()
{
}
bool Parser::_parse_op_unary()
{
}

bool Parser::_parse_dollar_global_clock()
{
}
bool Parser::_parse_dollar_pow_expr()
{
}
bool Parser::_parse_num_expr()
{
}
bool Parser::_parse_raw_num()
{
}
bool Parser::_parse_const_str()
{
}

bool Parser::_parse_expr_pre_dollar_func_of_one()
{
}
bool Parser::_parse_expr_post_dollar_func_of_one()
{
}
bool Parser::_parse_dollar_func_of_one()
{
}
bool Parser::_parse_expr_cat()
{
}
bool Parser::_parse_expr_repl()
{
}

bool Parser::_parse_ident_etc()
{
}
bool Parser::_parse_ident_member_access()
{
}
bool Parser::_parse_ident_scope_access()
{
}
bool Parser::_parse_ident_non_member_scope_access()
{
}
bool Parser::_parse_ident_call()
{
}
bool Parser::_parse_ident_no_param_overloaded_call()
{
}
bool Parser::_parse_ident_param_member_overloaded_call()
{
}
bool Parser::_parse_ident_terminal()
{
}
bool Parser::_parse_ident()
{
}
bool Parser::_parse_generate_any_if(const string& parse_scope_func_str,
	ParseFunc parse_scope_func)
{
}
bool Parser::_parse_generate_any_for(const string& parse_scope_func_str,
	ParseFunc parse_scope_func)
{
}

template<typename AstNodeScopeType>
bool Parser::_parse_any_scope(const string& scope_type_str,
	const TheSeqParse& list_seq)
{
}

void Parser::_finish_parse_expr_any_dollar_func_of_one
	(const SrcCodeChunk& s_src_code_chunk)
{
	auto s_expr = _pop_ast_child();

	switch (_pop_tok())
	{
	case Tok::KwDollarUnsgn:
		_push_ast_child(NodeExprUnopDollarUnsgn(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarSgn:
		_push_ast_child(NodeExprUnopDollarSgn(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarIsUnsgn:
		_push_ast_child(NodeExprUnopDollarIsUnsgn(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarIsSgn:
		_push_ast_child(NodeExprUnopDollarIsSgn(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarRange:
		_push_ast_child(NodeExprUnopDollarRange(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarSize:
		_push_ast_child(NodeExprUnopDollarSize(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarFirst:
		_push_ast_child(NodeExprUnopDollarFirst(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarLast:
		_push_ast_child(NodeExprUnopDollarLast(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarHigh:
		_push_ast_child(NodeExprUnopDollarHigh(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarLow:
		_push_ast_child(NodeExprUnopDollarLow(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarClog2:
		_push_ast_child(NodeExprUnopDollarClog2(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarPast:
		_push_ast_child(NodePseudoExprDollarPast(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarStable:
		_push_ast_child(NodePseudoExprDollarStable(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarRose:
		_push_ast_child(NodePseudoExprDollarRose(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarFell:
		_push_ast_child(NodePseudoExprDollarFell(s_src_code_chunk,
			move(s_expr)));
		break;
	default:
		s_src_code_chunk.err("_finish_parse_expr_any_dollar_func_of_one"
			"():  Eek!");
	}
}

} // namespace frost_hdl
