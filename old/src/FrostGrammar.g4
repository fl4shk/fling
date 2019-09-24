grammar FrostGrammar;

// Parser Rules
program:
	programItem*
	;

headerIf:
	'if' '(' expr ')'
	;
headerElseIf:
	'else' 'if' '(' expr ')'
	;
headerElse:
	'else'
	;

headerSwitch:
	'switch' '(' expr ')'
	;
headerCase:
	'case' expr ':'
	;
headerDefault:
	'default' ':'
	;

headerFor:
	'for' '(' ident ':' rangeOrExpr ')'
	;
headerWhile:
	'while' '(' expr ')'
	;
headerDo:
	'do'
	;

headerGenerateIf:
	'generate' headerIf
	;
headerElseGenerateIf:
	'else' headerGenerateIf
	;
headerElseGenerate:
	'else' 'generate'
	;

headerGenerateSwitch:
	'generate' headerSwitch
	;

headerGenerateFor:
	'generate' headerFor
	;
headerGenerateWhile:
	'generate' headerWhile
	;
headerGenerateDo:
	'generate' headerDo
	;


programItem:
	programGenerate
	| anyScopeItem
	| declPackage
	;

programGenerate:
	programGenerateIf
	| programGenerateSwitch
	| programGenerateFor
	| programGenerateWhile
	| programGenerateDoWhile
	;

scopedProgramItems:
	'{'
		programItem*
	'}'
	;
programGenerateIf:
	headerGenerateIf scopedProgramItems
	headerElseGenerateIf scopedProgramItems
	headerElseGenerate scopedProgramItems
	;
programGenerateSwitch:
	headerGenerateSwitch
	'{'
		programGenerateSwitchItem*
	'}'
	;
programGenerateSwitchItem:
	(headerCase | headerDefault)
	(scopedProgramItems | programItem)
	;

programGenerateFor:
	headerGenerateFor scopedProgramItems
	;
programGenerateWhile:
	headerGenerateWhile scopedProgramItems
	;
programGenerateDoWhile
	headerGenerateDo
		scopedProgramItems
	headerWhile ';'
	;

anyScopeItem:
	declFunc
	| declCstmType
	| declGenvar
	| declConst

	// Sometimes, this must be something done with a genvar
	| expr ';'
	;

declPackage:
	'package' ident
	scopedPackageItems
	;
scopedPackageItems:
	'{'
		packageItem*
	'}'
	;

packageItem:
	packageGenerate
	| declPackage
	| anyScopeItem
	;

// Expression parsing
expr:
	logicalExpr logicalOp expr
	| logicalExpr
	;
logicalOp:
	TokLogAnd | TokLogOr
	;
logicalExpr:
	compareExpr compareOp logicalExpr
	| typeof compareOp typeof
	| compareExpr
	;
compareOp:
	TokCmpEq | TokCmpNe
	| TokCmpLt | TokCmptGt
	| TokCmpLe | TokCmpGe
	;
compareExpr:
	addSubExpr addSubOp compareExpr
	| addSubExpr
	;
addSubOp:
	TokPlus | TokMinus
	;
addSubExpr:
	mulDivModEtcExpr mulDivModEtcOp addSubExpr
	| mulDivModEtcExpr
	;
mulDivModEtcOp:
	TokMul | TokDiv | TokMod
	| TokBitAnd | TokBitOr | TokBitXor
	| TokBitLsl | TokBitLsr | TokBitAsr
	;

mulDivModEtcExpr:
	unaryOp expr
	| '(' expr ')'
	| identExpr
	| assignExpr
	| numExpr
	| stringLiteral
	;

unaryOp:
	TokPlus | TokMinus
	| TokLogNot | TokBitNot
	| TokDollar | TokAt
	;

identExpr:
	TokIdent genericInstList? (funcCallSuffix | arrayIndex)*
		((TokMemberAccess | TokScopeAccess | TokCstmMemberAccess)
		identExpr)?
	;

genericInstList:
	'{' expr (',' expr)* '}'
	;
funcCallSuffix:
	'(' (expr (',' expr)*)? ')'
	;
arrayIndex:
	'[' expr ']'
	;

assignExpr:
	expr assignOp expr
	;
assignOp:
	TokAtEquals
	| TokAssign | TokCstmAssign
	| TokPlusEquals | TokMinusEquals
	| TokMulEquals | TokDivEquals | TokModEquals
	| TokBitAndEquals | TokBitOrEquals | TokBitXorEquals
	| TokBitLslEquals | TokBitLsrEquals | TokBitAsrEquals
	;

numExpr:
	TokDecNum | TokHexNum | TokOctNum | TokBinNum
	;


// Similar to `decltype` in C++.
typeof:
	'typeof' '(' (expr | typename) ')'
	;


// Lexer Rules

LexWhitespace: (' ' | '\t' | '\n') -> skip ;
LexLineComment: '//' (~ '\n')* -> skip ;


TokStringLiteral:
	'"' FragOneChar* '"'
	;

fragment FragEscapeSequence:
	FragBasicEscapeSequence
	| FragHexEscapeSequence
	;

