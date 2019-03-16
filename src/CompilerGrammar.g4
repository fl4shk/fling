grammar CompilerGrammar;

// Parser rules

// Basically just "module", "package", and "interface" declarations.  There
// are no other things at global scope.
program:
	(
		declModule
		//| declPackage
		//| declInterface
	)+
	;




// Variable declaration stuff
lhsTypeName:
	lhsBuiltinTypeName
	//| lhsUnscopedTypeName
	//| lhsScopedTypeName
	;

lhsBuiltinTypeName:
	TokKwLogic ((TokKwUnsigned | TokKwSigned)?)
		((TokLBracket expr TokRBracket)?)
	;

// type name from the current scope, be it a module or a package.
lhsUnscopedTypeName:
	identName
	;

// type name from a package.
lhsScopedTypeName:
	scopedIdentName
	;


// Array dimensions
declNoLhsTypeVar:
	identName ((TokLBracket expr TokRBracket)?)
	;

declVarList:
	lhsTypeName declNoLhsTypeVar ((',' declNoLhsTypeVar)*)
	;

// For now, port vars can't be arrays.
declPortVarList:
	lhsTypeName identName ((',' identName)*)
	;

declPortInputVarList:
	TokKwInput declPortVarList
	;

declPortOutputVarList:
	TokKwOutput declPortVarList
	;
declPortInoutVarList:
	TokKwInout declPortVarList
	;



// "module" stuff
declModule:
	TokKwModule identName
		// FUTURE:  allow "parameter"s here
		TokLParen
			// FUTURE:  allow "interface" "modport"s here
			((declPortInputVarList | declPortOutputVarList
				| declPortInoutVarList)*)
		TokRParen

	TokLBrace
		moduleInsides
	TokRBrace
	;




moduleInsides:
	(
		declVarList TokSemicolon
		| moduleStmtAssign TokSemicolon
		//| moduleStmtInitial
		//| moduleStmtAlwaysComb
		//| moduleStmtAlwaysSeq
	)*
	;

moduleStmtAssign:
	TokKwAssign identExpr TokAssign expr
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


numExpr:
	rawNumExpr
	| sizedNumExpr
	;


rawNumExpr: (TokDecNum | TokHexNum | TokBinNum) ;
sizedNumExpr: rawNumExpr TokApostrophe rawNumExpr ;



identExpr:
	identName
	| scopedIdentName
	//| identConcatExpr
	//| identSliced
	;


identName: TokIdent ;
scopedIdentName: identName TokScope identName;


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

TokKwInterface: 'interface' ;
TokKwModport: 'modport' ;

TokKwInput: 'input' ;
TokKwOutput: 'output' ;
TokKwInout: 'inout' ;

TokKwLogic: 'logic' ;
TokKwStruct: 'struct' ;

TokKwPacked: 'packed' ;
TokKwUnpacked: 'unpacked' ;
TokKwSplitvar: 'splitvar' ;

TokKwUnsigned: 'unsigned' ;
TokKwSigned: 'signed' ;


TokKwPublic: 'public' ;
TokKwProtected: 'protected' ;
TokKwPrivate: 'private' ;
TokKwVirtual: 'virtual' ;


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
