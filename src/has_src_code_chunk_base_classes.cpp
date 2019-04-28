#include "has_src_code_chunk_base_classes.hpp"

namespace frost_hdl
{

HasSrcCodeChunkBase::HasSrcCodeChunkBase()
{
}
HasSrcCodeChunkBase::HasSrcCodeChunkBase(const SrcCodeChunk& s_src_code_chunk)
	: _src_code_chunk(s_src_code_chunk)
{
}
HasSrcCodeChunkBase::~HasSrcCodeChunkBase()
{
}


HasSrcCodeChunkAndIdentBase::HasSrcCodeChunkAndIdentBase()
{
}
HasSrcCodeChunkAndIdentBase::HasSrcCodeChunkAndIdentBase
	(const SrcCodeChunk& s_src_code_chunk, SavedString s_ident)
	: HasSrcCodeChunkBase(s_src_code_chunk), _ident(s_ident)
{
}
HasSrcCodeChunkAndIdentBase::~HasSrcCodeChunkAndIdentBase()
{
}

} // namespace frost_hdl
