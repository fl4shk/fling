" Vim syntax file
" Language: Fling
" Maintainer: Andrew Clark (FL4SHK)
" Latest Revision: Jan 3, 2020

if exists("b:current_syntax")
    finish
endif

let b:current_syntax = "fling"


syn match fling_line_comment "//.*$" 

syn region  fling_literal_string     start=+L\="+ skip=+\\\\\|\\"+ end=+"+ contains=fling_special_char,@Spell extend

syn match   fling_char  "L\='[^\\]'"
syn match   fling_char  "L'[^']*'" contains=fling_special
syn match   fling_special_error   "L\='\\[^'\"?\\abfnrtv]'"
syn match   fling_special_char "L\='\\['\"?\\abfnrtv]'"
syn match   fling_special_char display "L\='\\\o\{1,3}'"
syn match   fling_special_char display "'\\x\x\{1,2}'"
syn match   fling_special_char display "L'\\x\x\+'"
syn match   fling_special    display contained "\\\(x\x\+\|\o\{1,3}\|.\|$\)"
syn match   fling_special    display contained "\\\(u\x\{4}\|U\x\{8}\)"

"syn region fling_attribute start=+#\[+ end=+\]+
"syn region fling_attribute start=+L\=#\[+ end=+\]#+


syn match fling_lit_float_num "\(\([0-9][0-9_]*\.\(\[0-9][0-9_]*\)\?\|\.[0-9][0-9_]*\)\([eE][+-]\?[0-9][0-9_]*\)\?\([fdlFDL]\?\)\?\)"

syn match fling_lit_dec_num "\<\([0-9][0-9_]*\)\>"


"syn match fling_frag_float_frac "\(\zs?\.\zs\)\|\(\zs\)" contains=fling_lit_dec_num,fling_lit_dec_num,fling_lit_dec_num
"syn match fling_frag_float_exp_part "[eE][+-]?\zs" contains=fling_lit_dec_num
"syn match fling_frag_float_suffix "[fdlFDL]"
"syn match fling_lit_float_num "\(\zs\zs?\zs?\)\|\(\zs\zs\zs?\)" contains=fling_frag_float_frac,fling_frag_float_exp_part,fling_frag_float_suffix,fling_lit_dec_num,fling_frag_float_exp_part,fling_frag_float_suffix
"syn match fling_lit_float_num +\\zs?\.\\zs+ contains=fling_lit_dec_num,fling_lit_dec_num
"syn match fling_lit_float_num +\zs+ contains=fling_lit_dec_num


syn match fling_lit_hex_num "\<\(0x[0-9a-fA-F][0-9a-fA-F_]*\)\>"
syn match fling_lit_oct_num "\<\(0o[0-7][0-7_]*\)\>"
syn match fling_lit_bin_num "\<\(0b[0-1][0-1_]*\)\>"

"--------
syn keyword fling_non_type_name_keyword toident fromident
"--------

"--------
syn keyword fling_non_type_name_keyword cond else mux
syn keyword fling_non_type_name_keyword match default
syn keyword fling_non_type_name_keyword for while
syn keyword fling_non_type_name_keyword break continue label scope
syn keyword fling_non_type_name_keyword try catch
"--------

"--------
syn keyword fling_non_type_name_keyword class base mixin extends
syn keyword fling_non_type_name_keyword dyn abstract
syn keyword fling_non_type_name_keyword pub prot priv
syn keyword fling_non_type_name_keyword self
syn keyword fling_type_name_keyword self_t
syn keyword fling_builtin_member_func init
syn keyword fling_non_type_name_keyword initlist
syn keyword fling_builtin_member_func dest
"--------

"--------
syn keyword fling_non_type_name_keyword trait requires
"--------

"--------
syn keyword fling_non_type_name_keyword tuple variant enum union
"--------

"--------
syn keyword fling_non_type_name_keyword new delete
"--------

"--------
syn keyword fling_non_type_name_keyword using namespace library work
"syn keyword fling_non_type_name_keyword
"--------


"--------
syn keyword fling_non_type_name_keyword static const volatile
"--------

"--------
syn keyword fling_non_type_name_keyword static_assert
"--------

"--------
syn keyword fling_non_type_name_keyword func lambda captures return
syn keyword fling_type_name_keyword ret_t
"--------

"--------
syn keyword fling_non_type_name_keyword spec attr
"--------

"--------
syn keyword fling_non_type_name_keyword gen geneval
"--------

"--------
syn keyword fling_non_type_name_keyword var
"--------

"--------
syn keyword fling_non_type_name_keyword move
"--------

"--------
syn keyword fling_null_literal null
syn keyword fling_type_name_keyword null_t
"--------


"--------
syn keyword fling_non_type_name_keyword pack unpack
"--------

"--------
syn keyword fling_non_type_name_keyword type typeof instof
"--------

"--------
syn keyword fling_type_name_keyword toktree
"--------

"--------
syn keyword fling_type_name_keyword ctlist ctmap ctset

syn keyword fling_type_name_keyword u8 i8 u16 i16 u32 i32 u64 i64 u128 i128
syn keyword fling_type_name_keyword string
syn keyword fling_type_name_keyword float double longdouble

syn keyword fling_type_name_keyword bool
syn keyword fling_bool_literal true false

syn keyword fling_type_name_keyword void auto any range

syn keyword fling_type_name_keyword result option

syn keyword fling_type_name_keyword file thread

syn keyword fling_type_name_keyword allocator_t
"--------

"--------
syn keyword fling_non_type_name_keyword cast as reinterpret implicit
"--------


"--------
hi def link fling_line_comment Comment
hi def link fling_literal_string Number

hi def link fling_lit_dec_num Number
hi def link fling_lit_float_num Number
hi def link fling_lit_hex_num Number
hi def link fling_lit_oct_num Number
hi def link fling_lit_bin_num Number

hi def link fling_attribute Number

hi def link fling_builtin_member_func Function

hi def link fling_non_type_name_keyword Statement
hi def link fling_type_name_keyword Type

hi def link fling_null_literal Number
hi def link fling_bool_literal Number
"--------
