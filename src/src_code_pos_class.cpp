#include "src_code_pos_class.hpp"
#include "gen_src/FrostHdlGrammarLexer.h"
#include "gen_src/FrostHdlGrammarParser.h"
#include "gen_src/FrostHdlGrammarVisitor.h"

namespace frost_hdl
{

SrcCodePos::SrcCodePos()
	: _filename(nullptr), _ctx(nullptr)
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
SrcCodePos::SrcCodePos(SavedString s_filename, size_t s_src_line,
	size_t s_src_pos_in_line)
	: _filename(s_filename), _ctx(nullptr), _src_line(s_src_line),
	_src_pos_in_line(s_src_pos_in_line)
{
}

SrcCodePos::~SrcCodePos()
{
}

std::string SrcCodePos::convert_to_errwarn_string() const
{
	return sconcat(*_filename, ":", _src_line, ":", _src_pos_in_line);
}

} // namespace frost_hdl
