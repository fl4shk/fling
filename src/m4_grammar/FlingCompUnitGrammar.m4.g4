//--------
// A compilation unit
flingCompUnit:
	flingCompUnitItem
	(',' flingCompUnitItem)*
	','?
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
	KwUsing '{' flingIdent ',' flingExpr '}'
	;
//--------

//--------
// You can modify named scopes with compile-time code execution.
flingCompUnitScope:
	KwScope flingScopeHeaderSuffix
		flingCompUnitScopeInnards
	;

flingCompUnitScopeInnards:
	'{'
		flingCompUnit?
	'}'
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
	'{'
		flingIdentList ','? (':' flingExpr)? (PunctAssign flingExpr)?
	'}'
	;
//--------

//--------
_gen(CompUnit)
//--------

//--------
flingStaticAssert:
	KwStaticAssert flingExpr ',' flingExpr
//--------

//--------
flingIdentList:
	flingIdent (',' flingIdent)*
	;
flingExprList:
	flingExpr (',' flingExpr)*
	;
//--------
