#ifndef src_ast_node_classes_hpp
#define src_ast_node_classes_hpp

// src/ast_node_classes.hpp

#include "misc_includes.hpp"
#include "src_code_chunk_class.hpp"
#include "expr_value_class.hpp"
#include "lexer_class.hpp"


namespace frost_hdl
{

namespace ast
{

#define GEN_ACCEPT \
	virtual void accept(Visitor& visitor)

#include "list_of_ast_node_classes_define.hpp"
#define X(AstNodeType) \
	class AstNodeType;
LIST_OF_AST_NODE_CLASSES(X)
#undef X
#undef LIST_OF_AST_NODE_CLASSES

class Visitor;

#define GEN_POST_CONSTRUCTOR(AstNodeType) \
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(AstNodeType); \
	virtual ~AstNodeType() = default; \
	\
	GEN_ACCEPT

class NodeBase
{
public:		// types
	using TokSet = std::set<Tok>;
	using Children = std::map<string, std::vector<unique_ptr<NodeBase>>>;
	using Child = unique_ptr<NodeBase>;

protected:		// variables
	SrcCodeChunk _src_code_chunk;
	Children _children;

public:		// functions
	inline NodeBase()
	{
	}
	inline NodeBase(const SrcCodeChunk& s_src_code_chunk)
		: _src_code_chunk(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBase);

	inline bool has(const string& ident) const
	{
		//return ((children().count(ident) != 0)
		//	&& (children().at(ident).front().get() != nullptr));
		return (children().at(ident).front().get() != nullptr);
	}

	//template<typename FirstType, typename... RemArgTypes>
	//inline void append_children(ChildNode*& ret_node,
	//	FirstType&& first_child, RemArgTypes&&... rem_children)
	//{
	//	ret_node = _children.push_back(unique_ptr<NodeBase>(new NodeBase
	//		(move(first_child))));

	//	if constexpr (sizeof...(rem_children) != 0)
	//	{
	//		append_children(rem_children...);
	//	}
	//}
	inline const Children& children() const
	{
		return _children;
	}

	GEN_GETTER_BY_CON_REF(src_code_chunk)

protected:		// functions
	template<typename FirstType, typename... RemArgTypes>
	inline void _add_indiv_children(const string& first_ident,
		FirstType&& first_child, RemArgTypes&&... rem_children)
	{
		_insert_children_list(first_ident);
		_children[first_ident].push_back(move(first_child));
		if constexpr (sizeof...(rem_children) != 0)
		{
			_add_indiv_children(rem_children...);
		}
	}
	inline void _insert_children_list(const string& ident)
	{
		_children[ident] = std::vector<unique_ptr<NodeBase>>();
	}
	template<typename FirstType, typename... RemArgTypes>
	inline void _append_children(const string& ident,
		FirstType&& first_child, RemArgTypes&&... rem_children)
	{
		if (_children.count(ident) == 0)
		{
			_insert_children_list(ident);
		}
		_children[ident].push_back(move(first_child));

		if constexpr (sizeof...(rem_children) != 0)
		{
			_append_children(ident, rem_children...);
		}
	}
};


#define APPEND_CHILD(child) \
	#child, move(s_##child)

class NodeList : public NodeBase
{
public:		// functions
	inline NodeList(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
		_insert_children_list("list");
	}
	GEN_POST_CONSTRUCTOR(NodeList);

	inline void append_list_child(Child&& child)
	{
		_append_children("list", move(child));
	}
};

#include "ast_node_main_classes.hpp"


#undef GEN_ACCEPT
#undef GEN_BASIC
#undef GEN_LIST_BASIC
#undef GEN_LIST_W_ONE_C
#undef GEN_HAS_STRING
#undef GEN_POST_CONSTRUCTOR
#undef APPEND_CHILD

} // namespace ast


} // namespace frost_hdl

#endif		// src_ast_node_classes_hpp
