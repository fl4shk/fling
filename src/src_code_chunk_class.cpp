#include "src_code_chunk_class.hpp"

namespace frost_hdl
{

SrcCodeChunk::SrcCodeChunk()
	: _filename(), _text(), _src_line(0),
	_src_pos_in_line(0)
{
}
SrcCodeChunk::SrcCodeChunk(const string& s_filename,
	const string& s_text, size_t s_src_line, size_t s_src_pos_in_line)
	: _filename(s_filename), _text(s_text), _src_line(s_src_line),
	_src_pos_in_line(s_src_pos_in_line)
{
}

SrcCodeChunk::~SrcCodeChunk()
{
}

string SrcCodeChunk::convert_to_pos_string() const
{
	return sconcat(_filename, ":", _src_line, ":", _src_pos_in_line);
}
string SrcCodeChunk::convert_to_errwarn_string() const
{
	return sconcat(convert_to_pos_string(), " (near text \"", _text,
		"\")");
}

} // namespace frost_hdl
