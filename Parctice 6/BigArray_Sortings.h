#pragma once

#ifndef BIG_ARRAY_SORTINGS_H
#define BIG_ARRAY_SORTINGS_H
#include <stdio.h>
#include <stdlib.h>
#define QUICK_SELECTION_THRESHOLD 10
void mergeSort(int* array, int size);
void selectionSort(int* array, int size);
void quickSort(int* array, int size);
void hybridQuickSelectionSort(int* bigArray, int size);
void _hybridQuickSelectionSort(int* bigArray, int size, int left, int right);
void hybridQuickSelectionSort(int* bigArray, int size);
//void Hy_selectionSort(int* array, int size, int left, int right);  hybridQuickSelectionSort�ȿ� �����Ͽ��⿡ �ּ�ó��
#endif