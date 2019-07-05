" Vim syntax file
" Language:  Frost HDL
" Maintainer:  FL4SHK
" Latest Revision:  

if exists("b:current_syntax")
	finish
endif

let b:current_syntax = "ast_gen"

syn case match

syn match ast_gen_comment		"//.*"

syn keyword ast_gen_keyword		child var

hi def link ast_gen_comment		Comment
hi def link ast_gen_keyword		Statement
