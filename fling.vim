" Vim syntax file
" Language: Fling
" Maintainer: Andrew Clark (FL4SHK)
" Latest Revision: November 25, 2019

if exists("b:current_syntax")
    finish
endif

let b:current_syntax = "fling"

syn keyword 

syn match fling_line_comment "\v//.*$" 

syn match fling_basic_escape_sequence "\\['"?abfnrtv\\]"
syn match fling_hex_escape_sequence "\\x[A-Fa-f0-9_]+"
syn match fling_basic_char "~["\\]"

syn region fling_string_literal start='"' end='"' contains=fling_basic_escape_sequence,fling_hex_escape_sequence,fling_basic_char


syn match fling_dec_num "[0-9][0-9_]*"
syn match fling_frag_float_frac "\(\zs?\.\zs\)\|\(\zs\)" contains=fling_dec_num,fling_dec_num,fling_dec_num
syn match fling_frag_float_exp_part "[eE][+-]?\zs" contains=fling_dec_num
syn match fling_frag_float_suffix "[fdlFDL]"
syn match fling_float_num "\(\zs\zs?\zs?\)\|\(\zs\zs\zs?\)" contains=fling_frag_float_frac,fling_frag_float_exp_part,fling_frag_float_suffix,fling_dec_num,fling_frag_float_exp_part,fling_frag_float_suffix
syn match fling_hex_num "0x[0-9a-fA-F][0-9a-fA-F_]*"
syn match fling_oct_num "0o[0-7][0-7_]*"
syn match fling_bin_num "0b[0-1][0-1_]*"


syn keyword fling_ctrl_flow if else match default with for in while do
syn keyword fling_ctrl_flow continue break

syn keyword fling_metaprog gen macro define tokstrm cat fromident

syn keyword fling_func func return ret_t

syn keyword fling_hdl_func task proc

syn keyword fling_hdl module input output bidir hi_imped
syn keyword fling_hdl initial always_comb always_blk always_ff
syn keyword fling_hdl_dollar $display $monitor $finish

syn keyword fling_type_support type instof

syn keyword fling_library_namespace library work extern namespace using

syn keyword fling_build_main $library $shell $path $extern $flag $var

syn keyword fling_build_c_interop $c_library $c_header

syn keyword fling_c_interop c_extern cpp_define


syn keyword fling_builtin_type bool ubit sbit ulogic slogic wire
syn keyword fling_bool_value true false

syn keyword fling_builtin_type u8 i8 u16 i16 u32 i32 u64 i64 u128 i128
syn keyword fling_builtin_type uintptr_t intptr_t ptrdiff_t size_t cmp_t
syn keyword fling_builtin_type string char
syn keyword fling_builtin_type float double longdouble
syn keyword fling_builtin_type fpenv simd
syn keyword fling_builtin_type void auto range

