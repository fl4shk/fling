#include "misc_types.hpp"
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


} // namespace frost_hdl
