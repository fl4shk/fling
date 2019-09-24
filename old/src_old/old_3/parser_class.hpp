#ifndef src_parser_class_hpp
#define src_parser_class_hpp

// src/parser_class.hpp

#include "misc_includes.hpp"
#include "lexer_class.hpp"
#include "ast_node_classes.hpp"
#include "err_warn_base_class.hpp"
#include "parse_tree_class.hpp"

namespace frost_hdl
{

class Parser final : public OptAsFuncArgParserBase<Lexer>
{
public:		// types
	using Base = OptAsFuncArgParserBase<Lexer>;
	using Opt = typename Base::Opt;
	using ParseRet = typename Base::ParseRet;

private:		// variables
	//ast::NodeBase::Child _ast_root;
	unique_ptr<ParseTree> _pt_root;

	#define LIST_FOR_GEN_STACK(X) \
		X(BigNum, const BigNum&, num) \
		X(string, string, str) \
		X(Tok, Tok, tok) \

	#include "gen_stacks_stuff.hpp"
	#undef LIST_FOR_GEN_STACK


	std::stack<ParseTree> _pt_stack;
	inline void _push_pt(ParseTree&& to_push)
	{
		_pt_stack.push(move(to_push));
	}
	inline auto _pop_pt()
	{
		auto&& ret = _pt_stack.top();
		_pt_stack.pop();
		return move(ret);
	}

	inline void _push_num(const BigNum& to_push)
	{
		_stacks.push_num(to_push);
	}
	inline auto _pop_num()
	{
		return _stacks.pop_num();
	}

	inline void _push_str(const string& to_push)
	{
		_stacks.push_str(to_push);
	}
	inline auto _pop_str()
	{
		return _stacks.pop_str();
	}

	inline void _push_tok(Tok to_push)
	{
		_stacks.push_tok(to_push);
	}
	inline auto _pop_tok()
	{
		return _stacks.pop_tok();
	}

public:		// functions
	Parser(const string& s_filename, string* s_text);
	~Parser();

private:		// functions
	#include "list_of_parse_tree_nodes_define.hpp"
	#define X(node) \
		ParseRet _parse_##node(Opt opt);
	LIST_OF_PARSE_TREE_NODES(X)
	#undef X
	#undef LIST_OF_PARSE_TREE_NODES
};

} // namespace frost_hdl


#endif		// src_parser_class_hpp