fragment FragBasicEscapeSequence:
	'\\' ['"?abfnrtv\\]
	;

fragment FragHexEscapeSequence:
	'\\x' FragHexDigit+
	;

fragment FragHexDigit:
	[0-9A-Fa-f_]
	;

fragment FragOneChar:
	~["\\\r\n]
	| FragEscapeSequence
	;


TokDecNum: [0-9] [0-9_]* ;
TokHexNum: '0x' [0-9A-Fa-f_]+ ;
TokOctNum: '0o' [0-7_]+ ;
TokBinNum: '0b' [0-1_]+ ;

TokParamPack: '...' ;

TokLParen: '(' ;
TokRParen: ')' ;
TokLBrace: '[' ;
TokRBrace: ']' ;
TokLBracket: '{' ;
TokRBracket: '}' ;

TokMemberAccess: '.' ;
TokScopeAccess: '::' ;
TokCstmMemberAccess: '->' ;

TokDollar: '$' ;
TokAt: '@' ;
TokAtEquals: '@=' ;
TokPound: '#' ;

TokQuote: '"' ;
TokApostrophe: '\'';

TokQmark: '?' ;
TokColon: ':' ;
TokSemicolon: ';' ;

TokLogAnd: '&&' ;
TokLogOr: '||' ;

TokCmpEq: '==' ;
TokCmpNe: '!= ';
TokCmpLt: '<' ;
TokCmpGt: '>' ;
TokCmpLe: '<=' ;
TokCmpGe: '>=' ;

TokPlus: '+' ;
TokMinus: '-' ;

TokMul: '*' ;
TokDiv: '/' ;
TokMod: '%' ;

TokBitAnd: '&' ;
TokBitOr: '|' ;
TokBitXor: '^' ;
TokBitLsl: '<<' ;
TokBitLsr: '>>' ;
TokBitAsr: '>>>' ;

TokLogNot: '!' ;
TokBitNot: '~' ;


TokAssign: '=' ;
TokCstmAssign: ':=' ;

TokPlusEquals: '+=' ;
TokMinusEquals: '-=' ;

TokMulEquals: '*=' ;
TokDivEquals: '/=' ;
TokModEquals: '%=' ;

TokBitAndEquals: '&=' ;
TokBitOrEquals: '|=' ;
TokBitXorEquals: '^=' ;
TokBitLslEquals: '<<=' ;
TokBitLsrEquals: '>>=' ;
TokBitAsrEquals: '>>>=' ;

TokKwType: 'type' ;
TokKwTypeof: 'typeof' ;

TokKwClass: 'class' ;
TokKwSelf: 'self' ;

TokKwUnion: 'union' ;
TokKwEnum: 'enum' ;
TokKwUsing: 'using' ;

TokKwInit: 'init' ;
TokKwDest: 'dest' ;

TokKwPub: 'pub' ;
TokKwProt: 'prot' ;
TokKwPriv: 'priv' ;

TokKwFunc: 'func' ;
TokKwReturn: 'return' ;

TokKwVirtual: 'virtual' ;
TokKwStatic: 'static' ;
TokKwConst: 'const' ;

TokKwPtr: 'ptr' ;
TokKwRef: 'ref' ;
TokKwRvref: 'rvref' ;
TokKwNull: 'null' ;

TokKwPackage: 'package' ;
TokKwImport: 'import' ;
TokKwAll: 'all' ;
TokKwAs: 'as' ;

TokKwAlloc: 'alloc' ;
TokKwDealloc: 'dealloc' ;

TokKwIf: 'if' ;
TokKwElse: 'else' ;
TokKwSwitch: 'switch' ;
TokKwCase: 'case' ;
TokKwDefault: 'default' ;
TokKwWith: 'with' ;
TokKwFor: 'for' ;
TokKwWhile: 'while' ;
TokKwDo: 'do' ;
TokKwStaticAssert: 'static_assert' ;

TokKwGenerate: 'generate' ;
TokKwGenvar: 'genvar' ;

TokKwPrint: 'print' ;
TokKwCout: 'cout' ;
TokKwCerr: 'cerr' ;
TokKwCin: 'cin' ;
TokKwFile: 'file' ;
TokKwOpen: 'open' ;

TokKwInt: 'int' ;

TokKwU8: 'u8' ;
TokKwS8: 's8' ;
TokKwU16: 'u16' ;
TokKwS16: 's16' ;
TokKwU32: 'u32' ;
TokKwS32: 's32' ;
TokKwU64: 'u64' ;
TokKwS64: 's64' ;

TokKwBool: 'bool ';
TokKwFloat: 'float' ;
TokKwDouble: 'double' ;
TokKwString: 'string' ;

TokKwVoid: 'void' ;

// This is a built-in type only available to `genvar`s.
TokKwCont: 'cont' ;
TokKwContof: 'contof'

// Built-in container types
TokKwVector: 'vector' ;
TokKwList: 'list' ;
TokKwStack: 'stack' ;
TokKwDict: 'dict' ;
TokKwSet: 'set' ;
TokKwVariant: 'variant' ;
TokKwUptr: 'uptr' ;
TokKwSptr: 'sptr' ;
TokKwWptr: 'wptr' ;

TokKwLet: 'let' ;
TokKwRange: 'range' ;
TokKwSizeof: 'sizeof' ;

TokKwTrue: 'true' ;
TokKwFalse: 'false' ;


TokIdent: [A-Za-z_] ([A-Za-z0-9_])* ;

TokOther: . ;
