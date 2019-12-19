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


syn keyword fling_ctrl_flow if else match default with for in while do
syn keyword fling_ctrl_flow continue break provide

syn keyword fling_metaprog gen local macro define tokstrm cat fromident

syn keyword fling_func func closure
syn keyword fling_builtin_type ret_t

syn keyword fling_hdl_func task proc

syn keyword fling_hdl module input output bidir hi_imped
syn keyword fling_hdl initial always_comb always_blk always_ff delay
syn keyword fling_hdl_dollar $display $monitor $finish

syn keyword fling_type_support type typeof instof

syn keyword fling_library_namespace library work namespace using

syn keyword fling_build_main $library $shell $path $extern $flag $var

syn keyword fling_build_c_interop $c_library $c_header

syn keyword fling_c_interop c_extern cpp_define



syn keyword fling_cstm_type enum union variant class mixin extends 
syn keyword fling_cstm_type base friend dyn
syn keyword fling_cstm_type_self self
syn keyword fling_cstm_type_self_t self_t
syn keyword fling_builtin_member_func init dest 

syn keyword fling_cstm_type_access_spec pub priv prot

syn keyword fling_cstm_type trait requires

syn keyword fling_exception try catch
syn keyword fling_move move
syn keyword fling_allocator_t allocator_t
syn keyword fling_new_delete new delete

syn keyword fling_null null 
syn keyword fling_null_t null_t

syn keyword fling_decl_specifier volatile const restrict static
syn keyword fling_decl_specifier thread_local extern 

syn keyword fling_static_assert static_assert


syn keyword fling_builtin_type bool ubit ibit ulogic ilogic wire
syn keyword fling_bool_value true false

syn keyword fling_builtin_type u8 i8 u16 i16 u32 i32 u64 i64 u128 i128
syn keyword fling_builtin_type uintptr_t intptr_t ptrdiff_t size_t cmp_t
syn keyword fling_builtin_type string char ident
syn keyword fling_builtin_type float double longdouble
"syn keyword fling_builtin_type fpenv simd
syn keyword fling_builtin_type void auto range array

syn keyword fling_sizeof sizeof

syn keyword fling_c_interop_builtin_type c_uchar c_schar
syn keyword fling_c_interop_builtin_type c_ushortint c_shortint
syn keyword fling_c_interop_builtin_type c_uint c_int
syn keyword fling_c_interop_builtin_type c_ulongint c_longint
syn keyword fling_c_interop_builtin_type c_ulonglongint c_longlongint

syn keyword fling_builtin_type result option

"syn keyword fling_file_builtin_type file
"syn keyword fling_console_file stdin stdout stderr
"
"syn keyword fling_thread_builtin_type atomic atomic_ref thread mutex
"syn keyword fling_thread_builtin_type thrd_call_once thrd_once_flag
"syn keyword fling_thread_builtin_type thrd_cond tss


syn keyword fling_cast_pseudo_func cast reinterpret
syn keyword fling_cast_as as
syn keyword fling_cast_implicit implicit
syn keyword fling_attr_keyword attr


hi def link fling_line_comment Comment
hi def link fling_literal_string Number

hi def link fling_dec_num Number
hi def link fling_float_num Number
hi def link fling_hex_num Number
hi def link fling_oct_num Number
hi def link fling_bin_num Number

hi def link fling_ctrl_flow Statement
hi def link fling_metaprog Statement
hi def link fling_func Statement
hi def link fling_builtin_type Type

hi def link fling_hdl_func Statement
hi def link fling_hdl Statement
hi def link fling_hdl_dollar SpecialChar

hi def link fling_type_support Statement

hi def link fling_library_namespace Statement
hi def link fling_build_main SpecialChar
hi def link fling_build_c_interop SpecialChar
hi def link fling_c_interop Statement

hi def link fling_cstm_type Statement
hi def link fling_cstm_type_self Statement
hi def link fling_cstm_type_self_t Type
hi def link fling_builtin_member_func Function

hi def link fling_cstm_type_access_spec Statement

hi def link fling_exception Statement
hi def link fling_move Statement

hi def link fling_allocator_t Type
hi def link fling_new_delete Statement

hi def link fling_null Number
hi def link fling_null_t Type

hi def link fling_decl_specifier Statement

hi def link fling_static_assert Statement

hi def link fling_bool_value Number
hi def link fling_sizeof Statement

hi def link fling_c_interop_builtin_type Type

hi def link fling_file_builtin_type Type
hi def link fling_console_file Statement

hi def link fling_thread_builtin_type Type


hi def link fling_attribute Number

hi def link fling_cast_pseudo_func Function
hi def link fling_cast_as Statement
hi def link fling_cast_implicit Statement

hi def link fling_attr_keyword Statement
