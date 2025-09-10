/*
 * Interpreter error types and utility functions
 * See error.h for documentation
 * 2025 Aethari
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"

#define STR_MAX_LEN 4096

char *eval_err_to_string(ErrorType err) {
	char *out = malloc(STR_MAX_LEN);
	if(out == NULL) {
		printf("Error: Memory allocation failed\n");
		exit(1);
	}

	switch(err) {
		case ERR_SUCCESS:
			strcpy(out, "program executed successfully");
			break;
		case ERR_FAILURE:
			strcpy(out, "program failed during execution");
			break;
		case ERR_INVALID_NODE_TYPE:
			strcpy(out, "invalid node type");
			break;
		case ERR_DUPLICATE_PROGRAM:
			strcpy(out, "found a non-root 'program' node");
			break;
		default:
			char *buff = malloc(STR_MAX_LEN);
			strcpy(buff, "unrecognized error code '%d'");
			sprintf(out, buff, err);
			free(buff);
			break;
	}

	return out;
}

