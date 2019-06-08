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
	while (_inner_next_tok() == Tok::Comment);
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
			_set_tok(Tok::ContAssign, false);
		}
	}
	else if (c() == '!')
	{
		_next_char();

		if (c() == '=')
		{
			_set_tok
		}
		else
		{
		}
	}

}

} // namespace frost_hdl
