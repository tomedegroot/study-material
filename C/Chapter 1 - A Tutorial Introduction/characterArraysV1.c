#include <stdio.h>

#define MAXLINE 1000

int getLine(char line[], int maxline);
void copy(char from[], char to[]);

int main()
{
	char line[MAXLINE];
	char longest[MAXLINE];
	
	int length; /* current line length  */
	int max = 0; /* max line length */

	while((length = getLine(line, MAXLINE)) > 0){
		if (length > max){
			copy(line, longest);
			max = length;
		} 
	}

	if (max > 0) /* there was a line */
		printf("Longest sentence is: %s", longest);
}

/* getLine: read a line into s, return length*/
int getLine(char s[], int lim)
{
	int c, i;
	
	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	
	if (c == '\n'){
		s[i] = c;
		++i;
	}	

	s[i] = '\0';

	return i;

}

void copy(char from[], char to[])
{
	int i = 0;
	while((to[i] = from[i]) != '\0')
		++i;
	
	return;
}
