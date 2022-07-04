/*
*���ϸ� : "���α׷��� ���_21912229_��ΰ�_�ǽ� 3 - 2"
*���α׷��� ���� �� �⺻ ���:
*      -�� ���α׷��� 2���� �迭�� ����� ������ �����ϴ� ���α׷��̴�.
*���α׷� �ۼ��� : ��ΰ�(2022�� 03�� 12��)
*���� Update : Version 1.1, 2022�� 03�� 17��(��ΰ�)
*============================================================================
*���α׷� ����/���� �̷�
*============================================================================
*���α׷� ����/�����۾���   ����   ����/���ϳ���
*��ΰ�      2022/03/12      v1.1   �ּ��� �ۼ�
*============================================================================
*/
#include<stdio.h>
#define SIZE 5
#define MTRX_SIZE 5
void printMtrx(double mA[][SIZE], int size_n);
void printMtrx(double mA[][SIZE], int size);
void addMtrx(double mA[][MTRX_SIZE], double mB[][MTRX_SIZE], double mR[][MTRX_SIZE], int size); //�迭�� ����
void subMtrx(double mA[][MTRX_SIZE], double mB[][MTRX_SIZE], double mR[][MTRX_SIZE], int size); //�迭�� ����
void mulMtrx(double mA[][MTRX_SIZE], double mB[][MTRX_SIZE], double mR[][MTRX_SIZE], int size); //�迭�� ����

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
			mR[i][j] = 0; //�迭 �ʱ�ȭ
			for (int k = 0; k < size; k++)
				mR[i][j] += mA[i][k] * mB[k][j];
		}
}