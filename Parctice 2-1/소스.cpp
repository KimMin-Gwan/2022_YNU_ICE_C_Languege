/**
*파일명 : 2022 - 1 프로그래밍 언어 실습 2""
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 8자리 16진수를 입력받아 10진수, 8진수, 16진수,
*       32비트 2진수로 출력하고 Bitwise를 이용하여 입력받은 데이터를
*       AND, OR, XOR, SHIFT, NOT을 32비트 2진수로 출력하는 프로그램
*프로그램 작성자 : 김민관(2022년 월 일)
*최종 Update : Version 1.2, 2022년 03월 09일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자	일자	수정/보완내용
*김민관		2022/03/06		v1.0	초기파일 완성
*김민관		2022/03/09		v1.1	enum과 char*를 이용하여 간략하게 줄임
*김민관     2022/03/09      v1.2    사용하지않는 변수, 어려운 문맥 수정
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
	for (int i = BIT_SIZE - 1; i >= 0; i--) //BIT_SIZE는 32이며 출력하는 비트의 수를 나타낸다. 여기선
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