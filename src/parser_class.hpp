#ifndef src_parser_class_hpp
#define src_parser_class_hpp

// src/parser_class.hpp

#include "misc_includes.hpp"
#include "lexer_class.hpp"
#include "ast_node_classes.hpp"
#include "opt_as_func_arg_parser_base_class.hpp"
#include "err_warn_base_class.hpp"
#include "parse_tree_class.hpp"

namespace frost_hdl
{

class Parser final : public OptAsFuncArgParserBase<Lexer>
{
public:		// types
	using ParseRet = typename OptAsFuncArgParserBase<Lexer>::ParseRet;

private:		// variables
	//ast::NodeBase::Child _ast_root;
	unique_ptr<ParseTree> _pt_root;
	size_t _filename_index;

	#define LIST_FOR_GEN_STACK(X) \
		X(BigNum, const BigNum&, num) \
		X(string, string, str) \
		X(Tok, Tok, tok) \

	#include "gen_stacks_stuff.hpp"
	#undef LIST_FOR_GEN_STACK


	std::stack<ParseTree> _pt_stack;
	inline void _push_pt(ParseTree&& to_push)
	{
		_pt_stack.push(std::move(to_push));
	}
	inline auto _pop_pt()
	{
		auto&& ret = _pt_stack.top();
		_pt_stack.pop();
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
	Parser();
	~Parser();
};

} // namespace frost_hdl


#endif		// src_parser_class_hpp
