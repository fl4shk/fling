grammar CompilerGrammar;

// Parser rules
program:
	subProgram*
	;


subProgram:
	declModule
	| declStruct
	////| declUnion
	//| declEnum
	////| declInterface
	////| declPackage
	;


// Declarations
declModule:
	TokKwModule declParameters? identName
	TokLParen multiListModulePorts TokRParen
	scopedOuterStatements
	;


declStruct:
	TokKwStruct declParameters? identName
	TokLBrace
	(declVarList TokSemicolon)*
	TokRBrace
	TokSemicolon
	;

//declEnum:
//	TokKwEnum identName
//	TokLBrace
//	(listIdentNames | (listIdentNames TokComma))
//	TokRBrace
//	TokSemicolon
//	;


declVarList:
	typeName listIdentNames
	;

declParameters:
	TokNumber TokLParen listPortParams TokRParen
	;


typeName:
	// 
	TokKwLogic (slice?)

	// custom type name
	| identName
	;

slice:
	TokLBrace expr TokColon expr TokRBrace
	;


scopedOuterStatements:
	TokLBrace outerStatement* TokRBrace
	;

//scopedInnerStatements:
//	TokLBrace innerStatement* TokRBrace
//	;


// Outer statements
outerStatement:
	declVarList TokSemicolon
	//| outerStmtAssign TokSemicolon
	//| outerStmtBlockInitial
	//| outerStmtBlockAlwaysComb
	//| outerStmtBlockAlwaysSeq
	;


//outerStmtAssign

// Lists
listIdentNames:
	identName (TokComma identName)*
	;

multiListModulePorts:
	listModulePorts (TokComma listModulePorts)*
	;

listModulePorts:
	(TokKwInput | TokKwOutput) declVarList 
	;

listPortParams:
	portParam (TokComma portParam)*
	;


portParam:
	TokKwParameter identName (TokBlockingAssign expr)?
	;


// Expression parsing
expr:
	exprLogical
	| expr TokOpLogical exprLogical
	;

exprLogical:
	exprCompare
	| exprLogical TokOpCompare exprCompare
	;

exprCompare:
	exprAddSub
	| exprCompare TokPlus exprAddSub
	| exprCompare TokMinus exprAddSub
	;

exprAddSub:
	exprMulDivModEtc
	| exprAddSub TokOpMulDivMod exprMulDivModEtc
	| exprAddSub TokOpBitwise exprMulDivModEtc
	;

exprMulDivModEtc:
	exprUnary
	| numExpr
	| identExpr
	| TokLParen expr TokRParen
	;

exprUnary:
	exprBitInvert
	| exprNegate
	| exprLogNot
	;


exprBitInvert: TokBitInvert expr ;
exprNegate: TokMinus expr ;
exprLogNot: TokExclamPoint expr ;

numExpr: TokDecNum | TokHexNum | TokBinNum ;



identExpr:
	identName
	| identSliced
	//| memberAccessNonSliced
	//| memberAccessSliced
	;


identName: TokIdent ;
identSliced: TokIdent slice ;
//memberAccessNonSliced:
//	TokIdent (TokPeriod TokIdent)+
//	;
//memberAccessSliced:
//	memberAccessNonSliced slice
//	;




// Lexer rules
// ALL tokens get a lexer rule of some sort because it forces ANTLR to
// catch more (all?) syntax errors.
// So that means no raw '...' stuff in the parser rules.
LexWhitespace: (' ' | '\t' | '\n' ) -> skip ;
LexLineComment: ('//' | ';') (~ '\n')* -> skip ;

// Expressions
TokOpLogical: ('&&' | '||') ;
TokOpCompare: ('==' | '!=' | '<' | '>' | '<=' | '>=') ;
TokPlus: '+' ;
TokMinus: '-' ;
TokOpMulDivMod: ('*' | '/' | '%') ;
TokOpBitwise: ('&' | '|' | '^' | '<<' | '>>' | '>>>') ;
TokBitInvert: '~' ;

TokDecNum: [0-9] ([0-9]*) ;
TokHexNum: '0x' ([0-9A-Fa-f]+) ;
TokBinNum: '0b' ([0-1]+) ;


TokBlockingAssign: '=' ;
TokNonBlockingAssign: '<-' ;

// Punctuation, etc.
TokPeriod: '.' ;
TokComma: ',' ;
TokColon: ':' ;
TokScope: '::' ;
TokApostrophe: '\'' ;
TokQuote: '"' ;
TokSemicolon: ';' ;
TokExclamPoint: '!' ;
TokLParen: '(' ;
TokRParen: ')' ;
TokLBracket: '[' ;
TokRBracket: ']' ;
TokLBrace: '{' ;
TokRBrace: '}' ;

// Not "pound", not "hash".  "number".
TokNumber: '#' ;



// Keywords
TokKwModule: 'module' ;
TokKwParameter: 'parameter' ;

TokKwInput: 'input' ;
TokKwOutput: 'output' ;
TokKwLogic: 'logic' ;
TokKwInterface: 'interface' ;
TokKwStruct: 'struct' ;
TokKwPublic: 'public' ;
TokKwPrivate: 'private' ;
TokKwEnum: 'enum' ;
TokKwUnion: 'union' ;
TokKwTask: 'task' ;
TokKwFunction: 'function' ;
TokKwPackage: 'package' ;



TokKwDollarConcat: '$concat' ;
TokKwDollarReplicate: '$replicate' ;



TokKwAssign: 'assign' ;

TokKwInitial: 'initial' ;
TokKwAlwaysComb: 'always_comb' ;
TokKwAlwaysSeq: 'always_seq' ;


TokKwPosedge: 'posedge' ;
TokKwNegedge: 'negedge' ;


TokKwIf: 'if' ;
TokKwElse: 'else' ;
TokKwFor: 'for' ;
TokKwWhile: 'while' ;
TokKwDo: 'do' ;


TokKwSwitch: 'switch' ;
TokKwSwitchx: 'switchx' ;
TokKwSwitchz: 'switchz' ;
TokKwCase: 'case' ;
TokKwDefault: 'default' ;




TokIdent: [A-Za-z_] (([A-Za-z_] | [0-9])*) ;
TokOther: . ;
