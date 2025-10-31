/*
 * Interpreter memory management
 * 2025 Aethari
 */

// TODO: Document StackValueType fields
// TODO: Document `stack` functions
// TODO: Create a struct to store variables and functions on the stack
// TODO: Create paramters for `stack_push_function` and `stack_push_var`
// TODO: Create return type for `stack_check_function` and `stack_check_var`
// TODO: Rewrite `stack_get` to an individual function for each `StackValueType`

#ifndef STACK_H
#define STACK_H

/// The type of a StackValue.
enum StackValueType {
	SVT_NULL,
	
	SVT_FUNCTION,
	SVT_VAR,

	SVT_INTEGER,
	SVT_FLOAT,
	SVT_BOOL,
	SVT_CHAR
};

// returns the index of the pushed value, -1 if failure
int stack_push_null();
int stack_push_function();     // this pushes a tori function - accept an AST node?
int stack_push_var();          // see stack_push_function
int stack_push_integer(int i);
int stack_push_bool(int b);    // 0 for true, non-zero for false
int stack_push_char(char c);

// returns a success code, 0 if success, -1 if failure
int stack_insert_null(int index);
int stack_insert_function(int index);       // see stack_push_function
int stack_insert_var(int index);            // see stack_push_function
int stack_insert_integer(int i, int index);
int stack_insert_bool(int b, int index);
int stack_insert_char(char c, int index);

// returns the index of the popped value, -1 if failure
int stack_pop(int index);

// checks if the value is the correct type, and returns it if it is
int stack_check_null(int index);      // this returns a boolean - true if the value IS null
void stack_check_function(int index);
void stack_check_var(int index);
int stack_check_integer(int index);
int stack_check_bool(int index);      // returns 0 for false, 1 for true
char stack_check_char(int index);

#endif
