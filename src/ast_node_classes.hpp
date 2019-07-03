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
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeBase);
	virtual ~NodeBase() = default;

	GEN_ACCEPT;

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

protected:		// variables
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

#define GEN_BASIC(AstNodeType) \
class AstNodeType : public NodeBase \
{ \
public:		/* functions */ \
	inline AstNodeType(const SrcCodeChunk& s_src_code_chunk) \
		: NodeBase(s_src_code_chunk) \
	{ \
	} \
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(AstNodeType); \
	virtual ~AstNodeType() = default; \
	\
	GEN_ACCEPT; \
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
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeList);
	virtual ~NodeList() = default;

	GEN_ACCEPT;

	inline void append_list_child(Child&& child)
	{
		_append_children("list", move(child));
	}
};

#define GEN_LIST_BASIC(AstNodeType) \
class AstNodeType : public NodeList \
{ \
public:		/* functions */ \
	inline AstNodeType(const SrcCodeChunk& s_src_code_chunk) \
		: NodeList(s_src_code_chunk) \
	{ \
	} \
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(AstNodeType); \
	virtual ~AstNodeType() = default; \
	\
	GEN_ACCEPT; \
};

#define GEN_LIST_W_ONE_C(AstNodeType, child) \
class AstNodeType : public NodeList \
{ \
public:		/* functions */ \
	inline AstNodeType(const SrcCodeChunk& s_src_code_chunk, \
		Child&& s_##child) \
		: NodeList(s_src_code_chunk) \
	{ \
		_add_indiv_children(APPEND_CHILD(child)); \
	} \
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(AstNodeType); \
	virtual ~AstNodeType() = default; \
	\
	GEN_ACCEPT; \
};

class NodePackage : public NodeBase
{
public:		// functions
	inline NodePackage(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident, Child&& s_scope)
		: NodeBase(s_src_code_chunk)
		{
			_add_indiv_children(APPEND_CHILD(ident),
				APPEND_CHILD(scope));
		}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodePackage);
	virtual ~NodePackage() = default;

	GEN_ACCEPT;
};

GEN_LIST_BASIC(NodeScopePackage)

class NodeModule : public NodeBase
{
public:		// functions
	inline NodeModule(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident, Child&& s_param_list, Child&& s_port_list,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk)
		{
			_add_indiv_children(APPEND_CHILD(ident),
				APPEND_CHILD(param_list),
				APPEND_CHILD(port_list),
				APPEND_CHILD(scope));
		}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeModule);
	virtual ~NodeModule() = default;

	GEN_ACCEPT;
};

GEN_LIST_BASIC(NodeScopeModule)
GEN_LIST_W_ONE_C(NodeInputSubPortList, typename)
GEN_LIST_W_ONE_C(NodeOutputSubPortList, typename)
GEN_LIST_W_ONE_C(NodeBidirSubPortList, typename)

GEN_LIST_W_ONE_C(NodeSubParamList, primary)
GEN_LIST_W_ONE_C(NodePostTypenameIdent, ident)
class NodeBracketPair : public NodeBase
{
public:		// functions
	// Blank brackets (`[]`) indicate that (a) this pair is on a port
	// and (b) that this typename's generics or variable's dimensions are
	// determined by what is connected to the port.
	// For generics, it is different from when the brackets are left out
	// entirely, as that indicates use of purely default values for the
	// generics.  For arrays, it is not possible to have them without
	// brackets.
	// When there is no expression, it indicates that this bracket pair is
	// blank.
	inline NodeBracketPair(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(expr));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeBracketPair);
	virtual ~NodeBracketPair() = default;

	GEN_ACCEPT;
};

class NodeHasString : public NodeBase
{
protected:		// variables
	string _s;

public:		// functions
	inline NodeHasString(const SrcCodeChunk& s_src_code_chunk,
		const string& s_s)
		: NodeBase(s_src_code_chunk), _s(s_s)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeHasString);
	virtual ~NodeHasString() = default;

	GEN_ACCEPT;
	GEN_GETTER_AND_SETTER_BY_CON_REF(s)
};

#define GEN_HAS_STRING_BASIC(AstNodeType) \
class AstNodeType : public NodeHasString \
{ \
public:		/* functions */ \
	inline AstNodeType(const SrcCodeChunk& s_src_code_chunk, \
		const string& s_s) \
		: NodeHasString(s_src_code_chunk, s_s) \
	{ \
	} \
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(AstNodeType); \
	virtual ~AstNodeType() = default; \
	\
	GEN_ACCEPT; \
};

GEN_HAS_STRING_BASIC(NodeIdent)
GEN_HAS_STRING_BASIC(NodeConstString)


#include "ast_node_type_classes.hpp"
#include "ast_node_expr_classes.hpp"

#undef GEN_ACCEPT
#undef GEN_BASIC
#undef GEN_LIST_BASIC
#undef GEN_LIST_W_ONE_C
#undef GEN_HAS_STRING
#undef APPEND_CHILD

} // namespace ast


} // namespace frost_hdl

#endif		// src_ast_node_classes_hpp
