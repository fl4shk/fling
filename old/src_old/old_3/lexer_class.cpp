#include "lexer_class.hpp"

#include <ctype.h>

namespace frost_hdl
{

Lexer::Lexer(const string& s_filename, string* s_text)
	: LexerBase<Tok>(s_filename, s_text)
{
}
Lexer::~Lexer()
{
}

void Lexer::next_tok()
{
	_next_tok(Tok::Comment);
}

void Lexer::_inner_next_tok()
{
	_set_tok(Tok::Unknown, false);
	if (c() == '+')
	{
		_set_tok(Tok::Plus, true);
	}
	else if (c() == '-')
	{
		_set_tok(Tok::Minus, true);
	}
	else if (c() == '*')
	{
		_set_tok(Tok::Mul, true);
	}
	else if (c() == '/')
	{
		_next_char();
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
		else
		{
			_set_tok(Tok::Div, false);
		}
	}
	else if (c() == '<')
	{
		_next_char();

		if (c() == '<')
		{
			_set_tok(Tok::BitLsl, true);
		}
		else if (c() == '=')
		{
			_set_tok(Tok::CmpLe, true);
		}
		else
		{
			_set_tok(Tok::CmpLt, false);
		}
	}
	else if (c() == '>')
	{
		_next_char();

		if (c() == '>')
		{
			_next_char();

			if (c() == '>')
			{
				_set_tok(Tok::BitAsr, true);
			}
			else
			{
				_set_tok(Tok::BitLsr, false);
			}
		}
		else if (c() == '=')
		{
			_set_tok(Tok::CmpGe, true);
		}
		else
		{
			_set_tok(Tok::CmpGt, false);
		}
	}
	else if (c() == '&')
	{
		_next_char();

		if (c() == '&')
		{
			_set_tok(Tok::LogAnd, true);
		}
		else
		{
			_set_tok(Tok::BitAnd, false);
		}
	}
	else if (c() == '|')
	{
		_next_char();

		if (c() == '|')
		{
			_set_tok(Tok::LogOr, true);
		}
		else
		{
			_set_tok(Tok::BitOr, false);
		}
	}
	else if (c() == '^')
	{
		_set_tok(Tok::BitXor, true);
	}
	else if (c() == '~')
	{
		_set_tok(Tok::BitNot, true);
	}
	else if (c() == '=')
	{
		_next_char();

		if (c() == '=')
		{
			_set_tok(Tok::CmpEq, true);
		}
		else
		{
			_set_tok(Tok::Assign, false);
		}
	}
	else if (c() == '!')
	{
		_next_char();

		if (c() == '=')
		{
			_set_tok(Tok::CmpNe, true);
		}
		else
		{
			_set_tok(Tok::LogNot, false);
		}
	}
	else if (c() == '.')
	{
		_next_char();

		if (c() == '.')
		{
			_next_char();

			if (c() == '.')
			{
				_set_tok(Tok::ParamPack, true);
			}
			else
			{
				_set_tok(Tok::Unknown, false);
			}
		}
		else
		{
			_set_tok(Tok::MemberAccess, false);
		}
	}
	else if (c() == '#')
	{
		_set_tok(Tok::Pound, true);
	}
	else if (c() == ',')
	{
		_set_tok(Tok::Comma, true);
	}
	else if (c() == ';')
	{
		_set_tok(Tok::Semicolon, true);
	}
	else if (c() == ':')
	{
		_next_char();

		if (c() == ':')
		{
			_set_tok(Tok::ScopeAccess, true);
		}
		else
		{
			_set_tok(Tok::Colon, false);
		}
	}
	else if (c() == '"')
	{
		//_set_tok(Tok::Quote, true);
		_set_tok(Tok::String, true);
		state().set_s("");
		for (;;)
		{
			if (c() == '\\')
			{
				_next_char();
				if (c() == 'n')
				{
					state().set_s(state().s() + '\n');
				}
				else if (c() == 'r')
				{
					state().set_s(state().s() + '\r');
				}
				else if (c() == 't')
				{
					state().set_s(state().s() + '\t');
				}
				else if (c() == 'a')
				{
					state().set_s(state().s() + '\a');
				}
				else if (c() == 'f')
				{
					state().set_s(state().s() + '\f');
				}
				else if (c() == '\\')
				{
					state().set_s(state().s() + '\\');
				}
				else if (c() == '"')
				{
					state().set_s(state().s() + '\"');
				}
				else
				{
					// Last resort for a language that doesn't really have
					// good string support.
					state().set_s(state().s() + '?');
				}
			}
			else if (c() == '"')
			{
				break;
			}
			else if (state().x() >= _text->size())
			{
				_set_tok(Tok::Done, false);
				break;
			}
			else
			{
				state().set_s(state().s() + static_cast<char>(c()));
				_next_char();
			}
		}
	}
	else if (c() == '\'')
	{
		_set_tok(Tok::Apostrophe, true);
	}
	else if (c() == '(')
	{
		_set_tok(Tok::LParen, true);
	}
	else if (c() == ')')
	{
		_set_tok(Tok::RParen, true);
	}
	else if (c() == '[')
	{
		_set_tok(Tok::LBracket, true);
	}
	else if (c() == ']')
	{
		_set_tok(Tok::RBracket, true);
	}
	else if (c() == '{')
	{
		_set_tok(Tok::LBrace, true);
	}
	else if (c() == '}')
	{
		_set_tok(Tok::RBrace, true);
	}
	else if (c() == '$')
	{
		{
			string temp;
			temp = static_cast<char>(c());
			state().set_s(temp);
		}
		_next_char();

		for (; isalnum(c()) || (c() == '_'); _next_char())
		{
			state().set_s(state().s() + static_cast<char>(c()));
		}

		if (!_set_kw_tok(kw_dollar_tok_ident_map))
		{
			_set_tok(Tok::Unknown, false);
		}

	}
	else if (isalpha(c()) || (c() == '_'))
	{
		{
			string temp;
			temp = static_cast<char>(c());
			state().set_s(temp);
		}
		_next_char();

		for (; isalnum(c()) || (c() == '_'); _next_char())
		{
			state().set_s(state().s() + static_cast<char>(c()));
		}

		if (!_set_kw_tok(kw_tok_ident_map))
		{
			_set_tok(Tok::Ident, false);
		}
	}
	else if (isdigit(c()))
	{
		_set_tok(Tok::Num, false);
		state().set_n(static_cast<BigNum>(0));

		auto get_dec_num = [&]() -> void
		{
			for (; isdigit(c()); _next_char())
			{
				state().set_n((n() * 10) + (c() - '0'));
			}
		};

		if (c() == '0')
		{
			_next_char();
			if (c() == 'x')
			{
				_next_char();

				for (; isxdigit(c()); _next_char())
				{
					if (in_range_inclusive('A', 'F', c()))
					{
						state().set_n((n() * 16) + (c() - 'A'));
					}
					else if (in_range_inclusive('a', 'f', c()))
					{
						state().set_n((n() * 16) + (c() - 'a'));
					}
					else // if (isdigit(c()))
					{
						state().set_n((n() * 16) + (c() - '0'));
					}
				}
			}
			else if (c() == 'o')
			{
				_next_char();

				for (; in_range_inclusive('0', '7', c()); _next_char())
				{
					state().set_n((n() * 8) + (c() - '0'));
				}
			}
			else if (c() == 'b')
			{
				_next_char();

				for (; in_range_inclusive('0', '1', c()); _next_char())
				{
					state().set_n((n() * 2) + (c() - '0'));
				}
			}
			else
			{
				get_dec_num();
			}
		}
		else
		{
			get_dec_num();
		}
	}
}

} // namespace frost_hdl
