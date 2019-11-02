# Frost
Frost is a custom programming language for which a compiler is being
developed.  The compiler itself is just called `frost`.

Limitations of C++ are what really drove the creation of this project.

For example, in C++  I have sometimes found myself in need of compile-time
reflection.  I have often, in C++, found myself in need of some simple
compile-time code generation, for which I had used the C preprocessor.  The
ability to combine compile-time reflection with compile-time code
generation is a primary goal of this language.

C++ does have some compile-time code execution via `constexpr`, but I view
`constexpr` as supporting too little of the C++ language.  In comparison,
Frost does not place very many limits on what can be done with compile-time
code execution.   Almost every language feature is available at
compile-time, and some language features are *only* available at
compile-time.

Many language features of modern, idiomatic C++ are being brought into this
language nearly as-is (at with least my understanding of the as-is), but
with different syntax or perhaps some enhancements in some cases, with very
few cuts from the core language features that have no equivalent features.

The language will be object-oriented, generic, procedural, structural,
reflective, generative, and with type inference.  It will be a systems
programming language.

The main philosophy of the language is to allow the programmer to leverage
the compiler to do the programmer's dirty work, including examining (to an
extent) the source code of one section of the program in another section of
the program.

C interop is a must-have feature for the language, and C code generation is
actually what the first version of the compiler will produce.  Once the
first version of the compiler (to be written in C++) is finished, the
compiler will be re-implemented in its own language.  Long term, the
compiler will be provided as both C source code and Frost source code.  By
providing the compiler as C source code, bootstrapping the compiler will
only need to be done once by me, and I can leave future bootstrapping to
people making C compilers.

