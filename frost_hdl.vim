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

"syn keyword frost_hdl_keyword		wire logic unsigned signed
syn keyword frost_hdl_keyword		const type
syn keyword frost_hdl_keyword		typeof
"syn keyword frost_hdl_keyword		struct
syn keyword frost_hdl_keyword		class self union enum using
syn keyword frost_hdl_keyword		public protected private extends
syn keyword frost_hdl_keyword		packed
syn keyword frost_hdl_keyword		func task proc port return
syn keyword frost_hdl_keyword		virtual static
syn keyword frost_hdl_keyword		package module inst
syn keyword frost_hdl_keyword		input output bidir
syn keyword frost_hdl_keyword		if else switch switchz case default 
syn keyword frost_hdl_keyword		for while do range
syn keyword frost_hdl_keyword		assign initial
syn keyword frost_hdl_keyword		always_comb always_blk always_ff
syn keyword frost_hdl_keyword		assert assume cover
syn keyword frost_hdl_keyword		static_assert
syn keyword frost_hdl_keyword		posedge negedge
syn keyword frost_hdl_keyword		generate genvar var
syn keyword frost_hdl_keyword		cat repl


syn keyword frost_hdl_builtin_type		uwire swire ubit sbit
syn keyword frost_hdl_builtin_type		ubyte sbyte ushortint sshortint
syn keyword frost_hdl_builtin_type		uint sint ulongint slongint
syn keyword frost_hdl_builtin_type		void auto


"syn match frost_hdl_dollar_func		"\$[a-zA-Z_0-9]\+"
"syn match frost_hdl_dollar_func		"\$concat"
"syn match frost_hdl_dollar_func		"\$repl"


syn match frost_hdl_dollar_func		"\$unsgn"
syn match frost_hdl_dollar_func		"\$sgn"
syn match frost_hdl_dollar_func		"\$is_unsgn"
syn match frost_hdl_dollar_func		"\$is_sgn"
syn match frost_hdl_dollar_func		"\$range"
syn match frost_hdl_dollar_func		"\$size"
syn match frost_hdl_dollar_func		"\$msbpos"
syn match frost_hdl_dollar_func		"\$low"
syn match frost_hdl_dollar_func		"\$high"
syn match frost_hdl_dollar_func		"\$first"
syn match frost_hdl_dollar_func		"\$last"
syn match frost_hdl_dollar_func		"\$clog2"
syn match frost_hdl_dollar_func		"\$pow"

syn match frost_hdl_number		"\<[0-9]\+\>"
syn match frost_hdl_number		"\<0x[a-fA-F0-9]\+\>"
syn match frost_hdl_number		"\<0b[01]\+\>"
syn match frost_hdl_number		"\<0o[0-7]\+\>"

syn match frost_hdl_string		"\"[^"]*\""

syn match frost_hdl_uppercase_ident		"\<[A-Z_][A-Z_0-9]\+\>"

hi def link frost_hdl_comment		Comment
hi def link frost_hdl_keyword		Statement
hi def link frost_hdl_dollar_func		SpecialComment
hi def link frost_hdl_number		Number
hi def link frost_hdl_uppercase_ident		Constant
hi def link frost_hdl_builtin_type		Type
hi def link frost_hdl_string		Constant
"hi frost_hdl_uppercase_ident	ctermfg=Green guifg=Green
