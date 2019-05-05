#include "ast_node_class.hpp"

namespace frost_hdl
{


//--------
AstNode::AstNode()
{
}

AstNode::AstNode(const SrcCodeChunk& s_src_code_chunk, Type s_type,
	AstNode* s_parent)
	: HasSrcCodeChunkBase(s_src_code_chunk), _type(s_type),
	_parent(s_parent)
{
}

AstNode::~AstNode()
{
}
//--------

//--------
const Ident AstNode::type_to_str() const
{
	switch (type())
	{
		#define X(val) \
			case Type::val: \
				return #val; \

		LIST_OF_AST_NODE_TYPES(X)

		#undef X

		default:
			src_code_chunk().err("AstNode::type_to_str():  Eek!");
			break;
	}
	return "9,001";
}
//--------

//--------
void AstNode::push_child_back(Child&& to_push)
{
	_finish_child_insert(_children.push_back(std::move(to_push)));
}
void AstNode::push_child_front(Child&& to_push)
{
	_finish_child_insert(_children.push_front(std::move(to_push)));
}

void AstNode::insert_child_after(ChildrenList::Node* where,
	Child&& to_insert)
{
	if (where->data->parent() != this)
	{
		src_code_chunk().err("AstNode::insert_child_after():  Eek!");
	}

	_finish_child_insert(_children.insert_after(where,
		std::move(to_insert)));
}
void AstNode::insert_child_before(ChildrenList::Node* where,
	Child&& to_insert)
{
	if (where->data->parent() != this)
	{
		src_code_chunk().err("AstNode::insert_child_before():  Eek!");
	}

	_finish_child_insert(_children.insert_before(where,
		std::move(to_insert)));
}


void AstNode::remove_child_after(ChildrenList::Node* where)
{
	if (where->data->parent() != this)
	{
		src_code_chunk().err("AstNode::remove_child_after():  Eek!");
	}

	_children.remove_after(where);
	_finish_child_remove();
}
void AstNode::remove_child_before(ChildrenList::Node* where)
{
	if (where->data->parent() != this)
	{
		src_code_chunk().err("AstNode::remove_child_before():  Eek!");
	}

	_children.remove_before(where);
	_finish_child_remove();
}
void AstNode::remove_child(ChildrenList::Node* where)
{
	if (where->data->parent() != this)
	{
		src_code_chunk().err("AstNode::remove_child():  Eek!");
	}

	_children.remove(where);
	_finish_child_remove();
}
//--------

//--------
std::string AstNode::_inner_dump(size_t num_indents) const
{
	std::string ret;

	for (size_t i=0; i<num_indents; ++i)
	{
		ret += "  ";
	}

	ret += sconcat(type_to_str(), "(\"", text(), "\")\n");

	//for (const auto& iter : children())
	for (auto iter=cbegin(); iter!=cend(); ++iter)
	{
		ret += iter->data->_inner_dump(num_indents + 1);
	}

	return ret;
}
//--------

} // namespace frost_hdl
