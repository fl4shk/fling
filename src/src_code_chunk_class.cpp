#include "src_code_chunk_class.hpp"
#include "gen_src/FrostHdlGrammarLexer.h"
#include "gen_src/FrostHdlGrammarParser.h"
#include "gen_src/FrostHdlGrammarVisitor.h"

namespace frost_hdl
{

SrcCodeChunk::SrcCodeChunk()
	: _filename(), _ctx(nullptr), _text(), _src_line(0),
	_src_pos_in_line(0)
{
}
SrcCodeChunk::SrcCodeChunk(const std::string& s_filename,
	antlr4::ParserRuleContext* s_ctx)
	: _filename(s_filename), _ctx(s_ctx)
{
	auto tok = _ctx->getStart();

	_text = tok->getText();
	_src_line = tok->getLine();
	_src_pos_in_line = tok->getCharPositionInLine();
}
SrcCodeChunk::SrcCodeChunk(const std::string& s_filename,
	const std::string& s_text, size_t s_src_line, size_t s_src_pos_in_line)
	: _filename(s_filename), _ctx(nullptr), _text(s_text),
	_src_line(s_src_line), _src_pos_in_line(s_src_pos_in_line)
{
}

SrcCodeChunk::~SrcCodeChunk()
{
}

std::string SrcCodeChunk::convert_to_errwarn_string() const
{
	return sconcat(_filename, ":", _src_line, ":", _src_pos_in_line,
		"(near text \"", _text, "\")");
}

} // namespace frost_hdl
