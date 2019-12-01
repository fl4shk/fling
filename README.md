# Fling
Fling is a custom programming language for which a compiler is being
developed.  The compiler itself is just called `fling`.

The language is largely an enhancement over my own understanding of C++,
with much of the langauge having identical, equivalent, or similar enough
features compared to what exists in C++.

One key difference between this language and C++ is how error handling is
done.  Error handling is done similar to how it is done in Rust (`Result`
in Rust-speak).

The main enhancements over the way I write and understand C++ myself are in
the compile-time language support.  Nearly the entire language is available
at compile-time.  Macros similar to what you might find in a competent
assembler exist in this language.  They take arguments in the same way that
functions do (including templates), but such arguments are used entirely
for code generation.  Compile-time reflection, generally intended to be
used with code generation, is also supported (with a limitation of not
being able to look at functions other than their arguments).

The standard library is to be very small (such that what parts of it get
used are just compiled into the final binary), and it is to be implemented
entirely in the language itself with no compiler magic.

Libraries in general are a feature that is an explicit part of the
language.

Lastly, the language has C interop as a key feature, which allows the
programmer to use C libraries.  C interop is done by way of generating C
code.
