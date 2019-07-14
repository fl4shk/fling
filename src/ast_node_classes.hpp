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
#define X(AstNodeType, suffix) \
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

	#include "ast_node_type_enum.hpp"

protected:		// variables
	SrcCodeChunk _src_code_chunk;


public:		// functions
	inline NodeBase()
	{
	}
	inline NodeBase(const SrcCodeChunk& s_src_code_chunk)
		: _src_code_chunk(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBase);
	static inline bool has(const Child& child)
	{
		return (child.get() != nullptr);
	}

	virtual Type type() const
	{
		return Type::Base;
	}
	virtual string name() const
	{
		return "Base";
	}
	//virtual string to_string() const
	//{
	//	return sconcat(name(), "()\n");
	//}
	virtual inline void append(Child&& child)
	{
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
public:		// variables
	std::vector<Child> list;

public:		// functions
	inline NodeList(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeList);

	virtual inline void append(Child&& to_append)
	{
		list.push_back(std::move(to_append));
	}

	virtual Type type() const
	{
		return Type::List;
	}
	virtual string name() const
	{
		return "List";
	}
	//virtual string to_string() const
	//{
	//	string ret;
	//	ret += name();
	//	ret += "(";
	//	for (size_t i=0; i<list.size(); ++i)
	//	{
	//		ret += list.at(i).to_string();
	//		if ((i + 1) != list.size())
	//		{
	//			ret += ", ";
	//		}
	//	}
	//	ret += ")\n";
	//	return ret;
	//}
};

#include "ast_node_main_classes.hpp"

#undef GEN_ACCEPT
#undef GEN_POST_CONSTRUCTOR
#undef LIST_OF_AST_NODE_CLASSES

} // namespace ast


} // namespace frost_hdl

#endif		// src_ast_node_classes_hpp
