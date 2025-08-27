%{
#include "syntax.tab.h"
#include "syntax-no-main.tab.h"
%}

IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*
COMPARE "=="|"<="|">="|"!="

FLOAT [0-9]+\.[0-9]+
INT [0-9]+

%%

^:[^\n]* ; /* ignore comments */

"func"    return FUNC;
"param"   return PARAM;
"ret"     return RET;
"endfunc" return ENDFUNC;
"call"    return CALL;
"var"     return VAR;
"if"      return IF;
"else"    return ELSE;
"elif"    return ELIF;
"endif"   return ENDIF;
"for"     return FOR;
"while"   return WHILE;
"endloop" return ENDLOOP;
"include" return INCLUDE;

"int"   return TYPE;
"float" return TYPE;
"bool"  return TYPE;
"char"  return TYPE;

"true"       return BOOL;
"false"      return BOOL;
{FLOAT}      return FLOAT;
{INT}        return INT;
{IDENTIFIER} return IDENTIFIER;
{COMPARE}    return COMPARE;

":" return ':';
";" return ';';
"," return ',';

[ \t\r\n]+ ;
.          ;

%%
