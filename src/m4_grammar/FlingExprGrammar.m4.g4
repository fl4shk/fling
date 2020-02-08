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
flingPunctBitLslAssign: PunctCmpLt PunctCmpLe ;
flingPunctBitLsrAssign: PunctCmpGt PunctCmpGe ;
flingPunctBitAsrAssign: PunctCmpGt PunctCmpGt PunctCmpGe ;
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
flingPunctBitLsl: PunctCmpLt PunctCmpLt ;
flingPunctBitLsr: PunctCmpGt PunctCmpGt ;
flingPunctBitAsr: PunctCmpGt PunctCmpGt PunctCmpGt ;
//--------

//--------
flingBitShiftExpr:
	;
//--------
