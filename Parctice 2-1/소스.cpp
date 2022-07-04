/**
*���ϸ� : 2022 - 1 ���α׷��� ��� �ǽ� 2""
*���α׷��� ���� �� �⺻ ���:
*      -�� ���α׷��� 8�ڸ� 16������ �Է¹޾� 10����, 8����, 16����,
*       32��Ʈ 2������ ����ϰ� Bitwise�� �̿��Ͽ� �Է¹��� �����͸�
*       AND, OR, XOR, SHIFT, NOT�� 32��Ʈ 2������ ����ϴ� ���α׷�
*���α׷� �ۼ��� : ��ΰ�(2022�� �� ��)
*���� Update : Version 1.2, 2022�� 03�� 09��(��ΰ�)
*============================================================================
*���α׷� ����/���� �̷�
*============================================================================
*���α׷� ����/�����۾���	����	����/���ϳ���
*��ΰ�		2022/03/06		v1.0	�ʱ����� �ϼ�
*��ΰ�		2022/03/09		v1.1	enum�� char*�� �̿��Ͽ� �����ϰ� ����
*��ΰ�     2022/03/09      v1.2    ��������ʴ� ����, ����� ���� ����
*============================================================================
*/
#include<stdio.h>
#define SHIFT_SIZE 3
#define BIT_SIZE 32


enum Operate {ADD, SUB, AND, OR, XOR, SHIFT_LEFT, SHIFT_RIGHT, NOT};
const char* sign[] = { "+", "-", "&", "|", "^", "<<", ">>", "~" };

void printInt_Bits(int data);
void printIntOper_Bits(Operate value, int x, int y, int z);

int main(void)
{
	int data1 = 0;
	int data2 = 0;

	printf("Input first hexadecimal number in (0x00000000 ~ 0xFFFFFFFF) : ");
	scanf("%x", &data1);

	printf("x = %#X = (in decimal) %d = (in octal) %o \n = (in bits) ", data1, data1, data1);
	printInt_Bits(data1);

	printf("\nInput first hexadecimal number in (0x00000000 ~ 0xFFFFFFFF) : ");
	scanf("%x", &data2);

	printf("y = %#X = (in decimal) %d = (in octal) %o \n = (in bits) ", data2, data2, data2);
	printInt_Bits(data2);

	printf("\n%#X + %#X  => %#X \n", data1, data2, data1 + data2);
	printIntOper_Bits(ADD, data1, data2, data1 + data2);

	printf("\n%#X - %#X  => %#X \n", data1, data2, data1 - data2);
	printIntOper_Bits(SUB, data1, data2, data1 - data2);

	printf("\nBitwise AND : %#X & %#X  => %#X \n", data1, data2, data1 & data2);
	printIntOper_Bits(AND, data1, data2, data1 & data2);

	printf("\nBitwise OR : %#X | %#X  => %#X \n", data1, data2, data1 | data2);
	printIntOper_Bits(OR, data1, data2, data1 | data2);

	printf("\nBitwise XOR : %#X ^ %#X  => %#X \n", data1, data2, data1 ^ data2);
	printIntOper_Bits(XOR, data1, data2, data1 ^ data2);

	printf("\nBitwise Shift Left : %#X << %#X => %#X \n", data1, SHIFT_SIZE, data1 << SHIFT_SIZE);
	printIntOper_Bits(SHIFT_LEFT, data1, SHIFT_SIZE, data1 << SHIFT_SIZE);
	
	printf("\nBitwise Shift Left : %#X >> %#X => %#X \n", data2, SHIFT_SIZE, data2 >> SHIFT_SIZE);
	printIntOper_Bits(SHIFT_RIGHT, data2, SHIFT_SIZE, data2 >> SHIFT_SIZE);

	printf("\nBitwise Not : ~%#X => %#X \n", data2, ~data2);
	printIntOper_Bits(NOT, data1, data2, ~data2);
	
	return 0;
}

void printInt_Bits(int data)  
{
	for (int i = BIT_SIZE - 1; i >= 0; i--) //BIT_SIZE�� 32�̸� ����ϴ� ��Ʈ�� ���� ��Ÿ����. ���⼱
	{
		printf("%d", (data >> i) & 1);
		if (i % 8 == 0)
			printf(" ");
	}
}

void printIntOper_Bits(Operate value, int x, int y, int z)
{
	if (value != NOT)
		printf("    "); printInt_Bits(x); printf("\n");
	printf(" %2s ", sign[value]); printInt_Bits(y); printf("\n");
	printf("  -------------------------------------\n");
	printf("    "); printInt_Bits(z); printf("\n");
}