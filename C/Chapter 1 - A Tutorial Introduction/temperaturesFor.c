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

