#include "src_code_pos_class.hpp"
#include "gen_src/CompilerGrammarLexer.h"
#include "gen_src/CompilerGrammarParser.h"
#include "gen_src/CompilerGrammarVisitor.h"

namespace frost_hdl
{

SrcCodePos::SrcCodePos()
	: _ctx(nullptr)
{
}
SrcCodePos::SrcCodePos(antlr4::ParserRuleContext* s_ctx)
	: _ctx(s_ctx)
{
	auto tok = _ctx->getStart();
	_src_line = tok->getLine();
	_src_pos_in_line = tok->getCharPositionInLine();
}

SrcCodePos::~SrcCodePos()
{
}

std::string SrcCodePos::convert_to_errwarn_string() const
{
	return sconcat("line ", _src_line, ", position ", _src_pos_in_line);
}

} // namespace frost_hdl
