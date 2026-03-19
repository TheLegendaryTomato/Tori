// Tori program entry point

#include <string.h>

#include "tstring.h"
#include "tarray.h"

#include "tlex.h"
#include "tparse.h"

int main(int argc, char *argv[]) {
	// IMPROVMENT: put documentation for the core "loop" here?
	if(argc > 1) {
		TString path = string_new(argv[1], strlen(argv[1]));
		TArray tokens = tlex_lex(path);
		TArray ast = tparse_parse(tokens);
	
		string_free(path);
		tarray_free(tokens);
		tarray_free(ast);
	} else {
		printf("Error: No input file was found\n");
	}


	return 0;
}