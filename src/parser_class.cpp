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

bool Parser::_parse_package()
{
	if (just_test())
	{
		return _check_prefixed_tok_seq(TokSet(), Tok::KwPackage);
	}
	_next_lss_tokens();

	rwith(we, _wexpect(Tok::Ident))
	{
	}

	return true;
}

#undef fp

} // namespace frost_hdl
