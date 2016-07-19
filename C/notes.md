# Chapter 1 - A Tutorial Introduction

**Goal: Show the elements of C in a real program**

## p.6) Example hello.c:

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
  1. statements: specify the computing operations
2. variables store valuse during the computation

`main()` -> computation starts with executing this function.  

`#include <stdio.h>` -> tells the compiler to include information from the standard input/output library

Function *arguments* are used to communicate data between functions. Statements of a function are between '{}'. So the `printf("hello, world\n")` calls the function `printf` with a string of characters. 

A sequance of characters between double quotes is called:
1. string of text
2. string constant

`\n` -> escape sequance, in this case for newline. See section 2.3(p.38) for a complete list of escape sequances.

## p.8) Example: temperatures.c:

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
    
        while(fahr<upper) {
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
