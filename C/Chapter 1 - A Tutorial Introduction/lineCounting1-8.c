#include <stdio.h>

int main()
{
	
	long counter = 0;
	int c;

	while((c = getchar()) != EOF)
	{
		if ( c == '\n' || c == '\t' || c == ' ')
			++counter;
	}

	printf("There are %ld newlines, tabs or spaces in the standard input", counter);

	return 0;

}
