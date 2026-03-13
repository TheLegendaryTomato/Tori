// Tori lexer
// See `src/tlex.h` for documentation

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "tarray.h"
#include "terror.h"
#include "tstring.h"
#include "tpath.h"
#include "tlex.h"

const char *keywords[] = {
	"var"
};

const char *whitespace[] = {
	" ",
	"\t",
	"\n"
};

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

const char *delimiters[] = {
	";",
	","
};

const char *invalid[] = {
	"@",
	"#",
	"$",
	"^",
	"&",
	"\\"
};

// Retrives the best `TTokenType` for string `s`.
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
	TString current_word = string_new("", 0);
	int line = 1;
	for(int i = 0; i < file_len; i++) {
		char current = buff[i];

		// the main issue right now is that this doesn't split at
		// tab characters or delimiters
		// we also need a way to check for comments
		if(current != ' ' && current != '\n') {
			current_word = string_append(current_word, current);
		} else {
			// check if the character is invalid
			char *str = string_get(current_word);
			size_t len = sizeof(invalid) / sizeof(invalid[0]);
			for(int i = 0; i < strlen(str); i++) {
				for(int j = 0; j < len; j++) {
					if(str[i] == invalid[j][0]) {
						printf("Error: Invalid character found on line %d\n", line);
						exit(1);
					}
				}
			}

			TTokenType token_type = GetTokenType(current_word);

			printf("current word: ");
			string_println(current_word);

			string_free(current_word);

			// reset the current word
			current_word = string_new("", 0);
		}

		// advance the line tracker
		if(current == '\n') line++;
	}

	string_free(current_word);

	free(path);
	free(buff);

	fclose(file);

	return out;
}