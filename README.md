# Fling
Fling is a set of three custom computer languages all related to an
identical base language.

The main language of the three is a programming language intended to
resemble, in language features, my own take on what C++ could be without
being stuck with C source compatibility and support for legacy syntax.
Fling will also be a much smaller language if one considers that C++
without the standard library is a subset of "real" C++.  Fling's standard
library is considered to be a library like any other, so all pieces of it
are to be written in Fling itself.  It is intended to be so small a library
that whatever pieces of it get used simply get compiled into the final
binary.

The two other languages are a hardware description language (HDL) and a
build script system intended to prevent the need of ever using a makefile
with this language.

All three languages can use a nearly complete subset of the main language
at compile-time for code inspection, code generation, building a ROM for
your CPU implemented in the HDL, converting video game assets into your
video game's native format at build time, etc.
