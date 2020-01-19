# Fling
This is an in progress programming language (and compiler) inspired by C++,
Rust, Python, LISP, Verilog, VHDL, and SystemVerilog with object-oriented
programming, a small amount of functional programming, compile-time code
execution with built-in code generation facilities inspired especially by
the common HDL `generate` keyword, and an AST-inspecting and modifying
macro system ala Rust or LISP.

The intended domain of the language is anything one might have used C++ or
Rust for.  This is a different take on what C++ could be, but development
in the language is likely to feel more like C++ than Rust once you get past
the differences in syntax.

Although the language is primarily going to be a compiled, statically-typed
language without garbage collection, an interpreter for the language is to
be available as well.  Actually, an interpreter for some version of the
language is needed as part of the compilation process because of the
compile-time code execution and generation system within the language.

Instead of garbage collection, the language is, like in C++ or Rust, built
upon the RAII (Resource Acquisition Is Initialization) idiom.  As such,
Fling includes destructors.
