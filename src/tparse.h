// Tori parser

#include "tarray.h"

#ifndef TPARSE_H
#define TPARSE_H

// Creates an abstract syntax tree based off of a `TArray` returned by the lexer. Each node in the `TArray` will need to be manually freed using the `free()` function defined in `stdlib.h`.
TArray tparse_parse(TArray tokens);

#endif