#### List of keywords / built in functionality / instructions
- `func`
- `param` - read function parameters
- `ret` - return
- `endfunc`
- `var`
if true;
	write, "true";
endif;
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
- `include` - to include other `.tori` files
- `true`
- `false`
- `::` - signifies comments
- `:* *:` - block comment

#### Notes
- For variable reassignments, we could either do `<var> = <value>;` or use a `set`
  instruction: `set <var>, <value>;`. The `set` instruction is closer to assembly
  and feels more consistent to the language, but it is harder to read, and much less
  convenient in general.
- Looking back at the example code, I realize that `<var> = <var>++;` kind of
  defeats the entire purpose of an increment operator. I wonder if we should keep
  the increment and decrement operators? `+=`, `-=`, and other such operators are
  staying regardless...
- We might want to change the `param` instruction to something diferent, so that
  it is not as redunant (which would also make it easier to read).

#### Example code
```tori
:: include library files
include stdio.tori;

:: declaring variable
var x, 10;

:: if statement
if x == 10;
	write, "x is ten";
elif x == 11;
	write, "x is eleven";
else;
	write, "x is not ten or eleven";
endif;

:: declaring function
func add : int;
	var x : int;
	var y : int;

	:: Parameters are read in the order which they were sent in the `call` instruction
	param x, y;

	ret x+y;
endfunc;

:*
For the moment, this is how you get values returned from a function. I personally
don't want the syntax of `var x : int = call add, 1, 2;`, so we have this instead.
How it works is that the `ret` instruction simply sets the value of the variable
passed in as the last parameter to whatever came after it. So here, the value of
`o` (the last parameter) is set to `x+y`, which is what `add` returns. The
unfortunate part about this is that it requires the user to create a new variable
*before* calling the function, which can feel awkward and excessive.
*:
var o : int;
add, 1, 2, o;
write, o;

func print : int, char str[];
	var str[] : char;
	param str;

	write, str;
endfunc;

:: loops
var tbl[] : int;
var i : int = 0;
for i < 10;
	var out[] : char;
	itostr, i, out;
	write, out;

	:: variables need manually incremented
	i = i++;
endloop;

i = 0;
while i != 11;
	var out[] : char;
	itostr, i, out;
	write, out;

	i = i++;
endloop;
```
