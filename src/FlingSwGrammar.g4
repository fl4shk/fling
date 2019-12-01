parser grammar FlingSwGrammar;

import FlingSharedGrammar;


flingSwProgram:
	flingSwProgramItem*
	;

flingSwProgramItem:
	flingSwProgramGen
	| flingSwNamespace
	| flingSwCExtern
	| flingSwCppDefine
	| flingSharedProgramItem
	;

flingSwProgramGen:
	flingSwProgramGenIf
	| flingSwProgramGenMatch
	| flingSwProgramGenFor
	| flingSwProgramGenWhile
	| flingSwProgramGenDoWhile
	| flingSwGenDeclVar
	;

flingSwProgramGenIf:
	'gen' 'if' flingExpr
	'{'
		flingSwProgram
	'}'
	flingSwProgramElseGenIf*
	flingSwProgramElseGen?
	;
flingSwProgramElseGenIf:
	'else' 'gen' 'if' flingExpr
	'{'
		flingSwProgram
	'}'
	;
flingSwProgramElseGen:
	'else' 'gen'
	'{'
		flingSwProgram
	'}'
	;
flingSwProgramGenMatch:
	'gen' 'match' flingExpr
	'{'
		(flingSwProgramMatchCase '=>' flingSwProgram)*
	'}'
	;
flingSwProgramGenFor:
	'gen' 'for' flingIdent 'in' flingForBounds
	'{'
		flingSwProgram
	'}'
	;
flingSwProgramGenWhile:
	'gen' 'while' flingExpr
	'{'
		flingSwProgram
	'}'
	;
flingSwProgramGenDoWhile:
	'gen' 'do' flingExpr
	'{'
		flingSwProgram
	'}' 'while' flingExpr ';'
	;
flingSwGenDeclVar:
	'gen' flingDeclVar
	;


flingSwNamespace:
	'namespace' flingIdent
	'{'
		flingSwProgram
	'}'
	;

flingSwCExtern:
	'c_extern' flingDeclCstmType | flingDeclFunc | flingDeclVar ';'
	| 'c_extern' '{' flingSwProgram '}'
	;
flingSwCppDefine:
	'cpp_define' flingIdent ';'
	;
