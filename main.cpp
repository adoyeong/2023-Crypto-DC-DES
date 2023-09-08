#include <stdio.h>
#include "des.h"
int main()
{
	/*
	bit-by-bit complementation test
	if T = DES(P, K)
	then T' = DES(P', K')?
	*/

	char p1[17] = "0123456789abcdef";
	char p2[17] = "fedcba9876543210";
	char k1[17] = "133457799bbcdff1";
	char k2[17] = "eccba8866443200e";
	printf("#####[ bit-by-bit complementation test ]#####\n");
	printf("P : 0123456789abcdef, K : 133457799bbcdff1\n");
	byte* c = des(p1, k1, 0, 0, 16);
	for(int i=1; i<65; i++)
	{
		printf("%d", c[i]);
		if(i%4==0) printf(" ");
	}
	printf("\n");
	printf("P : fedcba9876543210, K : eccba8866443200e\n");
	c = des(p2, k2, 0, 0, 16);
	for(int i=1; i<65; i++)
	{
		printf("%d", c[i]);
		if(i%4==0) printf(" ");
	}
	printf("\n");
			
	/*
	Exploit complement property.
	The attacker encrypt P1 under only 2^55 keys.
	
	0) (P1, C1), (P2, C2), P1' = P2
	1) real key : K
	2) encrypt P1 by k -> C
	3) if C is equal to C1, then k is likely to be the real key K.
	4) else if C' is equal to C2, then k' is likely to be the K.
	*/
	
	byte c1[65], c2[65];
	char none[2] = {0, };
	char realkey[17] = "0000000000ef19f1";
	c = des(p1, realkey, 0, 0, 6);
	for(int i=1; i<65; i++)
	{
		c1[i] = c[i];
	}
	c = des(p2, realkey, 0, 0, 6);
	for(int i=1; i<65; i++)
	{
		c2[i] = c[i];
	}
	qword key = 0x0, max = 0xfffffe;
	byte* test;
	int flag1 = 0, flag2 = 0;
	do{
		flag1 = 0;
		flag2 = 0;
		key = key + 0x02;
		test = des(p1, none, 0, key, 6);
		for(int i=1; i<65; i++)
		{
			if(c1[i] != test[i]) flag1 = 1;
			if(c2[i] == test[i]) flag2 = 1;
		}
		if((flag1 * flag2) == 0)
		{
			printf("FOUND : real key is  %llx\n", key);
			break;
		}
	} while(key < max);
	return 0;
}
