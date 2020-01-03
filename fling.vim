" Vim syntax file
" Language: Fling
" Maintainer: Andrew Clark (FL4SHK)
" Latest Revision: November 25, 2019

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
syn region fling_attribute start=+L\=#\[+ end=+\]#+


syn match fling_dec_num "\<\([0-9][0-9_]*\)\>"
"syn match fling_frag_float_frac "\(\zs?\.\zs\)\|\(\zs\)" contains=fling_dec_num,fling_dec_num,fling_dec_num
"syn match fling_frag_float_exp_part "[eE][+-]?\zs" contains=fling_dec_num
"syn match fling_frag_float_suffix "[fdlFDL]"
"syn match fling_float_num "\(\zs\zs?\zs?\)\|\(\zs\zs\zs?\)" contains=fling_frag_float_frac,fling_frag_float_exp_part,fling_frag_float_suffix,fling_dec_num,fling_frag_float_exp_part,fling_frag_float_suffix
"syn match fling_float_num +\\zs?\.\\zs+ contains=fling_dec_num,fling_dec_num
"syn match fling_float_num +\zs+ contains=fling_dec_num
syn match fling_hex_num "\<\(0x[0-9a-fA-F][0-9a-fA-F_]*\)\>"
syn match fling_oct_num "\<\(0o[0-7][0-7_]*\)\>"
syn match fling_bin_num "\<\(0b[0-1][0-1_]*\)\>"


syn keyword fling_non_type_name_keyword cond if elif else
syn keyword fling_non_type_name_keyword with
syn keyword fling_non_type_name_keyword match case default
syn keyword fling_non_type_name_keyword for while dowhile scope

syn keyword fling_non_type_name_keyword class base extends dyn init_list
syn keyword fling_non_type_name_keyword pub prot priv
syn keyword fling_non_type_name_keyword self
syn keyword fling_type_name_keyword self_t

syn keyword fling_non_type_name_keyword variant enum union aux_list

syn keyword fling_non_type_name_keyword except try catch

syn keyword fling_non_type_name_keyword static const volatile extern

syn keyword fling_non_type_name_keyword spec
syn keyword fling_non_type_name_keyword type typeof

syn keyword fling_non_type_name_keyword var
syn keyword fling_non_type_name_keyword func
syn keyword fling_type_name_keyword ret_t

syn keyword fling_non_type_name_keyword gen macro mcall local ident
syn keyword fling_type_name_keyword tokstrm
syn keyword fling_non_type_name_keyword tokstrmof

syn keyword fling_type_name_keyword ctlist ctmap ctset

syn keyword fling_non_type_name_keyword namespace library

syn keyword fling_non_type_name_keyword using

syn keyword fling_builtin_member_func init dest


syn keyword fling_type_name_keyword u8 i8 u16 i16 u32 i32 u64 i64 u128 i128
syn keyword fling_type_name_keyword uintptr_t intptr_t ptrdiff_t size_t 
syn keyword fling_type_name_keyword cmp_t
syn keyword fling_type_name_keyword string char
syn keyword fling_type_name_keyword float double longdouble
"syn keyword fling_type_name_keyword fpenv simd

syn keyword fling_type_name_keyword bool
syn keyword fling_bool_literal true false

syn keyword fling_type_name_keyword void auto any range

syn keyword fling_type_name_keyword c_uchar c_schar c_ushortint c_shortint
syn keyword fling_type_name_keyword c_uint c_int c_ulongint c_longint
syn keyword fling_type_name_keyword c_ulonglongint c_longlongint

syn keyword fling_type_name_keyword result option


hi def link fling_line_comment Comment
hi def link fling_literal_string Number

hi def link fling_dec_num Number
hi def link fling_float_num Number
hi def link fling_hex_num Number
hi def link fling_oct_num Number
hi def link fling_bin_num Number

hi def link fling_attribute Number

hi def link fling_builtin_member_func Function

hi def link fling_non_type_name_keyword Statement
hi def link fling_type_name_keyword Type

hi def link fling_bool_literal Number


"hi def link fling_line_comment Comment
"hi def link fling_literal_string Number
"
"hi def link fling_dec_num Number
"hi def link fling_float_num Number
"hi def link fling_hex_num Number
"hi def link fling_oct_num Number
"hi def link fling_bin_num Number
"
"hi def link fling_ctrl_flow Statement
"hi def link fling_metaprog Statement
"hi def link fling_func Statement
"hi def link fling_builtin_type Type
"
"hi def link fling_extra_keywords Statement
"
"hi def link fling_hdl_func Statement
"hi def link fling_hdl Statement
"hi def link fling_hdl_dollar SpecialChar
"
"hi def link fling_type_support Statement
"
"hi def link fling_library_namespace Statement
"hi def link fling_build_main SpecialChar
"hi def link fling_build_c_interop SpecialChar
"hi def link fling_c_interop Statement
"
"hi def link fling_cstm_type Statement
"hi def link fling_cstm_type_self Statement
"hi def link fling_cstm_type_self_t Type
"hi def link fling_builtin_member_func Function
"
"hi def link fling_cstm_type_access_spec Statement
"
"hi def link fling_exception Statement
"hi def link fling_move Statement
"
"hi def link fling_allocator_t Type
"hi def link fling_new_delete Statement
"
"hi def link fling_null Number
"hi def link fling_null_t Type
"
"hi def link fling_decl_specifier Statement
"
"hi def link fling_static_assert Statement
"
"hi def link fling_bool_value Number
"hi def link fling_sizeof Statement
"
"hi def link fling_c_interop_builtin_type Type
"
"hi def link fling_file_builtin_type Type
"hi def link fling_console_file Statement
"
"hi def link fling_thread_builtin_type Type
"
"
"hi def link fling_attribute Number
"
"hi def link fling_cast_pseudo_func Function
"hi def link fling_cast_as Statement
"hi def link fling_cast_implicit Statement
"
"hi def link fling_attr_keyword Statement
