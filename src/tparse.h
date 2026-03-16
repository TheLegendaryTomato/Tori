// Tori parser

#include "tarray.h"

#ifndef TPARSE_H
#define TPARSE_H

// Creates an abstract syntax tree based off of a `TArray` returned by the lexer.
TArray tparse_parse(TArray tokens);

#endif