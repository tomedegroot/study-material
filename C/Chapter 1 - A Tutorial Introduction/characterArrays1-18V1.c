#include <stdio.h>
#define MAXLINE 1000

int getLine(char line[], int maxLine);
void sanitizeLine(char line[], int lineLength);

int main()
{
	int lineLength = 0;
	char line[MAXLINE];
	
	while ((lineLength = getLine(line, MAXLINE)) != 0){
		sanitizeLine(line, lineLength);	
		printf("%d: %si", lineLength, line);
	}

	return 0;
}

/* Remove trailing blanks and tabs from each line of input and set it to char line[] */
void sanitizeLine(char line[], int lineLength)
{
	int newLineAtEnd = 0;
	
	/* Skip the string terminator '\0' */
	lineLength--;

	/* Skip the newline indicator if it is there */
	if (line[lineLength - 1] == '\n'){
		lineLength--;
		newLineAtEnd = 1;	
	}

	while(line[lineLength - 1] == '\t' || line[lineLength - 1] == ' ') {
		lineLength--;
	} 

	if (newLineAtEnd){
		line[lineLength - 1] = '\n';
		lineLength++;
	}

	line[lineLength - 1] = '\0';

	return;
}

/* 
 * Get the next line and set it to the car line[]. 
 * Return the length of the line
 */
int getLine(char line[], int maxLine) 
{	
	int c;	
	int lineLength = 0;
	int charSubscript = 0;	

	while((c = getchar()) != '\n' && c != EOF){
		++lineLength;

		if(charSubscript < maxLine - 1){
			line[charSubscript] = c;
			++charSubscript;
		}
	}

	/* The \n is part of the line*/
	if (c == '\n'){
		++lineLength;

		if(charSubscript < maxLine - 1){
			line[charSubscript] = c;
			++charSubscript;
		}
	}

	line[charSubscript] = '\0';

	return lineLength;
}
