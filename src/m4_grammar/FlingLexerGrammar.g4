// Lexer rules
//--------
LexWhitespace: (' ' | '\t' | '\r' | '\n') -> skip ;

//FragLexLineComment: ('//' ~('\n')+) -> skip ;
fragment FragLexLineComment: ('//' ~('\n')+) '\n';
//--------


//--------
fragment FragDecNum:
	[0-9] [0-9_]*
	;
LitDecNum: FragLexLineComment* FragDecNum ;
LitHexNum: FragLexLineComment* '0x' [0-9a-fA-F] [0-9a-fA-F_]* ;
LitOctNum: FragLexLineComment* '0o' [0-7] [0-7_]* ;
LitBinNum: FragLexLineComment* '0b' [0-1] [0-1_]* ;


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
	FragLexLineComment*
	(
		FragFloatFrac FragFloatExpPart? FragFloatSuffix?
		| FragDecNum FragFloatExpPart FragFloatSuffix?
	)
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


LitString: FragLexLineComment* '"' FragChar* '"' ;
//--------


//--------
PunctParamPack: FragLexLineComment* '...' ;
PunctRangeSeparator: FragLexLineComment* '..' ;
//KwUnderscore: '_' ;
//--------

//--------
PunctLogOr: FragLexLineComment* '||' ;
PunctLogAnd: FragLexLineComment* '&&' ;

PunctCmpEq: FragLexLineComment* '==' ;
PunctCmpNe: FragLexLineComment* '!=' ;
PunctCmpLt: FragLexLineComment* '<' ;
PunctCmpGt: FragLexLineComment* '>' ;
PunctCmpLe: FragLexLineComment* '<=' ;
PunctCmpGe: FragLexLineComment* '>=' ;

PunctPlus: FragLexLineComment* '+' ;
PunctMinus: FragLexLineComment* '-' ;

PunctMulOrPtr: FragLexLineComment* '*' ;
PunctDiv: FragLexLineComment* '/' ;
PunctMod: FragLexLineComment* '%' ;

PunctBitOr: FragLexLineComment* '|' ;
PunctBitAnd: FragLexLineComment* '&' ;
PunctBitXor: FragLexLineComment* '^' ;

// These have been made into *parser* rules
//PunctBitLsl: '<<' ;
//PunctBitLsr: '>>' ;
//PunctBitAsr: '>>>' ;

PunctBitNot: FragLexLineComment* '~' ;
PunctLogNotOrForceSuccess: FragLexLineComment* '!' ;
//--------


//--------
PunctMapsTo: FragLexLineComment* '=>' ;
//--------

//--------
PunctAssign: FragLexLineComment* '=' ;
PunctCstmAssign: FragLexLineComment* ':=' ;

PunctPlusAssign: FragLexLineComment* '+=' ;
PunctMinusAssign: FragLexLineComment* '-=' ;

PunctMulAssign: FragLexLineComment* '*=' ;
PunctDivAssign: FragLexLineComment* '/=' ;
PunctModAssign: FragLexLineComment* '%=' ;

PunctBitOrAssign: FragLexLineComment* '|=' ;
PunctBitAndAssign: FragLexLineComment* '&=' ;
PunctBitXorAssign: FragLexLineComment* '^=' ;

//PunctBitLslAssign: '<<=' ;
//PunctBitLsrAssign: '>>=' ;
//PunctBitAsrAssign: '>>>=' ;

PunctAtAssign: FragLexLineComment* '@=' ;
//--------

//--------
PunctAt: FragLexLineComment* '@' ;
PunctAtAt: FragLexLineComment* '@@' ;
//--------

//--------
PunctErrorCheckOrNullCheck: FragLexLineComment* '?' ;

PunctMultiForceSuccess: FragLexLineComment* '!!' ;
PunctMultiErrorCheckOrNullCheck: FragLexLineComment* '??' ;
//--------

//--------
PunctMemberAccess: FragLexLineComment* '.' ;
PunctPtrMemberAccess: FragLexLineComment* '*.' ;
PunctCstmMemberAccess: FragLexLineComment* '->' ;
PunctScopeAccess: FragLexLineComment* '::' ;
//--------

//--------
PunctLParen: FragLexLineComment* '(' ;
PunctRParen: FragLexLineComment* ')' ;
PunctLBracket: FragLexLineComment* '[' ;
PunctRBracket: FragLexLineComment* ']' ;
PunctLBrace: FragLexLineComment* '{' ;
PunctRBrace: FragLexLineComment* '}' ;
PunctSemicolon: FragLexLineComment* ';' ;
PunctColon: FragLexLineComment* ':' ;
PunctComma: FragLexLineComment* ',' ;
//--------


