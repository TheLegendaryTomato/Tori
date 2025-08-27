%{
#include <stdio.h>

int yylex(void);
void yyerror(const char *s);
%}

// Bison declarations

%token FUNC PARAM RET ENDFUNC CALL
%token VAR TYPE IDENTIFIER
%token INT FLOAT BOOL CHAR
%token IF ELSE ELIF ENDIF COMPARE
%token FOR WHILE ENDLOOP
%token INCLUDE COMMENT

%%

// Grammar rules

program
	: statements
	;

statements
	: statements statement
	| /* empty */
	;

statement
	: var_decl
	| func_decl
	| if_stmt
	;

value
	: INT
	| FLOAT
	| BOOL
	| CHAR
	| IDENTIFIER
	;

var_decl
	: VAR IDENTIFIER ':' TYPE ';'
	;

func_decl
	: FUNC IDENTIFIER ':' TYPE ';'
	;

if_stmt
	: IF value COMPARE value ';'
	;

%%

// Helper functions, main functions (in C)

void yyerror(const char *s) {
	fprintf(stderr, "Parse error: %s\n", s);
}
