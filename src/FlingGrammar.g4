grammar FlingGrammar;




flingProgram:
	flingProgramItem*
	EOF
	;

flingProgramItem:
	flingLibrary
	| flingNamespace
	| flingLet
	| flingClass
	| flingEnum
	| flingFunc
	| flingUsing
	| flingProgramGen
	;

flingLibrary:
	TokKwLibrary flingIdent ';'
	;

flingNamespace:
	TokKwNamespace flingIdent
	'{'
		flingProgramItem*
	'}'
	;

flingLet:
	flingRefLet
	| flingNonRefLet
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
TokAtAt: '@@' ;
TokAtEquals: '@=' ;
TokDollar: '$' ;

TokVariantNeeded: '?' ;

TokScopeAccess: '.' ;
TokPtrScopeAccess: '$.' ;
TokQmarkScopeAccess: '?.' ;
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


TokKwIf: 'if' ;
TokKwElse: 'else' ;
TokKwMatch: 'match' ;
TokKwCase: 'case' ;
TokKwDefault: 'default' ;
TokKwWith: 'with' ;
TokKwFor: 'for' ;
TokKwIn: 'in' ;
TokKwWhile: 'while' ;
TokKwDo: 'do' ;

TokKwGen: 'gen' ;
TokKwMacro: 'macro' ;
TokKwDefine: 'define' ;
TokKwToident: 'toident' ;
TokKwLet: 'let' ;


// attribute ideas:  must_use, inline, noinline, deprecated, packed,
// section("string"), target("string"), force_soa, allow_soa, one_inst
TokKwAttr: 'attr' ;

TokKwFunc: 'func' ;
TokKwExpr: 'expr' ;
TokKwReturn: 'return' ;

TokKwType: 'type' ;
TokKwTypeof: 'typeof' ;
TokKwInstof: 'instof' ;

// `refl` is the type returned by `reflof`
TokKwRefl: 'refl' ;
TokKwReflof: 'reflof' ;


TokKwLibrary: 'library' ;
TokKwNamespace: 'namespace' ;
TokKwUsing: 'using' ;
TokKwExtern: 'extern' ;

TokKwCLibrary: 'c_library' ;
TokKwCHeader: 'c_header' ;
TokKwCExtern: 'c_extern' ;
TokKwCppInclude: 'cpp_include' ;
TokKwCppLine: 'cpp_line' ;
TokKwCppError: 'cpp_error' ;
TokKwCpppragma: 'cpp_pragma' ;
TokKwCppIf: 'cpp_if' ;
TokKwCppElif: 'cpp_elif' ;
TokKwCppElse: 'cpp_else' ;
TokKwCppDefined: 'cpp_defined' ;
TokKwCppIfdef: 'cpp_ifdef' ;
TokKwCppIfndef: 'cpp_ifndef' ;
TokKwCppDefine: 'cpp_define' ;
TokKwCppUndef: 'cpp_undef' ;

TokKwEnum: 'enum' ;
TokKwUnion: 'union' ;
TokKwVariant: 'variant' ;
TokKwClass: 'class' ;
TokKwExtends: 'extends' ;
TokKwAbstract: 'abstract' ;
TokKwFinal: 'final' ;
TokKwSelf: 'self' ;

TokKwConcept: 'concept' ;
TokKwRequires: 'requires' ;

TokKwPub: 'pub' ;
TokKwProt: 'prot' ;
TokKwPriv: 'priv' ;

TokKwMove: 'move' ;

TokKwNew: 'new' ;
TokKwDelete: 'delete' ;
TokKwStalloc: 'stalloc' ;

TokKwNull: 'null' ;
TokKwNullT: 'null_t' ;

TokKwVolatile: 'volatile' ;
TokKwConst: 'const' ;
TokKwMut: 'mut' ;
TokKwRestrict: 'restrict' ;

TokKwStatic: 'static' ;
TokKwStaticAssert: 'static_assert' ;

TokKwBool: 'bool' ;
TokKwTrue: 'true' ;
TokKwFalse: 'false' ;

TokKwU8: 'u8' ;
TokKwS8: 's8' ;
TokKwU16: 'u16' ;
TokKwS16: 's16' ;
TokKwU32: 'u32' ;
TokKwS32: 's32' ;
TokKwU64: 'u64' ;
TokKwS64: 's64' ;
TokKwU128: 'u128' ;
TokKwS128: 's128' ;
TokKwUintprT: 'uintptr_t' ;
TokKwIntptrT: 'intptr_t' ;
TokKwPtrdiffT: 'ptrdiff_t' ;
TokKwSizeT: 'size_t' ;
TokKwString: 'string' ;
TokKwChar: 'char' ;
TokKwFloat: 'float' ;
TokKwDouble: 'double' ;
TokKwLongdouble: 'longdouble' ;
TokKwFpenv: 'fpenv' ;
TokKwArray: 'array' ;
TokKwSimd: 'simd' ;
TokKwVoid: 'void' ;
TokKwAuto: 'auto' ;

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
TokKwCallOnce: 'call_once' ;
TokKwOnceFlag: 'once_flag' ;
TokKwCond: 'cond' ;
TokKwTss: 'tss' ;

TokKwCast: 'cast' ;
TokKwReinterpret: 'reinterpret' ;
TokKwImplicit: 'implicit' ;
//TokKwExplicit: 'explicit' ;


// The non-post/pre underscore parts must start and end with an
// alphanumeric character, and there must be at least two alphanumeric
// characters.
TokReservedMembfuncIdent: '__' [A-Za-z] ([A-Za-z0-9_]* [A-Za-z0-9])? '__' ;
TokMacroDefineIdent: '`' [A-Za-z_] [A-Za-z0-9_]* ;

fragment FragBasicIdent:
	([_]? [A-Za-z]) ([_]? [A-Za-z0-9])* [_]?
	;
TokBasicIdent: FragBasicIdent ;
TokRawIdent: '#' FragBasicIdent ;

TokOther: . ;
