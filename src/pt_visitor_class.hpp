#ifndef src_pt_visitor_class_hpp
#define src_pt_visitor_class_hpp

// src/pt_visitor_class.hpp

#include "misc_includes.hpp"
#include "parse_tree_class.hpp"
#include "ast_node_main_classes.hpp"

namespace frost_hdl
{

class PtVisitor final
{
private:		// variables
	ParseTree* _pt_root = nullptr;
	ast::NodeBase::Child _ast_root;

	#define LIST_FOR_GEN_STACK(X) \
		X(BigNum, const BigNum&, num) \
		X(string, string, str) \
		X(Tok, Tok, tok) \

	#include "gen_stacks_stuff.hpp"
	#undef LIST_FOR_GEN_STACK

	std::stack<ast::NodeBase::Child> _ast_child_stack;

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
		_stacks.push_num(to_push);
	}
	inline auto _get_top_num()
	{
		return _stacks.get_top_num();
	}
	inline auto _pop_num()
	{
		return _stacks.pop_num();
	}

	inline void _push_str(const string& to_push)
	{
		_stacks.push_str(to_push);
	}
	inline auto _get_top_str()
	{
		return _stacks.get_top_str();
	}
	inline auto _pop_str()
	{
		return _stacks.pop_str();
	}

	inline void _push_tok(Tok to_push)
	{
		_stacks.push_tok(to_push);
	}
	inline auto _get_top_tok()
	{
		return _stacks.get_top_tok();
	}
	inline auto _pop_tok()
	{
		return _stacks.pop_tok();
	}

public:		// functions
	inline PtVisitor() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(PtVisitor);
	inline ~PtVisitor() = default;

	GEN_GETTER_AND_SETTER_BY_VAL(pt_root)

	void run();

	GEN_GETTER_BY_REF(ast_root)

private:		// functions
	void _visit(ParseTree* tree);

	void _visit_program(ParseTree* tree);
	void _visit_header_if(ParseTree* tree);
	void _visit_header_else_if(ParseTree* tree);
	void _visit_header_else(ParseTree* tree);
	void _visit_header_for(ParseTree* tree);
	void _visit_header_generate_if(ParseTree* tree);
	void _visit_header_else_generate_if(ParseTree* tree);
	void _visit_header_else_generate(ParseTree* tree);
	void _visit_package(ParseTree* tree);
	void _visit_scope_package(ParseTree* tree);
	void _visit_scope_package_item(ParseTree* tree);

};


} // namespace frost_hdl

#endif		// src_pt_visitor_class_hpp
