#include <stdio.h>
#define MAXLINE 1000

int getLine(char line[], int maxLine);

int main()
{
	int lineLength = 0;
	char line[MAXLINE];
	
	while ((lineLength = getLine(line, MAXLINE)) != 0){
		if (lineLength > 80)
			printf("%d: %s", lineLength, line);
	}

	return 0;
}

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

INVALID OUTPUT: WIP
