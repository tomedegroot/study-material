#include <stdio.h>

#define TAB_SIZE 8 // Columns per tab

/** ENTAB: replace tabs with the a number of spaces */

/**
 * This programs is wrong. A tab is NOT placing a number of spaces,  tab used to brigde some amount of characters to the next tab stop on a line
 * This version 2
 */

int main()
{
	char c;
	int blanksToPlace, charPos, i;

	charPos = 1;

	
	
	while((c = getchar()) != EOF)
	{	
		if(c == '\t'){
			blanksToPlace = TAB_SIZE - ((charPos - 1) % TAB_SIZE); // (charPos - 1), because
			
			for(i = 0; i < blanksToPlace; i++){
				++charPos;
				putchar(' ');
			}
		}
		else if(c == '\n'){
			putchar(c);
			charPos = 1;
		}
		else{
			++charPos;
			putchar(c);
		}
	}
}

