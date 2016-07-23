#include <stdio.h>

#define IN  1 	/* inside a word */
#define OUT 2 	/* outside a word */

/* count lines, words and characters in input */

int c, nl, nw, nc, state;

int main()
{
	state = OUT;
	
	nl = nw = nc = 0;

	while ((c = getchar()) != EOF){
		
		++nc;

		if (c == '\n') {
			++nl;
		}

		if (c == '\n' || c == '\t' || c == ' ') {
			state = OUT;
		} else if (state == OUT) {
			++nw;
			state = IN;
		} 
	}

	printf("New lines:%d\nWords:%d\nCharacters:%d\n", nl, nw, nc);
	
}
