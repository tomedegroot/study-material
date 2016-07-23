#include <stdio.h>

/* count digits, white space and others */

int main()
{
	int c, i, nwhite, nother;
	int ndigit[10];

	nwhite = nother = 0;

	for (i = 0; i < 10; ++i)
		ndigit[i] = 0;

	while((c = getchar()) != EOF)
	{
		if (c >= '0' && c <= '9')
			++ndigit[c - '0'];

		else if (c == ' '|| c == '\t' || c == ' ')
		
			++nwhite;
		else
			++nother;
	}
	
	printf("digits[digit-occurences]:");

	for (i = 0; i < 10; ++i)
		printf(" [%d-%d]", i, ndigit[i]);
	
	printf(" whites: %d others: %d\n", nwhite, nother);

	return 0;

}