//--------
KwToident: FragLexLineComment* 'toident' ;
KwFromident: FragLexLineComment* 'fromident' ;
//--------

//--------
KwCond: FragLexLineComment* 'cond' ;
//KwIf: FragLexLineComment* 'if' ;
//KwElif: FragLexLineComment* 'elif' ;
KwElse: FragLexLineComment* 'else' ;
KwMux: FragLexLineComment* 'mux' ;

KwMatch: FragLexLineComment* 'match' ;
//KwCase: FragLexLineComment* 'case' ;
KwDefault: FragLexLineComment* 'default' ;

KwFor: FragLexLineComment* 'for' ;
KwWhile: FragLexLineComment* 'while' ;

KwBreak: FragLexLineComment* 'break' ;
KwContinue: FragLexLineComment* 'continue' ;

KwLabel: FragLexLineComment* 'label' ;

KwScope: FragLexLineComment* 'scope' ;

//KwExcept: FragLexLineComment* 'except' ;
KwTry: FragLexLineComment* 'try' ;
KwCatch: FragLexLineComment* 'catch' ;
//--------

//--------
KwModule: FragLexLineComment* 'module' ;

KwModport: FragLexLineComment* 'modport' ;

KwInput: FragLexLineComment* 'input' ;
KwOutput: FragLexLineComment* 'output' ;
KwBidir: FragLexLineComment* 'bidir' ;

KwAssign: FragLexLineComment: 'assign' ;
KwInitial: FragLexLineComment* 'initial' ;
KwAlwaysComb: FragLexLineComment* 'always_comb' ;
KwAlwaysFf: FragLexLineComment* 'always_ff' ;
KwAlwaysBlk: FragLexLineComment* 'always_blk' ;

KwPosedge: FragLexLineComment* 'posedge' ;
KwNegedge: FragLexLineComment* 'negedge' ;

KwInst: FragLexLineComment* 'inst' ;

KwBit: FragLexLineComment* 'bit' ;
KwLogic: FragLexLineComment* 'logic' ;

KwUnsigned: FragLexLineComment* 'unsigned' ;
KwSigned: FragLexLineComment* 'signed' ;

KwPacked: FragLexLineComment* 'packed' ;

KwTask: FragLexLineComment* 'task' ;

KwGenerate: FragLexLineComment* 'generate' ;

KwDollarSize: FragLexLineComment* '$size' ;
KwDollarRange: FragLexLineComment* '$range' ;
KwDollarHigh: FragLexLineComment* '$high' ;
KwDollarLow: FragLexLineComment* '$low' ;
KwDollarFirstel: FragLexLineComment* '$firstel' ;
KwDollarLastel: FragLexLineComment* '$lastel' ;
//--------

//--------
KwClass: FragLexLineComment* 'class' ;
KwBase: FragLexLineComment* 'base' ;
KwMixin: FragLexLineComment* 'mixin' ;
KwExtends: FragLexLineComment* 'extends' ;
KwDyn: FragLexLineComment* 'dyn' ;
KwAbstract: FragLexLineComment* 'abstract' ;

KwPub: FragLexLineComment* 'pub' ;
KwProt: FragLexLineComment* 'prot' ;
KwPriv: FragLexLineComment* 'priv' ;

KwSelf: FragLexLineComment* 'self' ;
KwSelfT: FragLexLineComment* 'self_t' ;
KwInit: FragLexLineComment* 'init' ;
KwInitlist: FragLexLineComment* 'initlist' ;
KwDest: FragLexLineComment* 'dest' ;
//--------

//--------
KwTrait: FragLexLineComment* 'trait' ;
KwRequires: FragLexLineComment* 'requires' ;
//--------

//--------
KwTuple: FragLexLineComment* 'tuple' ;
KwVariant: FragLexLineComment* 'variant' ;
KwEnum: FragLexLineComment* 'enum' ;
KwUnion: FragLexLineComment* 'union' ;
//--------

//--------
KwNew: FragLexLineComment* 'new' ;
KwDelete: FragLexLineComment* 'delete' ;
//--------

//--------
KwUsing: FragLexLineComment* 'using' ;
KwNamespace: FragLexLineComment* 'namespace' ;
KwLibrary: FragLexLineComment* 'library' ;
KwWork: FragLexLineComment* 'work' ;
KwExport: FragLexLineComment* 'export' ;
//--------

