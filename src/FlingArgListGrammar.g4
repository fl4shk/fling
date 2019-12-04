//flingDeclTemplateArgList:
//	flingDeclTemplateArgSublist (',' flingDeclTemplateArgSublist)*
//	;
//
//flingDeclTemplateArgSublist:
//	flingExpr (',' flingExpr)* ':'
//		(flingTypenameMaybeEquals | flingTypeMaybeEquals)
//	;
//
//flingTypenameMaybeEquals:
//	flingTypename ('=' flingExpr)?
//	;
//flingTypeMaybeEquals:
//	'type' ('=' flingTypename)?
//	;
//
//flingDeclFuncMacroArgList:
//	flingDeclFuncMacroArgSublist (',' flingDeclFuncMacroArgSublist)*
//	;
//flingDeclFuncMacroArgSublist


//--------
// Instantiated function or macro arguments
flingInstFuncMacroArgList:
	flingInstFuncMacroPosArgList
	| flingInstFuncMacroNamedArgList
	;

flingInstFuncMacroPosArgList:
	flingExpr (',' flingExpr)* (',')?
	;
flingInstFuncMacroNamedArgList:
	flingInstFuncMacroNamedArg (',' flingInstFuncMacroNamedArg)* (',')?
	;
flingInstFuncMacroNamedArg:
	flingIdent ':' flingExpr
	;
//--------


//--------
// Instantiated template arguments
flingInstTemplateArgList:
	flingInstTemplatePosArgList
	| flingInstTemplateNamedArgList
	;

flingInstTemplatePosArgList:
	flingInstTemplateArg (',' flingInstTemplateArg)* (',')?
	;
flingInstTemplateNamedArgList:
	flingInstTemplateNamedArg (',' flingInstTemplateNamedArg)* (',')?
	;
flingInstTemplateNamedArg:
	flingIdent ':' flingInstTemplateArg
	;

flingInstTemplateArg:
	flingExpr | flingTypename
	;
//--------

