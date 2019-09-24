grammar FrostGrammar;

program:
	packageItem*
	EOF
	;

headerIf:
	'if' letOrConstOrExpr ':'
	;
headerElseIf:
	'else' 'if' letOrConstOrExpr ':'
	;
headerElse:
	'else' ':'
	;
headerSwitch:
	'switch' letOrConstOrExpr ':'
	;
headerCase:
	'case' letOrConstOrExpr ':'
	;
headerDefault:
	'default' ':'
	;
headerWith:
	'with' (letSuffix | frostConstSuffix) ':'
	;
headerFor:
	'for' identExpr 'in' (iterExpr | rangeExpr) ':'
	;
headerWhile:
	'while' expr ':'
	;
headerDoWhile:
	'do' headerWhile ':'
	;
headerFunc:
	'func'
	;

headerGenIf:
	'gen' headerIf
	;
headerElseGenIf:
	'else' headerGenIf
	;
headerElseGen:
	'else' 'gen'
	;
headerGenSwitch:
	'gen' headerSwitch
	;
headerGenWith:
	'gen' headerWith
	;
headerGenFor:
	'gen' headerFor
	;
headerGenWhile:
	'gen' headerWhile
	;
headerGenDoWhile:
	'gen' headerDoWhile
	;
headerGenFunc:
	'gen' headerFunc
	;

letOrConstOrExpr:
	let
	| frostConst
	| expr
	;

anyScopeItem:
	declClass
	| frostConst
	| genLet
	| frostUsing

	// Sometimes this is a function call, and sometimes this is an
	// assignment.  In contexts outside of function scopes, this needs to
	// be an assignment to a `genvar` if it *is* an assignment because you
	// can only assign to a variable inside of a function.
	| expr ';'
	;

packageItem:
	anyScopeItem
	| package
	| packageGen
	| declPackagedOrGlobalFunc
	;

package:
	'package' identExpr
		scopedPackageItems
	;

scopedPackageItems:
	'{'
		packageItem*
	'}'
	;

packageGen:
	packageGenIf
	| packageGenSwitch
	| packageGenWith
	| packageGenFor
	| packageGenWhile
	| packageGenDoWhile
	;
packageGenIf:
	headerGenIf scopedPackageItems
	(headerElseGenIf scopedPackageItems)*
	(headerElseGen scopedPackageItems)?
	;
packageGenSwitch:
	headerGenSwitch
	'{'
		((headerCase | headerDefault)
		(scopedPackageItems | packageItem))*
	'}'
	;
packageGenWith:
	headerGenWith scopedPackageItems
	;
packageGenFor:
	headerGenFor scopedPackageItems
	;
packageGenWhile:
	headerGenWhile scopedPackageItems
	;
packageGenDoWhile:
	headerGenDoWhile
		scopedPackageItems
	;

let:
	'let' letSuffix ';'
	;
letOrConstSuffix:
	identExpr (':' typename)? (TokAssign | TokAtEquals) expr
	| identExpr TokAtEquals 'func' funcSuffix
	;
letSuffix:
	identExpr ':' typename
	| letOrConstSuffix
	;

// Constant lambdas are permissible and just mean that you can't reassign
// to the lambda.  Of course, this means that you can reassign to the
// lambda otherwise (i.e. when it's not constant)
frostConstSuffix:
	'const' letOrConstSuffix
	;

frostConst:
	'let'  frostConstSuffix ';'
	;

// This means that genvars can store lambdas.
genLet:
	'gen' 'let' TokKwConst? letSuffix ';'
	;

frostUsing:
	'using' identExpr '=' typename ';'
	| 'using' scopedIdent ';'
	;

declPackagedOrGlobalFunc:
	(headerGenFunc | headerFunc) identExpr
		funcSuffix
	;

funcSuffix:
	typename? genericList? argList
		scopedFuncItems
	;
funcItem:
	anyScopeItem
	| let
	;

declClass:
	'class' identExpr genericList? extends?
		scopedClassItems
	;
extends:
	'extends' typename (',' typename)*
	;

genericList:
	'{'
		oneGeneric (',' oneGeneric)*
	'}'
	;

oneGeneric:
	oneTypeGeneric
	| oneValGeneric
	;
oneTypeGeneric:
	'type' ((identExpr ('=' typename)?) | ('...' identExpr))
	;
oneValGeneric:
	typename ((identExpr ('=' expr)) | ('...' identExpr))
	;


// Expression parsing
expr:
	assignExpr assignOp expr
	| assignExpr
	;
assignOp:
	TokAssign
	| TokCstmAssign

	| TokPlusEquals
	| TokMinusEquals

	| TokMulEquals
	| TokDivEquals
	| TokModEquals

	| TokBitAndEquals
	| TokBitOrEquals
	| TokBitXorEquals

	| TokBitLslEquals
	| TokBitLsrEquals
	| TokBitAsrEquals

	| TokAtEquals
	;

assignExpr:
	logicalExpr logicalOp assignExpr
	| logicalExpr
	;
logicalOp:
	TokLogAnd
	| TokLogOr
	;

logicalExpr:
	compareExpr compareOp logicalExpr
	| compareExpr
	;
compareOp:
	TokCmpEq
	| TokCmpNe
	| TokCmpLt
	| TokCmpGt
	| TokCmpLe
	| TokCmpGe
	;

compareExpr:
	addSubExpr addSubOp compareExpr
	| addSubExpr
	;
addSubOp:
	TokPlus
	| TokMinus
	;

addSubExpr:
	mulDivModEtcExpr mulDivModEtcOp addSubExpr
	| mulDivModEtcExpr
	;
