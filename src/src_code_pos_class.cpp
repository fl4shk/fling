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
SrcCodePos::SrcCodePos(SavedString s_filename,
	antlr4::ParserRuleContext* s_ctx)
	: _filename(s_filename), _ctx(s_ctx)
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
	return sconcat("file \"", *_filename, "\" (at ", _src_line,
		":", _src_pos_in_line, ")");
}

} // namespace frost_hdl
