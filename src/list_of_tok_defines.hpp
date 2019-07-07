#define LIST_OF_KW_DOLLAR_TOK(X) \
	X(KwDollarDisplay, "$display") \
	X(KwDollarFinish, "$finish") \
	X(KwDollarUnsgn, "$unsgn") \
	X(KwDollarSgn, "$sgn") \
	X(KwDollarIsUnsgn, "$is_unsgn") \
	X(KwDollarIsSgn, "$is_sgn") \
	X(KwDollarRange, "$range") \
	X(KwDollarSize, "$size") \
	X(KwDollarMsbpos, "$msbpos") \
	X(KwDollarFirst, "$first") \
	X(KwDollarLast, "$last") \
	X(KwDollarHigh, "$high") \
	X(KwDollarLow, "$low") \
	X(KwDollarClog2, "$clog2") \
	X(KwDollarPow, "$pow") \

#define LIST_OF_KW_NON_DOLLAR_TOK(X) \
	X(KwConst, "const") \
	X(KwType, "type") \
	X(KwTypeof, "typeof") \
	\
	/* X(KwStruct, "struct") */ \
	X(KwClass, "class") \
	X(KwSelf, "self") \
	X(KwUnion, "union") \
	X(KwEnum, "enum") \
	X(KwUsing, "using") \
	\
	X(KwPacked, "packed") \
	\
	X(KwFunc, "func") \
	X(KwTask, "task") \
	X(KwProc, "proc") \
	X(KwVirtual, "virtual") \
	X(KwStatic, "static") \
	\
	X(KwPublic, "public") \
	X(KwProtected, "protected") \
	X(KwPrivate, "private") \
	X(KwExtends, "extends") \
	\
	X(KwPackage, "package") \
	X(KwModule, "module") \
	X(KwInst, "inst") \
	\
	X(KwInput, "input") \
	X(KwOutput, "output") \
	X(KwBidir, "bidir") \
	\
	X(KwIf, "if") \
	X(KwElse, "else") \
	X(KwSwitch, "switch") \
	X(KwSwitchz, "switchz") \
	X(KwCase, "case") \
	X(KwDefault, "default") \
	\
	X(KwFor, "for") \
	X(KwWhile, "while") \
	X(KwDo, "do") \
	\
	X(KwRange, "range") \
	\
	X(KwAssign, "assign") \
	X(KwInitial, "initial") \
	X(KwAlwaysComb, "always_comb") \
	X(KwAlwaysBlk, "always_blk") \
	X(KwAlwaysFf, "always_ff") \
	\
	X(KwAssert, "assert") \
	X(KwAssume, "assume") \
	X(KwCover, "cover") \
	\
	X(KwStaticAssert, "static_assert") \
	\
	X(KwPosedge, "posedge") \
	X(KwNegedge, "negedge") \
	\
	X(KwGenerate, "generate") \
	X(KwGenvar, "genvar") \
	X(KwVar, "var") \
	\
	X(KwCat, "cat") \
	X(KwRepl, "repl") \
	\
	X(KwVoid, "void") \
	X(KwAuto, "auto") \
	\
	X(KwUwire, "uwire") \
	X(KwSwire, "swire") \
	\
	X(KwUbit, "ubit") \
	X(KwSbit, "sbit") \
	\
	X(KwUbyte, "ubyte") \
	X(KwSbyte, "sbyte") \
	\
	X(KwUshortint, "ushortint") \
	X(KwSshortint, "sshortint") \
	\
	X(KwUint, "uint") \
	X(KwSint, "sint") \
	\
	X(KwUlongint, "ulongint") \
	X(KwSlongint, "slongint") \

#define LIST_OF_TOK(X) \
/* Built in type expression tokens */ \
/* -------- */ \
X(Plus, "+") \
X(Minus, "-") \
X(Mul, "*") \
X(Div, "/") \
\
X(BitLsl, "<<") \
X(BitLsr, ">>") \
X(BitAsr, ">>>") \
\
X(BitAnd, "&") \
X(BitOr, "|") \
X(BitXor, "^") \
X(BitNot, "~") \
\
X(LogAnd, "&&") \
X(LogOr, "||") \
X(LogNot, "!") \
\
X(CmpEq, "==") \
X(CmpNe, "!=") \
X(CmpLt, "<") \
X(CmpLe, "<=") \
X(CmpGt, ">") \
X(CmpGe, ">=") \
/* -------- */ \
\
/* -------- */ \
X(Assign, "=") \
/* -------- */ \
\
/* -------- */ \
X(Period, ".") \
\
X(Pound, "#") \
X(Comma, ",") \
X(Semicolon, ";") \
X(Colon, ":") \
\
/* X(Quote, "\"") */ \
X(Apostrophe, "'") \
\
X(LParen, "(") \
X(RParen, ")") \
\
X(LBracket, "[") \
X(RBracket, "]") \
\
X(LBrace, "{") \
X(RBrace, "}") \
/* -------- */ \
\
/* -------- */ \
LIST_OF_KW_DOLLAR_TOK(X) \
/* -------- */ \
\
/* -------- */ \
LIST_OF_KW_NON_DOLLAR_TOK(X) \
/* -------- */ \
\
/* -------- */ \
X(Ident, "identifier") \
X(String, "string") \
X(Num, "number") \
\
X(Comment, "comment") \
X(Unknown, "unknown") \
X(Done, "EOF") \
/* -------- */ \

