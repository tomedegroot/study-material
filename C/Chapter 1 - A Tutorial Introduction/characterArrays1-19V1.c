#include <stdio.h>

#define MAX_LINE 1000

int getLine(char line[]);
void reverseLine(char line[]);

int main()
{
	int length = 0;
	char line[MAX_LINE];

	while((length = getLine(line)) > 0)
	{	
		// reverse should come here
		reverseLine(line);
		printf("%d: %s", length, line);
	}
}

/* Reverse a line*/
void reverseLine(char line[])
{
	
	char temp;
	
	int incrementor, length;
	
	// Get the length of the line without the new line if present (otherwise, just take the char array terminator). We still want the new line at the end.
	for (length = 0; line[length] != '\n' && line[length] != '\0'; ++length)
		;
	
	// We de not want to swap the '\n' or '\0' chars.
	--length;
	
	/*
	 * incrementor counts from beginning, length counts from the end
         * as long as the incrementor is smaller than the length, swap.
	 * use a temp variable to hold the char from the incrementor's place and later store that one at the length's place.
	 */
	for(incrementor = 0; incrementor < length; ++incrementor, --length){
		temp = line[incrementor];
		line[incrementor] = line[length];
		line[length] = temp;
	}
	
	

}

/* Read from stdin and return in line */
int getLine(char line[])
{
	char c;
	int length, charsAssign = 0;

	/* Fetch char till \n or EOF */
	while ((c = getchar()) != '\n' && c != EOF){
		++length;

		/* If charsAssign is lower than MAX_LINE - 1, place the char */
		if (charsAssign < MAX_LINE - 1){
			line[charsAssign] = c;
			++charsAssign;
		}	
	}	

	/* If the last char was a new line, place it after charsPlaced if we still have place in memory  */
	if (c == '\n'){ 
		++length;
		
		if (charsAssign < (MAX_LINE - 1)) {
			line[charsAssign] = c;
			++charsAssign;
		}
	}

	/* Terminate the char array with '\0' at the end which is at most MAX_LINE -1 */
	line[charsAssign] = '\0';

	/* Return length */

	return length;

}
