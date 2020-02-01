//--------
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
//--------

//--------
flingHasLeafExpr:
	flingLeafExpr flingPostUnaryItem* flingHasLeafExprSuffix*
	| TokKwTypeof '(' flingExpr ')' (TokScopeAccess
		
	;

flingPostUnaryItem:
	(TokLogNotOrForceSuccess | TokErrorCheckOrNullCheck
	| TokMultiForceSuccess | TokMultiErrorCheckOrNullCheck)?
	flingPostUnaryItemSuffix*
	;

// Separate parser rule from `flingPostUnaryItem` because I need to know
// the ordering of these.
flingPostUnaryItemSuffix:
	// For array access or the overloaded "[]" operator
	'[' flingExpr ']'

	// for function objects
	| flingInstRegularArgList
	;

flingHasLeafExprSuffix:
	(TokMemberAccess | TokPtrMemberAccess | TokCstmMemberAccess
	| TokScopeAccess)

	// Generic member access
	(flingSuperLeafExpr

	// For overloaded operators as their string versions (you may want a
	// pointer to one of these)
	| flingRawString)

	flingPostUnaryItem*
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
	| flingCastExpr
	| flingReinterpretExpr
	| flingSuperLeafExpr
	;
flingLeafExprSuffix:
	TokParamPack
	| TokRangeSeparator flingExpr
	;

//--------
flingIfExpr:
	(flingIfHeader flingScopedExpr
	flingElseIfExpr*
	flingElseExpr?)
	| (flingGenIfHeader flingScopedExpr
	flingElseGenIfExpr*
	flingElseGenExpr?)
	;
flingElseIfExpr
	flingElseIfHeader flingScopedExpr
	;
flingElseExpr
	flingElseHeader flingScopedExpr
	;
flingElseGenIfExpr:
	flingElseGenIfHeader flingScopedExpr
	;
flingElseGenExpr:
	flingElseGenHeader flingScopedExpr
	;

//--------

//--------
flingMatchExpr:
	(flingMatchHeader | flingGenMatchHeader) flingMatchExprCaseList
	;
//--------


//--------
flingSuperLeafExpr:
	| flingSuperLeafIdentExpr
	| flingCallMacroOrDefine
	;

// Covers both function calls (using function identifiers)
flingSuperLeafIdentExpr:
	flingIdent
	(flingInstTemplateArgList? flingInstRegularArgList)?
	;

flingCallMacroOrDefine:
	TokMacroOrDefineIdent flingInstTemplateArgList?
		flingInstRegularArgList
	;
//--------
