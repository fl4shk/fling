//--------
// A global function
flingGlobalFunc:
	KwFunc (flingGlobalFuncSpec ',')?
		flingFuncInnards
	;
//--------

//--------
flingGlobalFuncSpec:
	_spec(flingGlobalFuncSpecItem)
	;

flingAnyFuncSpecItem:
	KwInline
	| KwNoinline
	;
flingGlobalFuncSpecItem:
	flingGlobalNonTypeSpecItem
	| flingAnyFuncSpecItem
	;
//--------

//--------
flingFuncInnards:
	flingIdent flingTemplateDeclList? flingArgDeclList
		flingFuncInnardsSuffix
	;
flingFuncInnardsSuffix:
	_list(flingFuncItem)
	;

flingFuncItem:
	flingUsing
	| flingStaticAssert

	| flingFuncScope

	| flingFuncVar
	| flingFuncGen
	| flingExpr

	| _type_etc_list(Local)
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
_gen(Func)
//--------
