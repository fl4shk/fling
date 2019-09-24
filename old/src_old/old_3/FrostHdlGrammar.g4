grammar FrostHdlGrammar;

// Parser Rules
program:
	program_item*
	EOF
	;
program_item:
	package
	| module
	| decl_cstm_type
	;


header_if:
	'if' '(' expr ')'
	;
header_else_if:
	'else' 'if' '(' expr ')'
	;
header_else:
	'else'
	;

header_for:
	'for' '(' ident ':' (expr | type_range) ')'
	;

header_generate_if:
	'generate' header_if
	;
header_else_generate_if:
	'else' header_generate_if
	;
header_else_generate:
	'else' 'generate'
	;
header_generate_for:
	'generate' ident? header_for
	;

package:
	'package' ident
		scope_package
	;

scope_package:
	'{'
		scope_package_item*
	'}'
	;
scope_package_item:
	generate_package
	| package
	| module
	| const
	| using
	| decl_callable
	| decl_cstm_type
	;
generate_package:
	generate_package_if
	| generate_package_for
	;

generate_package_if:
	header_generate_if scope_package
	generate_package_else_if*
	generate_package_else?
	;
generate_package_else_if:
	header_else_generate_if scope_package
	;
generate_package_else:
	header_else_generate scope_package
	;
generate_package_for:
	header_generate_for scope_package
	;

member_callable_prefix:
	non_ref_member_callable_prefix*
	| (kw_virtual kw_ref)
	| (kw_ref kw_virtual)
	| kw_ref
	;
non_ref_member_callable_prefix:
	kw_const | kw_virtual | kw_static
	;
kw_const:
	'const'
	;
kw_virtual:
	'virtual'
	;
kw_static:
	'static'
	;
kw_ref:
	'ref'
	;

contents_modproc:
	param_list? arg_list
		scope_modproc
	;

proc:
	'proc' proc_ident_etc
		contents_modproc
	;
module:
	'module' ident
		contents_modproc
	;

proc_ident_etc:
	(ident | kw_port | const_str)
	;
kw_port:
	'port'
	;

scope_modproc:
	'{'
		scope_modproc_item*
	'}'
	;
scope_modproc_item:
	generate_modproc
	| module
	| const
	| var
	| using
	| decl_callable
	| decl_cstm_type
	| hardware_block
	;

generate_modproc:
	generate_modproc_if
	| generate_modproc_for
	;

generate_modproc_if:
	header_generate_if scope_modproc
	generate_modproc_else_if*
	generate_modproc_else?
	;
generate_modproc_else_if:
	header_else_generate_if scope_modproc
	;
generate_modproc_else:
	header_else_generate scope_modproc
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
	'func' typename func_task_ident_etc
		contents_func_task
	;

func_task_ident_etc:
	ident | const_str
	;

task:
	'task' func_task_ident_etc
		contents_func_task
	;

scope_behav:
	'{'
		scope_behav_item*
	'}'
	;

scope_behav_item:
	generate_behav
	| const
	| var
	| using
	| assign_stmt
	| if_stmt
	| for_stmt
	| while_stmt
	| switch_stmt
	| switchz_stmt
	| return_stmt
	| dollar_resize_stmt
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
	generate_behav_else_if*
	generate_behav_else?
	;
generate_behav_else_if:
	header_else_generate_if scope_behav
	;
generate_behav_else:
	header_else_generate scope_behav
	;

generate_behav_for:
	header_generate_for scope_behav
	;

const:
	'const' typename?
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
	'using' ident_etc ('=' typename)?
		';'
	;

assign_stmt:
	valid_lhs_expr '=' expr ';'
	;
if_stmt:
	header_if scope_behav
	stmt_else_if*
	stmt_else?
	;
stmt_else_if:
	header_else_if scope_behav
	;
stmt_else:
	header_else scope_behav
	;

for_stmt:
	header_for
		scope_behav
	;

while_stmt:
	'while' '(' expr ')'
		scope_behav
	;
switch_stmt:
	'switch' '(' expr ')'
		scope_switch
	;
switchz_stmt:
	'switchz' '(' expr ')'
		scope_switch
	;

