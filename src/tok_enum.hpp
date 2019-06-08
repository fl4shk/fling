#ifndef src_tok_enum_hpp
#define src_tok_enum_hpp

// src/tok_enum.hpp

#include "misc_includes.hpp"

namespace frost_hdl
{

enum class Tok
{
	// Built in type expression tokens
	//--------
	Plus,
	Minus,
	Mul,
	Div,

	BitLsl,
	BitLsr,
	BitAsr,

	BitAnd,
	BitOr,
	BitXor,
	BitNot,

	LogAnd,
	LogOr,
	LogNot,

	CmpEq,
	CmpNe,
	CmpLt,
	CmpLe,
	CmpGt,
	CmpGe,
	//--------

	//--------
	// `=:`
	BlkAssign,

	// `=<`
	NonblkAssign,
	//--------

	//--------
	NextScope,
	PrevScope,
	//--------


	//--------
	DollarIdent,
	Ident,
	Num,

	Comment,
	Unknown,
	Done,
	//--------
};

} // namespace frost_hdl


#endif		// src_tok_enum_hpp
