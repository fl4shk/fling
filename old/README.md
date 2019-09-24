# Frost HDL Compiler
This is my compiler for a custom HDL, intended to solve some tool support
problems I've run into with SystemVerilog, especially among FLOSS software.

It will serve as a way to get access to higher level language features in
tools that only support Verilog (and not SystemVerilog).

In addition to solving the tool support problems I've run into, the
language is intended to be comparable to synthesizeable SystemVerilog,
perhaps even surpassing it in some ways.

## Code Generation
Code generation is currently being limited to Verilog-2001, and this is
considered the lowest common denominator of any possible language targets.

All language constructs must map into Verilog-2001 that "resembles" the
original source code (perhaps even putting the original comments into the
generated source code?).

There are (or will be, once they're implemented) some language features
that have been limited by using Verilog-2001 code as the target language of
the compiler.

The run-time semantics of this language piggy back off of the Verilog-2001
language implemention, but because it was deemed necessary for expressions
to work the same at compile time as they do at run-time, compile time
expression evaluation that is compatible with Verilog-2001 was developed.

Code generation that outputs VHDL is not considered necessary at this time,
but it may eventually come, perhaps with some caveats.


## Language Features
Yosys-compatible SystemVerilog assertions will be directly supported for
formal verification.  This is a "must have" feature.

Since this isn't a compiler for an existing HDL, there is freedom in
what the language features will be.  As such, object oriented programming
is being included in the language.

Support for Verilog's `x` and `z` constructs will be limited, except
perhaps for some very specific things, which are primarily `casez` and
tri-state buffers.  (Note that those listed features do not include `x`,
though.)

In general, a number of things have been simplified compared to
Verilog-2001.  Anything I consider not useful (or that has some other,
possibly better way to be done) for FPGA development is fair game to not be
supported in this language.

## Miscellaneous
Tabs are 4 spaces, and lines are at most 75 characters long.
