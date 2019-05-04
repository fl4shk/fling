#include "ast_node_class.hpp"

namespace frost_hdl
{

//--------
AstNode::AstNode()
{
}

AstNode::AstNode(const SrcCodeChunk& s_src_code_chunk,
	const Ident& s_ident, AstNode* s_parent)
	: HasSrcCodeChunkAndIdentBase(s_src_code_chunk, s_ident),
	_parent(s_parent), _actual_scope(nullptr),
	_children(new ChildrenList())
{
}

AstNode::~AstNode()
{
}
//--------

//--------
void AstNode::push_child_back(AstNode&& to_push)
{
	finish_child_insert(children().push_back(std::move(to_push)));
}
void AstNode::push_child_front(AstNode&& to_push)
{
	finish_child_insert(children().push_front(std::move(to_push)));
}
//--------

} // namespace frost_hdl
