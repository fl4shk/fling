#ifndef src_ast_node_class_hpp
#define src_ast_node_class_hpp

// src/ast_node_class.hpp

#include "misc_includes.hpp"
//#include "table_types.hpp"

#include "has_src_code_chunk_base_classes.hpp"

//#include "symbol_class.hpp"
//#include "scoped_table_classes.hpp"
#include "symbol_class.hpp"


namespace frost_hdl
{

class AstNode : public HasSrcCodeChunkAndIdentBase
{
public:		// types
	typedef std::unique_ptr<AstNode> Child;
	typedef CircLinkedList<Child> ChildrenList;

	// Node type
	enum class Type
	{
		Module,
		Interface,
		Package,
		Function,
		Task,

		Expr,
	};

protected:		// variables
	AstNode * _parent = nullptr,
		* _actual_scope = nullptr;

	ChildrenList _children;


public:		// functions
	//--------
	AstNode();

	AstNode(const SrcCodeChunk& s_src_code_chunk, const Ident& s_ident,
		AstNode* s_parent);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(AstNode);

	virtual ~AstNode();
	//--------

	//--------
	inline bool is_scope() const
	{
		return (_actual_scope == this);
	}
	//--------

	//--------
	void push_child_back(AstNode&& to_push);
	void push_child_front(AstNode&& to_push);

	void insert_child_after(ChildrenList::Node* where,
		AstNode&& to_insert);
	void insert_child_before(ChildrenList::Node* where,
		AstNode&& to_insert);

	void remove_child_after(ChildrenList::Node* where);
	void remove_child_before(ChildrenList::Node* where);
	void remove_child(ChildrenList::Node* where);


	inline ChildrenList::NodeIterator begin()
	{
		return _children.begin();
	}
	inline ChildrenList::NodeIterator end()
	{
		return _children.end();
	}
	inline ChildrenList::NodeIterator cbegin() const
	{
		return _children.cbegin();
	}
	inline ChildrenList::NodeIterator cend() const
	{
		return _children.cend();
	}
	//--------


	//--------
	GEN_GETTER_BY_VAL(parent)
	GEN_GETTER_BY_VAL(actual_scope)
	GEN_GETTER_BY_CON_REF(children)
	//GEN_GETTERS_BY_CON_REF_AND_REF(children)
	//GEN_GETTER_BY_CON_REF(children)
	//--------

private:		// functions
	inline void _finish_child_insert(ChildrenList::Node* inserted)
	{
		inserted->data->_parent = this;
		inserted->data->_actual_scope = _actual_scope;
	}
	inline Child _convert_to_child(AstNode&& to_convert)
	{
		return Child(new AstNode(std::move(to_convert)));
	}
};

} // namespace frost_hdl

#endif		// src_ast_node_class_hpp
