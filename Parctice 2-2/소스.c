
#include <stdio.h>
#include <limits.h>
#define BIT_MASK 0x01
#define BITS 31

void printInt_Bits(int a);

int main()
{
	char char_max, char_min;
	short short_max, short_min;
	int int_max, int_min;
	printf("CHAR_MAX = %d\n", CHAR_MAX);
	printf("CHAR_MIN = %d\n", CHAR_MIN);
	char_max = CHAR_MAX;
	char_min = CHAR_MIN;
	printf("CHAR_MAX (%d) + 1 = %d\n", char_max, char_max + 1);
	printf("CHAR_MIN (%d) - 1 = %d\n", char_min, char_min - 1);
	printf("\n");
	printf("SHRT_MAX = %d\n", SHRT_MAX);
	printf("SHRT_MIN = %d\n", SHRT_MIN);
	short_max = SHRT_MAX;
	short_min = SHRT_MIN;
	printf("SHRT_MAX (%d) + 1 = %d\n", short_max, short_max + 1);
	printf("SHRT_MIN (%d) - 1 = %d\n", short_min, short_min - 1);
	printf("\n");
	printf("INT_MAX = %d\n", INT_MAX);
	printInt_Bits(INT_MAX); 
	int_max = INT_MAX;
	printf("INT_MAX (%d) + 1 = %d\n", int_max, int_max + 1);
	printInt_Bits(INT_MAX + 1); 
	printf("\n");
	printf("\nINT_MIN = %d\n", INT_MIN);
	printInt_Bits(INT_MIN); 
	int_min = INT_MIN;
	printf("INT_MIN (%d) - 1 = %d\n", int_min, int_min - 1);
	printInt_Bits(INT_MIN - 1);
	return 0;
}

void printInt_Bits(int a)
{
	unsigned long bit; 
	for (int i = BITS; i >= 0; i--)
	{
		bit = (a >> i) & BIT_MASK;
		printf("%d", bit);
		if ((i % 8) == 0)
			printf(" ");
	}
	printf("\n");
}