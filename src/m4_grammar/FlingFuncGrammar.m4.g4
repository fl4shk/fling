//--------
// A global function
flingGlobalFunc:
	KwFunc (flingGlobalFuncSpec PunctComma)?
		flingFuncInnards
	;
//--------

//--------
flingGlobalFuncSpec:
	_spec_list(flingGlobalFuncSpecItem)
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
	(flingAttr PunctComma)?
		flingIdent flingTemplateDeclList?  flingArgDeclList
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
	| flingReturn

	| _type_etc_list(Local)
	;

flingFuncScope:
	KwScope flingScopeHeaderSuffix
		flingFuncInnardsSuffix
	;

flingFuncVar:
	KwVar (KwSpec PunctLBrace KwStatic PunctRBrace)?
		flingVarPostSpecInnards
	;
flingReturn:
	KwReturn flingExpr
	;
//--------

//--------
_gen(Func)
//--------
