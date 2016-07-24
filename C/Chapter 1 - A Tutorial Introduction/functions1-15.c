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
