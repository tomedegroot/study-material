#include <stdio.h>
#define MAXLINE 1000

int getLine(char line[], int maxLine);
void sanitizeLine(char line[], int lineLength);

int main()
{
	int lineLength = 0;
	char line[MAXLINE];
	
	while ((lineLength = getLine(line, MAXLINE)) != 0){
		if (lineLength == 1 && line[0] == '\n')
            		continue;

		sanitizeLine(line, lineLength);	
		printf("%d: %s", lineLength, line);
	}

	return 0;
}

/* Remove trailing blanks and tabs from each line of input and set it to char line[] */
void sanitizeLine(char line[], int lineLength)
{
	/*
	 * Remember: subscripts in array start from zero, so the line length is one higher than the last subscript of content.
	 * The last subscript of the char[] is the '\0' char, which indicates the end of the string (terminator) and doesn't count for the length of the contet.
	 * This means that the lineLength indicates the place of the line terminator. (lineLength - 1 = last content subscript, lineLength itself is the '\0' subscript)
	 */	
	
	// If the line ends with a newline, than it should be in the sanitized line as well	
	int newLineAtEnd = 0;
	if (line[lineLength-1] == '\n'){
		lineLength--; // strip the newline
		newLineAtEnd = 1;	
	}

	while(line[lineLength - 1] == '\t' || line[lineLength - 1] == ' ') {
		lineLength--;
	} 

	if (newLineAtEnd){
		line[lineLength] = '\n';
		lineLength++;
	}

	// Mark the end of the string
	line[lineLength] = '\0';

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
