#include <stdio.h>

#define N_ASCII_CHARS 128

int main()
{
	int c, i, j;
	
	int ncharacters[N_ASCII_CHARS];
	
	for(i = 0; i < N_ASCII_CHARS; ++i) {
		ncharacters[i] = 0;
	}

	while((c = getchar()) != EOF)
		++ncharacters[c];

	printf("char - ascii value\n");
	for(i = 0; i < N_ASCII_CHARS; ++i) {
		/* do not print the ESC char, because it can cause the terminal to switch to alternate character set.
		   only print if the occurence of the character is at least 1. */
		if (ncharacters[i] > 0 && i != 27) {
			printf("%4c - %11d:", i, i);
			
			for(j = 0; j < ncharacters[i]; ++j) {
				printf("-");
			}
			
			printf("\n");
		}
	}
}
