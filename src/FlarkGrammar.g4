grammar FlarkGrammar;

kwIf: 'if' ;
kwElse: 'else' ;
kwMatch: 'match' ;
kwCase: 'case' ;
kwDefault: 'default' ;
kwWith: 'with' ;
kwFor: 'for' ;
kwWhile: 'while' ;
kwDo: 'do' ;
kwGen: 'gen' ;
kwMacro: 'macro' ;
kwToident: 'toident' ;
kwLet: 'let' ;


// attribute ideas:  must_use, inline, noinline, deprecated, packed,
// section(string), target(string), force_soa, allow_soa
kwAttr: 'attr' ;

kwFunc: 'func' ;
kwReturn: 'return' ;

kwType: 'type' ;
kwTypeof: 'typeof' ;
kwInstof: 'instof' ;

// `refl` is the type returned by `reflof`
kwRefl: 'refl' ;
kwReflof: 'reflof' ;


kwNamespace: 'namespace' ;
kwUsing: 'using' ;
kwExtern: 'extern' ;
kwLibrary: 'library' ;

kwClibrary: 'clibrary' ;
kwCinclude: 'cinclude' ;
kwCheader: 'cheader' ;
kwCdefine: 'cefine' ;
kwCextern: 'cextern' ;

kwEnum: 'enum' ;
kwUnion: 'union' ;
kwVariant: 'variant' ;
kwClass: 'class' ;
kwExtends: 'extends' ;
kwAbstract: 'abstract' ;
kwFinal: 'final' ;
kwSelf: 'self' ;

kwPub: 'pub' ;
kwProt: 'prot' ;
kwPriv: 'priv' ;

kwMove: 'move' ;

kwNew: 'new' ;
kwDelete: 'delete' ;
kwStalloc: 'stalloc' ;

kwNull: 'null' ;
kwNullT: 'null_t' ;

kwVolatile: 'volatile' ;
kwConst: 'const' ;
kwMut: 'mut' ;
kwRestrict: 'restrict' ;
kwAtomic: 'atomic' ;

kwStatic: 'static' ;
kwStaticAssert: 'static_assert' ;

kwBool: 'bool' ;
kwTrue: 'true' ;
kwFalse: 'false' ;

kwU8: 'u8' ;
kwS8: 's8' ;
kwU16: 'u16' ;
kwS16: 's16' ;
kwU32: 'u32' ;
kwS32: 's32' ;
kwU64: 'u64' ;
kwS64: 's64' ;
kwSizeT: 'size_t' ;
kwString: 'string' ;
kwChar: 'char' ;
kwFloat: 'float' ;
kwDouble: 'double' ;
kwLongdouble: 'longdouble' ;
kwFpenv: 'fpenv' ;
kwVoid: 'void' ;
kwAuto: 'auto' ;

kwUchar: 'uchar' ;
kwSchar: 'schar' ;
kwUshortint: 'ushortint' ;
kwSshortint: 'sshortint' ;
kwUint: 'uint' ;
kwSint: 'sint' ;
kwUlongint: 'ulongint' ;
kwSlongint: 'slongint' ;


kwFile: 'file' ;
kwStdin: 'stdin' ;
kwStdout: 'stdout' ;
kwStderr: 'stderr' ;

kwCast: 'cast' ;
kwReinterpret: 'reinterpret' ;
kwImplicit: 'implicit' ;
//kwExplicit: 'explicit' ;




frostProgram:
	frostProgramItem*
	EOF
	;

frostProgramItem:
	frostNamespace
	| frostLet
	| frostClass
	| frostEnum
	| frostFunc
	| frostUsing
	| frostProgramGen
	;

frostNamespace:
	kwNamespace frostIdent
	'{'
		frostProgramItem*
	'}'
	;

frostLet:
	frostRefLet
	| frostOtherLet
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

// The non-post/pre underscore parts must start and end with an
// alphanumeric character, and there must be at least two alphanumeric
// characters.
TokReservedMembfuncIdent: '__' [A-Za-z] ([A-Za-z0-9_]* [A-Za-z0-9])? '__' ;
TokMacroIdent: '`' [A-Za-z_] [A-Za-z0-9_]* ;
TokBasicIdent: ('r#')?  ([_]? [A-Za-z]) ([_]? [A-Za-z0-9])* [_]?
 ;

TokOther: . ;
