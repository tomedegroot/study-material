#include <stdio.h>

/* Print Fahrenheit-Celsius Table */

int main()
{
	int fahr;

	printf("Fahrentheit\tCelsius\n");
	
	for (fahr = 300; fahr >= 0; fahr = fahr - 20) {
		printf("%10d\t%7.1f\n", fahr, (5.0/9.0) * (fahr-32));
	}
	
	return 0;
}

