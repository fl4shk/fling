//--------
// A global function
flingFuncDecl:
	KwFunc flingFuncDeclSpec
		flingFuncDeclInnards
	;
//--------

//--------
flingFuncDeclSpec:
	KwSpec
	'{'
		flingGlobalNonTypeDeclSpecItem
		(',' flingGlobalNonTypeDeclSpecItem)*
		','?
	'}'
	;
//--------

//--------
flingFuncDeclInnards:
	flingTemplateDeclList? flingArgDeclList
	'{'
		flingFuncDeclItem
		(',' flingFuncDeclItem)*
		','?
	'}'
	;
//--------
