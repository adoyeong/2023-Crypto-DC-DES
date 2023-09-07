#include <stdio.h>
#include "des.h"
typedef unsigned char byte;
int main()
{
	char a[17] = "0123456789abcdef";
	char b[17] = "0123456789abcdef";
	byte* c = des(a, b);
	return 0;
}
