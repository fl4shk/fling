parser grammar FlingBasicSharedGrammar;

import FlingLexerGrammar;

flingIdentOrArrayIdent:
	flingIdent flingArrayBounds+
	;
flingArrayBounds:
	'[' flingExpr ']'
	;

flingIdent:
	(TokIdent | '#' flingExpr) ('cat' flingIdent)?
	;

// The HDL needs expressions to be something you can check the validity of.
// Not every expression is valid in the HDL at runtime, but (almost) all
// are available at compile-time.
flingExpr:
	flingForcedAssignExpr
	| flingAssignExpr
	;
flingForcedAssignExpr:
	flingAssignExpr flingAssignOp flingExpr
	;
flingAssignOp:
	TokAssign | TokCstmAssign
	| TokPlusEquals | TokMinusEquals
	| TokMulEquals | TokDivEquals | TokModEquals
	| TokBitAndEquals | TokBitOrEquals | TokBitXorEquals
	| TokBitLslEquals | TokBitLsrEquals | TokBitAsrEquals
	| TokAtEquals
	;

flingAssignExpr:
	flingLogicalExpr (flingLogicalOp flingAssignExpr)?
	;
flingLogicalOp:
	TokLogAnd | TokLogOr
	;

flingLogicalExpr:
	flingCompareExpr (flingCompareOp flingLogicalExpr)?
	;
flingCompareOp:
	TokCmpEq | TokCmpNe
	| TokCmpLt | TokCmpGt
	| TokCmpLe | TokCmpGe
	;

flingCompareExpr:
	flingAddSubExpr (flingAddSubOp flingCompareExpr)?
	;
flingAddSubOp:
	TokPlus | TokMinus
	;

flingAddSubExpr:
	flingMulDivModBitExpr (flingMulDivModBitOp flingAddSubExpr)?
	;
flingMulDivModBitOp:
	TokMulOrPtr | TokDiv | TokMod
	| TokBitAnd | TokBitOr | TokBitXor
	| TokBitLsl | TokBitLsr | TokBitAsr
	;

flingMulDivModBitExpr:
	flingLowUnaryOp flingExpr
	| flingLowExpr
	;
flingLowUnaryOp:
	TokPlus | TokMinus
	| TokBitNot | TokLogNotOrForceSuccess
	;

flingLowExpr:
	TokMulOrPtr flingExpr
	| TokAt flingExpr
	| flingExpr TokLogNotOrForceSuccess
	| flingExpr TokErrorCheckOrNullCheck
	| flingIdent
	| TokStringLiteral
	| TokFloatNum
	| TokDecNum | TokHexNum | TokOctNum | TokBinNum
	| flingCastExpr
	| flingFuncCall
	| '(' flingExpr ')'
	;

flingAttr:
	'#[' flingExpr ('(' flingExpr ')')?  ']'
	| '#[' 'attr' '(' (flingSpecMacro | flingSpecFunc) ')' ']'
	;


flingStaticAssert:
	'static_assert' '(' flingExpr (',' flingExpr)? ')' ';'
	;
