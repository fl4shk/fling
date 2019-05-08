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
	| lhsUnscopedCstmTypeName
	| lhsScopedCstmTypeName
	;

lhsBuiltinTypeName:
	TokKwLogic (TokKwUnsigned | TokKwSigned)?  ('[' expr ']')?
	;

// custom type name from the current scope, be it a module or a package.
// (FUTURE)
lhsUnscopedCstmTypeName:
	identName
	;

// custom type name from a package.
// (FUTURE)
lhsScopedCstmTypeName:
	identScope identName
	;


// Array dimensions go here
declNoLhsTypeVar:
	identName ('[' expr ']')?
	;

// List of local variables.
// (FUTURE:  The current scope's type will be important once custom types
// are added in.)
declVarList:
	lhsTypeName declNoLhsTypeVar (',' declNoLhsTypeVar)*
	;

declNoKwLocalparam:
	identName TokAssign
	expr
	//callRetExpr
	;

declLocalparamList:
	TokKwLocalparam
		//lhsTypeName?
		declNoKwLocalparam (',' declNoKwLocalparam)*
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

// Port vars can be arrays!
declOnePortVar:
	identName ('[' expr ']')?
	;

declPortVarList:
	lhsTypeName declOnePortVar (',' declOnePortVar)*
	;


declPortDirectionalVarList:
	(TokKwInput | TokKwOutput) declPortVarList
	;

// "parameter" stuff
declParameterVar:
	identName (TokAssign expr)?
	;

declParameterVarList:
	declParameterVar (',' declParameterVar)*
	;


// "module" stuff
declModule:
	TokKwModule identName
		('#' '(' declParameterVarList ')')?

		// ports
		'('
			// FUTURE:  allow "interface" stuff here
			(declPortDirectionalVarList
				(',' declPortDirectionalVarList)*)?
		')'

	'{'
		moduleScope
	'}'
	;




moduleScope:
	(
		// Pass::ListModuleInnerDecl
		declLocalparamList ';'
		| declVarList ';'
		| generateBlockInModule

		// Pass::FinishRawModuleConstruct
		| moduleStmtContAssign ';'
		//| moduleStmtBehavBlock
		| moduleStmtInstantiateModule ';'
	)*
	;

moduleStmtContAssign:
	TokKwAssign identExpr TokAssign expr
	;


moduleStmtInstantiateModule:
	TokKwInstance

	// Name of the module
	identName

	// Optional name of the instance
	identName?

	instantiateModuleParameterConnectionList?
	'('
		// For "module"s that have ports, this is actually required.
		instantiateModuleConnectionList?
	')'
	;


instantiateModuleParameterConnectionList:
	'#' '('
		instantiateModuleConnectionList
	')'
	;
instantiateModuleConnectionList:
	'.' identName '(' identExpr ')'
		(',' '.' identName '(' identExpr ')')*
	;

// generate block (that is) in (a) module
// As of writing this comment, the only other place where "generate" can
// appear is inside of an interface.
generateBlockInModule:
	TokKwGenerate
		// Optional identifier, which is similar to a label in other HDLs;
		// it allows access to the insides of a generate block.
		identName?
		generateBlockAnyHeader
	'{'
		moduleScope
	'}'
	;


generateBlockAnyHeader:
	generateBlockHeaderForLoop
	| generateBlockHeaderIf
	;

generateBlockHeaderForLoop:
	stmtBehavHeaderForLoop
	;

generateBlockHeaderIf:
	stmtBehavHeaderIf
	;

pseudoFuncCallRange:
	TokKwPseudoFuncRange '(' (expr ',')? expr ')'
	;

//generateBlockInInterface:
//	TokKwGenerate
//		identName?
//		generateBlockAnyHeader
//	'{'
//		interfaceScope
//	'}'
//	;

// Behavioral code statement "headers"
stmtBehavHeaderForLoop:
	TokKwFor '(' identName ':' pseudoFuncCallRange ')'
	;

stmtBehavHeaderIf:
	TokKwIf '(' expr ')'
	;

stmtBehavHeaderElseif:
	TokKwElse TokKwIf '(' expr ')'
	;

// This is boring, but I put it in here for consistency's sake.
stmtBehavHeaderElse:
	TokKwElse
	;


//stmtChunkBehavIf:
//	stmtBehavHeaderIf
//	'{'
//		stmtBehavAny*
//	'}'
//	;
//stmtChunkBehavElseif:
//	stmtBehavHeaderElseif
//	'{'
//		stmtBehavAny*
//	'}'
//	;
//stmtChunkBehavElse:
//	stmtBehavHeaderElse
//	'{'
//		stmtBehavAny*
//	'}'
//	;
//
//stmtBehavIfElseChain:
//	stmtChunkBehavIf ((stmtChunkBehavElseif*) stmtChunkBehavElse)?
//	;