//--------
KwConst: FragLexLineComment* 'const' ;
KwVolatile: FragLexLineComment* 'volatile' ;
//--------

//--------
KwStatic: FragLexLineComment* 'static' ;
KwExtern: FragLexLineComment* 'extern' ;
//--------

//--------
KwStaticAssert: FragLexLineComment* 'static_assert' ;
//--------

//--------
KwFunc: FragLexLineComment* 'func' ;
KwLambda: FragLexLineComment* 'lambda' ;
KwCaptures: FragLexLineComment* 'captures' ;
KwReturn: FragLexLineComment* 'return' ;
KwRetT: FragLexLineComment* 'ret_t' ;

KwInline: FragLexLineComment* 'inline' ;
KwNoinline: FragLexLineComment* 'noinline' ;
//--------

//--------
KwSpec: FragLexLineComment* 'spec' ;
KwAttr: FragLexLineComment* 'attr' ;
//--------

//--------
KwGen: FragLexLineComment* 'gen' ;
KwGeneval: FragLexLineComment* 'geneval' ;
//--------

//--------
KwVar: FragLexLineComment* 'var' ;
//--------

//--------
KwMove: FragLexLineComment* 'move' ;
//--------

//--------
KwNull: FragLexLineComment* 'null' ;
KwNullT: FragLexLineComment* 'null_t' ;
//--------

//--------
KwType: FragLexLineComment* 'type' ;
KwTypeof: FragLexLineComment* 'typeof' ;
KwInstof: FragLexLineComment* 'instof' ;
//--------

//--------
KwToktree: FragLexLineComment* 'toktree' ;
//--------

// Built-in types
//--------
KwCtlist: FragLexLineComment* 'ctlist' ;
KwCtmap: FragLexLineComment* 'ctmap' ;
KwCtset: FragLexLineComment* 'ctset' ;

KwU8: FragLexLineComment* 'u8' ;
KwI8: FragLexLineComment* 'i8' ;
KwU16: FragLexLineComment* 'u16' ;
KwI16: FragLexLineComment* 'i16' ;
KwU32: FragLexLineComment* 'u32' ;
KwI32: FragLexLineComment* 'i32' ;
KwU64: FragLexLineComment* 'u64' ;
KwI64: FragLexLineComment* 'i64' ;
KwU128: FragLexLineComment* 'u128' ;
KwI128: FragLexLineComment* 'i128' ;

KwString: FragLexLineComment* 'string' ;

KwFloat: FragLexLineComment* 'float' ;
KwDouble: FragLexLineComment* 'double' ;
KwLongdouble: FragLexLineComment* 'longdouble' ;

KwBool: FragLexLineComment* 'bool' ;
KwTrue: FragLexLineComment* 'true' ;
KwFalse: FragLexLineComment* 'false' ;

KwVoid: FragLexLineComment* 'void' ;
KwAuto: FragLexLineComment* 'auto' ;
KwAny: FragLexLineComment* 'any' ;
KwRange: FragLexLineComment* 'range' ;

KwResult: FragLexLineComment* 'result' ;
KwOption: FragLexLineComment* 'option' ;

KwFile: FragLexLineComment* 'file' ;
KwThread: FragLexLineComment* 'thread' ;

KwAllocatorT: FragLexLineComment* 'allocator_t' ;
//--------

//--------
KwCast: FragLexLineComment* 'cast' ;
KwAs: FragLexLineComment* 'as' ;
KwReinterpret: FragLexLineComment* 'reinterpret' ;
KwImplicit: FragLexLineComment* 'implicit' ;
//--------




// The non-post/pre underscore parts must start and end with an
// alphanumeric character, and there must be at least two alphanumeric
// characters.
MiscReservedIdent:
	FragLexLineComment*
	'__' [A-Za-z] ([A-Za-z0-9_]* [A-Za-z0-9])? '__'
	;
MiscMacroOrDefineIdent:
	FragLexLineComment*
	'`' [A-Za-z_] [A-Za-z0-9_]*
	;

fragment FragBasicIdent: ([_]? [A-Za-z]) ([_]? [A-Za-z0-9])* [_]?  ;
fragment FragRawIdent: 'r#' FragBasicIdent ;

MiscIdent: 
	FragLexLineComment*
	(
		FragBasicIdent | FragRawIdent
	);

LexLineComment: FragLexLineComment -> skip ;

MiscOther: . ;
