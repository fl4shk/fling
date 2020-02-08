//--------
// A compilation unit
flingCompUnit:
	_list(flingCompUnitItem)
	;

flingCompUnitItem:
	flingUsing
	| flingStaticAssert

	| flingCompUnitScope

	| flingNamespace
	| flingCompUnitVar

	| flingCompUnitGen

	| _type_etc_list(Global)
	| flingGlobalFunc
	;
//--------

//--------
flingUsing:
	KwUsing 
	PunctLBrace
		flingIdent PunctComma flingExpr
	PunctRBrace
	;
//--------

//--------
// You can modify named scopes with compile-time code execution.
flingCompUnitScope:
	KwScope flingScopeHeaderSuffix
		flingCompUnitScopeInnards
	;

flingCompUnitScopeInnards:
	PunctLBrace
		flingCompUnit?
	PunctRBrace
	;
//--------

--------
flingNamespace:
	KwNamespace flingIdent
		flingCompUnitScopeInnards
	;
--------

//--------
flingCompUnitVar:
	KwVar flingCompUnitVarSpec?
		flingVarPostSpecInnards
	;
flingCompUnitVarSpec:
	_spec(flingGlobalNonTypeSpecItem)
	;
flingGlobalNonTypeSpecItem:
	// `static` and `extern` are mutually exclusive, but we'll let semantic
	// analysis take care of that.
	KwStatic | KwExtern
	| KwExport
	;
flingVarPostSpecInnards:
	PunctLBrace
		flingIdentList (PunctColon flingExpr)? (PunctAssign flingExpr)?
	PunctRBrace
	;
//--------

//--------
_gen(CompUnit)
//--------

//--------
flingStaticAssert:
	KwStaticAssert
	PunctLBrace
		flingExpr PunctComma flingExpr
	PunctRBrace
	;
//--------

//--------
flingIdentList:
	flingIdent (PunctComma flingIdent)*
	;
flingExprList:
	flingExpr (PunctComma flingExpr)*
	;
//--------
