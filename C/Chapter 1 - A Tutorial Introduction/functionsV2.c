#include <stdio.h>

/* test power function */
int power(int base, int n);

int main()
{
	int i;

	for (i = 0; i < 10; ++i)
		printf("%d %d %d\n", i, power(2,i), power(-3, i));
	return 0;
}

/* power: raise base to the n-th power; n >= 0 */
int power(int base, int n)
{
	int p = 1;
	
	for (; n > 0; --n)
		p = p * base;
	
	return p;
}
