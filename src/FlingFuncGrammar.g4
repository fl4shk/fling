//--------
// A global function
flingFunc:
	KwFunc flingFuncSpec
		flingFuncInnards
	;
//--------

//--------
flingFuncSpec:
	KwSpec
	'{'
		flingGlobalNonTypeSpecItem
		(',' flingGlobalNonTypeSpecItem)*
		','?
	'}'
	;
//--------

//--------
flingFuncInnards:
	flingTemplateDeclList? flingArgDeclList
		flingFuncInnardsSuffix
	;
flingFuncInnardsSuffix:
	'{'
		flingFuncItem
		(',' flingFuncItem)*
		','?
	'}'
	;

flingFuncItem:
	flingUsing
	| flingStaticAssert

	| flingFuncScope

	| flingFuncVar
	| flingFuncGen

	| flingTypeOrTraitOrFunc
	;

flingFuncScope:
	KwScope flingScopeHeaderSuffix
		flingFuncScopeInnards
	;

flingFuncScopeInnards:
	flingFuncInnardsSuffix
	;

flingFuncVar:
	KwVar (KwSpec '{' KwStatic '}')?
		flingVarPostSpecInnards
	;
//--------

//--------
flingFuncGen:
	flingSharedGenItem

	| flingFuncGenCond
	| flingFuncGenMux
	| flingFuncGenMatch

	| flingFuncGenFor
	| flingFuncGenWhile

	| flingFuncGenScope
	| flingFuncGenTry
	;

flingFuncGenCond:
	flingGenCondHeader
	'{'
		flingFuncGenIf
		(',' flingFuncGenIf)*
		(',' flingFuncGenElse)?
		','?
	'}'
	;
flingFuncGenIf:
	flingIfHeader flingFuncScopeInnards
	;
flingFuncGenElse:
	flingElseHeader flingFuncScopeInnards
	;


flingFuncGenMux:
	flingGenMuxHeader
	'{'
		// if
		flingFuncScopeInnards

		// else
		',' flingFuncScopeInnards
	'}'
	;


flingFuncGenMatch:
	flingGenMatchHeader
	'{'
		(
			flingFuncGenCase
			(',' flingFuncGenCase)*
			(',' flingFuncGenDefault)?
			','?
		)?
	'}'
	;

flingFuncGenMatchOptions:
	flingFuncGenCase
	| flingFuncGenDefault
	;
flingFuncGenCase:
	flingCaseHeader flingFuncScopeInnards
	;
flingFuncGenDefault:
	flingDefaultHeader flingFuncScopeInnards
	;


flingFuncGenFor:
	flingGenForHeader flingFuncScopeInnards
	;
flingFuncGenWhile:
	flingGenWhileHeader flingFuncScopeInnards
	;

flingFuncGenScope:
	flingGenScopeHeader flingFuncScopeInnards
	;

flingFuncGenTry:
	flingGenTryHeader
	'{'
		flingFuncGen
		',' flingFuncGenCatch
		','?
	'}'
	;
flingFuncGenCatch:
	flingCaseHeader flingFuncGen
	;
//--------
