#include "src_code_chunk_class.hpp"
#include "gen_src/FrostHdlGrammarLexer.h"
#include "gen_src/FrostHdlGrammarParser.h"
#include "gen_src/FrostHdlGrammarVisitor.h"

namespace frost_hdl
{

SrcCodeChunk::SrcCodeChunk()
	: _filename(), _text(), _src_line(0),
	_src_pos_in_line(0)
{
}
SrcCodeChunk::SrcCodeChunk(const string& s_filename,
	const string& s_text, size_t s_src_line, size_t s_src_pos_in_line)
	: _filename(s_filename), _text(s_text),
	_src_line(s_src_line), _src_pos_in_line(s_src_pos_in_line)
{
}

SrcCodeChunk::~SrcCodeChunk()
{
}

string SrcCodeChunk::convert_to_pos_string() const
{
	return sconcat(filename(), ":", src_line(), ":", src_pos_in_line());
}
string SrcCodeChunk::convert_to_errwarn_string() const
{
	return sconcat(convert_to_pos_string(), " (near text \"", text(),
		"\")");
}

} // namespace frost_hdl
