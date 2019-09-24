" Vim syntax file
" Language:  Frost HDL
" Maintainer:  FL4SHK
" Latest Revision:  

if exists("b:current_syntax")
	finish
endif

let b:current_syntax = "frost_hdl"

syn case match

syn match frost_comment		"//.*"

syn keyword frost_keyword		type typeof
syn keyword frost_keyword		class self union enum using
syn keyword frost_keyword		init dest
syn keyword frost_keyword		pub prot priv ext
syn keyword frost_keyword		func return
syn keyword frost_keyword		nomut
syn keyword frost_keyword		virtual static const 
syn keyword frost_keyword		ref null
syn keyword frost_keyword		package import all as
syn keyword frost_keyword		if else switch case default 
syn keyword frost_keyword		with
syn keyword frost_keyword		for while do
syn keyword frost_keyword		assert
syn keyword frost_keyword		ast
syn keyword frost_keyword		print stdout stderr stdin file input output

syn keyword frost_builtin_type		int bool float str void auto range
syn keyword frost_bool		true false

syn match frost_integer		"\<[0-9]\+\>"
syn match frost_integer		"\<0x[a-fA-F0-9]\+\>"
syn match frost_integer		"\<0b[01]\+\>"
syn match frost_integer		"\<0o[0-7]\+\>"

"syn match frost_string		"\"[^"]*\""
syn match frost_string		"\"\([\\][\"] | [^\"]\)*\""

hi def link frost_comment		Comment
hi def link frost_keyword		Statement
hi def link frost_bool			Constant
hi def link frost_integer		Number
hi def link frost_builtin_type		Type
hi def link frost_string		Constant
"hi frost_uppercase_ident	ctermfg=Green guifg=Green
