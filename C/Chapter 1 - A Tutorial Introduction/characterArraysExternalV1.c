#include <stdio.h>

#define MAX_LINE 1000 // To prevent memory overflow

char line[MAX_LINE]; // Current line
char max_line[MAX_LINE]; // Max line

int max_length = 0; // Length of max line

int getLine();
void copy();

/* Goal of program: Count the length of lines from stdin and output the length and content of the longest line */

// Loop over lines and if it is longer than the current max line, store the length in max_length and content in max_line
int main()
{
	extern char max_line[];
	
	int length;
	extern int max_length;
		
	
		
	while((length = getLine()) != 0){
		if (length > max_length) {
			copy();
			max_length = length;
		}
	}	
	
	printf("%d: %s", max_length, max_line);
}	

// Get the next line, store it and return the length
int getLine()
{
	char c;
	extern char line[];

	int length = 0;
	int charsAssigned = 0; // Keep track of the charsAssigned to prevent a memory overflow

	while((c = getchar()) != '\n' && c != EOF){
		++length;
		
		if (charsAssigned < MAX_LINE - 1){
			line[charsAssigned] = c;
			++charsAssigned;
		}
	}

	if (c == '\n') {
		++length;

		if (charsAssigned < MAX_LINE -1){
			line[charsAssigned] = c;
			++charsAssigned;
		}
	}

	line[charsAssigned] = '\0';
	return length;
}

// copy 
void copy(){
	extern char line[], maxline[];
	
	int i = 0;
	while((max_line[i] = line[i]) != '\0')
		++i;
}
