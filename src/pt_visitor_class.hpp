#ifndef src_pt_visitor_class_hpp
#define src_pt_visitor_class_hpp

// src/pt_visitor_class.hpp

#include "misc_includes.hpp"
#include "parse_tree_class.hpp"
#include "ast_node_classes.hpp"

namespace frost_hdl
{

class PtVisitor final
{
public:		// types
	using OnePtChild = typename ParseTree::OneChild;
	using PtChildVec = typename ParseTree::ChildVec;
	using VisitFunc = (PtVisitor::*)(ParseTree* tree);

private:		// variables
	map<string, VisitFunc> _func_map;
	ParseTree* _pt_root = nullptr;
	ast::NodeBase::Child _ast_root;

	std::stack<ast::NodeBase::Child> _ast_child_stack;
	std::stack<BigNum> _num_stack;
	std::stack<string> _str_stack;
	std::stack<Tok> _tok_stack;


	inline void _push_ast_child(ast::NodeBase::Child&& to_push)
	{
		_ast_child_stack.push(std::move(to_push));
	}
	template<typename ChildType>
	inline void _push_ast_child(ChildType&& to_push)
	{
		_push_ast_child(ast::NodeBase::Child(new ChildType(std::move
			(to_push))));
	}
	template<typename ChildType>
	inline auto _to_ast_child(ChildType&& to_convert)
	{
		return ast::NodeBase::Child(new ChildType(std::move(to_convert)));
	}
	inline auto _pop_ast_child()
	{
		auto&& ret = _ast_child_stack.top();
		_ast_child_stack.pop();
		return std::move(ret);
	}

	inline void _push_num(const BigNum& to_push)
	{
		_num_stack.push(to_push);
	}
	inline auto _pop_num()
	{
		auto&& ret = _num_stack.top();
		_num_stack.pop();
		return std::move(ret);
	}

	inline void _push_str(const string& to_push)
	{
		_str_stack.push(to_push);
	}
	inline auto _pop_str()
	{
		auto&& ret = _str_stack.top();
		_str_stack.pop();
		return std::move(ret);
	}

	inline void _push_tok(Tok to_push)
	{
		_tok_stack.push(to_push);
	}
	inline auto _pop_tok()
	{
		auto&& ret = _tok_stack.top();
		_tok_stack.pop();
		return std::move(ret);
	}

public:		// functions
	PtVisitor();
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(PtVisitor);
	inline ~PtVisitor() = default;

	GEN_GETTER_AND_SETTER_BY_VAL(pt_root)

	void run();

	GEN_GETTER_BY_REF(ast_root)

private:		// functions
	void _accept(ParseTree* tree);

	#include "list_of_parse_tree_nodes_define.hpp"
	#define X(node) \
		void _visit_##node(ParseTree* tree);
	LIST_OF_PARSE_TREE_NODES(X)
	#undef X
	#undef LIST_OF_PARSE_TREE_NODES

};


} // namespace frost_hdl

#endif		// src_pt_visitor_class_hpp
