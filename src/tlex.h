// Tori lexer

#include "tarray.h"
#include "tstring.h"

#ifndef TLEX_H
#define TLEX_H

// Defines all possible types for lexer tokens.
typedef enum {
	// Words reserved by Tori (if, call, int, etc.).
	TTOKENTYPE_KEYWORD,
	
	// Spaces, tabs, and newlines.
	TTOKENTYPE_WHITESPACE,

	// Mathematical or assignment operators (=, +, etc.).
	TTOKENTYPE_OPERATOR,

	// Essentially operators that aren't used for math (:, ;, ,, etc.).
	TTOKENTYPE_DELIMITER,

	// Numbers, bools, strings (1, 2.4, true, "example").
	TTOKENTYPE_LITERAL,

	// User-defined words (variable / function names).
	TTOKENTYPE_IDENTIFIER,

	// Used when a character or word is not part of any other token type.
	TTOKENTYPE_INVALID
} TTokenType;

// A struct that holds data for a single lexer token.
typedef struct {
	TTokenType type;
	TString value;
	int line;
	int col;
} TToken;

// Tokenizes input file `p`, turning it into a `TArray` of tokens.
TArray tlex_lex(TString p);

#endif