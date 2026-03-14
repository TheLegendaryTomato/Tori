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
	"\n"
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
	"--"
};

// Tori reserved symbols. Any characters that are not alphanumeric or part of this list
// will be considered invalid, and terminate program execution.
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
	"\\"
};

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
	// TODO: we need a way to do check for string literals
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
	free(str);
	return TTOKENTYPE_INVALID;
}

TArray tlex_lex(TString p) {
	// convert p to a full path and actual C string
	TString realpath = tpath_real(p);
	char *path = string_get(realpath);
	string_free(realpath);

	printf("path: %s\n", path);
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

	// lex through the string here

	/*
	 * steps to follow:
	 * 1) create an empty string to build upon
	 * 2) read the current character
	 *    2.5) check if the character is invalid
	 * 3.1) if the character is whitespace, create a token from the built string
	 * 3.2) if the character is a delimiter, create a token from the built string, then
	 *      create and insert a second token with the delimiter character
	 * 4) if the character is not a stopping point, add it to the built string (this
	 *    creates a "word" in between stopping points, such as "int" or "var")
	 *
	 * token building:
	 * 1) identify the type of the token
	 * 2) use the built string as the value of the token
	 * 3) identify the line the token is on
	 * 4) construct the token
	 * 5) add the newly constructed token to the array
	*/

	TString current_word = string_new("", 0);
	int line = 1;
	for(int i = 0; i < file_len; i++) {
		char current = buff[i];

		bool is_delim = false;

		for(int j = 0; j < sizeof(delimiters) / sizeof(delimiters[0]); j++) {
			if(current == *delimiters[j]) {
				is_delim = true;
				break;
			}
		}

		// the main issue right now is that this doesn't split at delimiters
		// we also need a way to check for comments
		if(current != ' ' && current != '\t' && current != '\n' && !is_delim) {	
			current_word = string_append(current_word, current);
		} else {
			// check if the character is invalid
			char *str = string_get(current_word);
			size_t len = sizeof(invalid) / sizeof(invalid[0]);
			for(int j = 0; j < strlen(str); j++) {
				for(int k = 0; k < len; k++) {
					if(str[j] == invalid[k][0]) {
						printf("Error: Invalid character found on line %d\n", line);
						exit(1);
					}
				}
			}
			free(str);

			// get the token type of the word that is currently being processed
			TTokenType token_type = GetTokenType(current_word);

			// create the token
			TToken *token = malloc(sizeof(TToken));

			if(!token) {
				terror_throw(TERRORTYPE_ALLOC_FAIL);
			}

			// delimiters need special handling, as the case where we check for them
			// does not set the delimiter to `current_word`
			if(is_delim) {
				token->type = TTOKENTYPE_DELIMITER;
				token->value = string_append(string_new("", 0), current);
			} else {
				token->type = token_type;
				token->value = string_dup(current_word);
			}

			token->line = line;

			// add the token to the array
			tarray_append(&out, token);

			// DEBUG: print the word to stdout
			printf("current word: ");
			string_println(current_word);

			string_free(current_word);

			// reset the current word
			current_word = string_new("", 0);
		}

		// advance the line tracker
		if(current == '\n') line++;
	}

	// free the final word, as it gets recreated at the end of the if statement
	string_free(current_word);

	free(path);
	free(buff);

	fclose(file);

	return out;
}