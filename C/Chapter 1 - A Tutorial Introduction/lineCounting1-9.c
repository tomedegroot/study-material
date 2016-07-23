#include <stdio.h>

#define NONBLANK '-'

int main()
{

	int c, lastC;
	long counter = 0;
	
	lastC = NONBLANK;

	while((c = getchar()) != EOF)
	{
		if (lastC != ' ')
			putchar(c);
		else {
			if (c != ' ')
				putchar(c);
		}
		
		lastC = c;

	}
	
	return 0;

}
