#ifndef src_ast_gen_class_hpp
#define src_ast_gen_class_hpp

// src/ast_gen_class.hpp

#include "misc_includes.hpp"

enum class Tok
{
	Comment,
	Colon,
	Semicolon,
	Comma,
	Ident,
	Unknown,
	Done,
};
extern const std::map<Tok, string> tok_ident_map;

class Lexer final : public LexerBase<Tok>
{
public:		// functions
	Lexer(const string& s_filename, string* s_text);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Lexer)
	~Lexer();

	Tok next_tok(bool just_test);
	inline auto src_code_chunk(State* state=nullptr) const
	{
		return LexerBase<Tok>::src_code_chunk<SrcCodeChunk>(state);
	}

private:		// functions
	void _inner_next_tok();
};

class AstGen final : public ParserBase<Lexer>
{
public:		// types
	using Base = ParserBase<Lexer>;
	using TokSet = std::set<Tok>;

	class Var final
	{
	public:		// variables
		string type, ident;

	public:		// functions
		Var() = default;
		GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Var);
		~Var() = default;
	};

	class Node final
	{
	public:		// variables
		string ident, extends;
		std::vector<string> children;
		std::vector<Var> var_vec;
		std::set<string> children_ident_set, var_ident_set;
	
	public:		// functions
		Node() = default;
		GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Node);
		~Node() = default;
	};

public:		// constants
	static const string node_base_str, node_list_str;

private:		// variables
	std::vector<Node> _node_vec;
	std::set<string> _node_ident_set;

public:		// functions
	AstGen(std::vector<string>&& s_filename_vec);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(AstGen)
	~AstGen();

	void run();

private:		// functions
	inline std::string _msg_for_expect(Tok tok,
		const LexerState& lex_state) const
	{
		return Base::_msg_for_expect(tok, tok_ident_map, lex_state);
	}
	inline void _expect(Tok tok, const LexerState& lex_state)
	{
		Base::_expect(tok, tok_ident_map, lex_state);
	}
	inline void _expect(Tok tok)
	{
		_expect(tok, _lexer().state());
	}
	inline void _unexpected(const LexerState& lex_state)
	{
		Base::_unexpected(tok_ident_map, lex_state);
	}
	inline void _unexpected()
	{
		_unexpected(_lexer().state());
	}
	inline void _unexpected(Lexer* lexer)
	{
		Base::_unexpected(tok_ident_map, lexer);
	}
	inline bool _to_next_in_list(Tok end, Tok separator=Tok::Comma)
	{
		return Base::_to_next_in_list(end, separator, tok_ident_map);
	}
	inline void _next_lss_tokens()
	{
		Base::_next_lss_tokens(tok_ident_map);
	}
	bool _check_prefixed_tok_seq(const TokSet& prefix_set, Tok end)
	{
		return Base::_check_prefixed_tok_seq(prefix_set, end);
	}
	bool _check_prefixed_tok_seq(Tok end)
	{
		return Base::_check_prefixed_tok_seq(TokSet(), end);
	}
	inline auto _lex_tok() const
	{
		return _lexer().tok();
	}
	inline void _next_tok()
	{
		_lexer.next_tok(just_test());
	}

	bool _parse_node();
	bool _parse_extends();
	bool _parse_var();
	bool _parse_child();
};

#endif		// src_ast_gen_class_hpp
