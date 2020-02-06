// Lexer rules
//--------
LexWhitespace: (' ' | '\t' | '\r' | '\n') -> skip ;

LexLineComment: ('//' ~('\n')+) -> skip ;
//--------


//--------
fragment FragDecNum:
	[0-9] [0-9_]*
	;
LitDecNum: FragDecNum ;
LitHexNum: '0x' [0-9a-fA-F] [0-9a-fA-F_]* ;
LitOctNum: '0o' [0-7] [0-7_]* ;
LitBinNum: '0b' [0-1] [0-1_]* ;


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

LitFloatNum: 
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


LitString: '"' FragChar* '"' ;
//--------


//--------
PunctParamPack: '...' ;
PunctRangeSeparator: '..' ;
//KwUnderscore: '_' ;
//--------

//--------
PunctLogOr: '||' ;
PunctLogAnd: '&&' ;

PunctCmpEq: '==' ;
PunctCmpNe: '!=' ;
PunctCmpLt: '<' ;
PunctCmpGt: '>' ;
PunctCmpLe: '<=' ;
PunctCmpGe: '>=' ;

PunctPlus: '+' ;
PunctMinus: '-' ;

PunctMulOrPtr: '*' ;
PunctDiv: '/' ;
PunctMod: '%' ;

PunctBitOr: '|' ;
PunctBitAnd: '&' ;
PunctBitXor: '^' ;

// These have been made into *parser* rules
//PunctBitLsl: '<<' ;
//PunctBitLsr: '>>' ;
//PunctBitAsr: '>>>' ;

PunctBitNot: '~' ;
PunctLogNotOrForceSuccess: '!' ;
//--------


//--------
PunctAssign: '=' ;
PunctCstmAssign: ':=' ;

PunctPlusAssign: '+=' ;
PunctMinusAssign: '-=' ;

PunctMulAssign: '*=' ;
PunctDivAssign: '/=' ;
PunctModAssign: '%=' ;

PunctBitOrAssign: '|=' ;
PunctBitAndAssign: '&=' ;
PunctBitXorAssign: '^=' ;

//PunctBitLslAssign: '<<=' ;
//PunctBitLsrAssign: '>>=' ;
//PunctBitAsrAssign: '>>>=' ;

PunctAtAssign: '@=' ;
//--------

//--------
PunctAt: '@' ;
PunctAtAt: '@@' ;
//--------

//--------
PunctErrorCheckOrNullCheck: '?' ;

PunctMultiForceSuccess: '!!' ;
PunctMultiErrorCheckOrNullCheck: '??' ;
//--------

//--------
PunctMemberAccess: '.' ;
PunctPtrMemberAccess: '*.' ;
PunctCstmMemberAccess: '->' ;
PunctScopeAccess: '::' ;
//--------

//--------
PunctLParen: '(' ;
PunctRParen: ')' ;
PunctLBracket: '[' ;
PunctRBracket: ']' ;
PunctLBrace: '{' ;
PunctRBrace: '}' ;
PunctSemicolon: ';' ;
PunctColon: ':' ;
PunctComma: ',' ;
//--------


//--------
KwToident: 'toident' ;
KwFromident: 'fromident' ;
//--------

//--------
KwCond: 'cond' ;
//KwIf: 'if' ;
//KwElif: 'elif' ;
KwElse: 'else' ;
KwMux: 'mux' ;

KwMatch: 'match' ;
//KwCase: 'case' ;
KwDefault: 'default' ;

KwFor: 'for' ;
KwWhile: 'while' ;

KwBreak: 'break' ;
KwContinue: 'continue' ;

KwLabel: 'label' ;

KwScope: 'scope' ;

//KwExcept: 'except' ;
KwTry: 'try' ;
KwCatch: 'catch' ;
//--------

//--------
KwModule: 'module' ;

KwInput: 'input' ;
KwOutput: 'output' ;
KwBidir: 'bidir' ;

KwInitial: 'initial' ;
KwAlwaysComb: 'always_comb' ;
KwAlwaysFf: 'always_ff' ;
KwAlwaysBlk: 'always_blk' ;

