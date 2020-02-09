//--------
flingGlobalClass:
	KwClass (flingGlobalClassSpec PunctComma)?
		flingClassInnards
	;
flingGlobalClassSpec:
	_spec_list(flingGlobalClassSpecItem)
	;
flingGlobalClassSpecItem:
	// `extern` and `export` are mutually exclusive, but we'll let semantic
	// analysis take care of that.
	KwExtern
	| KwExport
	| KwBase
	;

flingLocalClass:
	KwClass (flingLocalClassSpec PunctComma)?
		flingClassInnards
	;
flingLocalClassSpec:
	_spec_list(flingLocalClassSpecItem)
	;
flingLocalClassSpecItem:
	KwBase
	;
//--------

//--------
flingExtends:
	KwExtends flingExtendsList
	;
flingExtendsList:
	_list(flingExpr)
	;
//--------

//--------
flingClassInnards:
	(flingAttr PunctComma)?
		flingIdent flingTemplateDeclList? (PunctComma flingExtends)?
		flingClassInnardsSuffix
	;
flingClassInnardsSuffix:
	_list(flingClassItem)
	;

flingClassItem:
	flingClassUsing
	| flingStaticAssert

	| flingClassScope

	| flingClassVar
	| flingClassFunc
	| flingClassGen

	| _type_etc_list(Class)
	;

flingClassUsing:
	KwUsing flingAnyClassMemberAccessSpec?
		PunctLBrace flingIdent PunctComma flingExpr PunctRBrace
	;

flingAnyClassMemberAccessSpec:
	KwSpec
	PunctLBrace
		flingAnyClassMemberAccessSpecItem
	PunctRBrace
	;
flingAnyClassMemberAccessSpecItem:
	KwPub
	| KwProt
	| KwPriv
	;
flingClassMemberVarOrFuncSpec:
	_spec_list(flingClassMemberVarOrFuncSpecItem)
	;
flingClassMemberVarOrFuncSpecItem:
	flingAnyClassMemberAccessSpecItem
	| KwStatic
	;

flingClassScope:
	KwScope flingScopeHeaderSuffix
		flingClassInnardsSuffix
	;
//--------

//--------
_gen(Class)
//--------
