#include <stdio.h>

#define INWORD 1
#define OUTWORD 0

/* Print horizontal histogram with the length of words */

int main()
{
	int i, j, c, ncharacters, state;
	int nword[21];
	
	ncharacters = 0;
	state = OUTWORD;	

	for (i = 0; i < 21; ++i) {
		nword[i] = 0;
	}	

	while ((c = getchar()) != EOF) {
		if (c == '\n' || c == '\t' || c == ' ') {
			if (state == INWORD) {
				++nword[ncharacters];
				ncharacters = 0;
			}

			state = OUTWORD;
		} else {
			++ncharacters;
			state = INWORD;
		}
	}
	
	if (state == INWORD) {
		++nword[ncharacters];
	}
	
	for (i = 1; i < 21; ++i) {
		printf("%d", i);
		for (j = 0; j < nword[i]; ++j)
			printf("-");
		printf("\n");
	}

	return 0;
}

/* @todo improve with definers for max length. Take a look at ccpalettes */

//Other solution: https://github.com/ccpalettes/the-c-programming-language-second-edition-solutions/blob/master/Chapter1/Exercise%201-13/word_length.c
