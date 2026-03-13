// Tori lexer
// See `src/tlex.h` for documentation

#include <stdio.h>
#include <string.h>

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

// Retrives the best `TTokenType` for string `s`.
TTokenType GetTokenType(TString s) {
	char *str = string_get(s);

	// check for keyword
	size_t len = sizeof(keywords) / sizeof(keywords[0]);
	for(int i = 0; i < len; i++) {
		if(strcmp(keywords[i], str) == 0) {
			free(str);
			return TTOKENTYPE_KEYWORD;
		}
	}

	// check for whitespace
	len = sizeof(whitespace) / sizeof(whitespace[0]);
	for(int i = 0; i < len; i++) {
		if(strcmp(whitespace[i], str) == 0) {
			free(str);
			return TTOKENTYPE_WHITESPACE;
		}
	}

	// check for operator
	len = sizeof(operators) / sizeof(operators[0]);
	for(int i = 0; i < len; i++) {
		if(strcmp(operators[i], str) == 0) {
			free(str);
			return TTOKENTYPE_OPERATOR;
		}
	}

	// check for delimiter
	len = sizeof(delimiters) / sizeof(delimiters[0]);
	for(int i = 0; i < len; i++) {
		if(strcmp(delimiters[i], str) == 0) {
			free(str);
			return TTOKENTYPE_DELIMITER;
		}
	}

	// check for literal

	// check for identifier

	// it doesn't match any of the other TTokenTypes, so it must be invalid
	free(str);
	return TTOKENTYPE_INVALID;
}

TArray tlex_lex(TString p) {
	// convert p to a realpath and actual C string
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

	TArray out = tarray_new(1);

	// lex through the string here
	TString current_word = string_new("", 0);
	for(int i = 0; i < file_len; i++) {
		char current = buff[i];

		// the only issue right now is that this doesn't split at
		// tab characters or delimiters
		if(current != ' ' && current != '\n') {
			current_word = string_append(current_word, current);
		} else {
			TTokenType token_type = GetTokenType(current_word);
			printf("current word: ");
			string_println(current_word);
			current_word = string_new("", 0);
		}

	}

	string_free(current_word);

	free(path);
	free(buff);

	fclose(file);

	return out;
}