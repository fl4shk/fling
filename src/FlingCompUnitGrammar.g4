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
	KwUsing '(' flingIdent ',' flingTypename ')'
	;

flingAliasUsing:
	KwUsing '(' KwAlias ')' 
	;
flingTypeUsing:
	KwUsing '(' KwType ')' '('  flingIdent ',' flingTypename ')'
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
	| flingCompUnitGenIf

	| flingCompUnitGenMatch
	| flingCompUnitGenTagswitch

	| flingCompUnitGenFor
	| flingCompUnitGenWhile

	| flingCompUnitGenBreak
	| flingCompUnitGenContinue

	| flingCompUnitGenLabel
	| flingCompUnitGenScope
	| flingCompUnitGenTry
	| flingCompUnitGenCatch
	;

flingCompUnitGenIf:
	flingGenIfHeader flingCompUnitScopeInnards
	flingCompUnitGenElif*
	flingCompUnitGenElse?
	;
flingCompUnitGenElif:
	flingGenElifHeader flingCompUnitScopeInnards
	;
flingCompUnitGenElse:
	flingGenElseHeader flingCompUnitScopeInnards
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
// `switch`
flingCompUnitGenMatchOption:
	flingCompUnitGenCase
	| flingCompUnitGenDefault
	;
flingCompUnitGenCase:
	flingGenCaseHeader flingCompUnitScopeInnards
	;
flingCompUnitGenDefault:
	flingGenDefaultHeader flingCompUnitScopeInnards
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
