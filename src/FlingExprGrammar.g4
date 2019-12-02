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

flingHighUnaryExpr:
	(
		(
			flingHighestExpr TokLogNotOrForceSuccess
			| flingHighestExpr TokErrorCheckOrNullCheck
			| flingHighestExpr flingArrayIndexOrSlice
		)
		((TokScopeAccess | TokPtrScopeAccess | TokCstmScopeAccess)
		flingExpr)?
	)
	| flingHighestExpr
	;
flingArrayIndexOrSlice:
	'[' flingExpr ']'
	;

flingHighestExpr:
	'(' flingExpr ')'
	| flingIdent
	| TokStringLiteral
	| TokFloatNum
	| TokDecNum | TokHexNum | TokOctNum | TokBinNum
	| flingRunDefine
	| flingCallFunc
	| flingMatchExpr
	| flingIfExpr
	;
