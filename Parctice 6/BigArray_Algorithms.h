/**
*파일명 : "프로그래밍 언어 21912229_김민관_실습 6"
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 배열을 생성하여 SELETIONSORT, MERGESORT, QUICKSORT를
*		제작하고 SELETIONSORT와 QUICKSORT를 결합한 HYBRIDQUICKSORT를 구연하는
*		프로그램이다.
*프로그램 작성자 : 김민관(2022년 04월 03일)
*최종 Update : Version 1.0, 2022년 04월 03일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
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