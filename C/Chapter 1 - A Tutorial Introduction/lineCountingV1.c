#include <stdio.h>

/* Count lines */

int main()
{
	int c, nl;

	nl = 0;

	while ((c = getchar()) != EOF )
	{
		if (c == '\n')
			++nl;
	}
}
