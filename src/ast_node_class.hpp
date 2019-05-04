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
	typedef CircLinkedList<AstNode> ChildrenList;

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

	std::unique_ptr<ChildrenList> _children;


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
	void insert_child_after(const ChildrenList::NodeIterator& where,
		AstNode&& to_insert);
	void insert_child_before(const ChildrenList::NodeIterator& where,
		AstNode&& to_insert);
	void push_child_back(AstNode&& to_push);
	void push_child_front(AstNode&& to_push);
	//--------


	//--------
	inline ChildrenList& children()
	{
		return *_children;
	}
	inline const ChildrenList& children() const
	{
		return *_children;
	}

	GEN_GETTER_BY_VAL(parent)
	GEN_GETTER_BY_VAL(actual_scope)
	//GEN_GETTERS_BY_CON_REF_AND_REF(children)
	//GEN_GETTER_BY_CON_REF(children)
	//--------

private:		// functions
	template<typename NodeIteratorType>
	inline void finish_child_insert(NodeIteratorType inserted)
	{
		inserted->data._parent = this;

		// I'm not 100% certain this is correct, but I *think* it is.
		inserted->data._actual_scope = _actual_scope;
	}
};

} // namespace frost_hdl

#endif		// src_ast_node_class_hpp
