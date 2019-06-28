#include "parser_class.hpp"

namespace frost_hdl
{

Parser::Parser(std::vector<string>&& s_filename_vec)
	: ParserBase<Lexer>(std::move(s_filename_vec))
{
}
Parser::~Parser()
{
}



//std::vector<Lexer> Parser::_next_n_tokens(bool affect_lexer, size_t n)
//{
//	std::vector<Lexer> ret;
//
//	Lexer temp_lexer(_lexer());
//
//	auto* lexer = (!affect_lexer) ? &_lexer() : &temp_lexer;
//
//	for (size_t i=0; i<n; ++i)
//	{
//		_next_tok(lexer);
//		ret.push_back(*lexer);
//	}
//
//	return ret;
//}


} // namespace frost_hdl
