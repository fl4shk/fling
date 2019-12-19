//--------
flingIdentList:
	flingIdent (',' flingIdent)* (',')?
	;
flingExprList:
	flingExpr (',' flingExpr)* (',')?
	;
flingTypenameList:
	flingTypename (',' flingTypename)* (',')?
	;
//--------

//--------
flingDeclFuncMacroArgList:
	'('
		(flingDeclFuncMacroArg (',' flingDeclFuncMacroArg)* (',')?)?
	')'
	;
flingDeclFuncMacroArg:
	flingIdentList ':' flingTypename ('=' flingExprList)?
	;
//--------

//--------
flingDeclTemplateArgList:
	'<'
		flingDeclTemplateArg (',' flingDeclTemplateArg)* (',')?
	'>'
	;
flingDeclTemplateArg:
	flingIdentList ':'
	(flingDeclTemplateValueArg | flingDeclTemplateTypeArg)
	;
flingDeclTemplateValueArg:
	flingTypename ('=' flingExprList)?
	;
flingDeclTemplateTypeArg:
	'type' ('(' flingExprOfTraits ')')? ('=' flingTypenameList)?
	;

flingExprOfTraits:
	flingLogAndExprOfTraits ('&&' flingExprOfTraits)?
	;
flingLogAndExprOfTraits:
	flingLogOrExprOfTraits ('||' flingExprOfTraits)?
	;
flingLogOrExprOfTraits:
	TokLogNotOrForceSuccess flingExprOfTraits
	| '(' flingExprOfTraits ')'
	| flingTypename
	;
//--------


//--------
// Instantiated function or macro arguments
flingInstFuncMacroArgList:
	'('
		(
			flingInstFuncMacroPosArgList
			| flingInstFuncMacroNamedArgList
		)?
	')'
	;

flingInstFuncMacroPosArgList:
	flingExprList
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
	'<'
		(flingInstTemplatePosArgList | flingInstTemplateNamedArgList)
	'>'
	;

flingInstTemplateInnerArgList:
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
