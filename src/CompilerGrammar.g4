grammar CompilerGrammar;

// Parser rules
program:
	subProgram*
	;


// In addition to module declarations, "subProgram" includes things like
// struct definitions and packages, too.
subProgram:
	declModule
	//| declStruct
	//| declClass
	//| declEnum
	//| declTypedef
	//| declInterface
	//| declPackage
	;



// declarations
declModule:
	TokKwModule identName
		TokLParen
			// FUTURE:  insert input/output/inout variable declarations
			// here
		TokRParen

	TokLBrace
		moduleInsides
	TokRBrace
	;

declVar:
	// FUTURE:  convert this to be able to handle sizes.
	identName identName
	;





moduleInsides:
	// FUTURE:  convert this to list of variable declarations
	declVar TokSemicolon
	| moduleStmtAssign TokSemicolon
	//| moduleStmtInitial
	//| moduleStmtAlwaysComb
	//| moduleStmtAlwaysSeq
	;

moduleStmtAssign:
	TokKwAssign identExpr TokAssign expr
	;

//// initial behavioral block
//moduleStmtInitial:
//	TokKwInitial
//	scopedListStmtBehavioral
//	;
//
//// always_comb behavioral block
//moduleStmtAlwaysComb:
//	TokKwAlwaysComb
//	scopedListStmtBehavioral
//	;
//
//// always_seq behavioral block
//moduleStmtAlwaysSeq:
//	TokKwAlwaysSeq
//	scopedListStmtBehavioral
//	;
//
//scopedListStmtBehavioral:
//	TokLBrace
//		listStmtBehavioral
//	TokRBrace
//	;
//
//listStmtBehavioral:
//	stmtBehavioral*
//	;
//
//stmtBehavioral:
//	stmtBehavAssign
//	//| stmtBehavIf
//	//| stmtBehavFor
//	//| stmtBehavWhile
//	| scopedListStmtBehavioral
//	;
//
//stmtBehavAssign:
//	identExpr TokAssign expr TokSemicolon
//	;
//
////stmtBehavIf:
////	TokKwIf TokLParen expr TokRParen
////	scopedListStmtBehavioral
////	;


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

//exprConcat:
//	TokKwDollarConcat TokLParen expr TokRParen
//	;

numExpr: TokDecNum | TokHexNum | TokBinNum ;



identExpr:
	identName
	| identSliced
	| identConcatExpr
	//| memberAccessNonSliced
	//| memberAccessSliced
	;


identName: TokIdent ;

// For now, only support sliced identifiers.
identSliced: TokIdent (slice+) ;

identConcatExpr:
	TokKwDollarConcat TokLParen listIdentExpr TokRParen
	;

listIdentExpr:
	identExpr ((TokComma identExpr)*)
	;



slice:
	TokLBracket 
	(innerSliceOne
	| innerSliceTwo)
	TokRBracket
	;

innerSliceOne:
	expr
	;

innerSliceTwo:
	expr TokColon expr
	;


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


TokAssign: '=' ;
//TokBlockingAssign: '=' ;
//TokNonBlockingAssign: '<-' ;

// Punctuation, etc.
TokPeriod: '.' ;
TokComma: ',' ;
TokColon: ':' ;
TokScope: '::' ;
TokApostrophe: '\'' ;
TokQuote: '"' ;
TokSemicolon: ';' ;
TokExclamPoint: '!' ;
TokQmark: '?' ;
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
TokKwLocalparam: 'localparam' ;

TokKwInput: 'input' ;
TokKwOutput: 'output' ;
TokKwInout: 'inout' ;

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
TokKwDollarRepl: '$repl' ;
TokKwDollarUnsigned: '$unsigned' ;
TokKwDollarSigned: '$signed' ;
TokKwDollarIsUnsigned: '$is_unsigned' ;
TokKwDollarIsSigned: '$is_signed' ;
TokKwDollarSizeof: '$sizeof' ;



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
