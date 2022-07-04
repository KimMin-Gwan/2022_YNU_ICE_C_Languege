/**
*���ϸ� : "���α׷��� ���_21912229_��ΰ�_�ǽ�_8"
*���α׷��� ���� �� �⺻ ���:
*      -�� ���α׷��� ���Ϸ� ���� �迭�� �Է¹޾� ����ϰ�
*		������ ������ ���, ������ �����Ѵ�. ��,
*		���콺 ������ �̿��� �������׽��� �ظ� ���ϰ�, ������� �̿��Ͽ�
*		����ϴ� ������ ���ϴ� ���α׷��̴�.
*���α׷� �ۼ��� : ��ΰ�(2022�� 04�� 21��)
*============================================================================
*/

#ifndef MYMTRX_H
#define MYMTRX_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 10
double** createDoubleArray(int row_size, int col_size); //2���� �迭 �����
void deleteDynMtrx(double** dM, int row_size);  //2���� �迭 �ݳ�
void printMtrx(double** mA, int row_size, int col_size);   //2���� �迭 ���
double** fGetMtrx(FILE* fin, int* row_size, int* col_size = 0); //�迭 �޾ƿ��� �Լ�
double** fgetDoubleMtrx(FILE* fp, int row_size, int col_size); //���Ͽ��� 2���� �迭 �޾ƿ���
void fprintMtrx(FILE* fout, double** mA, int row_size, int col_size);   //2���� �迭 ���
double** addMatrix(double** mA, double** mB, int row_size, int col_size);  //�迭��
double** subtractMatrix(double** mA, double** mB, int row_size, int col_size);  //�迭��
double** multiplyMatrix(double** mA, double** mB, int row_size, int col_size, int n_col_size);  //�迭��

#endif