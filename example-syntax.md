#### List of keywords / built in functionality / instructions
- `func`
- `param` - read function parameters
- `ret` - return
- `endfunc`
- `call`
- `var`
- `if`
- `else`
- `elif`
- `endif`
- `for`
- `while`
- `endloop`
- `int`
- `float`
- `bool`
- `char`
- `include` - to include other language files
- `true`
- `false`
- `:` - signifies comments
- `:* *:` - block comment?

#### Notes
- For variable reassignments, we could either do `<var> = <value>;` or use a `set`
  instruction: `set <var>, <value>;`
- We might want to make it so that you don't need the call operator to call
  functions: `<func> <param1>, <param2>, <return>;`. This would allow users to write
  their own "instructions" and allow the standard libraries to be made easier. This
  would drastically increase readability when using included functions or libraries,
  becuase you don't need the `call` instruction **literally everywhere**. For the
  example, it does not do this (at leat for now).
	- Using this method allows us to do "C-type" stdlib design, as opposed to other
	  languages where stuff like printing is built-in

#### Example code
```tori
: include library files
include stdio.tori;

: declaring variable
var x, 10;

: if statement
if x == 10;
	call write, "x is ten";
elif x == 11;
	call write, "x is eleven";
else;
	call write, "x is not ten or eleven"
endif;

: declaring function
func add : int;
	var x : int;
	var y : int;
	: Parameters are read in the order which they were sent in the `call` instruction
	param x, y;

	ret x+y;
endfunc;

: For the moment, this is how you get values returned from a function. I personally
: don't want the syntax of `var x : int = call add, 1, 2;`, so we have this instead.
: How it works is that the `ret` instruction simply sets the value of the variable
: passed in as the last parameter to whatever came after it. So here, the value of
: `o` (the last parameter) is set to `x+y`, which is what `add` returns.
var o : int;
call add, 1, 2, o;
call write, o;

func print : int, char str[];
	var str[] : char;
	param str;

	call write, str;
endfunc;

: loops
var tbl[] : int;
var i : int = 0;
for i < 10;
	var out[] : char;
	call itostr, i, out;
	call write, out;

	: variables need manually incremented
	i = i++;
endloop;

i = 0;
while i != 11;	var out[] : char;
	call itostr, i, out;
	call write, out;

	i = i++;
endloop;
```
