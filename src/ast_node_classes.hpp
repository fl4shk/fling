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
class Visitor;

class NodeBase
{
public:		// types
	typedef std::set<Tok> TokSet;

protected:		// variables
	//string _s;
	//ExprNum _n;
	SrcCodeChunk _src_code_chunk;
	CircLinkedList<unique_ptr<NodeBase>> _children;

public:		// functions
	inline NodeBase(const SrcCodeChunk& s_src_code_chunk)
		: _src_code_chunk(s_src_code_chunk)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeBase);
	virtual ~NodeBase() = default;

	virtual inline void accept(Visitor& visitor)
	{
	}

	template<typename FirstType, typename... RemArgTypes>
	inline void append_children(FirstType&& first_child,
		RemArgTypes&&... rem_children)
	{
		_children.push_back(unique_ptr<NodeBase>(new NodeBase(std::move
			(first_child))));
		if constexpr (sizeof...(rem_children) != 0)
		{
			append_children(rem_children...);
		}
	}

	GEN_GETTER_BY_CON_REF(src_code_chunk)
	GEN_GETTER_BY_CON_REF(children)
};


class NodeExprBase : public NodeBase
{
protected:		// variables
	ExprValue _n;

public:		// functions
	inline NodeExprBase(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeExprBase);
	virtual ~NodeExprBase() = default;

	GEN_GETTER_AND_SETTER_BY_CON_REF(n)
};

class NodeBinopBase : public NodeExprBase
{
public:		// functions
	NodeBinopBase(const SrcCodeChunk& s_src_code_chunk, NodeBase&& s_left,
		NodeBase&& s_right)
		: NodeExprBase(s_src_code_chunk)
	{
		append_children(std::move(s_left), std::move(s_right));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeBinopBase);
	virtual ~NodeBinopBase() = default;

	inline auto left()
	{
		return _children.front();
	}
	inline auto right()
	{
		return _children.back();
	}
};

class NodeUnopBase : public NodeExprBase
{
private:		// variables
	//using NodeIterator = typename _children.NodeIterator;

public:		// functions
	inline NodeUnopBase(const SrcCodeChunk& s_src_code_chunk,
		NodeBase&& s_only_child)
		: NodeExprBase(s_src_code_chunk)
	{
		append_children(std::move(s_only_child));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeUnopBase);
	virtual ~NodeUnopBase() = default;

	inline auto only_child()
	{
		return _children.front();
	}
};


class NodePackage : public NodeBase
{
public:		// constants
	static const inline TokSet tok_prefix_set = TokSet();
	static const inline Tok end_tok = Tok::KwPackage;

public:		// functions
	NodePackage(const SrcCodeChunk& s_src_code_chunk, NodeBase&& s_ident,
		NodeBase&& s_scope)
		: NodeBase(s_src_code_chunk)
		{
			append_children(std::move(s_ident), std::move(s_scope));
		}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodePackage);
	virtual ~NodePackage() = default;

	inline auto ident()
	{
		return _children.front();
	}
	inline auto scope()
	{
		return _children.back();
	}
};

class NodeModule : public NodeBase
{
public:		// constants
	static const inline TokSet tok_prefix_set = TokSet();
	static const inline Tok end_tok = Tok::KwModule;

public:		// functions
	NodeModule(const SrcCodeChunk& s_src_code_chunk, NodeBase&& s_ident,
		NodeBase&& s_scope)
		: NodeBase(s_src_code_chunk)
		{
			append_children(std::move(s_ident), std::move(s_scope));
		}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeModule);
	virtual ~NodeModule() = default;

	inline auto ident()
	{
		return _children.front();
	}
	inline auto scope()
	{
		return _children.back();
	}
};

} // namespace ast


} // namespace frost_hdl

#endif		// src_ast_node_classes_hpp
