# Tori program design structure

All program files are contained in the "src" directory. Anything else is simply used for development, testing,
or documentation.

### Notes:
- we may need to define each of Tori's variable types in .h files later

`main.c` handles program entry, commandline parameters, and the program loop

## Program lib files
- `tstring.h` is a basic dynamic string library  
- `tarray.h` is a dynamic array struct that is used by the C backend, but **not** by Tori  
- `tlog.h` is a small logging library designed to assist in development (may get dropped)  
- `terror.h` handles errors that are thrown during Tori lexing / parsing, as well as runtime errors  

## Lexer
- `tlex.h` reads files, tokenizes them, then returns the tokens in a dynamic array  

## Parser
*Builds ast*  
- `tparse.h` goes through the tokens returned from `tlex.h` and turns them into an AST  

## AST
*Defines AST types / methods*  
- `tast.h` defines a dynamic array specifically designed to hold an AST  
- `tasttypes.h` defines structs for AST node types  

## Interpreter
*Runs the code*  
- `tinterp.h` uses the AST to run the Tori program

## Runtime
*Manages memory, used by interpreter*  
- `tstack.h` manages the variable / function stack  
*plan more later*  

# Tori standard library
*These files are not built by C, but rather handwritten and copied to the proper locations*  

- `stdio.tori` provides functions for reading and writing from standard input/output  
