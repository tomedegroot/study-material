#include <stdio.h>

#define ENTER 10

int c;

int main()
{
	while ((c = getchar()) != EOF) {
		if (c != ENTER) {
			printf("%c\n", c);
		}	
	}

	return 0;
}

