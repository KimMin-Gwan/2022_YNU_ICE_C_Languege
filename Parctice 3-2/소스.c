/*
*파일명 : "프로그래밍 언어_21912229_김민관_실습 3 - 2"
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 2차원 배열을 만들어 연산을 시행하는 프로그램이다.
*프로그램 작성자 : 김민관(2022년 03월 12일)
*최종 Update : Version 1.1, 2022년 03월 17일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
*김민관      2022/03/12      v1.1   주석문 작성
*============================================================================
*/
#include<stdio.h>
#define SIZE 5
#define MTRX_SIZE 5
void printMtrx(double mA[][SIZE], int size_n);
void printMtrx(double mA[][SIZE], int size);
void addMtrx(double mA[][MTRX_SIZE], double mB[][MTRX_SIZE], double mR[][MTRX_SIZE], int size); //배열의 덧셈
void subMtrx(double mA[][MTRX_SIZE], double mB[][MTRX_SIZE], double mR[][MTRX_SIZE], int size); //배열의 뺄셈
void mulMtrx(double mA[][MTRX_SIZE], double mB[][MTRX_SIZE], double mR[][MTRX_SIZE], int size); //배열의 곱셈

int main() {
	double mA[SIZE][SIZE] = { {5.0, 4.0, 3.0, 2.0, 1.0},
	{6.0, 7.0, 8.0, 9.0, 10.0},
	{11.0, 12.0, 13.0, 14.0, 15.0},
	{16.0, 17.0, 18.0, 19.0, 20.0},
	{21.0, 22.0, 23.0, 24.0, 25.0}
	};
	double mB[SIZE][SIZE] = { {1.0, 0.0, 0.0, 0.0, 0.0},
	{0.0, 1.0, 0.0, 0.0, 0.0},
	{0.0, 0.0, 1.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 1.0, 0.0},
	{0.0, 0.0, 0.0, 0.0, 1.0}
	};
	double mC[SIZE][SIZE], mD[SIZE][SIZE], mE[SIZE][SIZE];
	printf("\n Matrix mA:\n");
	printMtrx(mA, 4);
	printf("\n Matrix mB:\n");
	printMtrx(mB, 4);
	addMtrx(mA, mB, mC, 4);
	printf("\n Matrix mC = mA + mB:\n");
	printMtrx(mC, 4);
	subMtrx(mA, mB, mD, 4);
	printf("\n Matrix mD = mA - mB:\n");
	printMtrx(mD, 4);
	mulMtrx(mA, mB, mE, 4);
	printf("\n Matrix mE = mA x mB:\n");
	printMtrx(mE, 4);
	printf("\n");
	return 0;
}

void printMtrx(double mA[][SIZE], int size)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
		{
			if ((i == 0) && (j == 0))
				printf("%c%c%7.2lf", a6, a3, mA[i][j]);
			else if ((i == 0) && j == (size - 1))
				printf("%7.2lf%c%c", mA[i][j], a6, a4);
			else if ((i > 0) && (i < size - 1) && (j == 0))
				printf("%c%c%7.2lf", a6, a2, mA[i][j]);
			else if ((i > 0) && (i < size - 1) && (j == (size - 1)))
				printf("%7.2lf%c%c", mA[i][j], a6, a2);
			else if ((i == (size - 1)) && (j == 0))
				printf("%c%c%7.2lf", a6, a6, mA[i][j]);
			else if ((i == (size - 1)) && (j == (size - 1)))
				printf("%7.2lf%c%c", mA[i][j], a6, a5);
			else
				printf("%7.2lf", mA[i][j]);
		}
		printf("\n");
	}
}

void addMtrx(double mA[][MTRX_SIZE], double mB[][MTRX_SIZE], double mR[][MTRX_SIZE], int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			mR[i][j] = mA[i][j] + mB[i][j];
}
void subMtrx(double mA[][MTRX_SIZE], double mB[][MTRX_SIZE], double mR[][MTRX_SIZE], int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			mR[i][j] = mA[i][j] - mB[i][j];
}
void mulMtrx(double mA[][MTRX_SIZE], double mB[][MTRX_SIZE], double mR[][MTRX_SIZE], int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			mR[i][j] = 0; //배열 초기화
			for (int k = 0; k < size; k++)
				mR[i][j] += mA[i][k] * mB[k][j];
		}
}