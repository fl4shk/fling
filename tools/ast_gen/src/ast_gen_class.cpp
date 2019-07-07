#include "ast_gen_class.hpp"

#include <ctype.h>

Lexer::Lexer(const string& s_filename, string* s_text)
	: LexerBase<Tok>(s_filename, s_text)
{
}
Lexer::~Lexer()
{
}

const std::map<Tok, string> tok_ident_map
= {
	{Tok::Comment, "//"},
	{Tok::Colon, ":"},
	{Tok::Semicolon, ";"},
	{Tok::Comma, ","},
	{Tok::Ident, "ident"},
	{Tok::Unknown, "unknown"},
	{Tok::Done, "done"},
};
Tok Lexer::next_tok()
{
	return _next_tok(Tok::Comment);
}

void Lexer::_inner_next_tok()
{
	if (c() == '/')
	{
		_set_tok(Tok::Unknown, true);
		if (c() == '/')
		{
			_set_tok(Tok::Comment, true);
			while ((c() != '\n') && (c() != EOF))
			{
				_next_char();
			}
			if (c() == EOF)
			{
				_set_tok(Tok::Done, false);
			}
		}
	}
	else if (c() == ':')
	{
		_set_tok(Tok::Colon, true);
	}
	else if (c() == ';')
	{
		_set_tok(Tok::Semicolon, true);
	}
	else if (c() == ',')
	{
		_set_tok(Tok::Comma, true);
	}
	else if (isalpha(c()) || (c() == '_'))
	{
		{
			string temp;
			temp = static_cast<char>(c());
			_state.set_s(temp);
		}
		_next_char();

		for (; isalnum(c()) || (c() == '_'); _next_char())
		{
			_state.set_s(_state.s() + static_cast<char>(c()));
		}
		_set_tok(Tok::Ident, false);
	}
	else if (c() == EOF)
	{
		_set_tok(Tok::Done, false);
	}
	else
	{
		_set_tok(Tok::Unknown, true);
	}
}

//const string AstGen::node_base_str
//	= sconcat("class NodeBase\n",
//	"{\n",
//	"public:		// types\n",
//	"	using TokSet = std::set<Tok>;\n",
//	"	using Children = std::map<string, ",
//		"std::vector<unique_ptr<NodeBase>>>;\n",
//	"	using Child = unique_ptr<NodeBase>;\n",
//	"\n",
//	"protected:		// variables\n",
//	"	SrcCodeChunk _src_code_chunk;\n",
//	"	Children _children;\n",
//	"\n",
//	"public:		// functions\n",
//	"	inline NodeBase()\n",
//	"	{\n",
//	"	}\n",
//	"	inline NodeBase(const SrcCodeChunk& s_src_code_chunk)\n",
//	"		: _src_code_chunk(s_src_code_chunk)\n",
//	"	{\n",
//	"	}\n",
//	"	GEN_POST_CONSTRUCTOR(NodeBase);\n",
//	"\n",
//	"	inline bool has(const string& ident) const\n",
//	"	{\n",
//	"		//return ((children().count(ident) != 0)\n",
//	"		//	&& (children().at(ident).front().get() != nullptr));\n",
//	"		return (children().at(ident).front().get() != nullptr);\n",
//	"	}\n",
//	"\n",
//	"	inline const Children& children() const\n",
//	"	{\n",
//	"		return _children;\n",
//	"	}\n",
//	"\n",
//	"	GEN_GETTER_BY_CON_REF(src_code_chunk)\n",
//	"\n",
//	"protected:		// functions\n",
//	"	template<typename FirstType, typename... RemArgTypes>\n",
//	"	inline void _add_indiv_children(const string& first_ident,\n",
//	"		FirstType&& first_child, RemArgTypes&&... rem_children)\n",
//	"	{\n",
//	"		_insert_children_list(first_ident);\n",
//	"		_children[first_ident].push_back(move(first_child));\n",
//	"		if constexpr (sizeof...(rem_children) != 0)\n",
//	"		{\n",
//	"			_add_indiv_children(rem_children...);\n",
//	"		}\n",
//	"	}\n",
//	"	inline void _insert_children_list(const string& ident)\n",
//	"	{\n",
//	"		_children[ident] = std::vector<unique_ptr<NodeBase>>();\n",
//	"	}\n",
//	"	template<typename FirstType, typename... RemArgTypes>\n",
//	"	inline void _append_children(const string& ident,\n",
//	"		FirstType&& first_child, RemArgTypes&&... rem_children)\n",
//	"	{\n",
//	"		if (_children.count(ident) == 0)\n",
//	"		{\n",
//	"			_insert_children_list(ident);\n",
//	"		}\n",
//	"		_children[ident].push_back(move(first_child));\n",
//	"\n",
//	"		if constexpr (sizeof...(rem_children) != 0)\n",
//	"		{\n",
//	"			_append_children(ident, rem_children...);\n",
//	"		}\n",
//	"	}\n",
//	"};\n");
//
//const string AstGen::node_list_str
//	= sconcat("class NodeList : public NodeBase\n",
//	"{\n",
//	"public:		// functions\n",
//	"	inline NodeList(const SrcCodeChunk& s_src_code_chunk)\n",
//	"		: NodeBase(s_src_code_chunk)\n",
//	"	{\n",
//	"		_insert_children_list(\"list\");\n",
//	"	}\n",
//	"	GEN_POST_CONSTRUCTOR(NodeList);\n",
//	"\n",
//	"	inline void append_list_child(Child&& child)\n",
//	"	{\n",
//	"		_append_children(\"list\", move(child));\n",
//	"	}\n",
//	"};\n");


