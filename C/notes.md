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

Extra information:
1. [Integer division will result in the floor of the division.](http://stackoverflow.com/questions/3602827/what-is-the-behavior-of-integer-division-in-c) So (1/i) where i is an int > 1 will always result in 0. This explains way the formula for conversion celsius = 5  * (fahr-32) / 9 is writtenthe way it is.
2. Once a variable is created as a certain typed, it is locked to a certain type. So you can't reassign a float to a variable of an int type. You have to create new variable.
3. If the 5 and the 9 were declared as floats before the division, the result would not be floored (or truncated) as stated in point 1. So the formula could also be written as celsius = 5  * (fahr-32) / 9;



