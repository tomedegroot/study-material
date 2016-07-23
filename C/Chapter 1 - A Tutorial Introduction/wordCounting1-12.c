#include <stdio.h>

/* Print every word from STDIN on a new line */

int main()
{
	int c, lastC;

	lastC = '\n';
	
	while ((c = getchar()) != EOF){
		
		if (c != '\n' && c != '\t' && c!= ' '){
			putchar(c);
		} else if (lastC != '\n' && lastC != '\t' && lastC != ' '){
			putchar('\n');
		}

		lastC = c;

	}	

	return 0;
}

// Other possible solution: https://github.com/ccpalettes/the-c-programming-language-second-edition-solutions/blob/master/Chapter1/Exercise%201-12/one_word_per_line.c
