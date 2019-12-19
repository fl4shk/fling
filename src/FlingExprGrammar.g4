flingExpr:
	flingAssignExpr (flingAssignOp flingExpr)?
	;
flingAssignOp:
	TokAssign | TokCstmAssign
	| TokPlusEquals | TokMinusEquals
	| TokMulEquals | TokDivEquals | TokModEquals
	| TokBitOrEquals | TokBitAndEquals | TokBitXorEquals
	| flingPseudoTokBitLslEquals | flingPseudoTokBitLsrEquals
	| flingPseudoTokBitAsrEquals
	| TokAtEquals
	;
flingPseudoTokBitLslEquals: flingPseudoTokBitLsl '=' ;
flingPseudoTokBitLsrEquals: flingPseudoTokBitLsr '=' ;
flingPseudoTokBitAsrEquals: flingPseudoTokBitAsr '>' '=' ;

flingAssignExpr:
	flingLogOrExpr (TokLogOr flingExpr)?
	;
flingLogOrExpr:
	flingLogAndExpr (TokLogAnd flingExpr)?
	;

flingLogAndExpr:
	flingCompareExpr (flingCompareOp flingExpr)?
	;
flingCompareOp:
	TokCmpEq | TokCmpNe
	| TokCmpLt | TokCmpGt
	| TokCmpLe | TokCmpGe
	;

flingCompareExpr:
	flingAddSubExpr ((TokPlus | TokMinus) flingExpr)?
	;

flingAddSubExpr:
	flingMulDivModExpr ((TokMulOrPtr | TokDiv | TokMod) flingExpr)?
	;

flingMulDivModExpr:
	flingBitShiftExpr (flingBitShiftOp flingExpr)?
	;
flingBitShiftOp:
	flingPseudoTokBitLsl | flingPseudoTokBitLsr | flingPseudoTokBitAsr
	;
flingPseudoTokBitLsl: '<' '<' ;
flingPseudoTokBitLsr: '>' '>' ;
flingPseudoTokBitAsr: '>' '>' '>';


flingBitShiftExpr:
	flingBitOrExpr (TokBitOr flingExpr)?
	;

flingBitOrExpr:
	flingBitAndExpr (TokBitAnd flingExpr)?
	;

flingBitAndExpr:
	flingBitXorExpr (TokBitXor flingExpr)?
	;

flingBitXorExpr:
	flingPreUnaryOp flingExpr
	| flingHasLeafExpr
	;
flingPreUnaryOp:
	TokPlus | TokMinus
	| TokBitNot | TokLogNotOrForceSuccess
	| TokMulOrPtr | TokAt
	;

flingHasLeafExpr:
	flingLeafExpr flingPostUnaryItem* flingLeafExprSuffix*
	;
flingPostUnaryItem:
	flingPostUnaryOp? flingPostUnaryItemSuffix*
	;
flingLeafExprSuffix:
	flingScopeAccessOp flingSuperLeafExpr flingPostUnaryItem*
	;
flingPostUnaryItemSuffix:
	flingArrayAccessSuffix | flingFuncMacroArgList
	;
flingPostUnaryOp;
	TokLogNotOrForceSuccess | TokErrorCheckOrNullCheck
	| TokMultiForceSuccess | TokMultiErrorCheckOrNullCheck
	;
flingArrayAccessSuffix:
	'[' flingExpr ']'
	;
flingScopeAccessOp:
	TokMemberAccess | TokPtrMemberAccess | TokCstmMemberAccess
	| TokScopeAccess
	;

flingLeafExpr:
	flingLeafExprPrefix flingLeafExprSuffix
	;
flingLeafExprPrefix:
	TokDecNum | TokHexNum | TokOctNum | TokBinNum
	| TokFloatNum
	| flingRawString
	| '(' flingExpr ')'
	| flingIfExpr
	| flingMatchExpr
	| flingSuperLeafExpr
	;
flingLeafExprSuffix:
	TokParamPack
	| TokRangeSeparator flingExpr
	;

//--------
flingIfExpr:
	flingNonGenIfExpr | flingGenIfExpr
	;


flingNonGenIfExpr:
	'if' flingExpr flingScopedExpr
	flingElseIfExpr*
	flingElseExpr?
	;
flingElseIf:
	'else' 'if' flingExpr flingScopedExpr
	;
flingElse:
	'else' flingScopedExpr
	;


flingGenIfExpr:
	'gen' 'if' flingExpr flingScopedExpr
	flingElseGenIfExpr*
	flingElseGenExpr?
	;
flingElseGenIfExpr:
	'else' 'gen' 'if' flingExpr flingScopedExpr
	;
flingElseGenExpr:
	'else' 'gen' flingScopedExpr
	;
//--------

//--------
flingMatchExpr:
	flingNonGenMatchExpr | flingGenMatchExpr
	;

flingNonGenMatchExpr:
	'match' flingExpr flingMatchExprCaseList
	;
flingGenMatchExpr:
	'gen' 'match' flingExpr flingMatchExprCaseList
	;
//--------


flingSuperLeafExpr:
	| flingSuperLeafIdentExpr
	| flingCallMacroOrDefine
	;

flingSuperLeafIdentExpr:
	(flingIdent | TokKwGen '<' flingIdent '>')
	(flingInstTemplateArgList? flingInstRegularArgList)?
	;
flingCallMacroOrDefine:
	TokMacroOrDefineIdent flingInstTemplateArgList?
		flingInstRegularArgList
	;
