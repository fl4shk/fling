grammar FrostHdlGrammar;

// Parser Rules
program:
	(
		package
		| module
		| decl_cstm_type
	)*
	EOF
	;


header_if:
	TokKwIf '(' expr ')'
	;
header_else_if:
	TokKwElse TokKwIf '(' expr ')'
	;
header_else:
	TokKwElse
	;

header_for:
	TokKwFor '(' ident ':' (expr | type_range) ')'
	;

header_generate_if:
	TokKwGenerate header_if
	;
header_else_generate_if:
	TokKwElse header_generate_if
	;
header_else_generate:
	TokKwElse TokKwGenerate
	;
header_generate_for:
	TokKwGenerate ident? header_for
	;

package:
	TokKwPackage ident
		scope_package
	;

scope_package:
	'{'
		(
			generate_package
			| package
			| module
			| const
			| using
			| decl_callable
			| decl_cstm_type
		)*
	'}'
	;
generate_package:
	generate_package_if
	| generate_package_for
	;

generate_package_if:
	header_generate_if scope_package
	(header_else_generate_if scope_package)*
	(header_else_generate scope_package)?
	;
generate_package_for:
	header_generate_for scope_package
	;

member_callable_prefix:
	TokKwConst
	| (TokKwConst TokKwVirtual)
	| (TokKwConst TokKwStatic)
	| (TokKwConst TokKwVirtual TokKwStatic)
	| (TokKwConst TokKwStatic TokKwVirtual)
	| TokKwVirtual
	| (TokKwVirtual TokKwConst)
	| (TokKwVirtual TokKwStatic)
	| (TokKwVirtual TokKwConst TokKwStatic)
	| (TokKwVirtual TokKwStatic TokKwConst)
	| TokKwStatic
	| (TokKwStatic TokKwConst)
	| (TokKwStatic TokKwVirtual)
	| (TokKwStatic TokKwConst TokKwVirtual)
	| (TokKwStatic TokKwVirtual TokKwConst)
	;

contents_modproc:
	param_list? arg_list
		scope_modproc
	;

proc:
	TokKwProc proc_ident_etc
		contents_modproc
	;
module:
	TokKwModule ident
		contents_modproc
	;

proc_ident_etc:
	(ident | TokKwPort | const_str)
	;

scope_modproc:
	'{'
		(
			generate_modproc
			| module
			| const
			| var
			| using
			| decl_callable
			| decl_cstm_type
			| hardware_block
		)*
	'}'
	;

generate_modproc:
	generate_modproc_if
	| generate_modproc_for
	;

generate_modproc_if:
	header_generate_if scope_modproc
	(header_else_generate_if scope_modproc)*
	(header_else_generate scope_modproc)?
	;
generate_modproc_for:
	header_generate_for scope_modproc
	;

decl_callable:
	func
	| task
	| proc
	;

contents_func_task:
	param_list? arg_list
		scope_behav
	;

func:
	TokKwFunc typename func_task_ident_etc
		contents_func_task
	;

func_task_ident_etc:
	ident | const_str
	;

task:
	TokKwTask func_task_ident_etc
		contents_func_task
	;

scope_behav:
	'{'
		inner_scope_behav*
	'}'
	;

inner_scope_behav:
	generate_behav
	| const
	| var
	| using
	| stmt_assign
	| stmt_if
	| stmt_for
	| stmt_while
	| stmt_switch
	| stmt_switchz
	| stmt_return
	| ident_etc
	| decl_cstm_type
	| scope_behav
	;


generate_behav:
	generate_behav_if
	| generate_behav_for
	;
generate_behav_if:
	header_generate_if scope_behav
	(header_else_generate_if scope_behav)*
	(header_else_generate scope_behav)?
	;

generate_behav_for:
	header_generate_for scope_behav
	;

const:
	TokKwConst typename?
		one_const
		(',' one_const)* 
		';'
	;
one_const:
	ident_terminal '=' expr
	;

var:
	typename
		one_var
		(',' one_var)*
		';'
	;

one_var:
	ident_terminal (('=' expr) | arg_inst_list)?
	;

using:
	TokKwUsing ident_etc ('=' typename)?
		';'
	;

stmt_assign:
	expr '=' expr ';'
	;
stmt_if:
	header_if scope_behav
	(header_else_if scope_behav)*
	(header_else scope_behav)?
	;

