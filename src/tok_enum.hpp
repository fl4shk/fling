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
	// `.`
	NextScope,

	// `..`
	PrevScope,

	Pound,
	Comma,
	Semicolon,
	Colon,

	Quote,
	Apostrophe,

	LParen,
	RParen,

	LBracket,
	RBracket,

	LBrace,
	RBrace,
	//--------

	//--------
	KwDollarUnsgn,
	KwDollarSgn,
	KwDollarIsUnsgn,
	KwDollarIsSgn,
	KwDollarRange,
	KwDollarSize,
	KwDollarMsbpos,
	KwDollarFirst,
	KwDollarLast,
	KwDollarHigh,
	KwDollarLow,
	KwDollarClog2,
	KwDollarPow,
	//--------

	//--------
	KwConst,
	KwType,
	KwTypeof,

	KwStruct,
	KwClass,
	KwUnion,
	KwEnum,
	KwUsing,

	KwFunc,
	KwTask,
	KwVirtual,

	KwPublic,
	KwProtected,
	KwPrivate,

	KwPackage,
	KwModule,
	KwInterface,

	KwInput,
	KwOutput,
	KwInout,

	KwIf,
	KwElse,
	KwSwitch,
	KwCase,
	KwDefault,

	KwFor,
	KwWhile,
	//KwDo,

	KwRange,

	KwAssign,
	KwInitial,
	KwAlwaysComb,
	KwAlwaysSeq,

	KwPosedge,
	KwNegedge,

	KwGenerate,
	KwGenvar,

	KwConcat,
	KwRepl,

	KwWireu,
	KwWires,

	KwLogicu,
	KwLogics,

	KwByteu,
	KwBytes,

	KwShortintu,
	KwShortints,

	KwIntu,
	KwInts,

	KwLongintu,
	KwLongints,
	//--------

	//--------
	Ident,
	Num,

	Comment,
	Unknown,
	Done,
	//--------
};

} // namespace frost_hdl


#endif		// src_tok_enum_hpp
