#include "parser_class.hpp"

namespace frost_hdl
{
using namespace ast;

Parser::Parser(std::vector<string>&& s_filename_vec)
	: ParserBase<Lexer>(std::move(s_filename_vec))
{
	_ast.reset(new NodeBase(SrcCodeChunk()));
}
Parser::~Parser()
{
}

bool Parser::_parse_decl_package()
{
	if (just_test())
	{
		//return _check_prefixed_tok_seq<NodePackage>();
		return _check_prefixed_tok_seq(TokSet(), Tok::KwPackage);
	}
	else // if (!just_test())
	{
		_next_lss_tokens();
	}

	return true;
}
bool Parser::_parse_decl_module()
{
	if (just_test())
	{
		return _check_prefixed_tok_seq(TokSet(), Tok::KwModule);
	}
	else // if (!just_test())
	{
		_next_lss_tokens();
	}

	return true;
}
bool Parser::_parse_decl_enum()
{
	if (just_test())
	{
		return _check_prefixed_tok_seq(TokSet(), Tok::KwEnum);
	}
	else // if (!just_test())
	{
		_next_lss_tokens();
	}
	return true;
}
bool Parser::_parse_decl_class()
{
	if (just_test())
	{
		//return _check_prefixed_tok_seq({Tok::KwPacked}, Tok::KwClass);
		return _check_prefixed_tok_seq({Tok::KwPacked}, Tok::KwClass);
	}
	else // if (!just_test())
	{
		_next_lss_tokens();
	}
	return true;
}
bool Parser::_parse_generate()
{
	if (just_test())
	{
	}
	else // if (!just_test())
	{
	}
	return true;
}

bool Parser::_parse_member_access_label()
{
	if (just_test())
	{
	}
	else // if (!just_test())
	{
	}
	return true;
}

bool Parser::_parse_decl_member_func()
{
	if (just_test())
	{
	}
	else // if (!just_test())
	{
	}
	return true;
}
bool Parser::_parse_decl_func()
{
	if (just_test())
	{
	}
	else // if (!just_test())
	{
	}
	return true;
}
bool Parser::_parse_decl_member_task()
{
	if (just_test())
	{
	}
	else // if (!just_test())
	{
	}
	return true;
}
bool Parser::_parse_decl_task()
{
	if (just_test())
	{
	}
	else // if (!just_test())
	{
	}
	return true;
}
bool Parser::_parse_decl_member_proc()
{
	if (just_test())
	{
	}
	else // if (!just_test())
	{
	}
	return true;
}
bool Parser::_parse_decl_proc()
{
	if (just_test())
	{
	}
	else // if (!just_test())
	{
	}
	return true;
}

bool Parser::_parse_param_list()
{
	if (just_test())
	{
	}
	else // if (!just_test())
	{
	}
	return true;
}
bool Parser::_parse_port_list()
{
	if (just_test())
	{
	}
	else // if (!just_test())
	{
	}
	return true;
}

bool Parser::_parse_expr()
{
	if (just_test())
	{
	}
	else // if (!just_test())
	{
	}
	return true;
}

} // namespace frost_hdl
