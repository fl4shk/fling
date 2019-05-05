#include "ast_node_class.hpp"

namespace frost_hdl
{

//--------
AstNode::AstNode()
{
}

AstNode::AstNode(const SrcCodeChunk& s_src_code_chunk,
	Type s_type, AstNode* s_parent)
	: HasSrcCodeChunkBase(s_src_code_chunk), _type(s_type),
	_parent(s_parent)
{
}

AstNode::~AstNode()
{
}
//--------

//--------
void AstNode::push_child_back(Child&& to_push)
{
	++_num_children;
	_finish_child_insert(_children.push_back(std::move(to_push)));
}
void AstNode::push_child_front(Child&& to_push)
{
	++_num_children;
	_finish_child_insert(_children.push_front(std::move(to_push)));
}

void AstNode::insert_child_after(ChildrenList::Node* where,
	Child&& to_insert)
{
	if (where->data->_parent != this)
	{
		src_code_chunk().err("AstNode::insert_child_after():  Eek!");
	}

	++_num_children;

	_finish_child_insert(_children.insert_after(where,
		std::move(to_insert)));
}
void AstNode::insert_child_before(ChildrenList::Node* where,
	Child&& to_insert)
{
	if (where->data->_parent != this)
	{
		src_code_chunk().err("AstNode::insert_child_before():  Eek!");
	}

	++_num_children;

	_finish_child_insert(_children.insert_before(where,
		std::move(to_insert)));
}


void AstNode::remove_child_after(ChildrenList::Node* where)
{
	if (where->data->_parent != this)
	{
		src_code_chunk().err("AstNode::remove_child_after():  Eek!");
	}

	--_num_children;

	_children.remove_after(where);
}
void AstNode::remove_child_before(ChildrenList::Node* where)
{
	if (where->data->_parent != this)
	{
		src_code_chunk().err("AstNode::remove_child_before():  Eek!");
	}

	--_num_children;

	_children.remove_before(where);
}
void AstNode::remove_child(ChildrenList::Node* where)
{
	if (where->data->_parent != this)
	{
		src_code_chunk().err("AstNode::remove_child():  Eek!");
	}

	--_num_children;

	_children.remove(where);
}
//--------

} // namespace frost_hdl
