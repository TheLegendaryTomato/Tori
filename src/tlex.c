// Tori lexer
// See `src/tlex.h` for documentation

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "tarray.h"
#include "terror.h"
#include "tstring.h"
#include "tpath.h"
#include "tlex.h"

// Every keyword in Tori.
const char *keywords[] = {
	"var",
	"int"
};

// Common whitespace characters.
const char *whitespace[] = {
	" ",
	"\t",
	"\n",
	"\r"
};

// Mathematical operators.
const char *operators[] = {
	"=",
	"+",
	"-",
	"*",
	"/",
	"+=",
	"-=",
	"*=",
	"/=",
	"++",
	"--",
	"==",
	"!=",
	"<=",
	">=",
	">",
	"<",
};

// Tori reserved symbols. Any characters that are not alphanumeric or part of this list will be considered invalid, and terminate program execution.
const char *delimiters[] = {
	":",
	";",
	","
};

// Characters that will terminate the program if found in the input stream.
const char *invalid[] = {
	"@",
	"#",
	"$",
	"^",
	"&",
	"%",
	"\\"
};

// Checks if a character is a whitespace character.
bool IsWhitespace(char c) {
	for(int i = 0; i < sizeof(whitespace) / sizeof(whitespace[0]); i++) {
		if(c == *whitespace[i]) return true;
	}

	return false;
}

// Checks if a character is a delimiter.
bool IsDelim(char c) {
	for(int i = 0; i < sizeof(delimiters) / sizeof(delimiters[0]); i++) {
		if(c == *delimiters[i]) return true;
	}

	return false;
}

// Checks if a character is an invalid character.
bool IsInvalid(char c) {
	for(int i = 0; i < sizeof(invalid) / sizeof(invalid[0]); i++) {
		if(c == *invalid[i]) return true;
	}

	return false;
}

// Retrives the best `TTokenType` value for string `s`.
TTokenType GetTokenType(TString s) {
	char *str = string_get(s);

	// check for keyword
	size_t len = sizeof(keywords) / sizeof(keywords[0]);
	for(size_t i = 0; i < len; i++) {
		if(strcmp(keywords[i], str) == 0) {
			free(str);
			return TTOKENTYPE_KEYWORD;
		}
	}

	// check for whitespace
	len = sizeof(whitespace) / sizeof(whitespace[0]);
	for(size_t i = 0; i < len; i++) {
		if(strcmp(whitespace[i], str) == 0) {
			free(str);
			return TTOKENTYPE_WHITESPACE;
		}
	}

	// check for operator
	len = sizeof(operators) / sizeof(operators[0]);
	for(size_t i = 0; i < len; i++) {
		if(strcmp(operators[i], str) == 0) {
			free(str);
			return TTOKENTYPE_OPERATOR;
		}
	}

	// check for delimiter
	len = sizeof(delimiters) / sizeof(delimiters[0]);
	for(size_t i = 0; i < len; i++) {
		if(strcmp(delimiters[i], str) == 0) {
			free(str);
			return TTOKENTYPE_DELIMITER;
		}
	}

	// check for literal
	// TODO: we need a way to check for string literals
	if(
		strcmp(str, "true") == 0 ||
		strcmp(str, "false") == 0 ||
		string_is_int(s) ||
		string_is_float(s)
	) {
		free(str);
		return TTOKENTYPE_LITERAL;
	}

	// check for identifier
	if(isalpha(str[0]) || str[0] == '_') {
		free(str);
		return TTOKENTYPE_IDENTIFIER;
	}

	// it doesn't match any of the other TTokenTypes, so it must be invalid
	// this kind of token **should** throw an error, but I would rather leave it up to the parser than do it here
	free(str);
	return TTOKENTYPE_INVALID;
}

// Creates a `TToken` based on several input values. The value returned by this function needs to be freed by the caller.
TToken *CreateToken(TString str, int line, int col) {
	TToken *token = malloc(sizeof(TToken));

	if(!token) {
		terror_throw(TERRORTYPE_ALLOC_FAIL);
	}

	TTokenType token_type = GetTokenType(str);

	token->type = token_type;
	token->value = string_dup(str);
	token->line = line;
	token->col = col;

	return token;
}

