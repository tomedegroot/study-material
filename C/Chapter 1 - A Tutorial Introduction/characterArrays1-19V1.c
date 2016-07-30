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
		printf("%d: %d: %s", reverseLine(line), length, line);
	}
}

/* Reverse a line*/
void reverseLine(char line[])
{
	int length;

	for (length = 0; line[length] != '\0'; ++length)
		;
	
	

}

/* Read from stdin and return in line */
int getLine(char line[])
{
	int c, length, charsAssign;
	
	length = charsAssign = 0;

	/* Fetch char till \n or EOF */
	while ((c = getchar()) != '\n' && c != EOF){
		++length;

		/* If charsAssign is lower than MAX_LINE - 1, place the char */
		if (charsAssign < MAX_LINE - 1){
			line[charsAssign] = c;
			++charsAssign;
		}	
	}	

	/* If the last char was a new line, place it after charsPlaced OR a the MAX_LINE - 1  */
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
