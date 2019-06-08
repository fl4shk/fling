#include "lexer_class.hpp"

#include <ctype.h>

namespace frost_hdl
{

Lexer::Lexer(std::string* s_text)
	: _text(s_text)
{
	next_tok();
}
Lexer::~Lexer()
{
}

Tok Lexer::next_tok()
{
	do
	{
		_inner_next_tok();
	} while (tok() == Tok::Comment);

	return tok();
}

int Lexer::_next_char()
{
	if (x() < text()->size())
	{
		_c = text()->at(_x++);

		++_pos_in_line;

		if (c() == '\n')
		{
			++_line_num;
			_pos_in_line = 1;
		}

		return c();
	}
	else
	{
		return EOF;
	}
}

void Lexer::_eat_whitespace()
{
	while (isspace(c()))
	{
		_next_char();
	}
}

void Lexer::_set_tok(Tok n_tok, bool perf_next_char)
{
	_tok = n_tok;

	if (perf_next_char)
	{
		_next_char();
	}
}
void Lexer::_inner_next_tok()
{
	_eat_whitespace();

	if (c() == EOF)
	{
		_set_tok(Tok::Done, false);
	}

	else if (c() == '+')
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
		else if (c() == ':')
		{
			_set_tok(Tok::BlkAssign, true);
		}
		else if (c() == '<')
		{
			_set_tok(Tok::NonblkAssign, true);
		}
		else
		{
			_set_tok(Tok::Unknown, false);
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
			_set_tok(Tok::PrevScope, true);
		}
		else
		{
			_set_tok(Tok::NextScope, true);
		}
	}
	else if (c() == '$')
	{
		_set_tok(Tok::DollarIdent, false);
		_s = static_cast<char>(c());
		_next_char();

		for (; isalnum(c()) || (c() == '_'); _next_char())
		{
			_s += static_cast<char>(c());
		}
	}
	else if (isalpha(c()) || (c() == '_'))
	{
		_set_tok(Tok::Ident, false);
		_s = static_cast<char>(c());
		_next_char();

		for (; isalnum(c()) || (c() == '_'); _next_char())
		{
			_s += static_cast<char>(c());
		}
	}
	else if (isdigit(c()))
	{
		_set_tok(Tok::Num, false);
		_n = static_cast<BigNum>(0);

		auto get_dec_num = [&]() -> void
		{
			for (; isdigit(c()); _next_char())
			{
				_n = (_n * 10) + (c() - '0');
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
					if (in_range_inclusive('A', 'F', c())
					{
						_n = (_n * 16) + (c() - 'A');
					}
					else if (in_range_inclusive('a', 'f', c()))
					{
						_n = (_n * 16) + (c() - 'a');
					}
					else // if (isdigit(c()))
					{
						_n = (_n * 16) + (c() - '0');
					}
				}
			}
			else if (c() == 'o')
			{
				_next_char();

				for (; in_range_inclusive('0', '7', c()); _next_char())
				{
					_n = (_n * 8) + (c() - '0');
				}
			}
			else if (c() == 'b')
			{
				_next_char();

				for (; in_range_inclusive('0', '1', c()); _next_char())
				{
					_n = (_n * 2) + (c() - '0');
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
