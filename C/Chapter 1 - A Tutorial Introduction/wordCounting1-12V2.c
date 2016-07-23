#include <stdio.h>

int main() {
	int c, lineStarted;

	lineStarted = 0;

	while ((c = getchar()) != EOF) {
		if (c == '\n' || c == '\t' || c == ' '){
			if (lineStarted == 0) {
				putchar('\n');
				lineStarted = 1;
			}
		} else {
			putchar(c);
			lineStarted = 0;
		}
	}

	return 0;
}
