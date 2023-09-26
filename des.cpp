#include <stdio.h>
#include <iostream>
#include <string>
#include "des.h"
typedef unsigned char byte;
typedef unsigned long long qword;
byte IP_box[64] = {
58,	50,	42,	34,	26,	18,	10,	2,
60,	52,	44,	36,	28,	20,	12,	4,
62,	54,	46,	38,	30,	22,	14,	6,
64,	56,	48,	40,	32,	24,	16,	8,
57,	49,	41,	33,	25,	17,	9,	1,
59,	51,	43,	35,	27,	19,	11,	3,
61,	53,	45,	37,	29,	21,	13,	5,
63,	55,	47,	39,	31,	23,	15,	7
};
byte FP_box[64] = {
40, 8, 48, 16, 56, 24, 64, 32,
39, 7, 47, 15, 55, 23, 63, 31,
38, 6, 46, 14, 54, 22, 62, 30,
37, 5, 45, 13, 53, 21, 61, 29,
36, 4, 44, 12, 52, 20, 60, 28,
35, 3, 43, 11, 51, 19, 59, 27,
34, 2, 42, 10, 50, 18, 58, 26,
33, 1, 41, 9, 49, 17, 57, 25
};
byte epbox[48] = {
32,  1,  2,  3,  4,  5,
4,  5,  6,  7,  8,  9,
8,  9, 10, 11, 12, 13,
12, 13, 14, 15, 16, 17,
16, 17, 18, 19, 20, 21,
20, 21, 22, 23, 24, 25,
24, 25, 26, 27, 28, 29,
28, 29, 30, 31, 32,  1
};
byte spbox[32] = {
16,  7, 20, 21,
29, 12, 28, 17,
1, 15, 23, 26,
5, 18, 31, 10,
2,  8, 24, 14,
32, 27,  3,  9,
19, 13, 30,  6,
22, 11,  4, 25
};
byte s1[4][16] = {
		14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
		0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
		4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
		15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
};
byte s2[4][16] = {
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
};
byte s3[4][16] = {
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
};
byte s4[4][16] = {
	7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
};
byte s5[4][16] = {
	2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
};
byte s6[4][16] = {
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
};
byte s7[4][16] = {
	4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
};
byte s8[4][16] = {
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};
byte pbd[56] = {
57, 49, 41, 33, 25, 17,  9,
1, 58, 50, 42, 34, 26, 18,
10,  2, 59, 51, 43, 35, 27,
19, 11,  3, 60, 52, 44, 36,
63, 55, 47, 39, 31, 23, 15,
7, 62, 54, 46, 38, 30, 22,
14,  6, 61, 53, 45, 37, 29,
21, 13,  5, 28, 20, 12,  4
};
byte cpbox[48] =
{
14, 17, 11, 24,  1,  5,
3, 28, 15,  6, 21, 10,
23, 19, 12,  4, 26,  8,
16,  7, 27, 20, 13,  2,
41, 52, 31, 37, 47, 55,
30, 40, 51, 45, 33, 48,
44, 49, 39, 56, 34, 53,
46, 42, 50, 36, 29, 32
};
byte shift[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
byte shift_de[16] = { 0, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
byte plain[65];
byte block[65];
byte cipher[65];
byte expanded[49];
byte fout[33];
byte sout[33];
byte round_key[17][49];
byte left[33], right[33];
byte keytmp[57];
byte key[65];
void IP(void)
{
	for (int i = 0; i < 64; i++)
	{
		block[i + 1] = plain[IP_box[i]];
	}
}
void FP(void)
{
	for (int i = 0; i < 64; i++)
	{
		cipher[i + 1] = block[FP_box[i]];
	}
}
void f_epbox(void)
{
	for (int i = 0; i < 48; i++)
	{
		expanded[i + 1] = right[epbox[i]];
	}
}
void f_sbox(void)
{
	byte row[8] = { 0, };
	byte col[8] = { 0, };
	byte out[8] = { 0, };
	for (int i = 0; i < 8; i++)
	{
		row[i] = (expanded[i * 6 + 1] << 1) | expanded[i * 6 + 6];
		col[i] = (expanded[i * 6 + 2] << 3) | (expanded[i * 6 + 3] << 2) | (expanded[i * 6 + 4] << 1) | expanded[i * 6 + 5];
	}
	out[0] = s1[row[0]][col[0]];
	out[1] = s2[row[1]][col[1]];
	out[2] = s3[row[2]][col[2]];
	out[3] = s4[row[3]][col[3]];
	out[4] = s5[row[4]][col[4]];
	out[5] = s6[row[5]][col[5]];
	out[6] = s7[row[6]][col[6]];
	out[7] = s8[row[7]][col[7]];
	for (int i = 0; i < 8; i++)
	{
		for (int j = 4; j > 0; j--)
		{
			sout[i * 4 + j] = out[i] & 1;
			out[i] = out[i] >> 1;
		}
	}
}
void f_spbox(void)
{
	for (int i = 0; i < 32; i++)
	{
		fout[i + 1] = sout[spbox[i]];
	}
}
void f_function(int n)
{
	f_epbox();
	for (int i = 1; i < 49; i++)
	{
		expanded[i] = expanded[i] ^ round_key[n][i];
	}
	f_sbox();
	f_spbox();
}
void round(int n, int nr)
{
	int i;
	for (i = 1; i < 33; i++)
	{
		left[i] = block[i];
	}
	for (i = 1; i < 33; i++)
	{
		right[i] = block[i + 32];
	}
	f_function(n);
	if (n == nr)
	{
		for (i = 1; i < 33; i++)
		{
			block[i + 32] = right[i];
			block[i] = left[i] ^ fout[i];
		}
	}
	else
	{
		for (i = 1; i < 33; i++)
		{
			block[i] = right[i];
			block[i + 32] = left[i] ^ fout[i];
		}
	}

}
void pbdrop()
{
	for (int i = 0; i < 56; i++)
	{
		keytmp[i + 1] = key[pbd[i]];
	}
}
void rkeygen(int n, int enorde) //shift and compression p-box
{
	int i;
	//shift
	byte mem1, mem2, move;
	move = shift[n - 1];
	//left
	mem1 = keytmp[1];
	if (move == 2) mem2 = keytmp[2];
	for (i = 1 + move; i < 29; i++)
	{
		keytmp[i - move] = keytmp[i];
	}
	if (move == 1) keytmp[28] = mem1;
	else
	{
		keytmp[27] = mem1;
		keytmp[28] = mem2;
	}
	//right
	mem1 = keytmp[29];
	if (move == 2) mem2 = keytmp[30];
	for (i = 29 + move; i < 57; i++)
	{
		keytmp[i - move] = keytmp[i];
	}
	if (move == 1) keytmp[56] = mem1;
	else
	{
		keytmp[55] = mem1;
		keytmp[56] = mem2;
	}
	/*
	else
	{
		//shift
                byte mem1, mem2, move;
                move = shift_de[n - 1];
                //left
                mem1 = keytmp[28];
                if (move == 2) mem2 = keytmp[27];
                for (i = 28 - move; i > 0; i--)
                {
                        keytmp[i + move] = keytmp[i];
                }
                if (move == 1) keytmp[1] = mem1;
                else
                {
                        keytmp[2] = mem1;
                        keytmp[1] = mem2;
                }
                //right
                mem1 = keytmp[56];
                if (move == 2) mem2 = keytmp[55];
                for (i = 56 - move; i > 28 ; i--)
                {
                        keytmp[i + move] = keytmp[i];
                }
                if (move == 1) keytmp[29] = mem1;
                else
                {
                        keytmp[30] = mem1;
                        keytmp[29] = mem2;
                }
	}*/
	//compression
	if(enorde == 1)
	{
		for(i=1; i<49; i++)
		{
			round_key[17-n][i] = keytmp[cpbox[i-1]];
		}
	}
	else
	{
		for (i = 1; i < 49; i++)
		{
			round_key[n][i] = keytmp[cpbox[i-1]];
		}
	}
}
byte* des(char p[], char k[], qword pp, qword kk, int numofr, int enorde)
{
	int i;
	if(numofr < 1) return NULL;
	// convert string to bit
	qword input = 0, initkey = 0;
	if(pp == 0)
	{
		if(p != NULL)
		{
			input = strtoull(p, NULL, 16);
		}
		else
		{
			printf("[syntax error] func des error!\n");
			return NULL;
		}
	}
	else input = pp;
	if(kk == 0)
        {
                if(p != NULL)
                {
                        initkey = strtoull(k, NULL, 16);
                }
                else
                {
                        printf("[syntax error] func des error!\n");
                        return NULL;
                }
        }
	else initkey = kk;
	for (i = 0; i < 64; i++)
	{
		plain[64 - i] = input & 1;
		input = input >> 1;
	}
	for (i = 0; i < 64; i++)
	{
		key[64 - i] = initkey & 1;
		initkey = initkey >> 1;
	}

	//key scheduling
	pbdrop(); 
	for (i = 1; i < 17; i++)
	{
		rkeygen(i, enorde);
	}

	// DES algorithm
	IP(); 
	for (i = 1; i < numofr+1; i++) round(i, numofr);
	FP();

	return cipher;
}
