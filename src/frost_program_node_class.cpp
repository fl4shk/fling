#include "src/frost_program_node_class.hpp"

namespace frost_hdl
{

//--------
FrostProgramNode::FrostProgramNode()
{
}

FrostProgramNode::FrostProgramNode(const SrcCodeChunk& s_src_code_chunk,
	const Ident& s_ident)
	: HasSrcCodeChunkAndIdentBase(s_src_code_chunk, s_ident),
	_parent(nullptr), _actual_scope_fpn(nullptr),
	_children(new CircLinkedList<FrostProgramNode>())
{
}

FrostProgramNode::~FrostProgramNode()
{
}
//--------

//--------
bool FrostProgramNode::is_expr() const
{
	return false;
}

bool FrostProgramNode::is_constant_expr() const
{
	return false;
}

auto FrostProgramNode::scope_type() const
	-> ScopeType
{
	return ScopeType::None;
}

auto FrostProgramNode::symbol_type() const
	-> SymbolType
{
	return SymbolType::None;
}
auto FrostProgramNode::port_type() const
	-> PortType
{
	return PortType::None;
}
//--------

} // namespace frost_hdl
