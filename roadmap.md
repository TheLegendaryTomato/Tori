# Tori roadmap
#### 1
- design Tori syntax / features
- create a BNF file (tori.y) for Bison to use
- setup a build system to generate the Bison output

#### 2
- take the Bison output / modify the build process to make an AST of some kind
- create a basic C interpreter structure - make sure to organize the projects so that
  there are basically two "modules" or programs in the project - the Bison parser and
  the interpereter that reads Bison's output
- the interpreter is the `tori` command - it just wraps Tori calls into C calls

#### 3
- begin work on a parallel program - `gate`
- gate compiles Tori code into executables
- this is NOT the interpreter, but it does use the AST like the interpreter does