stmt_for:
	header_for
		scope_behav
	;

stmt_while:
	TokKwWhile '(' expr ')'
		scope_behav
	;
stmt_switch:
	TokKwSwitch '(' expr ')'
		scope_switch
	;
stmt_switchz:
	TokKwSwitchz '(' expr ')'
		scope_switch
	;

scope_switch:
	'{'
		(
			stmt_case
			| stmt_default
		)*
	'}'
	;
stmt_case:
	TokKwCase expr ':' inner_scope_behav
	;
stmt_default:
	TokKwDefault ':' inner_scope_behav
	;

stmt_return:
	TokKwReturn expr ';'
	;

decl_cstm_type:
	class
	| enum
	| union
	;

class:
	TokKwPacked? TokKwClass ident param_list?
		extends?
		scope_class
		(one_var
		(',' one_var)*)? ';'
	;
extends:
	TokKwVirtual? TokKwExtends typename
	;

scope_class:
	'{'
		(
			generate_class
			| member_access_label
			| const
			| var
			| arg_port_sublist
			| modport
			| using
			| member_callable
			| decl_cstm_type
		)*
	'}'
	;

modport:
	TokKwModport ident
	'('
		inner_modport
		(',' inner_modport)*
		(',')?
	')' ';'
	;

inner_modport:
	(TokKwInput
	| TokKwOutput
	| TokKwBidir)
	ident
	(',' ident)*
	;

member_callable:
	member_callable_prefix? decl_callable
	;

generate_class:
	generate_class_if
	| generate_class_for
	;
generate_class_if:
	header_generate_if scope_class
	(header_else_generate_if scope_class)*
	(header_else_generate scope_class)?
	;
generate_class_for:
	header_generate_for scope_class
	;

member_access_label:
	(TokKwPublic | TokKwPrivate | TokKwProtected) ':'
	;

enum:
	TokKwEnum typename? ident
	'{'
		ident_terminal
		(',' ident_terminal)
		(',')?
	'}'
		(one_var
		(',' one_var)*)? ';'
	;

union:
	TokKwUnion ident
	'{'
		var*
	'}'
		(one_var
		(',' one_var)*)? ';'
	;

hardware_block:
	cont_assign
	| initial
	| always_comb
	| always_blk
	| always_ff
	| dff
	| inst

	// This needs to be a proc call
	| ident_etc
	;

cont_assign:
	TokKwAssign expr '=' expr ';'
	;
initial:
	TokKwInitial inner_scope_behav
	;
always_comb:
	TokKwAlwaysComb inner_scope_behav
	;
always_blk:
	TokKwAlwaysBlk edge_list
		inner_scope_behav
	;
always_ff:
	TokKwAlwaysFf edge_list
		inner_scope_behav
	;
dff:
	TokKwDff expr
		inner_scope_behav
	;

edge_list:
	'('
		(posedge_inst | negedge_inst)
		(',' (posedge_inst | negedge_inst))*
	')'
	;
posedge_inst:
	TokKwPosedge expr
	;
negedge_inst:
	TokKwNegedge expr
	;
inst:
	TokKwInst ident_etc param_inst_list?
		ident? arg_inst_list? ';'
	;

param_list:
	'['
		param_sublist
		(',' param_sublist)*
		(',')?
	']'
	;

param_sublist:
	(pararg_type_sublist
	| param_module_sublist
	| pararg_var_sublist)
	;

arg_list:
	'('
		(arg_sublist
		(',' arg_sublist)*)?
		(',')?
	')'
	;
arg_sublist:
	(arg_port_sublist
	| pararg_type_sublist)
	;

arg_port_sublist:
	(TokKwInput
	| TokKwOutput
	| TokKwBidir)
	pararg_var_sublist
	;
pararg_var_sublist:
	typename
	TokParamPack? ident_terminal ('=' expr)?
	(',' TokParamPack? ident_terminal ('=' expr)?)*
	;
pararg_type_sublist:
	TokKwType
	pararg_ident_equals_typename_sublist
	;
param_module_sublist:
	TokKwModule
	pararg_ident_equals_typename_sublist
	;
pararg_ident_equals_typename_sublist:
	TokParamPack? ident ('=' typename)?
	(',' TokParamPack? ident ('=' typename)?)*
	;

param_inst_list:
	'['
		(
			pos_pararg_inst_list
			| named_pararg_inst_list
		)?
		(',')?
	']'
	;

