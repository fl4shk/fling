flingExpr:
	flingAssignExpr (flingAssignOp flingExpr)?
	;
// Done this way to not conflict with `>>` in a template instantiation.
flingBitLslAssignOp: '<' '<=' ;
flingBitLsrAssignOp: '>' '>=' ;
flingBitAsrAssignOp: '>' '>' '>=' ;
flingAssignOp:
	TokAssign | TokCstmAssign
	| TokPlusEquals | TokMinusEquals
	| TokMulEquals | TokDivEquals | TokModEquals
	| TokBitAndEquals | TokBitOrEquals | TokBitXorEquals
	| flingBitLslAssignOp | flingBitLsrAssignOp | flingBitAsrAssignOp
	| TokAtEquals
	;

flingAssignExpr:
	flingLogAndExpr ('&&' flingExpr)?
	;

flingLogAndExpr:
	flingLogOrExpr ('||' flingExpr)?
	;

flingLogOrExpr:
	flingCompareExpr (flingCompareOp flingExpr)?
	;
flingCompareOp:
	TokCmpEq | TokCmpNe
	| TokCmpLt | TokCmpGt
	| TokCmpLe | TokCmpGe
	;

flingCompareExpr:
	flingAddSubExpr (flingAddSubOp flingExpr)?
	;
flingAddSubOp:
	TokPlus | TokMinus
	;

flingAddSubExpr:
	flingMulDivModBitExpr (flingMulDivModBitOp flingExpr)?
	;
flingBitLslOp: '<' '<' ;
flingBitLsrOp: '>' '>' ;
flingBitAsrOp: '>' '>' '>' ;
flingMulDivModBitOp:
	TokMulOrPtr | TokDiv | TokMod
	| TokBitAnd | TokBitOr | TokBitXor
	| flingBitLslOp | flingBitLsrOp | flingBitAsrOp
	;

flingMulDivModBitExpr:
	flingPreUnaryOp flingExpr
	| TokAt? flingLeafExpr
	;
flingPreUnaryOp:
	TokPlus | TokMinus
	| TokBitNot | TokLogNotOrForceSuccess
	| TokMulOrPtr
	;

flingLeafExpr:
	(
		TokKwMove '(' flingExpr ')'
		| (
			flingLeafExprPrologue
			(
				(
					flingLeafExprContinuedRegularPrefix
					| flingLeafExprContinuedCstmPrefix
				)
				flingLeafExprPartialSuffix
			)*
		)
	)
	;
flingLeafExprPrologue:
	flingPrefixLeafExpr flingLeafExprPartialSuffix
	;
flingLeafExprPartialSuffix:
	flingArrayIndexOrFuncObjCall* flingLeafExprPartialSuffixOp?
	;
flingLeafExprPartialSuffixOp:
	TokLogNotOrForceSuccess | TokErrorCheckOrNullCheck
	| TokMultiForceSuccess | TokMultiErrorCheckOrNullCheck
	;
flingArrayIndexOrFuncObjCall:
	'[' flingExpr ']'
	| flingInstFuncMacroArgList 
	;
flingLeafExprContinuedRegularPrefix:
	(TokMemberAccess | TokPtrMemberAccess)
	(flingIdent | flingFuncCallExpr)
	;
flingLeafExprContinuedCstmPrefix:
	TokCstmMemberAccess flingIdent
	;


flingPrefixLeafExpr:
	TokDecNum | TokHexNum | TokOctNum | TokBinNum
	| TokFloatNum
	| TokKwSelf
	| '(' flingExpr ')'
	| flingPackedParamPackExpr:
	| flingRawString
	| flingCastExpr
	| flingMatchExpr
	| flingIfExpr
	| flingScopedIdent
	| flingScopedFuncCallExpr
	;


flingScopedIdent:
	flingScopedIdent
	;

// Not for overloaded operators which are technically also functions
flingFuncCallExpr:
	flingIdent
	;


//flingNonIdentLeafExpr:
//	TokDecNum | TokHexNum | TokOctNum | TokBinNum
//	| TokFloatNum
//	| '(' flingExpr ')'
//	| flingPackedParamPackExpr
//	| flingRawString
//	| flingCastExpr
//	| flingMatch
//	| flingIf
//	;
//
//flingPackedParamPackExpr:
//	'[' flingExpr (',' flingExpr)* (',')? ']'
//	;
//flingCastExpr:
//	(TokKwCast | TokKwReinterpret) '[' flingTypename ']' '(' flingExpr ')'
//	;