scope_switch:
	'{'
		scope_switch_item*
	'}'
	;
scope_switch_item:
	expr_case_item
	| default_case_item
	;
expr_case_item:
	'case' expr ':' scope_behav_item
	;
default_case_item:
	'default' ':' scope_behav_item
	;

return_stmt:
	'return' expr ';'
	;

// For compile-time arrays, which can have different sizes.
dollar_resize_stmt:
	'$resize' '(' ident_etc ',' expr ')' ';'
	| ident_etc '$resize' '(' expr ')' ';'
	;

decl_cstm_type:
	class
	| enum
	| union
	;

class:
	TokKwPacked? 'class' ident param_list?
		extends?
		scope_class
		(one_var
		(',' one_var)*)? ';'
	;
extends:
	TokKwVirtual? 'extends' typename
	;

scope_class:
	'{'
		scope_class_item*
	'}'
	;
scope_class_item:
	generate_class
	| member_access_label
	| const
	| var
	| arg_port_sublist
	| modport
	| using
	| member_callable
	| decl_cstm_type
	;

modport:
	'modport' ident
	'('
		inner_modport
		(',' inner_modport)*
		(',')?
	')' ';'
	;

inner_modport:
	(TokKwInput | TokKwOutput | TokKwBidir)
	ident (',' ident)*
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
	generate_class_else_if*
	generate_class_else?
	;
generate_class_else_if:
	header_else_generate_if scope_class
	;
generate_class_else:
	header_else_generate scope_class
	;
generate_class_for:
	header_generate_for scope_class
	;

member_access_label:
	(TokKwPublic | TokKwPrivate | TokKwProtected) ':'
	;

enum:
	'enum' typename? ident
	'{'
		ident_terminal
		(',' ident_terminal)*
		(',')?
	'}'
		(one_var
		(',' one_var)*)? ';'
	;

union:
	TokKwPacked? 'union' ident
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
	'assign' valid_lhs_expr '=' expr ';'
	;
initial:
	'initial' scope_behav_item
	;
always_comb:
	'always_comb' scope_behav_item
	;
always_blk:
	'always_blk' edge_list
		scope_behav_item
	;
always_ff:
	'always_ff' edge_list
		scope_behav_item
	;
dff:
	'dff' expr
		scope_behav_item
	;

edge_list:
	'('
		edge_list_item
		(',' edge_list_item)*
	')'
	;
edge_list_item:
	posedge_inst | negedge_inst
	;
posedge_inst:
	'posedge' expr
	;
negedge_inst:
	'negedge' expr
	;
inst:
	'inst' ident_etc param_inst_list?
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
		(
			arg_sublist
			(',' arg_sublist)*
			(',')?
		)?
	')'
	;
arg_sublist:
	arg_port_sublist
	| pararg_type_sublist
	;

arg_port_sublist:
	(TokKwInput | TokKwOutput | TokKwBidir)
	pararg_var_sublist
	;
pararg_var_sublist:
	typename
	pararg_var_sublist_item
	(',' pararg_var_sublist_item)*
	;
pararg_var_sublist_item:
	ident_terminal (TokParamPack | ('=' expr))?
	;
pararg_type_sublist:
	'type'
	pararg_ident_equals_typename_sublist
	;
param_module_sublist:
	'module'
	pararg_ident_equals_typename_sublist
	;
pararg_ident_equals_typename_sublist:
	pararg_ident_equals_typename_sublist_item
	(',' pararg_ident_equals_typename_sublist_item)*
	;
pararg_ident_equals_typename_sublist_item:
	ident (TokParamPack | ('=' typename))?
	;

param_inst_list:
	'['
		(
			pos_pararg_inst_list
			| named_pararg_inst_list
			(',')?
		)?
	']'
	;

arg_inst_list:
	'('
		(
			pos_pararg_inst_list
			| named_pararg_inst_list
			(',')?
		)?
	')'
	;

pos_pararg_inst_list:
	expr
	(',' expr)*
	;
named_pararg_inst_list:
	named_pararg_inst_list_item
	(',' named_pararg_inst_list_item)*
	;
named_pararg_inst_list_item:
	ident '(' expr ')'
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
	'typeof'
	'('
		(expr | typename)
	')'
	;