// Creates a `TToken` representing a delimiter, whose value is determined by `c`. The value returned by the function needs to be freed by the caller.
TToken *CreateDelimToken(char c, int line, int col) {
	TToken *token = malloc(sizeof(TToken));

	if(!token) {
		terror_throw(TERRORTYPE_ALLOC_FAIL);
	}

	token->type = TTOKENTYPE_DELIMITER;
	token->value = string_append(string_new("", 0), c);
	token->line = line;
	token->col = col;

	return token;
}

TArray tlex_lex(TString p) {
	// convert p to a full path and actual C string
	TString realpath = tpath_real(p);
	char *path = string_get(realpath);
	string_free(realpath);

	FILE *file = fopen(path, "rb");

	if(!file) {
		terror_throw(TERRORTYPE_FILE_OPEN_FAIL);
	}

	// get the file size
	fseek(file, 0, SEEK_END);
	size_t file_len = ftell(file);
	// move back to beginning of the file
	rewind(file);

	// create a string that contains the file's contents
	char *buff = malloc(file_len + 1);

	if(!buff) {
		terror_throw(TERRORTYPE_ALLOC_FAIL);
	}
	
	fread(buff, 1, file_len, file);
	buff[file_len] = '\0';

	// the array that tokens will be wrote to
	TArray out = tarray_new(1);

	// TODO: rewrite the following process as an actual, well-written documentation comment
	/*
	 * steps to follow:
	 * 1) create an empty string to build upon
	 * 2) read the current character
	 *    2.5) check if the character is invalid
	 * 3.1) if the character is whitespace, create a token from the built string
	 * 3.2) if the character is a delimiter, create a token from the built string, then create and insert a second token with the delimiter character
	 * 4) if the character is not a stopping point, add it to the built string (this creates a "word" in between stopping points, such as "int" or "var")

	 * token building:
	 * 1) identify the type of the token
	 * 2) use the built string as the value of the token
	 * 3) identify the line the token is on
	 * 4) construct the token
	 * 5) add the newly constructed token to the array
	*/

	// lex through the string here
	TString current_word = string_new("", 0);
	int line = 1, col = 1;
	bool is_comment = false;
	bool is_block_comment = false;
	// loops through all of the characters in the file
	for(int i = 0; i < file_len; i++) {
		char current = buff[i];

		// set states when a comment is detected
		// TODO: implement errors for unfinished block comments
		if(current == ':') {
			if(buff[i+1] == '*') {
				is_block_comment = true;
			} else if(buff[i-1] == '*') {
				is_block_comment = false;
				
				// skip the current character
				// without this, the final ":" would be tokenized
				col++;
				i++;
				continue;
			} else if(buff[i+1] == ':') {
				is_comment = true;
			}
		}

		if(!is_comment && !is_block_comment) {
			bool is_whitespace = false;
			bool is_delim = false;

			// check if the character is invalid
			if(IsInvalid(current)) {
				printf("Error: Invalid character \'%c\' found on line %d, column %d\n", current, line, col);
				exit(1);
			}

			// check if the character is whitespace
			if(IsWhitespace(current)) is_whitespace = true;

			// check if the character is a delimiter
			if(IsDelim(current)) is_delim = true;

			TToken *token;

			if(is_whitespace) {
				// only create the token if the string is not empty (avoids whitespace tokens)
				if(string_len(current_word) > 0) {
					// create a `TToken` based off of the current word
					token = CreateToken(current_word, line, col - string_len(current_word));
					// add the token to the out array
					tarray_append(&out, token);
				}

				// free the old word
				string_free(current_word);
				// reset current_word
				current_word = string_new("", 0);
			} else if(is_delim) {
				// this implementation is the same as whitespace, with the addition of the delimiter tokem

				if(string_len(current_word) > 0) {
					token = CreateToken(current_word, line, col - string_len(current_word));
					tarray_append(&out, token);
				}

				// create the delimiter token
				TToken *delim = CreateDelimToken(current, line, col);
				// add the delimiter to the out array
				tarray_append(&out, delim);

				string_free(current_word);
				current_word = string_new("", 0);
			} else {
				// continue to build the currrent word
				current_word = string_append(current_word, current);
			}
		}

		// advance the column tracker
		col++;

		// advance the line tracker
		if(current == '\n') {
			col = 1;
			is_comment = false;
			line++;
		}
	}

	// free the final word, as it gets recreated at the end of the if statement
	string_free(current_word);

	free(path);
	free(buff);

	fclose(file);

	return out;
}