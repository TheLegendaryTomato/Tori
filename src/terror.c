// Handles various errors throughout program execution
// See terror.h for documentation

/* This file does not have **every** error the program can through, just
 * those that are commonly thrown from multiple locations. for example,
 * multiple different headers may run into malloc fails, but the string
 * header may have errors specific to the header that would not crop up in
 * other files.
 */

#include <stdio.h>
#include <stdlib.h>

#include "terror.h"

void terror_throw(TErrorType type) {
	switch(type) {
		case TERRORTYPE_FILE_OPEN_FAIL:
			printf("Error: Could not open file\n");
			exit(1);
		case TERRORTYPE_ALLOC_FAIL:
			printf("Error: Memory allocation failed\n");
			exit(1);
		case TERRORTYPE_OUT_OF_BOUNDS:
			printf("Error: Attempt to access an index that is out-of-bounds\n");
			exit(1);
		case TERRORTYPE_INVALID_LITERAL:
			printf("Error: Invalid literal located. If you are a normal user and you are reading this, please report it to the developers immediately.\n");
			exit(1);
	}
}