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

	| flingDeclCompUnitClass
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
	KwScope ('(' flingIdent ')')?
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
	KwSpec '(' KwStatic ')'
	;
//--------

//--------
flingCompUnitGen:
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