arg_inst_list:
	'('
		(
			pos_pararg_inst_list
			| named_pararg_inst_list
		)?
		(',')?
	')'
	;

pos_pararg_inst_list:
	expr
	(',' expr)*
	;
named_pararg_inst_list:
	'.' ident '(' expr ')'
	(',' '.' ident '(' expr ')' )*
	;

typename:
	param_possible_typename
	| no_param_possible_typename
	| typeof
	| type_range
	;
param_possible_typename:
	(ident_etc
		| TokKwUwire | TokKwSwire
		| TokKwUbit | TokKwSbit)
		(param_inst_list | range_suffix)?
	;
no_param_possible_typename:
	TokKwVoid | TokKwAuto
	| TokKwUbyte | TokKwSbyte
	| TokKwUshortint | TokKwSshortint
	| TokKwUint | TokKwSint
	| TokKwUlongint | TokKwSlongint
	;
typeof:
	TokKwTypeof
	'('
		(expr | typename)
	')'
	;

type_range:
	TokKwRange
	range_suffix
	;

range_suffix:
	'['
		expr (':' expr)?
	']'
	;

expr:
	logical_expr logical_op expr 
	| logical_expr
	;
logical_op:
	TokLogAnd
	| TokLogOr
	;

logical_expr:
	compare_expr compare_op logical_expr
	;
compare_op:
	TokCmpEq
	| TokCmpNe
	| TokCmpLt
	| TokCmpGt
	| TokCmpLe
	| TokCmpGe
	;

compare_expr:
	add_sub_expr add_sub_op compare_expr
	| add_sub_expr
	;
add_sub_op:
	TokPlus
	| TokMinus
	;

add_sub_expr:
	mul_div_mod_etc_expr mul_div_mod_etc_op add_sub_expr
	| mul_div_mod_etc_expr
	;
mul_div_mod_etc_op:
	TokMul
	| TokDiv
	| TokMod
	| TokBitLsl
	| TokBitLsr
	| TokBitAsr
	| TokBitAnd
	| TokBitOr
	| TokBitXor
	;

mul_div_mod_etc_expr:
	unary_op expr
	| '(' expr ')'
	| dollar_global_clock
	| dollar_pow_expr
	| ident_etc
	| num_expr
	| const_str
	| pre_dollar_func_of_oneExpr
	| post_dollar_func_of_oneExpr
	| cat_expr
	| repl_expr
	;

unary_op:
	TokLogNot
	| TokBitNot
	| TokPlus
	| TokMinus
	;
dollar_global_clock:
	TokKwDollarGlobalClock
	;
dollar_pow_expr:
	TokKwDollarPow '(' expr ',' expr ')'
	;

num_expr:
	((raw_num | ident_etc | ( '(' expr ')' )) '\'')? raw_num
	;
raw_num:
	TokDecNum
	| TokHexNum
	| TokOctNum
	| TokBinNum
	;
const_str:
	TokConstStr
	;
pre_dollar_func_of_oneExpr:
	dollar_func_of_one '(' ident_etc ')'
	;
post_dollar_func_of_oneExpr:
	ident_etc dollar_func_of_one
	;
dollar_func_of_one:
	TokKwDollarUnsgn | TokKwDollarSgn
	| TokKwDollarIsUnsgn | TokKwDollarIsSgn
	| TokKwDollarRange | TokKwDollarRevrange
	| TokKwDollarSize
	| TokKwDollarFirst | TokKwDollarLast
	| TokKwDollarHigh | TokKwDollarLow
	| TokKwDollarClog2
	| TokKwDollarPast | TokKwDollarStable
	| TokKwDollarRose | TokKwDollarFell
	;

cat_expr:
	TokKwCat
	'('
		expr
		(',' expr)*
	')'
	;
repl_expr:
	TokKwRepl
	'('
		expr ',' expr
	')'
	;

ident_etc:
	ident_member_access
	| ident_scope_access
	| ident_non_member_scope_access
	;

ident_member_access:
	ident_non_member_scope_access '.' ident_etc
	;
ident_scope_access:
	ident_non_member_scope_access '::' ident_etc
	;

ident_non_member_scope_access:
	ident_call
	| ident_no_param_overloaded_call
	| ident_param_member_overloaded_call
	| ident_terminal
	;

ident_call:
	ident param_inst_list? arg_inst_list
	;