// Expression parsing
// (avoid left-recursion)
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
	exprPlusUnary
	| exprMinusUnary
	| exprLogNot
	| exprBitNot
	| exprCastUnsgn
	| exprCastSgn
	| exprClog2
	//| exprPow
	| numExpr
	| identExpr
	| '(' expr ')'
	;



exprPlusUnary: TokPlus expr ;
exprMinusUnary: TokMinus expr ;
exprLogNot: TokExclamPoint expr ;
exprBitNot: TokBitInvert expr ;
exprCastUnsgn: TokKwDollarUnsgn '(' expr ')' ;
exprCastSgn: TokKwDollarSgn '(' expr ')' ;
exprClog2: TokKwDollarClog2 '(' expr ')' ;
//exprPow: TokKwDollarPow '(' expr ',' expr ')' ;


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
// are forced to do "$sgn(...)" instead of "...'s...".  The lexer would
// have to be more heavily involved here if signed, hard-coded numbers were
// to be allowed with Verilog-style syntax.
rawSizedNumExpr: rawNumExpr TokApostrophe rawNumExpr ;

// This permits using a constant to indicate the width of a hard-coded
// number, permitting shorter Frost HDL source code in some situations.
identSizedNumExpr: identPure TokApostrophe rawNumExpr ;



sliceWithOne:
	'[' expr ']'
	;

sliceWithRange:
	'[' expr ':' expr ']'
	;

sliceWithAny:
	sliceWithOne
	| sliceWithRange
	;


identPure:
	identScope? identName
	;

identExpr:
	(identScope? identInnerExpr)
	| (identConcatExpr)
	;

identInnerExpr:
	identName (sliceWithAny?) (TokPeriod identInnerExpr)?
	;

identConcatExpr:
	TokKwPseudoFuncConcat '(' identExpr (',' identExpr)* ')'
	;


identName: TokIdent ;

identScope:
	(identName TokScope)+
	;


// This needs work.
//genScopedIdentExpr:
//	identName (TokGenScope identName (sliceWithOne? sliceWithAny)?)+
//	(TokGenScope memberAccessIdentExpr)
//	;




// Lexer rules
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

TokDecNum: [0-9] [0-9]* ;
TokHexNum: '0x' [0-9A-Fa-f]+ ;
TokBinNum: '0b' [0-1]+ ;


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

// Well, pointers don't exist in this language, despite the fact that
// structs do.  Thus, we can just repurpose this symbol.  It's pretty
// unambiguous.
TokGenScope: '->' ;



// Keywords
TokKwModule: 'module' ;
//TokKwParameter: 'parameter' ;
TokKwLocalparam: 'localparam' ;

TokKwInterface: 'interface' ;
TokKwModport: 'modport' ;

TokKwInput: 'input' ;
TokKwOutput: 'output' ;
TokKwInout: 'inout' ;

TokKwLogic: 'logic' ;
TokKwStruct: 'struct' ;
TokKwClass: 'class' ;

TokKwPacked: 'packed' ;
TokKwUnpacked: 'unpacked' ;

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

TokKwInstance: 'instance' ;

TokKwPseudoFuncConcat: 'concat' ;
TokKwPseudoFuncRepl: 'repl' ;

TokKwDollarUnsgn: '$unsgn' ;
TokKwDollarSgn: '$sgn' ;
TokKwDollarIsUnsgn: '$is_unsgn' ;
TokKwDollarIsSgn: '$is_sgn' ;
TokKwDollarSize: '$size' ;
TokKwDollarLow: '$low' ;
TokKwDollarHigh: '$high' ;
TokKwDollarFirst: '$first' ;
TokKwDollarLast: '$last' ;
TokKwDollarMsbpos: '$msbpos' ;
TokKwDollarClog2: '$clog2' ;
TokKwDollarPow: '$pow' ;



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
//TokKwDo: 'do' ;

TokKwGenerate: 'generate' ;
TokKwPseudoFuncRange: 'range' ;

TokKwSwitch: 'switch' ;
//TokKwSwitchx: 'switchx' ;
TokKwSwitchz: 'switchz' ;
TokKwCase: 'case' ;
TokKwDefault: 'default' ;




TokIdent: [A-Za-z_] ([A-Za-z_0-9])* ;

TokOther: . ;