mulDivModEtcOp:
	TokMul
	| TokDiv
	| TokMod

	| TokBitAnd
	| TokBitOr
	| TokBitXor

	| TokBitLsl
	| TokBitLsr
	| TokBitAsr
	;

mulDivModEtcExpr:
	'(' expr ')'
	| identExpr
	| unaryExpr
	;

unaryExpr:
	unaryOp expr
	;
unaryOp:
	TokAt
	| TokDollar

	| TokBitNot
	| TokLogNot

	| TokPlus
	| TokMinus
	;

// If done with `genLet`, can use compile-time code execution with this to
// produce an identifier by casting the `genLet` to a `string` (or just
// using its value if it is already a `string`)
identExpr:
	simpleIdentExpr (TokIdentConcat simpleIdentExpr)*
	;
simpleIdentExpr:
	identConcatExpr

	// Require '(' and ')' because of infinite recursion in top-down
	// parsing.  Use of '(' and ')' in this situation is good code style
	// anyway.
	| '(' expr ')'
	;

identConcatExpr:
	lowestIdentExpr
	((TokScopeAccess | TokCstmScopeAccess) lowestIdentExpr)*
	;

lowestIdentExpr:
	// '(' expr ')' allows you to give priority to '#' over '.' and
	// '->'
	(basicIdent | ('(' expr ')'))
		(genericInstList? funcCallSuffix)?
		(funcCallSuffix | ('[' expr ']'))*
	;
basicIdent:
	TokBasicIdent
	;

// Lexer rules
LexWhitespace:
	(' ' | '\t' | '\r' | '\n') -> skip
	;

LexLineComment:
	('//' ~('\n')+) -> skip
	;


fragment FragEscapeSequence:
	FragBasicEscapeSequence
	| FragHexEscapeSequence
	;

fragment FragBasicEscapeSequence:
	'\\' ['"?abfnrtv\\]
	;

fragment FragHexEscapeSequence:
	'\\x' [A-Fa-f0-9_]+
	;

fragment FragChar:
	~["\\]
	| FragEscapeSequence
	;

TokStringLiteral:
	'"' FragChar* '"'
	;

TokDecNum: [0-9] [0-9_]* ;
TokHexNum: '0x' [0-9a-fA-F] [0-9a-fA-F_]* ;
TokOctNum: '0o' [0-7] [0-7_]* ;
TokBinNum: '0b' [0-1] [0-1_]* ;

TokParamPack: '...' ;

TokLogAnd: '&&' ;
TokLogOr: '||' ;

TokCmpEq: '==' ;
TokCmpNe: '!=' ;
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

TokBitNot: '~' ;
TokLogNot: '!' ;

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

TokAt: '@' ;
TokAtEquals: '@=' ;
TokDollar: '$' ;
TokIdentConcat: '#' ;

TokScopeAccess: '.' ;
TokCstmScopeAccess: '->' ;

TokLParen: '(' ;
TokRParen: ')' ;
TokLBracket: '[' ;
TokRBracket: ']' ;
TokLBrace: '{' ;
TokRBrace: '}' ;
TokSemicolon: ';' ;
TokColon: ':' ;
TokComma: ',' ;


TokKwString: 'string' ;
TokKwVector: 'vector' ;
TokKwStack: 'stack' ;
TokKwList: 'list' ;
TokKwSet: 'set' ;
TokKwDict: 'dict' ;
TokKwVariant: 'variant' ;

TokKwU8: 'u8' ;
TokKwS8: 's8' ;
TokKwU16: 'u16' ;
TokKwS16: 's16' ;
TokKwU32: 'u32' ;
TokKwS32: 's32' ;
TokKwU64: 'u64' ;
TokKwS64: 's64' ;

TokKwAny: 'any' ;
TokKwVoid: 'void' ;

TokKwContents: 'contents' ;
TokKwContentsof: 'contentsof' ;

TokKwCast: 'cast' ;


TokKwPtr: 'ptr' ;
TokKwNull: 'null' ;

TokKwPref: 'pref' ;
TokKwRref: 'rref' ;
TokKwCref: 'cref' ;

TokKwNew: 'new' ;
TokKwDelete: 'delete' ;
TokKwMove: 'move' ;

TokKwLet: 'let' ;

TokKwPackage: 'package' ;
TokKwUsing: 'using' ;

TokKwFunc: 'func' ;
TokKwReturn: 'return' ;

TokKwType: 'type' ;
TokKwTypeof: 'typeof' ;

TokKwClass: 'class' ;
TokKwSelf: 'self' ;
TokKwExtends: 'extends' ;

TokKwInit: 'init' ;
TokKwDest: 'dest' ;
TokKwFiter: 'fiter' ;
TokKwRiter: 'riter' ;
TokKwRange: 'range' ;

TokKwVirtual: 'virtual' ;
TokKwStatic: 'static' ;
TokKwConst: 'const' ;

TokKwPub: 'pub' ;
TokKwProt: 'prot' ;
TokKwPriv: 'priv' ;

TokKwGen: 'gen' ;

TokKwIf: 'if' ;
TokKwElse: 'else' ;
TokKwSwitch: 'switch' ;
TokKwCase: 'case' ;
TokKwDefault: 'default' ;

TokKwWith: 'with' ;

TokKwFor: 'for' ;
TokKwIn: 'in' ;
TokKwWhile: 'while' ;
TokKwDo: 'do' ;


TokBasicIdent: [A-Za-z_] [A-Za-z0-9_]* ;

TokOther: . ;
