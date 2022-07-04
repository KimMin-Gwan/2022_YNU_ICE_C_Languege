/**
*���ϸ� : "���α׷��� ��� 21912229_��ΰ�_�ǽ� 5"
*���α׷��� ���� �� �⺻ ���:
*      -�� ���α׷��� �迭�� �����ϰų� ������� �迭�� �м��Ͽ�
*		�ִ�, �ּ�, ���, �л�, ǥ�������� ����Ѵ�. 
*		���� ���� ����ϴ� ���α׷��̴�.
*���α׷� �ۼ��� : ��ΰ�(2022�� 03�� 27��)
*���� Update : Version 1.5, 2022�� 04�� 01��(��ΰ�)
*============================================================================
*���α׷� ����/���� �̷�
*============================================================================
*���α׷� ����/�����۾���   ����   ����/���ϳ���
*��ΰ�   22/03/29  V1.1 getarraystatistics���� ����ϴ� �κ��� ���
*��ΰ�   22/03/30  V1.2 ����ϴ� �κ��� ����ȭ��Ŵ
*��ΰ�   22/03/31  V1.3 ���� �޸𸮸� �Ҵ� �޾Ƽ� ���޸𸮸� ����
*��ΰ�   22/04/01  V1.4 ���� �޸𸮸� �Ϲ� �迭�� �ٲپ� ���� ����
*��ΰ�   22/04/01  V1.5 ������� �ʴ� ���� ����, ����ȭ
*============================================================================
*/
#ifndef BIG_ARRAY_H
#define BIG_ARRAY_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

enum statistics_name { min = 0, max, sum, avg, var, SD };
void printBigArraySample(int* array, int size, int line_size, int num_line);  //���� ū �迭 ���
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int num_line);  //���� ū �迭 ���Ͽ� ���
void getBigRandArray(int* array, int size, int base); //���� ���� ����
void getArrayStatistics(int* array, int size);  // �м��Ͽ� ���
void fgetArrayStatistics(FILE* fout, int* array, int size);  //�м��Ͽ� ���Ͽ� ���
void statistics(int* arr, double* save, int size); //statistics�� �ߺ� �κ��� �и�
int fgetArrayFromFile(const char* fin_name, int* array, int max_size); //���Ͽ��� �����͸� ������ͼ� ����
#endif