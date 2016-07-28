#include <stdio.h>

#define MAX_LINE 1000

int getLine(char s[]);

int main()
{
	int length = 0;
	char line[MAX_LINE];

	while((length = getLine()) > 0)
	{	
		// reverse should come here
		printf("%s", line);
	}
}
