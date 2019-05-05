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
	_parent(s_parent), _actual_scope(nullptr)
{
}

AstNode::~AstNode()
{
}
//--------

//--------
void AstNode::insert_child_after(const ChildrenList::NodeIterator& where,
	AstNode&& to_insert)
{
	_finish_child_insert(children().insert_after(where, _convert_to_child
		(std::move(to_insert))));
}
void AstNode::insert_child_before(const ChildrenList::NodeIterator& where,
	AstNode&& to_insert)
{
	_finish_child_insert(children().insert_before(where, _convert_to_child
		(std::move(to_insert))));
}

void AstNode::push_child_back(AstNode&& to_push)
{
	_finish_child_insert(children().push_back(_convert_to_child(
		std::move(to_push))));
}
void AstNode::push_child_front(AstNode&& to_push)
{
	_finish_child_insert(children().push_front(_convert_to_child
		(std::move(to_push))));
}

void AstNode::remove_child_after(const ChildrenList::NodeIterator& where)
{
}
void AstNode::remove_child_before(const ChildrenList::NodeIterator& where)
{
}
//--------

} // namespace frost_hdl
