# Chapter 1 - A Tutorial Introduction

**Goal: Show the elements of C in a real program**

## p.6) 1.1 Getting Started. hello.c:

```
#include <stdio.h>

int main()
{
        printf("hello, world\n");
        return 0;
}
```

Compile by running `cc hello.c`

### Explanation:

A C program consists of:
1. functions
  1. statements: specify the computing operations. There are [3])(http://farside.ph.utexas.edu/teaching/329/lectures/node11.html):
    1. expression statements. This is an expression followed by a semicolon. This causes the expression to be evaluated. An [expression]((http://www.c4learn.com/c-programming/c-expression/)) is:
      1. Any legal combination of characters that represent a value.
      2. Every expression consists of at least one operand and can have one or more operators(such as *addition operator* + or the *assignment operator* = ).
      3. Operands are values and Operators are symbols that represent particular actions.
    2. compound statements
    3. control statement (branching and looping)
2. variables store values during the computation

`main()` -> computation starts with executing this function.  

`#include <stdio.h>` -> tells the compiler to include information from the standard input/output library

Function *arguments* are used to communicate data between functions. Statements of a function are between '{}'. So the `printf("hello, world\n")` calls the function `printf` with a string of characters. 

A sequance of characters between double quotes is called:
1. string of text
2. string constant

`\n` -> escape sequance, in this case for newline. See section 2.3(p.38) for a complete list of escape sequances.

## p.8) 1.2 Variables and Arithmetic Expressions. temperatures.c:

```
#include <stdio.h>

/* print Fahrenheit-Celsius table for fahr = 0, 20 ..., 300 */

/* Formula for conversion: C = (5/9) * (F-32) */

int main()
{
        int fahr, celsius;
        int lower, upper, step;
    
        lower = 0;      /* lower limit of temperature table */
        upper = 300;    /* upper limit */
        step = 20;      /* step size */

        fahr = lower;
    
        while(fahr <= upper) {
                celsius = 5  * (fahr-32) / 9;
                printf("%d\t%d\n", fahr, celsius);
                fahr = fahr + step;
        }   

        return 0;

}
```

###Extra information:
1. [Integer division will result in the floor of the division.](http://stackoverflow.com/questions/3602827/what-is-the-behavior-of-integer-division-in-c) So (1/i) where i is an int > 1 will always result in 0. This explains way the formula for conversion celsius = 5  * (fahr-32) / 9 is written the way it is.
2. Once a variable is created as a certain type, it is locked to a certain type. So you can't reassign a float to a variable of an int type. You have to create a new variable.
3. If the 5 and the 9 were declared as floats before the division, the result would not be floored (or truncated) as stated in point 1. So the formula could also be written as celsius = (5.0/9.0)  * (fahr-32);

###Explanation

1. `/* */` and `//` -> comments
2. **Basic** variable types:
  1. char -> character - a single byte
  2. int -> range of ints depends on the machine, e.g. 16 bit lies between -32768 and + 32767
  2. short -> short integer
  3. long -> long integer
  4. float -> floating point, i.e. number which may have a fractional part. A float is typically 32-bit with at least six [significant digits](http://www.purplemath.com/modules/rounding2.htm). Magnitude somewhere between 10^-38 and 10^38
  5. double > double-precision floating point
3. **Other** variables types which consist of basic types:
  1. arrays
  2. structures
  3. unions
4. **Pointers** to basic types
5. **Functions** which return the types

A variable declaration exists of the type and the variable name:
```
int fahr, celsius;
int lower, upper, step;
```

Assignment statements which assigns a value to a variable:
```
lower = 0;
upper = 300;
step = 20; 
```

while-loop: the conditional is tested and if the true the statements of the loop are executed:
```
while(fahr <= upper) {
                //celsius = 5  * (fahr-32) / 9;
                celsius = (5.0/9.0)  * (fahr-32);
                //printf("%d\t%d\n", fahr, celsius);
		printf("%6d\t%6d\n", fahr, celsius);
                fahr = fahr + step;
        }
```
1. `printf(string, arguments...)` -> the string contains placeholders for the other arguments and the placeholder shows in what form it needs to be printed. So the %d and the argument must match by place and type. 
2. `printf("%d\t%d\n", fahr, celsius);` -> Right justify the numbers in the field

Integers get truncated to zero. So don't get the fractional part of the result. To get that:

```
#include <stdio.h>

/* print Fahrenheit-Celsius table for fahr = 0, 20 ..., 300 */

/* Formula for conversion: C = (5/9) * (F-32) */

int main()
{
        float fahr, celsius;
        int lower, upper, step;

        lower = 0;      /* lower limit of temperature table */
        upper = 300;    /* upper limit */
        step = 20;      /* step size */

        fahr = lower;

        while(fahr <= upper) {
                //celsius = 5  * (fahr-32) / 9;
                celsius = (5.0/9.0)  * (fahr-32.0);
                //printf("%f\t%f\n", fahr, celsius);
                printf("%3.0f\t%6.1f\n", fahr, celsius);
                fahr = fahr + step;
        }

        return 0;

}
```

Remember:

1. A decimal point in a constant (e.g. 5.0 and 9.0) indicate it is a float
2. If arithmetic operator has only integer operands -> result is an integer (possible truncated) (thats why `celsius = (5/9)  * (fahr-32);` doesn't work. The result `5/9` is <1 and gets truncated to 0)
3. If arithmetic operator has an integer and a floating point -> integer is converted to a float and the result is a float.
4. So even though the compiler convers an int to a float for you, for readibility it is better to make it a float explicitly
5. Formatting options for the placeholders of the first argument `printf()`:
  1. `%d` -> print as decimal integer
  2. `%6d` -> print as decimal integer at  least 6 characters wide
  3. `%f` -> print as floating point
  4. `%6f` -> print as floating point at least 6 characters wide
  5. `%.2f` -> print as floating point, 2 characters after decimal point
  6. `%6.2f` -> print as floating point, 6 characters wide, 2 characters after decimal point

## p.13)  1.3 The for statement

Genereal syntax:

```
for (init; conditionIfTrueIterate; increment) {
	bodyStatements
}
```

Example of the temperature program with for loop:

```
#include <stdio.h>

/* Print Fahrenheit-Celsius Table */

int main()
{
        int fahr;

        printf("Fahrentheit\tCelsius\n");

        for (fahr = 0; fahr <= 300; fahr = fahr + 20) {
                printf("%10d\t%7.1f\n", fahr, (5.0/9.0) * (fahr-32));
        }

        return 0;
}
```

General rule: In any context where it is permissible to use the value of a variable of some type, you can use a more complicated expression of that type. See the last argument of printf() for an exmaple: `printf("%10d\t%7.1f\n", fahr, (5.0/9.0) * (fahr-32));` () 

Note: an expression is a type of statement.

The for loop is a generalization of the while loop. Base your decision on whether to use a `for` or `while` loop on what seems clearer. The `for` loop is more appropiate (clearer) when the initialization and increment are single statements that are logically related, since it's more compact than while and it keeps all the control statements in one line.

## p.14) 1.4 Symbolic Constants

Symbolic constant: `#define name replacement`
Any occurence of *name* wil be replaced by *replacement*
Example: `#define LOWER 0`

Why use them? In our program, it's hard to understand what the numbers 0(lower limit), 300(uppet limit), and 20(step) actually do. Deal with these magic numbers by giving them a symbolic name via a symbolic constant.

The compiler changes the symbolic constant for the associated replacement. Therefor, it is a [preprocessor statement](http://www.cprogrammingexpert.com/C/Tutorial/fundamentals/symbolic_constant_c_programming_language.aspx). Preprocessor statements start with a `#` and the convention is to write preprocessor constants in UPPERCASE. A symbolic constant is not a variable, so there is no variable declaration, so there is no semicolin at the end of `#define` line.

Adaption of temperatures table with symbolic constants:

```
#include <stdio.h>

#define LOWER 0 /* lower limit of table */
#define UPPER 300 /* upper limit of table */
#define STEP 20 /* step size */

/* Print Fahrenheit-Celsius Table */
int main()
{
        int fahr;

        printf("Fahrentheit\tCelsius\n");

        for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP) {
                printf("%10d\t%7.1f\n", fahr, (5.0/9.0) * (fahr-32));
        }

        return 0;
}
```
## p.15) 1.5 Character Input and Output

The standard library deals with text input and output as a stream of characters. A *text stream* is a sequance of character divided into lines; each line consists of zero or more characters followd by a newline character.

1. `c = getchar()` -> read next input character.
2. `putchar(c)` -> prints a character each time it is called.

In C chars are unsigned integers. Unsigned [means](https://nl.wikipedia.org/wiki/Integer_(informatica)) it doesn't contain a + or -, thus it is positive. [Extra info](http://stackoverflow.com/questions/247873/signed-versus-unsigned-integers)

The integer corresponds with the [ASCII table](http://www.ascii-code.com/)

`getchar()` [returns an unsigned char converted to an int](http://stackoverflow.com/questions/7119470/int-c-getchar)

Lookup: how does conversion between int and char happens?


### p.16) 1.5.1 File copying

```
#include <stdio.h>

/* copy input to output; 1stversion */

int main()
{
        int c;

        c = getchar();
        while (c != EOF) {
                putchar(c);
                c = getchar();
        }   

        return 0;

}
```

`getchar()` returns EOF to mark the end of a file. EOF is a symbolic constant definied in the standard library. That is also why the variable c must be of type integer: it must be suitable for storing the value of EOF as well.

In C, any assignment such as `c = getchar()` is an expression with a value (that is the value of the leftside after assignment). *This means that an assigment can appear as part of a larger expression*. Therefor, the following is possible:

```
#include <stdio.h>

/* copy input to output; 2nd version */

int main()
{

        int c;

        while((c = getchar()) != EOF) {
                putchar(c);
        }   
        return 0;
}
```

The while gets a character, assigns it to c and then tests whether c is then end-of-file signal. The parentheses around `c = getchar()` is necassary, because the *relation operator* `!=` has precendence over the *assignment operator* `=`. So:

`c = getchar() != EOF` is equivalent to:
`c = (getchar() != EOF)`

The `getchar() != EOF evaluates to `bool`. `bool` gets [converted](http://stackoverflow.com/questions/4276207/is-c-c-bool-type-always-guaranteed-to-be-0-or-1-when-typecasted-to-int) to the `int` 0 or 1 when it is assigned to c. Check the ASCII table: both 0 and 1 are not seen on tty with `putchar()`;

Extra info: [Original version of C didn't have the boolean type.](https://www.le.ac.uk/users/rjm1/cotter/page_37.htm). It represented booleans with `0` being **false**, every other numeric value is **true**. So in the older versions, `getchar()) != EOF` resulted directly in either 0 or 1.



Notice you have to press `enter` every time. This is because the terminal will buffer all input [until enter is pressed](http://stackoverflow.com/questions/1798511/how-to-avoid-press-enter-with-any-getchar). To fix this weird behaviour, I have made *copyInputToOutputV2-2.c*

### p.17) 1.5.2 Character Counting

Program to count characters:

```
#include <stdio.h>

/* Count characters in input; 1st version  */

int main()
{
        long nc = 0;

        while (getchar() != EOF) {
                ++nc;
        }   

        printf("%ld\n", nc);
}
```

`++` -> increment by one. Can be poth prefix and postfix, but as will be explained in Chapter 2, it has different meaning. 
 
We use the long type here, because long take [at least 4 bytes and can store larger values than int](http://www.tutorialspoint.com/cprogramming/c_data_types.htm)

`%ld` -> tells printf that the corresponding argument is a long integer

The program could have been written with a for loop and a double(a double takes 8 bytes for storage) for the character counter:

```	
#include <stdio.h>

int main()
{

        double nc; 

        for (nc = 0; getchar() != EOF; nc++)
		;
    
        printf("%.0f\n", nc);
}
```

C requires that the for loop has a body. The isolated semicolon called a null statement is there to satisfy that requirement.

Note: the while and for loop test at the top of the loop before proceeding with the body. This enusres that the programs deals intelligently when there is a zero-length input.

### p.19) 1.5.3 Line Counting

Count input lines. Remember: an input text stream appears as a sequence of lines, each terminated by a newsline (`\n`)


```
#include <stdio.h>

/* Count lines */

int main()
{
        int c, nl; 

        nl = 0;

        while ((c = getchar()) != EOF )
        {   
                if (c == '\n')
                        ++nl;
        }   
}
```

A character written within *single quotes* represents an integer value equal to the numerical value of the character in the machines character set. This is called a *character constant* Example:
`'A'` is an integer with the value 65 in an ASCII character set ([see ASCII](http://www.asciitable.com/)). We prefer to write 'A' because the meaning is obvious and it gets a different value in a different character set. Be careful: **don't use double quotes**, double quotes make it a string constant (or string literal).

### p.20) 1.5.4 Word Counting

```
#include <stdio.h>

#define IN  1   /* inside a word */
#define OUT 2   /* outside a word */

/* count lines, words and characters in input */

int c, nl, nw, nc, state;

int main()
{
        state = OUT;
    
        nl = nw = nc = 0;

        while ((c = getchar()) != EOF){
    
                ++nc;

                if (c == '\n') {
                        ++nl;
                }   

                if (c == '\n' || c == '\t' || c == ' ') {
                        state = OUT;
                } else if (state == OUT) {
                        ++nw;
                        state = IN; 
                }   
        }   

        printf("New lines:%d\nWords:%d\nCharacters:%d\n", nl, nw, nc);
    
}
```

`nl = nw = nc = 0;` -> sets all three variables to zero. This is because an assignment is an expression and assignemnts associations are from right to left.
`||` -> OR operator
`&&` -> AND operator. AND precedes over OR

### p.22) 1.6 Arrays

```
#include <stdio.h>

/* count digits, white space and others */

int main()
{
        int c, i, nwhite, nother;
        int ndigit[10];

        nwhite = nother = 0;

        for (i = 0; i < 10; ++i)
                ndigit[i] = 0;

        while((c = getchar()) != EOF)
        {   
                if (c >= '0' && c <= '9')
                        ++ndigit[c - '0'];

                else if (c == '\n' || c == '\t' || c == ' ')
                        ++nwhite;
                else
                        ++nother;
        }   
            
        printf("digits:");

        for (i = 0; i < 10; ++i)
                printf(" %d", ndigit[i]);
            
        printf(" whites: %d others: %d\n", nwhite, nother);

        return 0;

}
```

`int ndigit[10];` -> declares ndigit to be an array of 10 integers. The invidual elements are referenced by an *array subscript*, in c these subscripts start with 0.
`int myArray[10] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };` -> another way of declaring an array. [More ways](http://stackoverflow.com/a/201116)

```
if (c >= '0' && c <= '9')
	++ndigit[c - '0'];
```

This part of the program tests if the character is a digit and increments by referencing via the right subscript (`c - '0'`). This only works if the digits 0..9 are placed consecutively in the character set. chars are identical to ints in arithmetic expressions. So `c - '0'` is an integer expressions.

Notes on exercise 1-14: If you print the ESC sequance literally, the terminal switches to the VT100 Alternate Character Set mode. From [wikipedia](https://en.wikipedia.org/wiki/Box-drawing_character):

```
Unix, CP/M, BBS[edit]
On many Unix systems and early dial-up bulletin board systems the only common standard for box-drawing characters was the VT100 alternate character set. The escape sequence Esc ( 0 switched the codes for lower-case ASCII letters to draw this set, and the sequence Esc ( B switched back:
```

On MAC printing the ESC character (ASCII: 27) switches the terminal to the alternate character set, replacing all the lower case characters with drawing characters. So do not print the ESC key. To witch to to the normal mode again, type `reset` or `tput rmacs` [source](http://superuser.com/questions/197764/reset-garbled-terminal-window-on-os-x)

 ### p.24) 1.7 Functions

A function encapsulates a piece of computation. With a **proper** function, it doesn't matter to the client *how* it is done, only matters *what* is done. In C many small computations will be in its own function, just because it **clarifies** a piece of code.

The standard library contains a function pow(x, y) that computes base x to the y'th power, but for practice we make one ourselves. Ours is only suitable for small positive integers for power:

```
#include <stdio.h>

/* test power function */
int power(int base, int n); 

int main()
{
        int i;

        for (i = 0; i < 10; ++i)
                printf("%d %d %d\n", i, power(2,i), power(-3, i));
        return 0;
}

/* power: raise base to the n-th power; n >= 0 */

int power(int base, int n)
{
        int i, p;
            
        p = 1;
            
        for (i = 1; i <= n; ++i)
                p = p * base;
            
        return p;
}
```

1. Function needs to be declared before it is invoked. (see also point 6)
2. *parameter* is used for a variable named in the parenthesized list, an *argument* is used for the value in the call.
3. Params to a function are local in scope.
4. Any expression may follow from return.
5. If no expression after return, causes to only return control, but not a useful value.
6. On line 4 is a *function prototype*. The function prototype has to agree with the definition and usages of the function, otherwise -> error.

A program that converts fahrenheit to celsius using a function:

```
#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

/* function to convert fahrenheit to celsius */
float convertftoc(int fahrenheit);

int main()
{

int i;

printf("fahrenheit\tcelsius\n");

for (i = LOWER; i <= UPPER; i = i + STEP)
        printf("%10d\t%7.1f\n", i, convertftoc(i));

return 0;
}

float convertftoc(int fahrenheit)
{
        return (5.0/9.0) * (fahrenheit - 32);
}
```

### p. 27 1.8 Arguments - Call by Value

In C all arguments are passed by value. However, it is possible to let a function access a variable directly: the caller must then provide a pointer to the variable.  
**Exception for arrays**: arrays are passed as a pointer to the memory location. By subscripting the value, functions can access the values of an array. (see 1.9)

So, since arguments are passed by value, the power function could have been written as follows:
```
/* power: raise base to the n-th power; n >= 0 */
int power(int base, int n)
{
        int p = 1;
    
        for (; n > 0; --n)
                p = p * base;
    
        return p;
}
```
### p. 28 1.9 Character Arrays

Write a program that reads a set text lines and prints the longest. In pseudo code:

while (*another line*)
  if (*longer than previous)
    *save line*
    *save length*
*print longest line*

Steps:
1. Write a function which reads the next line, saves into a character string and returns the length. -> getLine function  
2. Write a function to copy a line into the longest line variable -> copy function  
3. Write the while loop to control the program.  

```
#include <stdio.h>

#define MAXLINE 1000

int getLine(char line[], int maxline);
void copy(char from[], char to[]);

int main()
{
        char line[MAXLINE];
        char longest[MAXLINE];
    
        int length; /* current line length  */  
        int max = 0; /* max line length */

        while((length = getLine(line, MAXLINE)) > 0){ 
                if (length > max){
                        copy(line, longest);
                        max = length;
                }   
        }   

        if (max > 0) /* there was a line */
                printf("Longest sentence is: %s", longest);
}

/* getLine: read a line into s, return length*/
int getLine(char s[], int lim)
{
        int c, i;
    
        for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
                s[i] = c;
    
        if (c == '\n'){
                s[i] = c;
                ++i;
        }    

        s[i] = '\0';

        return i;

}

void copy(char from[], char to[])
{
        int i = 0;
        while((to[i] = from[i]) != '\0')
                ++i;
    
        return;
}
```

