parser grammar FlingSharedGrammar;

import FlingLexerGrammar;

flingSharedProgramItem:
	flingUsing
	| flingDeclMacro
	| flingDeclDefine
	| flingDeclCstmType
	| flingDeclFunc
	| flingDeclVar
	| flingStaticAssert
	;


flingUsing:
	flingUsingTypedef
	| flingUsingLibraryNamespace
	;


flingUsingTypedef:
	'using' flingIdentOrArrayIdent '=' flingTypename ';'
	;

flingUsingLibraryNamespace:
	'using' TokKwLibrary? flingIdent ('::' flingTypename)?  ';'
	;


flingDeclCstmType:
	flingDeclEnum
	| flingDeclUnion
	| flingDeclVariant
	| flingDeclClass
	;

flingDeclEnum:
	'enum' flingAttr? flingIdent
	'{'
		flingEnumContents
	'}'
	;

flingDeclFunc:
	'func' flingAttr? flingDeclFuncSuffix
	;
flingDeclLambdaFunc:
	'func' flingAttr? flingLambdaFuncCapture? flingDeclFuncSuffix
	;

flingDeclFuncSuffix:
	(flingIdent | flingString) flingDeclTemplateArgList?
		flingDeclFuncArgList
	'{'
		flingFuncContents
	'}'
	;

flingDeclVar:
	flingDeclTypedVar
	| flingDeclUntypedVar
	;
flingDeclTypedVar:
	flingAttr? (flingIdentOrArrayIdent | flingTuplePattern)
		':' flingTypename ((TokAssign | TokAtEquals) flingExpr)? ';'
	;
flingDeclUntypedVar:
	flingAttr? flingCvPointerRefPrefix? 
		(flingIdentOrArrayIdent | flingTuplePattern) ':=' flingExpr ';'
	;

flingStaticAssert:
	'static_assert' '(' flingExpr (',' flingString)? ')' ';'
	;

flingAttr:
	'#[' 'attr' '(' (flingSpecMacro | flingSpecFunc) ')' ']'
	| '#[' flingIdent ('(' flingString ')')?  ']'
	;
