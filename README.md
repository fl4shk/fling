# Frost HDL Compiler
This is my compiler for a custom HDL, intended to solve some tool support
problems I've run into with SystemVerilog, especially among FLOSS software.
(It is not intended to be a compiler for SystemVerilog itself)

In addition to solving the tool support problems I've run into, the
language is intended as well to be higher level than synthesizeable
SystemVerilog.

Support for yosys-compatible SystemVerilog assertions will be directly
supported.

Code generation is currently being limited to Verilog-2001, but support for
outputing SystemVerilog may also come.

Code generation that outputs VHDL is unlikely, but may eventually come
(perhaps with some caveats).


Support for Verilog's `x` and `z` constructs will be limited, except
perhaps for some very specific things, such as `casez` and tri-state
buffers.