type_range:
	'range'
	range_suffix
	;

range_suffix:
	'['
		expr (':' expr)?
	']'
	;

expr:
	logical_expr
		(TokLogAnd | TokLogOr)
		expr 
	| logical_expr
	;

logical_expr:
	logical_expr_first_choice
	| typeof (TokCmpEq | TokCmpNe) typeof
	| compare_expr
	;
logical_expr_first_choice:
	compare_expr
		(TokCmpEq | TokCmpNe
		| TokCmpLt | TokCmpGt
		| TokCmpLe | TokCmpGe)
		logical_expr
	;

compare_expr:
	compare_expr_first_choice
	| add_sub_expr
	;
compare_expr_first_choice:
	add_sub_expr
		(TokPlus | TokMinus)
		compare_expr
	;

add_sub_expr:
	add_sub_expr_first_choice
	| mul_div_mod_etc_expr
	;
add_sub_expr_first_choice:
	mul_div_mod_etc_expr 
		(TokMul | TokDiv | TokMod
		| TokBitLsl | TokBitLsr | TokBitAsr
		| TokBitAnd | TokBitOr | TokBitXor)
		add_sub_expr
	;

mul_div_mod_etc_expr:
	unary_expr
	| paren_expr
	| dollar_global_clock
	| dollar_pow_expr
	| pre_dollar_func_of_one_expr
	| post_dollar_func_of_one_expr
	| valid_lhs_expr
	| num_expr
	| const_str
	| cat_expr
	| repl_expr
	;

unary_expr:
	(TokLogNot | TokBitNot
	| TokPlus | TokMinus)
	expr
	;
paren_expr:
	'(' expr ')'
	;
dollar_global_clock:
	'$global_clock'
	;
dollar_pow_expr:
	'$pow' '(' expr ',' expr ')'
	;

num_expr:
	((raw_num | ident_etc |  paren_expr) '\'')? raw_num
	;
raw_num:
	TokDecNum | TokHexNum | TokOctNum | TokBinNum
	;
const_str:
	TokConstStr
	;
pre_dollar_func_of_one_expr:
	expr_dollar_func_of_one '(' ident_etc ')'
	;
post_dollar_func_of_one_expr:
	ident_etc expr_dollar_func_of_one
	;
expr_dollar_func_of_one:
	TokKwDollarUnsigned | TokKwDollarSigned
	| TokKwDollarIsUnsigned | TokKwDollarIsSigned
	| TokKwDollarRange | TokKwDollarRevrange
	| TokKwDollarSize
	| valid_lhs_expr_dollar_func_of_one
	| TokKwDollarHigh | TokKwDollarLow
	| TokKwDollarClog2
	| TokKwDollarPast | TokKwDollarStable
	| TokKwDollarRose | TokKwDollarFell
	;
valid_lhs_expr_dollar_func_of_one
	TokKwDollarFirst | TokKwDollarLast
	;
pre_dollar_func_of_one_valid_lhs_expr:
	valid_lhs_expr_dollar_func_of_one '(' ident_etc ')'
	;
post_dollar_func_of_one_valid_lhs_expr:
	ident_etc valid_lhs_expr_dollar_func_of_one
	;

cat_expr:
	'cat'
	'('
		expr
		(',' expr)*
	')'
	;
valid_lhs_expr:
	pre_dollar_func_of_one_valid_lhs_expr
	| post_dollar_func_of_one_valid_lhs_expr
	| ident_etc
	| 'cat' '(' valid_lhs_expr (',' valid_lhs_expr)* ')'
	;

// Replicate
repl_expr:
	'repl' '(' expr ',' expr ')'
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
		'.' param_inst_list arg_inst_list
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
TokKwRef: 'ref' ;

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

TokKwDollarUnsigned: '$unsigned' ;
TokKwDollarSigned: '$signed' ;
TokKwDollarIsUnsigned: '$is_unsigned' ;
TokKwDollarIsSigned: '$is_signed' ;
TokKwDollarRange: '$range' ;
TokKwDollarRevrange: '$revrange' ;
TokKwDollarSize: '$size' ;
TokKwDollarResize: '$resize' ;
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