KwPosedge: 'posedge' ;
KwNegedge: 'negedge' ;

KwInst: 'inst' ;
//--------

//--------
KwClass: 'class' ;
KwBase: 'base' ;
KwMixin: 'mixin' ;
KwExtends: 'extends' ;
KwDyn: 'dyn' ;
KwAbstract: 'abstract' ;

KwPub: 'pub' ;
KwProt: 'prot' ;
KwPriv: 'priv' ;

KwSelf: 'self' ;
KwSelfT: 'self_t' ;
KwInit: 'init' ;
KwInitlist: 'initlist' ;
KwDest: 'dest' ;
//--------

//--------
KwTrait: 'trait' ;
KwRequires: 'requires' ;
//--------

//--------
KwTuple: 'tuple' ;
KwVariant: 'variant' ;
KwEnum: 'enum' ;
KwUnion: 'union' ;
//--------

//--------
KwNew: 'new' ;
KwDelete: 'delete' ;
//--------

//--------
KwUsing: 'using' ;
KwNamespace: 'namespace' ;
KwLibrary: 'library' ;
KwWork: 'work' ;
KwExport: 'export' ;
//--------

//--------
KwConst: 'const' ;
KwVolatile: 'volatile' ;
//--------

//--------
KwStatic: 'static' ;
KwExtern: 'extern' ;
//--------

//--------
KwStaticAssert: 'static_assert' ;
//--------

//--------
KwFunc: 'func' ;
KwRetT: 'ret_t' ;
//--------

//--------
KwSpec: 'spec' ;
KwAttr: 'attr' ;
//--------

//--------
KwGen: 'gen' ;
KwGeneval: 'geneval' ;
//--------

//--------
KwVar: 'var' ;
//--------

//--------
KwMove: 'move' ;
//--------

//--------
KwNull: 'null' ;
KwNullT: 'null_t' ;
//--------

//--------
KwType: 'type' ;
KwTypeof: 'typeof' ;
KwInstof: 'instof' ;
//--------

//--------
KwTokstrm: 'tokstrm' ;
//--------

// Built-in types
//--------
KwCtlist: 'ctlist' ;
KwCtmap: 'ctmap' ;
KwCtset: 'ctset' ;

KwU8: 'u8' ;
KwI8: 'i8' ;
KwU16: 'u16' ;
KwI16: 'i16' ;
KwU32: 'u32' ;
KwI32: 'i32' ;
KwU64: 'u64' ;
KwI64: 'i64' ;
KwU128: 'u128' ;
KwI128: 'i128' ;

KwString: 'string' ;

KwFloat: 'float' ;
KwDouble: 'double' ;
KwLongdouble: 'longdouble' ;

KwBool: 'bool' ;
KwTrue: 'true' ;
KwFalse: 'false' ;

KwVoid: 'void' ;
KwAuto: 'auto' ;
KwAny: 'any' ;
KwRange: 'range' ;

KwResult: 'result' ;
KwOption: 'option' ;

KwFile: 'file' ;
KwThread: 'thread' ;

KwAllocatorT: 'allocator_t' ;
//--------

//--------
KwCast: 'cast' ;
KwAs: 'as' ;
KwReinterpret: 'reinterpret' ;
KwImplicit: 'implicit' ;
//--------




// The non-post/pre underscore parts must start and end with an
// alphanumeric character, and there must be at least two alphanumeric
// characters.
MiscReservedIdent: '__' [A-Za-z] ([A-Za-z0-9_]* [A-Za-z0-9])? '__' ;
MiscMacroOrDefineIdent: '`' [A-Za-z_] [A-Za-z0-9_]* ;

fragment FragBasicIdent: ([_]? [A-Za-z]) ([_]? [A-Za-z0-9])* [_]?  ;
fragment FragRawIdent: 'r#' FragBasicIdent ;

MiscIdent: FragBasicIdent | FragRawIdent ;

MiscOther: . ;
