#ifndef src_ast_node_class_hpp
#define src_ast_node_class_hpp

// src/ast_node_class.hpp

#include "misc_includes.hpp"
//#include "table_types.hpp"

#include "has_src_code_chunk_base_classes.hpp"

//#include "symbol_class.hpp"
//#include "scoped_table_classes.hpp"
#include "expr_value_class.hpp"
#include "symbol_class.hpp"

#include "ast_node_type_list_stuff.hpp"


namespace frost_hdl
{

class AstNode final : public HasSrcCodeChunkBase
{
public:		// types
	typedef std::unique_ptr<AstNode> Child;
	typedef CircLinkedList<Child> ChildrenList;

	typedef AstNodeType Type;


private:		// variables
	Type _type = Type::Bad;

	AstNode * _parent = nullptr,
		* _actual_scope = nullptr;

	ChildrenList _children;
	size_t _num_children = 0;

	ExprValue _expr_value;

public:		// functions
	//--------
	AstNode();

	AstNode(const SrcCodeChunk& s_src_code_chunk, Type s_type,
		AstNode* s_parent);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(AstNode);

	~AstNode();
	//--------

	//--------
	inline std::string dump(bool show_src_code_chunk) const
	{
		return _inner_dump(0, show_src_code_chunk);
	}
	const Ident type_to_str() const;
	//--------

	//--------
	inline bool is_scope() const
	{
		return (_actual_scope == this);
	}
	//--------

	//--------
	void push_child_back(Child&& to_push);
	void push_child_front(Child&& to_push);

	void insert_child_after(ChildrenList::Node* where, Child&& to_insert);
	void insert_child_before(ChildrenList::Node* where, Child&& to_insert);

	void remove_child_after(ChildrenList::Node* where);
	void remove_child_before(ChildrenList::Node* where);
	void remove_child(ChildrenList::Node* where);

	inline auto begin()
	{
		return _children.begin();
	}
	inline auto end()
	{
		return _children.end();
	}
	inline auto cbegin() const
	{
		return _children.cbegin();
	}
	inline auto cend() const
	{
		return _children.cend();
	}
	//--------

	//--------
	inline const auto& text() const
	{
		return src_code_chunk().text();
	}

	GEN_GETTER_BY_VAL(type)
	GEN_GETTER_BY_VAL(parent)
	GEN_GETTER_AND_SETTER_BY_VAL(actual_scope)
	GEN_GETTER_BY_CON_REF(children)
	GEN_GETTER_BY_VAL(num_children)
	//--------

private:		// functions
	inline void _finish_child_insert(ChildrenList::Node* inserted)
	{
		inserted->data->_parent = this;
		inserted->data->_actual_scope = _actual_scope;
		++_num_children;
	}
	inline void _finish_child_remove()
	{
		--_num_children;
	}

	std::string _inner_dump(size_t num_indents,
		bool show_src_code_chunk) const;
};

} // namespace frost_hdl

#endif		// src_ast_node_class_hpp
