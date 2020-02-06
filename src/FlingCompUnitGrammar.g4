//--------
// A compilation unit
flingCompUnit:
	flingCompUnitItem
	(',' flingCompUnitItem)*
	','?
	;

flingCompUnitItem:
	flingUsing
	| flingCompUnitScope

	| flingNamespace
	| flingDeclCompUnitVar

	| flingCompUnitGen

	| flingStaticAssert

	| flingClassDecl
	| flingVariantDecl
	| flingEnumDecl
	| flingUnionDecl
	| flingTraitDecl
	| flingFuncDecl
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
flingDeclCompUnitVar:
	KwVar flingDeclCompUnitVarSpec?
	'{'
		flingDeclVarPostSpecInnards
	'}'
	;
flingDeclCompUnitVarSpec:
	KwSpec
	'{'
		flingGlobalNonTypeDeclSpecItem
		(',' flingGlobalNonTypeDeclSpecItem)*
		','?
	'}'
	;
flingGlobalNonTypeDeclSpecItem:
	// `static` and `extern` are mutually exclusive, but we'll let semantic
	// analysis take care of that.
	KwStatic | KwExtern
	| KwExport
	;
	
flingDeclVarPostSpecInnards:
	flingIdentList ','? ':' flingExpr (PunctAssign flingExprList)?
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
flingIdentList:
	flingIdent (',' flingIdent)*
	;
flingExprList:
	flingExpr (',' flingExpr)*
	;
//--------
