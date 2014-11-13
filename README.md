EagleCompiler
=============

###Abstract
The EagleCompiler is a platform independent IML compiler written in C++, which generates native executables.

###How it works
`[IML] ----- (transpiled) ------> [Assembler] ---- (compiled) -----> [machine-code/binary]`

The compiler parses the IML source code and generates an Abstract Syntax Tree (AST). 
The AST is then used to emit assembler source code, which is then being compiled to native machine code.

