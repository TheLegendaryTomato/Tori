// Tori lexer

#include "tarray.h"
#include "tstring.h"

#ifndef TLEX_H
#define TLEX_H

// Tokenizes an input file, turning it into a `TArray` of tokens.
TArray tlex_lex(TString p);

#endif