parser grammar FlingSharedGrammar;

//import FlingBasicSharedGrammar;
import FlingUsingSharedGrammar;
import FlingDeclMacroSharedGrammar;
import FlingDeclDefineSharedGrammar;
import FlingDeclCstmTypeSharedGrammar;
import FlingDeclVarSharedGrammar;

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
	| flingDeclTrait
	;

flingDeclEnum:
	'enum' flingAttr? flingIdent?
	'{'
		flingEnumContents*
		(',')?
	'}'
	;

flingEnumContents:
	flingEnumGen
	| flingIdent ('=' flingExpr) ','
	;
flingEnumGen:
	flingEnumGenIf
	| flingEnumGenMatch
	| flingEnumGenFor
	| flingEnumGenWhile
	| flingEnumGenDoWhile
	| flingEnumGenDeclVar
	| flingSharedStmt
	;

flingDeclFunc:
	'func' flingAttr? flingExpr flingDeclFuncSuffix
	;
flingDeclLambdaFunc:
	'func' flingAttr? flingLambdaFuncCapture? 
		(flingIdent flingDeclTemplateArgList? | flingString)
		flingDeclFuncSuffix
	;

flingDeclFuncSuffix:
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
	flingAttr? (flingIdentOrArrayIdent | flingPattern)
		':' flingTypename ((TokAssign | TokAtEquals) flingExpr)? ';'
	;
flingDeclUntypedVar:
	flingAttr? flingCvPtrRefPrefix? 
		(flingIdentOrArrayIdent | flingPattern) ':=' flingExpr ';'
	;

flingCvPtrRefPrefix:
	(flingCvPrefix? (TokAt | TokAtAt))?
	(flingCvPrefix? TokMulOrPtr)*
	;

flingCvPrefix:
	(TokKwConst TokKwVolatile?) | (TokKwVolatile TokKwConst?)
	;


