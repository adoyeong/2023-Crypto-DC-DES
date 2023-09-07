#include <stdio.h>
#include "des.h"
typedef unsigned char byte;
int main()
{
	char a[17] = "0123456789abcdef";
	char b[17] = "0123456789abcdef";
	byte* c = des(a, b);
	for(int i=1; i<65; i++)
	{
		printf("%d", c[i]);
		if(i%4==0) printf(" ");
	}
	printf("\n");
	return 0;
}
