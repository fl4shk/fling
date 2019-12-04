//--------
flingExpr:
	flingAssignExpr (flingAssignOp flingExpr)?
	;
flingAssignOp:
	TokAssign | TokCstmAssign | TokAtEquals
	| TokPlusEquals | TokMinusEquals
	| TokMulEquals | TokDivEquals | TokModEquals
	| TokBitAndEquals | TokBitOrEquals | TokBitXorEquals
	| TokBitLslEquals | TokBitLsrEquals | TokBitAsrEquals
	;

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
	flingAddSubExpr (flingAddSubOp flingExpr)?
	;
flingAddSubOp:
	TokPlus | TokMinus
	;

flingAddSubExpr:
	flingMulDivModBitExpr (flingMulDivModBitOp flingExpr)?
	;
flingMulDivModBitOp:
	TokMulOrPtr | TokDiv | TokMod
	| TokBitAnd | TokBitOr | TokBitXor
	| TokBitLsl | TokBitLsr | TokBitAsr
	;

flingMulDivModBitExpr:
	flingLowUnaryOp flingExpr
	| flingLowUnaryExpr
	;
flingLowUnaryOp:
	TokPlus | TokMinus
	| TokBitNot | TokLogNotOrForceSuccess
	;

flingLowUnaryExpr:
	flingHighUnaryOp flingExpr
	| flingHighUnaryExpr
	;
flingHighUnaryOp:
	TokMulOrPtr | TokAt
	;
//--------

--------
flingHighUnaryExpr:
	flingHighestExpr
	(flingHighUnaryExprSuffixPart0 flingHighUnaryExprSuffixPart1?)?
	;
flingHighUnaryExprSuffixPart0:
	TokLogNotOrForceSuccess
	| TokErrorCheckOrNullCheck
	| TokGlobalForceSuccess
	| TokGlobalErrorCheckOrNullCheck
	| flingArrayIndexOrSlice
	;
	
flingHighUnaryExprSuffixPart1:
	flingHighUnaryExprSuffixPart1Opt0
	| flingHighUnaryExprSuffixPart1Opt1
	;
flingHighUnaryExprSuffixPart1Opt0:
	(TokMemberAccess | TokPtrMemberAccess)
	(flingIdent | flingCallFuncExpr | flingPointableFuncExpr)
	;
flingHighUnaryExprSuffixPart1Opt1:
	TokCstmMemberAccess flingIdent
	;
flingArrayIndexOrSlice:
	'[' flingExpr ']'
	;

flingHighestExpr:
	flingHighestExprPrefix flingHighestExprSuffix?
	;
flingHighestExprPrefix:
	TokDecNum | TokHexNum | TokOctNum | TokBinNum
	| TokFloatNum
	| '(' flingExpr ')'
	| flingIdent
	| flingCallFuncExpr
	| flingPointableFuncExpr
	| flingString
	| flingPackedParamPackExpr
	| flingCastExpr
	| flingMatchExpr
	| flingIfExpr
	;
flingHighestExprSuffix:
	TokRangeSeparator flingExpr
	| TokParamPack
	;

flingPackedParamPackExpr:
	'[' flingExpr (',' flingExpr)* (',')? ']'
	;
flingUnpackedParamPackExpr:
	flingHighestExpr '...'
	;


flingCallFuncExpr:
	(flingIdent | flingString) flingInstTemplateArgList?
		flingInstFuncMacroArgList
	;
flingPointableFuncExpr:
	(flingIdent | flingString) flingInstTemplateArgList?
		flingInstPointableFuncArgList
	;
//--------
