grammar FrostHdlGrammar;

// Parser rules

// Basically just "module", "interface", and "package" declarations.  There
// are no other things at global scope.
program:
	(
		declPackage
		//| declInterface
		| declModule
	)*
	EOF
	;




// Variable declaration stuff
lhsTypeName:
	lhsBuiltinTypeName
	//| lhsUnscopedCstmTypeName
	//| lhsScopedCstmTypeName
	;

lhsBuiltinTypeName:
	TokKwLogic ((TokKwUnsigned | TokKwSigned)?)
		(('[' expr ']')?)
	;

// custom type name from the current scope, be it a module or a package.
// (FUTURE)
lhsUnscopedCstmTypeName:
	identName
	;

// custom type name from a package.
// (FUTURE)
lhsScopedCstmTypeName:
	scopedIdentName
	;


// Array dimensions go here
declNoLhsTypeVar:
	identName (('[' expr ']')?)
	;

// List of local variables.
// (FUTURE:  The current scope's type will be important once custom types
// are added in.)
declVarList:
	lhsTypeName declNoLhsTypeVar ((',' declNoLhsTypeVar)*)
	;

declNoKwLocalparam:
	identName TokAssign expr
	;

declLocalparamList:
	TokKwLocalparam declNoKwLocalparam ((',' declNoKwLocalparam)*)
	;

// "package" stuff
declPackage:
	TokKwPackage identName
	'{'
		insidePackage
	'}'
	;

insidePackage:
	(
		declLocalparamList ';'
		//| declStruct ';'
		////| declClass ';'
		//| declEnum ';'
		//| declFunction ';'
		//| declTypedef ';'
	)*
	;


// For now, port vars can't be arrays.  Perhaps things will actually stay
// that way (such that arrays on ports *must* be in "splitvar" "struct"s)
declPortVarList:
	lhsTypeName identName ((',' identName)*)
	;


declPortDirectionalVarList:
	(TokKwInput | TokKwOutput | TokKwInout) declPortVarList
	;

// "parameter" stuff
declParameterVar:
	identName ((TokAssign expr)?)
	;
declParameterVarList:
	declParameterVar ((',' declParameterVar)*)
	;


// "module" stuff
declModule:
	TokKwModule identName
		((TokKwParameter '(' declParameterVarList ')')?)

		// ports
		'('
			// FUTURE:  allow "interface" "modport"s here
			(declPortDirectionalVarList
				((',' declPortDirectionalVarList)*))?
		')'

	'{'
		insideModule
	'}'
	;




insideModule:
	(
		declLocalparamList ';'
		| declVarList ';'
		| moduleStmtContAssign ';'
		//| moduleStmtBehavBlock
		//| moduleStmtInstantiateModule ';'
	)*
	;

moduleStmtContAssign:
	TokKwAssign identExpr TokAssign expr
	;



// Expression parsing
expr:
	exprLogical
	| exprLogical TokOpLogical expr 
	;

exprLogical:
	exprCompare
	| exprCompare TokOpCompare exprLogical 
	;

exprCompare:
	exprAddSub
	| exprAddSub TokPlus exprCompare
	| exprAddSub TokMinus exprCompare
	;

exprAddSub:
	exprMulDivModEtc
	| exprMulDivModEtc TokOpMulDivMod exprAddSub
	| exprMulDivModEtc TokOpBitwise exprAddSub
	;

exprMulDivModEtc:
	exprUnary
	| numExpr
	| identExpr
	| '(' expr ')'
	;

exprUnary:
	| exprPlusUnary
	| exprMinusUnary
	| exprLogNot
	| exprBitNot
	| exprCastUnsigned
	| exprCastSigned
	//| exprClog2
	;


exprPlusUnary: TokPlus expr ;
exprMinusUnary: TokMinus expr ;
exprLogNot: TokExclamPoint expr ;
exprBitNot: TokBitInvert expr ;
exprCastUnsigned: TokKwDollarUnsigned '(' expr ')' ;
exprCastSigned: TokKwDollarSigned '(' expr ')' ;
//exprClog2: TokKwDollarClog2 '(' expr ')' ;


numExpr:
	rawNumExpr
	| rawSizedNumExpr
	| identSizedNumExpr
	;


// I have no interest in octal numbers, at least for now.
rawNumExpr: (TokDecNum | TokHexNum | TokBinNum) ;

// Yes, this is done with the parser instead of the lexer.
//
// That is very strange, Bobbeh.
//
// It allows you to do things like
//
// 0x3        ' 9
//
// Also, signed hard-coded numbers are *not* properly handled here, so you
// are forced to do "$signed(...)" instead of "...'s...".  The lexer would
// have to be more heavily involved here if signed, hard-coded numbers were
// to be allowed with Verilog-style syntax.
rawSizedNumExpr: rawNumExpr TokApostrophe rawNumExpr ;

identSizedNumExpr: pureIdentExpr TokApostrophe rawNumExpr ;



// Forcibly
identExpr:
	pureIdentExpr
	////| identConcatExpr
	////| identSliced
	;

pureIdentExpr:
	identName
	| scopedIdentName
	;

identName: TokIdent ;
scopedIdentName: identName TokScope identName
	((TokScope identName)?);


// Lexer rules
// ALL tokens get a lexer rule of some sort because it forces ANTLR to
// catch more (all?) syntax errors.
// So that means no raw '...' stuff in the parser rules.
LexWhitespace: (' ' | '\t' | '\n') -> skip ;
LexLineComment: '//' (~ '\n')* -> skip ;

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
//TokNonBlockingAssign: '<=' ;

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


// I am unsure if these will be used
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
TokKwDollarClog2: '$clog2' ;



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
