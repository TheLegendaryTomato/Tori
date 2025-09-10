/*
 * Tori interpreter entry point
 * 2025 Aethari
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "syntax-no-main.tab.h"

#include "ast.h"
#include "eval.h"

#define MAX_STRING_LEN 4096

// == Variables ================================================
extern FILE *yyin;
char filename[MAX_STRING_LEN] = "";

// == Functions ================================================
// We need to decide whether or not we want more command line
// parameters than just the input file

void parse_args(int argc, char *args[]) {
	for(int i = 1; i < argc; i++) {
		int is_option = 0;

		char arg[MAX_STRING_LEN];
		strcpy(arg, args[i]);

		if(arg[0] == '-') {
			is_option = 1;
		} else {
			strcpy(filename, arg);
		}

		if(is_option == 1) {
		}
	}
}

int main(int argc, char *argv[]) {
	if(argc > 1) {
		parse_args(argc, argv);
	}

	if(strcmp(filename, "") == 0) {
		printf("Error (main.c): No input file was found. See `tori -h` for more information.\n");
		return 1;
	}

	// parse the file, then run the interpreter
	FILE *f = fopen(filename, "r");

	if(f == NULL) {
		printf("Error (main.c): Could not open file '%s':\n\t", filename);
		perror("");
		return 1;
	}

	yyin = f;
	int res = yyparse();
	fclose(f);

	// 1 is an error message, I forget what it is though
	if(res == 1) {
		return 1;
	} else if(res == 2) {
		printf("Parse error: inadequate memory\n");
		return 1;
	}

	printf("HELLO WORLD! Testing includes\n");
}
