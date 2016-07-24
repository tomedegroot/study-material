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
int getLine(char s[], int lim)
{
	int c, i, l;
	
	for (i = 0, l = 0; (c = getchar()) != EOF && c != '\n'; ++i) {
		/* lim - 1 because we need the last subscript for the \0 char */
		if (i < lim - 1){
			s[l] = c;
			++l;
		}
	}

	if (c == '\n'){
		if (l < lim - 1)
			s[++l] = c;
		++i;
	}	

	s[l] = '\0';

	return i;

}

void copy(char from[], char to[])
{
	int i = 0;
	while((to[i] = from[i]) != '\0')
		++i;
	
	return;
}
