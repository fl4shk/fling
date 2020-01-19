// Lexer rules
LexWhitespace: (' ' | '\t' | '\r' | '\n') -> skip ;

LexLineComment: ('//' ~('\n')+) -> skip ;


fragment FragDecNum:
	[0-9] [0-9_]*
	;
TokDecNum: FragDecNum ;
TokHexNum: '0x' [0-9a-fA-F] [0-9a-fA-F_]* ;
TokOctNum: '0o' [0-7] [0-7_]* ;
TokBinNum: '0b' [0-1] [0-1_]* ;


fragment FragFloatFrac:
	FragDecNum? '.' FragDecNum
	| FragDecNum '.'
	;
fragment FragFloatExpPart:
	'e' FragFloatSign? FragDecNum
	| 'E' FragFloatSign? FragDecNum
	;
fragment FragFloatSign: '+' | '-' ;
fragment FragFloatSuffix: 'f' | 'd' | 'l' | 'F' | 'D' | 'L' ;

TokFloatNum: 
	FragFloatFrac FragFloatExpPart? FragFloatSuffix?
	| FragDecNum FragFloatExpPart FragFloatSuffix?
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


TokStringLiteral: '"' FragChar* '"' ;


//TokParamPack: '...' ;
//TokRangeSeparator: '..' ;
//TokKwUnderscore: '_' ;

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

TokMulOrPtr: '*' ;
TokDiv: '/' ;
TokMod: '%' ;

TokBitAnd: '&' ;
TokBitOr: '|' ;
TokBitXor: '^' ;

// These have been made into *parser* rules
//TokBitLsl: '<<' ;
//TokBitLsr: '>>' ;
//TokBitAsr: '>>>' ;

TokBitNot: '~' ;
TokLogNotOrForceSuccess: '!' ;

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

//TokBitLslEquals: '<<=' ;
//TokBitLsrEquals: '>>=' ;
//TokBitAsrEquals: '>>>=' ;

TokAtEquals: '@=' ;
TokAt: '@' ;
TokAtAt: '@@' ;

TokErrorCheckOrNullCheck: '?' ;

TokMultiForceSuccess: '!!' ;
TokMultiErrorCheckOrNullCheck: '??' ;

TokMemberAccess: '.' ;
TokPtrMemberAccess: '*.' ;
TokCstmMemberAccess: '->' ;
TokScopeAccess: '::' ;

TokLParen: '(' ;
TokRParen: ')' ;
TokLAttr: '#[' ;
TokRAttr: ']#' ;
TokLBracket: '[' ;
TokRBracket: ']' ;
TokLBrace: '{' ;
TokRBrace: '}' ;
TokSemicolon: ';' ;
TokColon: ':' ;
TokComma: ',' ;


//--------
TokToident: 'toident' ;
//--------

//--------
TokKwIf: 'if' ;
TokKwElif: 'elif' ;
TokKwElse: 'else' ;

TokKwMatch: 'match' ;
TokKwCase: 'case' ;
TokKwDefault: 'default' ;

TokKwFor: 'for' ;
TokKwWhile: 'while' ;
TokKwScope: 'scope' ;
TokKwLabel: 'label' ;

TokKwTry: 'try' ;
TokKwCatch: 'catch' ;
//--------

//--------
TokKwClass: 'class' ;
TokKwBase: 'base' ;
TokKwMixin: 'mixin' ;
TokKwExtends: 'extends' ;
TokKwDyn: 'dyn' ;
TokKwAbstract: 'abstract' ;

TokKwPub: 'pub' ;
TokKwProt: 'prot' ;
TokKwPriv: 'priv' ;

TokKwSelf: 'self' ;
TokKwSelfT: 'self_t' ;
TokKwInit: 'init' ;
TokKwDest: 'dest' ;
TokKwInitlist: 'initlist' ;
//--------

//--------
TokKwUsing: 'using' ;
TokKwNamespace: 'namespace' ;
TokKwLibrary: 'library' ;
TokKwWork: 'work' ;
//--------

//--------
TokKwTrait: 'trait' ;
TokKwRequires: 'requires' ;
//--------

//--------
TokKwVariant: 'variant' ;
TokKwTuple: 'tuple' ;
TokKwEnum: 'enum' ;
TokKwUnion: 'union' ;
//--------

//--------
TokKwStatic: 'static' ;
TokKwConst: 'const' ;
TokKwVolatile: 'volatile' ;
//--------

//--------
TokKwStaticAssert: 'static_assert' ;
//--------

//--------
TokKwFunc: 'func' ;
TokKwRetT: 'ret_t' ;
//--------

//--------
TokKwSpec: 'spec' ;
//--------

//--------
TokKwGen: 'gen' ;
//--------

//--------
TokKwVar: 'var' ;
//--------

//--------
TokKwMove: 'move' ;
//--------

//--------
TokKwNull: 'null' ;
TokKwNullT: 'null_t' ;
//--------


//--------
TokKwPack: 'pack' ;
TokKwUnpack: 'unpack' ;
//--------

//--------
TokKwType: 'type' ;
TokKwTypeof: 'typeof' ;
TokKwInstof: 'instof' ;
//--------

//--------
TokKwTokstrm: 'tokstrm' ;
//--------

// Built-in types
//--------
TokKwCtlist: 'ctlist' ;
TokKwCtmap: 'ctmap' ;
TokKwCtset: 'ctset' ;

TokKwU8: 'u8' ;
TokKwI8: 'i8' ;
TokKwU16: 'u16' ;
TokKwI16: 'i16' ;
TokKwU32: 'u32' ;
TokKwI32: 'i32' ;
TokKwU64: 'u64' ;
TokKwI64: 'i64' ;
TokKwU128: 'u128' ;
TokKwI128: 'i128' ;

TokKwString: 'string' ;

TokKwFloat: 'float' ;
TokKwDouble: 'double' ;
TokKwLongdouble: 'longdouble' ;

TokKwBool: 'bool' ;
TokKwTrue: 'true' ;
TokKwFalse: 'false' ;

TokKwVoid: 'void' ;
TokKwAuto: 'auto' ;
TokKwAny: 'any' ;
TokKwRange: 'range' ;

TokKwResult: 'result' ;
TokKwOption: 'option' ;

TokKwFile: 'file' ;
TokKwThread: 'thread' ;

TokKwAllocatorT: 'allocator_t' ;
//--------

//--------
TokKwNew: 'new' ;
TokKwDelete: 'delete' ;
//--------

//--------
TokKwCast: 'cast' ;
TokKwAs: 'as' ;
TokKwReinterpret: 'reinterpret' ;
TokKwImplicit: 'implicit' ;
//--------




// The non-post/pre underscore parts must start and end with an
// alphanumeric character, and there must be at least two alphanumeric
// characters.
TokReservedIdent: '__' [A-Za-z] ([A-Za-z0-9_]* [A-Za-z0-9])? '__' ;
TokMacroOrDefineIdent: '`' [A-Za-z_] [A-Za-z0-9_]* ;

fragment FragBasicIdent: ([_]? [A-Za-z]) ([_]? [A-Za-z0-9])* [_]?  ;
fragment FragRawIdent: 'r#' FragBasicIdent ;

TokIdent: FragBasicIdent | FragRawIdent ;

TokOther: . ;
