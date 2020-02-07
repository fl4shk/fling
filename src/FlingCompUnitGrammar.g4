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

	| flingTypeOrTraitOrFunc
	;

flingTypeOrTraitOrFunc:
	flingClass
	| flingVariant
	| flingEnum
	| flingUnion
	| flingTrait
	| flingFunc
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
	'{'
		flingCompUnit?
	'}'
	;
--------

//--------
flingCompUnitVar:
	KwVar flingCompUnitVarSpec?
		flingVarPostSpecInnards
	;
flingCompUnitVarSpec:
	KwSpec
	'{'
		flingGlobalNonTypeSpecItem
		(',' flingGlobalNonTypeSpecItem)*
		','?
	'}'
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
flingCompUnitGen:
	flingSharedGenItem

	| flingCompUnitGenCond
	| flingCompUnitGenMux
	| flingCompUnitGenMatch

	| flingCompUnitGenFor
	| flingCompUnitGenWhile

	| flingCompUnitGenScope
	| flingCompUnitGenTry
	;

flingCompUnitGenCond:
	flingGenCondHeader
	'{'
		flingCompUnitGenIf
		(',' flingCompUnitGenIf)*
		(',' flingCompUnitGenElse)?
		','?
	'}'
	;
flingCompUnitGenIf:
	flingIfHeader flingCompUnitScopeInnards
	;
flingCompUnitGenElse:
	flingElseHeader flingCompUnitScopeInnards
	;


flingCompUnitGenMux:
	flingGenMuxHeader
	'{'
		// if
		flingCompUnitScopeInnards

		// else
		',' flingCompUnitScopeInnards
	'}'
	;


flingCompUnitGenMatch:
	flingGenMatchHeader
	'{'
		(
			flingCompUnitGenCase
			(',' flingCompUnitGenCase)*
			(',' flingCompUnitGenDefault)?
			','?
		)?
	'}'
	;

flingCompUnitGenMatchOptions:
	flingCompUnitGenCase
	| flingCompUnitGenDefault
	;
flingCompUnitGenCase:
	flingCaseHeader flingCompUnitScopeInnards
	;
flingCompUnitGenDefault:
	flingDefaultHeader flingCompUnitScopeInnards
	;


flingCompUnitGenFor:
	flingGenForHeader flingCompUnitScopeInnards
	;
flingCompUnitGenWhile:
	flingGenWhileHeader flingCompUnitScopeInnards
	;

flingCompUnitGenScope:
	flingGenScopeHeader flingCompUnitScopeInnards
	;

flingCompUnitGenTry:
	flingGenTryHeader
	'{'
		flingCompUnitGen
		',' flingCompUnitGenCatch
		','?
	'}'
	;
flingCompUnitGenCatch:
	flingCaseHeader flingCompUnitGen
	;
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
