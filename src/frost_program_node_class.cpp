#include "src/frost_program_node_class.hpp"

namespace frost_hdl
{

FrostProgramNode::FrostProgramNode()
{
}

FrostProgramNode::FrostProgramNode(const SrcCodeChunk& s_src_code_chunk,
	SavedString s_ident)
	: HasSrcCodeChunkAndIdentBase(s_src_code_chunk, s_ident)
{
}

FrostProgramNode::~FrostProgramNode()
{
}

bool FrostProgramNode::is_expr() const
{
	return false;
}

bool FrostProgramNode::is_constant_expr() const
{
	return false;
}

} // namespace frost_hdl