ident_no_param_overloaded_call:
	ident_terminal arg_inst_list
	;
ident_param_member_overloaded_call:
	ident_terminal
		'.'
		param_inst_list arg_inst_list
		;

ident_terminal:
	ident
	any_range_suffix*
	;
any_range_suffix:
	range_suffix
	| ('[' expr (TokPlusColon | TokMinusColon) expr ']')
	;
ident:
	TokIdent
	;

// Lexer Rules

LexWhitespace: (' ' | '\t' | '\n') -> skip ;
LexLineComment: '//' (~ '\n')* -> skip ;

TokConstStr: '"' (('\\' '"') | ('\\' '"'))*  '"' ;

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

TokPlusColon: '+:' ;
TokMinusColon: '-:' ;

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

TokKwIf: 'if' ;
TokKwElse: 'else' ;
TokKwFor: 'for' ;
TokKwWhile: 'while' ;
TokKwSwitch: 'switch' ;
TokKwSwitchz: 'switchz' ;
TokKwCase: 'case' ;
TokKwDefault: 'default' ;
TokKwReturn: 'return' ;

TokKwGenerate: 'generate' ;
TokKwPacked: 'packed' ;

TokKwPackage: 'package' ;

TokKwModule: 'module' ;
TokKwProc: 'proc' ;
TokKwPort: 'port' ;

TokKwConst: 'const' ;
TokKwVirtual: 'virtual' ;
TokKwStatic: 'static' ;

TokKwFunc: 'func' ;
TokKwTask: 'task' ;
TokKwUsing: 'using' ;

TokKwClass: 'class' ;
TokKwExtends: 'extends' ;
TokKwModport: 'modport' ;

TokKwInput: 'input' ;
TokKwOutput: 'output' ;
TokKwBidir: 'bidir' ;

TokKwPublic: 'public' ;
TokKwProtected: 'protected' ;
TokKwPrivate: 'private' ;
TokKwNew: 'new' ;

TokKwEnum: 'enum' ;
TokKwUnion: 'union' ;

TokKwAssign: 'assign' ;
TokKwInitial: 'initial' ;
TokKwAlwaysComb: 'always_comb' ;
TokKwAlwaysBlk: 'always_blk' ;
TokKwAlwaysFf: 'always_ff' ;
TokKwDff: 'dff' ;

TokKwPosedge: 'posedge' ;
TokKwNegedge: 'negedge' ;

TokKwAssert: 'assert' ;
TokKwAssume: 'assume' ;
TokKwCover: 'cover' ;
TokKwProperty: 'property' ;

TokKwInst: 'inst' ;
TokKwType: 'type' ;

TokKwUwire: 'uwire' ;
TokKwSwire: 'swire' ;
TokKwUbit: 'ubit' ;
TokKwSbit: 'sbit' ;

TokKwVoid: 'void' ;
TokKwAuto: 'auto' ;

TokKwUbyte: 'ubyte' ;
TokKwSbyte: 'sbyte' ;
TokKwUshortint: 'ushortint' ;
TokKwSshortint: 'sshortint' ;
TokKwUint: 'uint' ;
TokKwSint: 'sint' ;
TokKwUlongint: 'ulongint' ;
TokKwSlongint: 'slongint' ;

TokKwTypeof: 'typeof' ;
TokKwRange: 'range' ;

TokKwDollarGlobalClock: '$global_clock' ;
TokKwDollarPow: '$pow' ;

TokKwDollarUnsgn: '$unsgn' ;
TokKwDollarSgn: '$sgn' ;
TokKwDollarIsUnsgn: '$is_unsgn' ;
TokKwDollarIsSgn: '$is_sgn' ;
TokKwDollarRange: '$range' ;
TokKwDollarRevrange: '$revrange' ;
TokKwDollarSize: '$size' ;
TokKwDollarFirst: '$first' ;
TokKwDollarLast: '$last' ;
TokKwDollarHigh: '$high' ;
TokKwDollarLow: '$low' ;
TokKwDollarClog2: '$clog2' ;
TokKwDollarPast: '$past' ;
TokKwDollarStable: '$stable' ;
TokKwDollarRose: '$rose' ;
TokKwDollarFell: '$fell' ;

TokKwCat: 'cat' ;
TokKwRepl: 'repl' ;


TokIdent: [A-Za-z_] ([A-Za-z_0-9])* ;

TokOther: . ;
