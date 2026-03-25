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
				// variable declarations have no values for the variables, so there is nothing to do. later, we will add the variable to the stack, but we can't do that now.

				TAstVarDefNode *var = (TAstVarDefNode *)node;
				string_free(var->identifier);

				free(n);
			} else if(node->node_type == TASTNODETYPE_VAR_INIT) {
				TAstVarDefNode *var = (TAstVarDefNode *)node;
				
				if(!var->null) {
					switch(var->var_type) {
						case TVARTYPE_INT:
							printf("int variable \"");
							string_print(var->identifier);
							printf("\" found: %d\n", var->value.i);

							string_free(var->identifier);
							break;
						case TVARTYPE_FLOAT:
							printf("float variable \"");
							string_print(var->identifier);
							printf("\" found: %f\n", var->value.f);

							string_free(var->identifier);
							break;
						case TVARTYPE_BOOL:
							printf("boolean variable \"");
							string_print(var->identifier);
							printf("\" found: %s\n", var->value.b ? "true" : "false");

							string_free(var->identifier);
							break;
						case TVARTYPE_STRING:
							char *out = string_get(var->value.s);
						
							printf("string variable \"");
							string_print(var->identifier);
							printf("\" found: %s\n", out);
		
							string_free(var->identifier);
							string_free(var->value.s);
							free(out);
							break;
					}
				}

				free(var);
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