AstGen::AstGen(std::vector<string>&& s_filename_vec)
	: ParserBase<Lexer>(std::move(s_filename_vec))
{
}
AstGen::~AstGen()
{
}

void AstGen::run()
{
	while (_opt_parse(&AstGen::_parse_node));

	for (size_t i=0; i<_node_vec.size(); ++i)
	{
		_node_ident_map[_node_vec.at(i).ident] = i;
	}

	if (auto&& f = std::ofstream("ast_node_main_classes.hpp"); true)
	{
		for (const auto& node : _node_vec)
		{
			osprintout(f, "class Node", node.ident);
			if (node.extends.size() != 0)
			{
				osprintout(f, " : public Node", node.extends);
			}
			else
			{
				osprintout(f, " : public NodeBase");
			}
			osprintout(f, "\n");
			osprintout(f, "{\n");

			if (node.var_vec.size() != 0)
			{
				bool start = true, was_protected = false;

				for (const auto& var : node.var_vec)
				{
					if (start)
					{
						if (var.is_protected())
						{
							osprintout(f, "protected:  // variables\n");
						}
						else // if (!var.is_protected())
						{
							osprintout(f, "public:  // variables\n");
						}
						start = false;
					}
					else // if (!start)
					{
						if (var.is_protected() != was_protected)
						{
							if (var.is_protected())
							{
								osprintout(f, "protected:  // ",
									"variables\n");
							}
							else // if (!var.is_protected())
							{
								osprintout(f, "public:  // variables\n");
							}
						}
					}
					osprintout(f, "\t", var.type, " ", var.ident, ";\n");

					was_protected = var.is_protected();
				}
			}

			const auto ext_children = _extended_children(node);
			const auto ext_var_vec = _extended_var_vec(node);
			std::vector<string> ext_only_children;
			std::vector<Var> own_init_vec, ext_init_vec, ext_only_init_vec;

			for (size_t i=node.children.size(); i<ext_children.size(); ++i)
			{
				ext_only_children.push_back(ext_children.at(i));
			}

			for (const auto& var : node.var_vec)
			{
				if (var.init)
				{
					own_init_vec.push_back(var);
				}
			}
			for (const auto& var : ext_var_vec)
			{
				if (var.init)
				{
					ext_init_vec.push_back(var);
				}
			}
			for (size_t i=node.var_vec.size(); i<ext_var_vec.size(); ++i)
			{
				const auto& var = ext_var_vec.at(i);
				if (var.init)
				{
					ext_only_init_vec.push_back(var);
				}
			}

			osprintout(f, "public:  // functions\n");
			osprintout(f, "\tinline Node", node.ident, "(const ",
				"SrcCodeChunk& s_src_code_chunk");
			//--------
			// Var args
			if (ext_init_vec.size() != 0)
			{
				osprintout(f, ",\n\t\t");
				for (size_t i=0; i<ext_init_vec.size(); ++i)
				{
					const auto& var = ext_init_vec.at(i);
					osprintout(f, "const ", var.type, "& ");

					osprintout(f, var.init_ident());

					if ((i + 1) != ext_init_vec.size())
					{
						osprintout(f, ", ");
					}
				}
			}
			//--------

			//--------
			// Child args
			if (ext_children.size() != 0)
			{
				osprintout(f, ",\n\t\t");
				for (size_t i=0; i<ext_children.size(); ++i)
				{
					osprintout(f, "Child&& s_", ext_children.at(i));

					if ((i + 1) != ext_children.size())
					{
						osprintout(f, ",\n\t\t");
					}
				}
			}
			//--------

			osprintout(f, ")\n");

			if (node.extends.size() == 0)
			{
				osprintout(f, "\t\t: NodeBase(s_src_code_chunk)");
			}
			else if (node.extends == "List")
			{
				osprintout(f, "\t\t: NodeList(s_src_code_chunk)");
			}
			else
			{
				osprintout(f, "\t\t: Node", node.extends,
					"(s_src_code_chunk");

				if (ext_only_init_vec.size() != 0)
				{
					osprintout(f, ",\n\t\t\t");

					for (size_t i=0; i<ext_only_init_vec.size(); ++i)
					{
						const auto& var = ext_only_init_vec.at(i);

						osprintout(f, var.init_ident());
						if ((i + 1) != ext_only_init_vec.size())
						{
							osprintout(f, ",\n\t\t\t");
						}
					}
				}
				if (ext_only_children.size() != 0)
				{
					osprintout(f, ",\n\t\t\t");

					for (size_t i=0; i<ext_only_children.size(); ++i)
					{
						const auto& child = ext_only_children.at(i);

						osprintout(f, "std::move(s_", child, ")");
						if ((i + 1) != ext_only_children.size())
						{
							osprintout(f, ",\n\t\t\t");
						}
					}
				}
				osprintout(f, ")");
			}
			if (own_init_vec.size() != 0)
			{
				osprintout(f, ", ");

				for (size_t i=0; i<own_init_vec.size(); ++i)
				{
					const auto& var = own_init_vec.at(i);

					osprintout(f, var.ident, "(", var.init_ident(), ")");

					if ((i + 1) != own_init_vec.size())
					{
						osprintout(f, ",\n\t\t\t");
					}
				}
			}
			osprintout(f, "\n");

			osprintout(f, "\t{\n");

			if (node.children.size() != 0)
			{
				osprintout(f, "\t\t_add_indiv_children(");

				for (size_t i=0; i<node.children.size(); ++i)
				{
					osprintout(f, "APPEND_CHILD(", node.children.at(i),
						")");
					if ((i + 1) != node.children.size())
					{
						osprintout(f, ",\n\t\t\t");
					}
				}
				osprintout(f, ");\n");
			}
			osprintout(f, "\t}\n");
			osprintout(f, "\tGEN_POST_CONSTRUCTOR(Node", node.ident,
				");\n");

			for (const auto& var : node.var_vec)
			{
				if (var.is_protected())
				{
					osprintout(f, "\tGEN_GETTER_AND_SETTER_BY_CON_REF(",
						var.ident.substr(1), ");\n");
				}
			}

			osprintout(f, "};\n\n");
		}
	}
	if (auto&& f = std::ofstream("list_of_ast_node_classes_define.hpp");
		true)
	{
		osprintout(f,
			"//#ifndef src_list_of_ast_node_classes_define_hpp\n",
			"//#define src_list_of_ast_node_classes_define_hpp\n",
			"\n",
			"// src/list_of_ast_node_classes_define.hpp\n",
			"\n",
			"#define LIST_OF_AST_NODE_CLASSES(X) \\\n",
			"\tX(NodeBase) \\\n",
			"\tX(NodeList) \\\n");

		for (const auto& node : _node_vec)
		{
			osprintout(f, "\tX(Node", node.ident, ") \\\n");
		}
		osprintout(f,
			"\n",
			"//#endif		// src_list_of_ast_node_classes_define_hpp\n");

	}
}

