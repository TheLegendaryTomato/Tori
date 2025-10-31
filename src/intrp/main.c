/*
 * Tori interpreter entry point
 * 2025 Aethari
 */

/*
	General project todo:
	TODO: Rewrite .h files to be more like `stack.h`
	TODO: Rewrite stuff so that it isn't limited to 65 characters
	TODO: Create file src/README.md to explain project folders
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "syntax-no-main.tab.h"

#include "eval.h"

#define MAX_STRING_LEN 4096
#define VERSION "Unnumbered alpha version"

// == Variables ================================================
extern FILE *yyin;
char filename[MAX_STRING_LEN] = "";

// == Functions ================================================
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
			switch(arg[1]) {
				case 'h':
					printf("Usage: tori [OPTIONS] [filename]\n");
					printf("Interpreter for the Tori programming language\n\n");

					printf("Options:\n");
					printf("\t-v\tDisplay the version number and exit\n");
					printf("\t-h\tDisplay this help menu and exit\n");
					exit(1);
				case 'v':
					printf("%s\n", VERSION);
					exit(1);
				default:
					printf("Unrecognized option '-%c'\n", arg[1]);
					printf("Use `tori -h` for more info\n");
					exit(1);
			}
		}
	}
}

int main(int argc, char *argv[]) {
	if(argc > 1) {
		parse_args(argc, argv);
	}

	if(strcmp(filename, "") == 0) {
		printf("Error: No input file was found. See `tori -h` for more information.\n");
		return 1;
	}

	// parse the file, then run the interpreter
	FILE *f = fopen(filename, "r");

	if(f == NULL) {
		printf("Error: Could not open file '%s':\n\t", filename);
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
	
	return 0;
}
