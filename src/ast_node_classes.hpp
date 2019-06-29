#ifndef src_ast_node_classes_hpp
#define src_ast_node_classes_hpp

// src/ast_node_classes.hpp

#include "misc_includes.hpp"
#include "src_code_chunk_class.hpp"
#include "expr_value_class.hpp"
#include "lexer_class.hpp"


namespace frost_hdl
{

class AstVisitor;

class AstNodeBase
{
public:		// types
	typedef std::set<Tok> TokSet;

protected:		// variables
	//string _s;
	//ExprNum _n;
	SrcCodeChunk _src_code_chunk;
	//std::vector<unique_ptr<AstNodeBase>> _children;

public:		// variables
	CircLinkedList<AstNodeBase> children;

public:		// functions
	AstNodeBase(const SrcCodeChunk& s_src_code_chunk);
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(AstNodeBase);
	virtual ~AstNodeBase() = default;

	virtual void accept(AstVisitor& visitor);

	//inline void append_child(unique_ptr<AstNodeBase>&& child)
	//{
	//	_children.push_back(std::move(child));
	//}

	virtual const TokSet prefix_tok_set() const
	{
		return TokSet();
	}
	virtual Tok end_tok() const
	{
		return Tok::Comment;
	}

	GEN_GETTER_BY_CON_REF(src_code_chunk)
	//GEN_GETTER_BY_CON_REF(children)
};


class AstNodeExprBase : public AstNodeBase
{
protected:		// variables
	ExprValue _n;

public:		// functions
	AstNodeExprBase(const SrcCodeChunk& s_src_code_chunk);
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(AstNodeExprBase);
	virtual ~AstNodeExprBase() = default;

	virtual void eval();

	GEN_GETTER_AND_SETTER_BY_CON_REF(n)
};

class AstNodeBinopBase : public AstNodeExprBase
{
public:		// functions
	AstNodeBinopBase(const SrcCodeChunk& s_src_code_chunk,
		unique_ptr<AstNodeBase>&& s_left,
		unique_ptr<AstNodeBase>&& s_right);
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(AstNodeBinopBase);
	virtual ~AstNodeBinopBase() = default;

	inline auto& left()
	{
		return _children.at(0);
	}
	inline const auto& left() const
	{
		return children().at(0);
	}
	inline auto& right()
	{
		return _children.at(1);
	}
	inline const auto& right() const
	{
		return children().at(1);
	}
};

class AstNodeUnopBase : public AstNodeExprBase
{
public:		// functions
	AstNodeUnopBase(const SrcCodeChunk& s_src_code_chunk,
		unique_ptr<AstNodeBase>&& s_only_child);
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(AstNodeUnopBase);
	virtual ~AstNodeUnopBase() = default;

	inline auto& only_child()
	{
		return children().at(0);
	}
	inline const auto& only_child() const
	{
		return _children.at(0);
	}
};



} // namespace frost_hdl

#endif		// src_ast_node_classes_hpp
