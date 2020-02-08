//--------
flingExpr:
	flingAssignExpr
	(
		(
			PunctAssign | PunctCstmAssign
			| PunctPlusAssign | PunctMinusAssign
			| PunctMulAssign | PunctDivAssign | PunctModAssign
			| PunctBitAndAssign | PunctBitOrAssign | PunctBitXorAssign
			| flingPunctBitLslAssign | flingPunctBitLsrAssign
			| flingPunctBitAsrAssign
			| PunctAtAssign
		)
		flingExpr
	)?
	;
flingPunctBitLslAssign: '<' '<' '=' ;
flingPunctBitLsrAssign: '>' '>' '=' ;
flingPunctBitAsrAssign: '>' '>' '>' '=' ;
//--------

//--------
flingAssignExpr:
	flingCompareExpr
	(
		(
			PunctCmpEq | PunctCmpNe
			| PunctCmpLt | PunctCmpGt
			| PunctCmpLe | PunctCmpGe
		)
		flingExpr
	)?
	;
//--------

//--------
flingCompareExpr:
	flingLogOrExpr (PunctLogOr flingExpr)?
	;
//--------

//--------
flingLogOrExpr:
	flingLogAndExpr (PunctLogAnd flingExpr)?
	;
//--------

//--------
flingLogAndExpr:
	flingPlusMinusExpr
	(
		(PunctPlus | PunctMinus) 
		flingExpr
	)?
	;
//--------

//--------
flingPlusMinusExpr:
	flingMulDivModExpr
	(
		(PunctMulOrPtr | PunctDiv | PunctMod)
		flingExpr
	)?
	;
//--------

//--------
flingMulDivModExpr:
	flingBitOrExpr (PunctBitOr flingExpr)?
	;
//--------

//--------
flingBitOrExpr:
	flingBitAndExpr (PunctBitAnd flingExpr)?
	;
//--------

//--------
flingBitAndExpr:
	flingBitXorExpr (PunctBitXor flingExpr)?
	;
//--------

//--------
flingBitXorExpr:
	flingBitShiftExpr
	(
		(flingPunctBitLsl | flingPunctBitLsr | flingPunctBitAsr)
		flingExpr
	)?
	;
flingPunctBitLsl: '<' '<' ;
flingPunctBitLsr: '>' '>' ;
flingPunctBitAsr: '>' '>' '>' ;
//--------

//--------
flingBitShiftExpr:
	;
//--------