auto AstGen::_extended_children(const Node& node) const
	-> std::vector<string>
{
	std::vector<string> ret;

	for (const auto& iter : node.children)
	{
		ret.push_back(iter);
	}

	if ((node.extends != "") && (node.extends != "List"))
	{
		const auto temp = _extended_children(_node_vec.at(_node_ident_map
			.at(node.extends)));
		for (const auto& iter : temp)
		{
			ret.push_back(iter);
		}
	}
	return ret;
}
auto AstGen::_extended_var_vec(const Node& node) const -> std::vector<Var>
{
	std::vector<Var> ret;

	for (const auto& iter : node.var_vec)
	{
		ret.push_back(iter);
	}

	if ((node.extends != "") && (node.extends != "List"))
	{
		const auto temp = _extended_var_vec(_node_vec.at(_node_ident_map
			.at(node.extends)));
		for (const auto& iter : temp)
		{
			ret.push_back(iter);
		}
	}
	return ret;
}

bool AstGen::_parse_node()
{
	if (just_test())
	{
		return _check_prefixed_tok_seq(Tok::Ident);
	}
	_next_lss_tokens();

	_node_vec.push_back(Node());

	_node_vec.back().ident = _lss.find_found().s();

	_opt_parse(&AstGen::_parse_extends);

	_expect(Tok::Colon);

	while (_opt_parse(&AstGen::_parse_var, &AstGen::_parse_child));
	return false;
}
bool AstGen::_parse_extends()
{
	if (just_test())
	{
		return _check_prefixed_tok_seq(Tok::Comma);
	}
	_next_lss_tokens();

	with(we, _wexpect(Tok::Ident))
	{
		_node_vec.back().extends = _lex_state().s();
	}

	return false;
}
bool AstGen::_parse_var()
{
	if (just_test())
	{
		_check_prefixed_tok_seq(Tok::Ident);
		return ((_lss.find_found().s() == "initvar")
			|| (_lss.find_found().s() == "noinitvar"));
	}
	const bool s_init = (_lss.find_found().s() == "initvar");
	_next_lss_tokens();

	string type;
	with(we, _wexpect(Tok::Ident))
	{
		type = _lex_state().s();
	}

	for (;;)
	{
		auto& node = _node_vec.back();
		node.var_vec.push_back(Var());

		auto& var = node.var_vec.back();

		with(we, _wexpect(Tok::Ident))
		{
			var.type = type;
			var.ident = _lex_state().s();
			var.init = s_init;

			if (node.var_ident_set.count(var.ident))
			{
				_err("Duplicate var \"", var.ident, "\"");
			}

			node.var_ident_set.insert(var.ident);
		}
		if (!_to_next_in_list(Tok::Semicolon))
		{
			break;
		}
	}

	return false;
}
bool AstGen::_parse_child()
{
	if (just_test())
	{
		_check_prefixed_tok_seq(Tok::Ident);
		return (_lss.find_found().s() == "child");
	}
	_next_lss_tokens();

	for (;;)
	{
		auto& node = _node_vec.back();

		with(we, _wexpect(Tok::Ident))
		{
			node.children.push_back(_lex_state().s());

			if (node.child_ident_set.count(node.children.back()))
			{
				_err("Duplicate child \"", node.children.back(), "\"");
			}

			node.child_ident_set.insert(node.children.back());
		}
		if (!_to_next_in_list(Tok::Semicolon))
		{
			break;
		}
	}

	return false;
}
