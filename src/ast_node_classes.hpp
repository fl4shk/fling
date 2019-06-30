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

#define BLANK_TOK_PREFIX_SET(some_end_tok) \
public:		/* constants */ \
	static const inline auto tok_prefix_set = TokSet(); \
	static const inline auto end_tok = some_end_tok
#define TOK_PREFIX_SET(args, some_end_tok) \
public:		/* constants */ \
	static const inline auto tok_prefix_set = TokSet(args); \
	static const inline auto end_tok = some_end_tok


class Visitor;

class NodeBase
{
public:		// types
	using TokSet = std::set<Tok>;
	using Children = std::map<string, std::vector<unique_ptr<NodeBase>>>;

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
		return (children().count(ident) != 0);
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
		_children[first_ident].push_back(unique_ptr<NodeBase>(new NodeBase
			(move(first_child))));
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
		_children[ident].push_back(unique_ptr<NodeBase>(new NodeBase
			(move(first_child))));

		if constexpr (sizeof...(rem_children) != 0)
		{
			_append_children(ident, rem_children...);
		}
	}
};

class NodeScopeBase : public NodeBase
{
public:		// functions
	inline NodeScopeBase(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
		_insert_children_list("list");
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeScopeBase);
	virtual ~NodeScopeBase() = default;

	GEN_ACCEPT;

	inline void append_child(NodeBase&& child)
	{
		_append_children("list", move(child));
	}
};

class NodePackage : public NodeBase
{
	BLANK_TOK_PREFIX_SET(Tok::KwPackage);

public:		// functions
	inline NodePackage(const SrcCodeChunk& s_src_code_chunk,
		NodeBase&& s_ident, NodeBase&& s_scope)
		: NodeBase(s_src_code_chunk)
		{
			_add_indiv_children("ident", move(s_ident),
				"scope", move(s_scope));
		}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodePackage);
	virtual ~NodePackage() = default;

	GEN_ACCEPT;

};

#define GEN_SCOPE(AstNodeScopeName) \
class AstNodeScopeName : public NodeScopeBase \
{ \
public:		/* functions */ \
	inline AstNodeScopeName(const SrcCodeChunk& s_src_code_chunk) \
		: NodeScopeBase(s_src_code_chunk) \
	{ \
	} \
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(AstNodeScopeName); \
	virtual ~AstNodeScopeName() = default; \
	\
	GEN_ACCEPT; \
};

GEN_SCOPE(NodeScopePackage)

class NodeModule : public NodeBase
{
	BLANK_TOK_PREFIX_SET(Tok::KwModule);

public:		// functions
	inline NodeModule(const SrcCodeChunk& s_src_code_chunk,
		NodeBase&& s_ident, NodeBase&& s_scope)
		: NodeBase(s_src_code_chunk)
		{
			_add_indiv_children("ident", move(s_ident),
				"scope", move(s_scope));
		}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeModule);
	virtual ~NodeModule() = default;

	GEN_ACCEPT;
};

GEN_SCOPE(NodeScopeModule)

class NodeEnum : public NodeBase
{
	BLANK_TOK_PREFIX_SET(Tok::KwEnum);

public:		// functions
	inline NodeEnum(const SrcCodeChunk& s_src_code_chunk,
		NodeBase&& s_ident, NodeBase&& s_scope)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children("ident", move(s_ident),
			"scope", move(s_scope));
	}
	inline NodeEnum(const SrcCodeChunk& s_src_code_chunk,
		NodeBase&& s_typename, NodeBase&& s_ident, NodeBase&& s_scope)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children("typename", move(s_typename),
			"ident", move(s_ident),
			"scope", move(s_scope));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeEnum);
	virtual ~NodeEnum() = default;

	GEN_ACCEPT;
};

GEN_SCOPE(NodeScopeEnum)

class NodeClass : public NodeBase
{
	TOK_PREFIX_SET({Tok::KwPacked}, Tok::KwClass);

private:		// variables
	bool _packed = false;

public:		// functions
	inline NodeClass(const SrcCodeChunk& s_src_code_chunk,
		bool s_packed, NodeBase&& s_ident, NodeBase&& s_scope)
		: NodeBase(s_src_code_chunk)
	{
		_packed = s_packed;
		_add_indiv_children("ident", move(s_ident),
			"scope", move(s_scope));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeClass);
	virtual ~NodeClass() = default;

	GEN_ACCEPT;
};

GEN_SCOPE(NodeScopeClass)

class NodeExprBase : public NodeBase
{
public:		// variables
	ExprValue value;

public:		// functions
	inline NodeExprBase(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeExprBase);
	virtual ~NodeExprBase() = default;

	GEN_ACCEPT;
};

class NodeBinopBase : public NodeExprBase
{
public:		// functions
	NodeBinopBase(const SrcCodeChunk& s_src_code_chunk, NodeBase&& s_left,
		NodeBase&& s_right)
		: NodeExprBase(s_src_code_chunk)
	{
		_add_indiv_children("left", move(s_left),
			"right", move(s_right));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeBinopBase);
	virtual ~NodeBinopBase() = default;

	GEN_ACCEPT;
};

class NodeUnopBase : public NodeExprBase
{
public:		// functions
	inline NodeUnopBase(const SrcCodeChunk& s_src_code_chunk,
		NodeBase&& s_child)
		: NodeExprBase(s_src_code_chunk)
	{
		_add_indiv_children("child", move(s_child));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeUnopBase);
	virtual ~NodeUnopBase() = default;

	GEN_ACCEPT;
};


#undef GEN_ACCEPT
#undef BLANK_TOK_PREFIX_SET
#undef TOK_PREFIX_SET
#undef GEN_SCOPE

} // namespace ast


} // namespace frost_hdl

#endif		// src_ast_node_classes_hpp
