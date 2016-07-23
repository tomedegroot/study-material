#include <stdio.h>

int main()
{
	int c;

	while((c = getchar()) != EOF)
	{
		
		if(c == '\t')
			printf("\\t");
		else if(c == '\b')
			printf("\\b");
		else if(c == '\\')
			printf("\\\\");
		else
			putchar(c);

	}
	
	return 0;
}

// Possible solution with putchar(): http://www.learntosolveit.com/cprogramming/Ex_1.10_TbsBlnkSpaces.html
