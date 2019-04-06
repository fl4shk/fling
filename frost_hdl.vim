" Vim syntax file
" Language:  Frost HDL
" Maintainer:  FL4SHK
" Latest Revision:  

if exists("b:current_syntax")
	finish
endif

let b:current_syntax = "frost_hdl"

syn case match

syn match frost_hdl_comment		"//.*"

syn keyword frost_hdl_keyword		wire logic unsigned signed
syn keyword frost_hdl_keyword		parameter localparam 
syn keyword frost_hdl_keyword		struct class enum typedef 
syn keyword frost_hdl_keyword		function task 
syn keyword frost_hdl_keyword		package interface module 
syn keyword frost_hdl_keyword		input output inout 
syn keyword frost_hdl_keyword		if else switch case default 
syn keyword frost_hdl_keyword		for while do range
syn keyword frost_hdl_keyword		assign initial always_comb always_seq
syn keyword frost_hdl_keyword		generate
syn keyword frost_hdl_keyword		posedge negedge
syn keyword frost_hdl_keyword		instance
syn keyword frost_hdl_keyword		concat repl

"syn match frost_hdl_dollar_func		"\$[a-zA-Z_0-9]\+"
"syn match frost_hdl_dollar_func		"\$concat"
"syn match frost_hdl_dollar_func		"\$repl"
syn match frost_hdl_dollar_func		"\$unsgn"
syn match frost_hdl_dollar_func		"\$sgn"
syn match frost_hdl_dollar_func		"\$is_unsgn"
syn match frost_hdl_dollar_func		"\$is_sgn"
syn match frost_hdl_dollar_func		"\$sizeof"
syn match frost_hdl_dollar_func		"\$arrsize"
syn match frost_hdl_dollar_func		"\$lastindex"
syn match frost_hdl_dollar_func		"\$clog2"
syn match frost_hdl_dollar_func		"\$pow"

syn match frost_hdl_number		"\<[0-9]\+\>"
syn match frost_hdl_number		"\<0x[a-fA-F0-9]\+\>"
syn match frost_hdl_number		"\<0b[01]\+\>"

syn match frost_hdl_uppercase_ident		"\<[A-Z_][A-Z_0-9]\+\>"

hi def link frost_hdl_comment		Comment
hi def link frost_hdl_keyword		Statement
hi def link frost_hdl_dollar_func		SpecialComment
hi def link frost_hdl_number		Number
hi def link frost_hdl_uppercase_ident		Constant
"hi frost_hdl_uppercase_ident	ctermfg=Green guifg=Green
