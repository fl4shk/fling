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
	using Child = unique_ptr<NodeBase>;


protected:		// variables
	SrcCodeChunk _src_code_chunk;

	#include "ast_node_type_enum.hpp"

public:		// functions
	inline NodeBase()
	{
	}
	inline NodeBase(const SrcCodeChunk& s_src_code_chunk)
		: _src_code_chunk(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBase);

	virtual Type type() const
	{
		return Type::Base;
	}

	GEN_GETTER_BY_CON_REF(src_code_chunk)

protected:		// functions
	//template<typename FirstType, typename... RemArgTypes>
	//inline void _add_indiv_children(const string& first_ident,
	//	FirstType&& first_child, RemArgTypes&&... rem_children)
	//{
	//	_insert_children_list(first_ident);
	//	_children[first_ident].push_back(move(first_child));
	//	if constexpr (sizeof...(rem_children) != 0)
	//	{
	//		_add_indiv_children(rem_children...);
	//	}
	//}
	//inline void _insert_children_list(const string& ident)
	//{
	//	_children[ident] = std::vector<unique_ptr<NodeBase>>();
	//}
	//template<typename FirstType, typename... RemArgTypes>
	//inline void _append_children(const string& ident,
	//	FirstType&& first_child, RemArgTypes&&... rem_children)
	//{
	//	if (_children.count(ident) == 0)
	//	{
	//		_insert_children_list(ident);
	//	}
	//	_children[ident].push_back(move(first_child));

	//	if constexpr (sizeof...(rem_children) != 0)
	//	{
	//		_append_children(ident, rem_children...);
	//	}
	//}
};

class NodeList : public NodeBase
{
protected:		// variables
	std::vector<Child> _list;

public:		// functions
	inline NodeList(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeList);

	inline void append_child(Child&& to_append)
	{
		_list.push_back(std::move(to_append));
	}

	virtual Type type() const
	{
		return Type::List;
	}

	GEN_GETTER_BY_CON_REF(list)
};

#include "ast_node_main_classes.hpp"

#undef GEN_ACCEPT
#undef GEN_POST_CONSTRUCTOR
#undef LIST_OF_AST_NODE_CLASSES

} // namespace ast


} // namespace frost_hdl

#endif		// src_ast_node_classes_hpp
