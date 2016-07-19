#include <stdio.h>

/* print Fahrenheit-Celsius table for fahr = 0, 20 ..., 300 */

/* Formula for conversion: C = (5/9) * (F-32) */

int main()
{
	float fahr, celsius;
	int lower, upper, step;
	
	lower = -20;	/* lower limit of temperature table */
	upper = 150;	/* upper limit */
	step = 10;	/* step size */

	celsius = lower;

	printf("Celsius\tFahrenheit\n");
	
	while(celsius <= upper) {
		//celsius = (5.0/9.0)  * (fahr-32.0);
		fahr = (celsius * (9.0/5.0)) + 32.0;
		printf("%7.1f\t%10.0f\n", celsius, fahr);
		celsius = celsius + step;
	}

	return 0;

}
