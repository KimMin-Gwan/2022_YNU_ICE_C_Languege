/**
*���ϸ� : "���α׷��� ���_21912229_��ΰ�_�ǽ�_7"
*���α׷��� ���� �� �⺻ ���:
*      -�� ���α׷��� 2���� ���� �޸𸮸� �Ҵ�ް�, �迭�� ������ ���ġ��
*		���, ����, ����, ������ �����ϴ� ���α׷��̴�.
*���α׷� �ۼ��� : ��ΰ�(2022�� 04�� 10��)
*���� Update : Version 1.0, 2022�� 04�� 10��(��ΰ�)
*============================================================================
*���α׷� ����/���� �̷�
*============================================================================
*���α׷� ����/�����۾���   ����   ����/���ϳ���
*============================================================================
*/


#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <stdlib.h>
double** createDoubleArray(int row_size, int col_size); //2���� �迭 �����
void checkAddress_2DimArray_for_Matrix(double** dM, int row_size, int col_size); //2���� �迭 �׽�Ʈ
void deleteDoubleMtrx(double** dM, int row_size);  //2���� �迭 �ݳ�
double** fgetDoubleMtrx(FILE* fp, int row_size, int col_size); //���Ͽ��� 2���� �迭 �޾ƿ���
void printMtrx(double** mA, int row_size, int col_size);   //2���� �迭 ���
#endif