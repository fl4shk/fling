lexer grammar FlingLexerGrammar;

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

fragment FragDecNum:
	[0-9] [0-9_]*
	;
fragment FragFloatFrac:
	FragDecNum? '.' FragDecNum
	| FragDecNum '.'
	;
fragment FragFloatExpPart:
	'e' FragFloatSign? FragDecNum
	| 'E' FragFloatSign? FragDecNum
	;
fragment FragFloatSign:
	'+' | '-'
	;
fragment FragFloatSuffix:
	'f' | 'd' | 'l' | 'F' | 'D' | 'L'
	;

TokFloatNum: 
	FragFloatFrac FragFloatExpPart? FragFloatSuffix?
	| FragDecNum FragFloatExpPart FragFloatSuffix?
	;

TokDecNum: FragDecNum ;
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
TokLogNotOrForceSuccessOrPointerDeref: '!' ;

TokAssign: '=' ;
TokVarCreateAssign: ':=' ;
TokCstmAssign: '::=' ;

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
TokAtAt: '@@' ;
TokAtEquals: '@=' ;

TokErrorCheckOrNullCheck: '?' ;

TokScopeAccess: '.' ;
TokCstmScopeAccess: '->' ;

TokLParen: '(' ;
TokRParen: ')' ;
TokLAttr: '#[' ;
TokLBracket: '[' ;
TokRBracket: ']' ;
TokLBrace: '{' ;
TokRBrace: '}' ;
TokSemicolon: ';' ;
TokColon: ':' ;
TokComma: ',' ;

TokCase: '=>' ;

TokToident: '#' ;


TokKwIf: 'if' ;
TokKwElse: 'else' ;
TokKwMatch: 'match' ;
TokKwDefault: 'default' ;
TokKwFor: 'for' ;
TokKwIn: 'in' ;
TokKwWhile: 'while' ;
TokKwDo: 'do' ;
TokKwContinue: 'continue' ;
TokKwBreak: 'break' ;

TokKwGen: 'gen' ;
TokKwMacro: 'macro' ;
TokKwDefine: 'define' ;
TokKwTokstrm: 'tokstrm' ;
TokKwCat: 'cat' ;
TokKwFromident: 'fromident' ;


// attribute ideas:  must_use, inline, noinline, deprecated, packed,
// section("string"), target("string"), force_soa, allow_soa,
// force_one_inst, force_multi_inst, attr(some_macro(args...))
// Getter and setter attribute ideas:  pub_vget, pub_vset, pub_crget,
// pub_crset, pub_rvset, (priv and prot of these)

TokKwFunc: 'func' ;
TokKwReturn: 'return' ;
TokKwRetT: 'ret_t' ;


TokKwTask: 'task' ;
TokKwProc: 'proc' ;

TokKwModule: 'module' ;
TokKwInput: 'input' ;
TokKwOutput: 'output' ;
TokKwBidir: 'bidir' ;
TokKwHiImped: 'hi_imped' ;

TokKwInitial: 'initial' ;
TokKwAlwaysComb: 'always_comb' ;
TokKwAlwaysBlk: 'always_blk' ;
TokKwAlwaysFf: 'always_ff' ;

TokKwDollarDisplay: '$display' ;
TokKwDollarMonitor: '$monitor' ;
TokKwDollarFinish: '$finish' ;


TokKwType: 'type' ;
TokKwInstof: 'instof' ;


// Build scripts, libraries, namespaces, etc.
TokKwLibrary: 'library' ;
TokKwWork: 'work' ;
TokKwExtern: 'extern' ;
TokKwNamespace: 'namespace' ;
TokKwUsing: 'using' ;

TokKwDollarLibrary: '$library' ;
TokKwDollarShell: '$shell' ;
TokKwDollarPath: '$path' ;
TokKwDollarExtern: '$extern' ;
TokKwDollarFlag: '$flag' ;
TokKwDollarVar: '$var' ;

TokKwDollarCLibrary: '$c_library' ;
TokKwDollarCHeader: '$c_header' ;
TokKwCHeader: 'c_header' ;
TokKwCExtern: 'c_extern' ;
// This just specifies that a `#define` exists C-side.  Such `#define`s
// have values that fling doesn't care about.
TokKwCppDefine: 'cpp_define' ;

