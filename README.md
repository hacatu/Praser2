#Praser 2

This is the second incarnation of the Praser parser library.  The first iteration function,
but due to its parser combinator paradigm it was ill suited to being coded in C.  This
version is purely based on parser description files (*.pra) that use a BNF like syntax.
There are three examples provided right now: `src/parser.pra` is the description of the
description language, `src/calculator.pra` is a description for a subset of mathematical
notation, and `src/set.pra` is a description for a simplified charset notation (it is
basically useless but good for testing the parsers based on `src/parser.pra`).  The goal
of this library is to provide a basis for the creation of a parser for a programming
language.

This distribution contains a script, `parser_runner.sh`, that runs various parsers and
callbacks.  The implementation of this script is described later.  Once the library has
been built, it can be run like:

	./parser_runner.sh <parser> <action> <file to parse> [<action arguments>]

Where `<parser>` is the name of the parser to use (by default, `parser` and `generated`
are built and they should have the same behavior) and `<action>` is what to do with the
abstract syntax tree (ast) the parser returns (currently there are `print` to print,
`interpret <file to interpret>` to parse a file by interpreting the ast returned by the
parser description parser, and `compile <output file>` to generate a C source file for
a parser described in `<file to parse>`).  `src/modules/generated_parser.c` is generated
by running `./parser_runner.sh parser compile src/parser.pra src/modules/generated_parser.c`.

`parser_runner.sh` works by dynamically linking a glue program (`src/parser_runner.c`) with
different shared libraries.  The glue program has two functions, `start_parser` and
`ast_callback`, that are provided by stub libraries that report them as missing when they are
called.  The shell script sets `LS_PRELOAD` to load different shared libraries and change
`start_parser` and `ast_callback`.  Unfortunately this only works on Linux, but the library
itself should be cross platform so on other platforms it should be easy to just build
executables for every combination of parser and callback.  I may add that to the tupfile, but
it is not currently a priority.

#Building

Praser 2 uses tup as its build system, but should not have any other dependencies (besides
the avl tree and slab allocator libraries included in this repository and not currently used).
To build Praser on Linux, simply run `tup`.  The demonstration cannot currently be built on
OSX or Windows, and because I'm using dynamic linking it probably won't be soon.  Basically any
solution to having multiple parsers and multiple callbacks that does not build a separate program
for every combination is not cross platform and hence would require multiple implementations.

