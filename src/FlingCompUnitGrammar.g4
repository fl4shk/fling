//--------
// A compilation unit
flingCompUnit:
	flingCompUnitItem
	(',' flingCompUnitItem)*
	(',')?
	;

flingCompUnitItem:
	flingUsing
	| flingCompUnitScope

	| flingNamespace
	| flingDeclCompUnitVar

	| flingCompUnitGen

	| flingStaticAssert

	| flingDeclClass
	| flingDeclVariant
	| flingDeclEnum
	| flingDeclUnion
	| flingDeclTrait
	| flingDeclFunc
	;
//--------

//--------
flingUsing:
	KwUsing '(' flingIdent ',' flingExpr ')'
	;
//--------

//--------
// You can modify named scopes with compile-time code execution.
flingCompUnitScope:
	flingScopeHeader
		flingCompUnitScopeInnards

flingCompUnitScopeInnards:
	'('
		flingCompUnit?
	')'
	;
//--------

--------
flingNamespace:
	KwNamespace '(' flingIdent ')'
	'('
		flingCompUnit?
	')'
	;
--------

//--------
flingDeclCompUnitVar:
	KwVar
	'('
		(flingDeclCompUnitVarSpec ',')?
		flingDeclVarPostSpecInnards
	')'
	;
flingDeclCompUnitVarSpec:
	KwSpec '(' (KwStatic | KwExtern) ')'
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
	| flingCompUnitGenCatch
	;

flingCompUnitGenCond:
	flingGenCondHeader
	'('
		flingIfHeader flingCompUnitScopeInnards
		(',' flingCompUnitGenElif)*
		(',' flingCompUnitGenElse)?
	')'
	;
flingCompUnitGenElif:
	flingElifHeader flingCompUnitScopeInnards
	;
flingCompUnitGenElse:
	flingElseHeader flingCompUnitScopeInnards
	;


flingCompUnitGenMux:
	flingGenMuxHeader
	'('
		// if
		flingCompUnitScopeInnards

		// else
		',' flingCompUnitScopeInnards
	')'
	;


flingCompUnitGenMatch:
	flingGenMatchHeader
	'('
		(
			flingCompUnitGenMatchOption
			(',' flingCompUnitGenMatchOption)*
			(',')?
		)?
	')'
	;

// Semantic analysis should ban more than one `default` case within one
// `match`
flingCompUnitGenMatchOption:
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
//--------

//--------
flingIdentList:
	flingIdent (',' flingIdent)*
	;
flingExprList:
	flingExpr (',' flingExpr)*
	;
//--------
