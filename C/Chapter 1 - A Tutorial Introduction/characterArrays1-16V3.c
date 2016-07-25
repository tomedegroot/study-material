#include <stdio.h>

#define MAXLINE 1000

int getLine(char line[], int maxline);
void copy(char from[], char to[]);

int main()
{
	char line[MAXLINE];
	char longest[MAXLINE];

	int c;	
	int length; /* current line length  */
	int max = 0; /* max line length */

	while((length = getLine(line, MAXLINE)) > 0){
		if (length > max){
			copy(line, longest);
			max = length;
		} 
	}

	if (max > 0) /* there was a line */
		printf("\nLongest sentence (%d characters)is: %s\n", max, longest);
}

/* getLine: read a line into s, return length*/
int getLine(char s[], int maxline)
{
	int c, length, characterCount;
	
	length = characterCount = 0;

	while ((c = getchar()) != EOF && c != '\n'){
		++length;

		if (characterCount < maxline - 1) {
			s[characterCount] = c;
			++characterCount;
		}
	}

	/* Since the '\n' char counts as part of the line, we have to add it to the length and the string if we still have mem left for the '\n' AND the string terminator '\0'*/
	if (c == '\n') {
		++length;	
		if (characterCount < maxline - 1) {
			s[characterCount] = c;
			++characterCount;
		}
	}

	s[characterCount] = '\0';

	return length;

}

void copy(char from[], char to[])
{
	int i = 0;
	while((to[i] = from[i]) != '\0')
		++i;
	
	return;
}
