// Tori program entry point

#include <string.h>

#include "tstring.h"
#include "tarray.h"
#include "tast.h"

#include "tlex.h"
#include "tparse.h"

int main(int argc, char *argv[]) {
	// IMPROVMENT: put documentation for the core "loop" here?
	if(argc > 1) {
		TString path = string_new(argv[1], strlen(argv[1]));
		TArray tokens = tlex_lex(path);
		TArray ast = tparse_parse(tokens);

		// this loop will probably form the interpreter later
		for(int i = 0; i < tarray_len(ast); i++) {
			void *n = tarray_get(ast, i);
			TAstBaseNode *node = (TAstBaseNode *)n;

			if(node->node_type == TASTNODETYPE_VAR_DECL) {
				TAstVarDefNode *var = (TAstVarDefNode *)node;

				if(!var->value.null && var->var_type == TVARTYPE_STRING) {
					char *out = string_get(var->value.s);
					printf("string variable found: %s\n", out);

					string_free(var->value.s);
					free(out);
				}
			} else if(node->node_type == TASTNODETYPE_VAR_INIT) {
				TAstVarDefNode *var = (TAstVarDefNode *)node;
				
				if(!var->value.null && var->var_type == TVARTYPE_STRING) {
					char *out = string_get(var->value.s);
					printf("string variable found: %s\n", out);

					string_free(var->value.s);
					free(out);
				}
			}
		}
	
		string_free(path);
		tarray_free(tokens);
		tarray_free(ast);
	} else {
		printf("Error: No input file was found\n");
	}


	return 0;
}