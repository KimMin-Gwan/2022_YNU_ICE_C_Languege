/**
*���ϸ� : "���α׷��� ��� 21912229_��ΰ�_�ǽ� 6"
*���α׷��� ���� �� �⺻ ���:
*      -�� ���α׷��� �迭�� �����Ͽ� SELETIONSORT, MERGESORT, QUICKSORT��
*		�����ϰ� SELETIONSORT�� QUICKSORT�� ������ HYBRIDQUICKSORT�� �����ϴ�
*		���α׷��̴�.
*���α׷� �ۼ��� : ��ΰ�(2022�� 04�� 03��)
*���� Update : Version 1.0, 2022�� 04�� 03��(��ΰ�)
*============================================================================
*���α׷� ����/���� �̷�
*============================================================================
*���α׷� ����/�����۾���   ����   ����/���ϳ���
*============================================================================
*/

#ifndef BIG_ARRAY_H
#define BIG_ARRAY_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void printBigArraySample(int* array, int size, int items_per_line =10, int num_sample_lines =2);
//void fprintBigArraySample(FILE* fout, int* array, int size, int items_per_line, int num_sample_lines);
void genBigRandArray(int* array, int size, int base);
void suffleArray(int* array, int size);

#endif