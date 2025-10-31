/*
 * Interpreter memory management
 * See stack.h for documentation
 * 2025 Aethari
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"

// == Local variables ==========================================
/// A struct representing a single value on the stack.
typedef struct {
	/// The type of the `StackValue`
	enum StackValueType type;

	/// The name / key of the `StackValue`
	char *name;

	/// The actual value of the `StackValue`
	char *value;
} StackValue;

StackValue **stack = NULL;
int stacklen = 0;

// == Local Functions ==========================================

/// Creates a new `StackValue` object and returns it.
///
/// Parameters:
/// - type: A `StackValueType` enumeration that will fill the `StackValue.type` field
/// - name: A string that will fill the `StackValue.name` field
/// - value: A string that will fill the `StackValue.value` field
///
/// Returns:
/// A `StackValue` object filled with the parameters passed to the function
StackValue stack_value_new(enum StackValueType type, char *name, char *value) {
	StackValue out = {};
	out.type = type;
	strcpy(out.name, name);
	strcpy(out.value, value);
	
	return out;
}

/// Initializes the stack if it is not already initialized
///
/// Returns:
/// 0 if the stack was already set up, 1 if it was
int stack_init() {
	if(stack == NULL) {
		stack = malloc((stacklen * 1) * sizeof(StackValue*));
		stacklen = 1;
		if(stack == NULL) {
			printf("Error: memory allocation failed\n");
			exit(1);
		}

		return 0;
	}

	return 1;
}

/// Increases the length of the stack
///
/// Parameters:
/// - i: How many empty entries to add to the stack; how much to increase the
///   length
void stack_append(int i) {
	StackValue **tmp = NULL;
	tmp = realloc(stack, (stacklen + i) * sizeof(StackValue*));
	if(tmp == NULL) {
		printf("Error: memory reallocation failed\n");
		exit(1);
	}
	
	stack = tmp;
	stacklen += i;
}

// == Functions ================================================
int stack_push_null() {
	stack_append(1);
	StackValue out = stack_value_new(SVT_NULL, "Null", "NULL");
	stack[stacklen-1] = &out;
	return 0;
}

int stack_push_function() {
	stack_append(1);
	return 0;
}

int stack_push_var() {
	stack_append(1);
	return 0;
}

int stack_push_integer(int i) {
	stack_append(1);
	return 0;
}

int stack_push_bool(int i) {
	stack_append(1);
	return 0;
}

int stack_push_char(char c) {
	stack_append(1);
	return 0;
}

int stack_pop(int index) {
	return 0;
}

int stack_check_null(int index) {
	if(index > stacklen) {
		printf("Error: index %d out of stack bounds\n", index);
		exit(1);
	}

	if(stack[index] != NULL && stack[index]->type != SVT_NULL) {
		return 1;
	}

	return 0;
}

void stack_check_function(int index) {
	if(index > stacklen) {
		printf("Error: index %d out of stack bounds\n", index);
		exit(1);
	}
}

void stack_check_var(int index) {
	if(index > stacklen) {
		printf("Error: index %d out of stack bounds\n", index);
		exit(1);
	}
}

int stack_check_integer(int index) {
	if(index > stacklen) {
		printf("Error: index %d out of stack bounds\n", index);
		exit(1);
	}

	return 0;
}

int stack_check_bool(int index) {
	if(index > stacklen) {
		printf("Error: index %d out of stack bounds\n", index);
		exit(1);
	}

	return 0;
}

char stack_check_char(int index) {
	if(index > stacklen) {
		printf("Error: index %d out of stack bounds\n", index);
		exit(1);
	}

	return '0';
}