TokKwEnum: 'enum' ;
TokKwUnion: 'union' ;
TokKwVariant: 'variant' ;
TokKwClass: 'class' ;
TokKwExtends: 'extends' ;
TokKwAbstract: 'abstract' ;
TokKwBase: 'base' ;
TokKwSelf: 'self' ;
TokKwSelfT: 'self_t' ;

TokKwTrait: 'trait' ;
TokKwRequires: 'requires' ;

TokKwTry: 'try' ;
TokKwCatch: 'catch' ;

TokKwPub: 'pub' ;
TokKwProt: 'prot' ;
TokKwPriv: 'priv' ;

TokKwMove: 'move' ;

TokKwAlloc: 'alloc' ;
TokKwAllocT: 'alloc_t' ;

TokKwNull: 'null' ;
TokKwNullT: 'null_t' ;

TokKwVolatile: 'volatile' ;
TokKwConst: 'const' ;
TokKwRestrict: 'restrict' ;

TokKwStatic: 'static' ;
TokKwStaticAssert: 'static_assert' ;

TokKwBool: 'bool' ;
TokKwTrue: 'true' ;
TokKwFalse: 'false' ;

TokKwUbit: 'ubit' ;
TokKwIbit: 'ibit' ;
TokKwUlogic: 'ulogic' ;
TokKwIlogic: 'ilogic' ;
TokKwWire: 'wire' ;

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
TokKwUintprT: 'uintptr_t' ;
TokKwIntptrT: 'intptr_t' ;
TokKwPtrdiffT: 'ptrdiff_t' ;
TokKwSizeT: 'size_t' ;
TokKwCmpT: 'cmp_t' ;
TokKwString: 'string' ;
TokKwChar: 'char' ;
TokKwFloat: 'float' ;
TokKwDouble: 'double' ;
TokKwLongdouble: 'longdouble' ;
TokKwFpenv: 'fpenv' ;
TokKwSimd: 'simd' ;

TokKwVoid: 'void' ;
TokKwAuto: 'auto' ;
TokKwRange: 'range' ;


TokKwSizeof: 'sizeof' ;

TokKwCUchar: 'c_uchar' ;
TokKwCSchar: 'c_schar' ;
TokKwCUshortint: 'c_ushortint' ;
TokKwCSshortint: 'c_sshortint' ;
TokKwCUint: 'c_uint' ;
TokKwCSint: 'c_sint' ;
TokKwCUlongint: 'c_ulongint' ;
TokKwCSlongint: 'c_slongint' ;
TokKwCUlonglongint: 'c_ulonglongint' ;
TokKwCSlonglongint: 'c_slonglongint' ;


TokKwFile: 'file' ;
TokKwStdin: 'stdin' ;
TokKwStdout: 'stdout' ;
TokKwStderr: 'stderr' ;

TokKwAtomic: 'atomic' ;
TokKwAtomicRef: 'atomic_ref' ;
TokKwThread: 'thread' ;
TokKwMutex: 'mutex' ;
TokKwCallOnce: 'thrd_call_once' ;
TokKwOnceFlag: 'thrd_once_flag' ;
TokKwCond: 'thrd_cond' ;
TokKwTss: 'tss' ;

TokKwCast: 'cast' ;
TokKwReinterpret: 'reinterpret' ;
TokKwImplicit: 'implicit' ;
//TokKwExplicit: 'explicit' ;

TokKwAttr: 'attr' ;


// The non-post/pre underscore parts must start and end with an
// alphanumeric character, and there must be at least two alphanumeric
// characters.
TokReservedIdent: '__' [A-Za-z] ([A-Za-z0-9_]* [A-Za-z0-9])? '__' ;
TokMacroDefineIdent: '`' [A-Za-z_] [A-Za-z0-9_]* ;

fragment FragBasicIdent:
	([_]? [A-Za-z]) ([_]? [A-Za-z0-9])* [_]?
	;
fragment FragRawIdent: 'r#' FragBasicIdent ;

TokIdent: FragBasicIdent | FragRawIdent;

TokOther: . ;
