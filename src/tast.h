// Definitions for structs and enums required by the parser / AST

#ifndef TAST_H
#define TAST_H

typedef enum {
	// A variable declaration that does gives the variable's type, but not the value.
	TASTNODETYPE_VAR_DECL,

	// Basically a TASTNODETYPE_VAR_DECL, but instead of giving the type, the user gives the value, and the parser infers the type.
	TASTNODETYPE_VAR_INIT,

	// Just an int literal
	TASTNODETYPE_INT_LITERAL,
	// Just a float literal
	TASTNODETYPE_FLOAT_LITERAL,
	// Just a boolean literal
	TASTNODETYPE_BOOL_LITERAL,
	// Just a string literal
	TASTNODETYPE_STRING_LITERAL
} TAstNodeType;

#endif