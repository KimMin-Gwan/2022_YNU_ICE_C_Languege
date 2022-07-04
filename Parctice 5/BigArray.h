/**
*파일명 : "프로그래밍 언어 21912229_김민관_실습 5"
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 배열을 생성하거나 만들어진 배열을 분석하여
*		최대, 최소, 평균, 분산, 표준편차를 계산한다. 
*		계산된 값을 출력하는 프로그램이다.
*프로그램 작성자 : 김민관(2022년 03월 27일)
*최종 Update : Version 1.5, 2022년 04월 01일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
*김민관   22/03/29  V1.1 getarraystatistics에서 계산하는 부분을 때어냄
*김민관   22/03/30  V1.2 출력하는 부분을 간소화시킴
*김민관   22/03/31  V1.3 동적 메모리를 할당 받아서 통계메모리를 저장
*김민관   22/04/01  V1.4 동적 메모리를 일반 배열로 바꾸어 값을 저장
*김민관   22/04/01  V1.5 사용하지 않는 변수 정리, 최적화
*============================================================================
*/
#ifndef BIG_ARRAY_H
#define BIG_ARRAY_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

enum statistics_name { min = 0, max, sum, avg, var, SD };
void printBigArraySample(int* array, int size, int line_size, int num_line);  //아주 큰 배열 출력
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int num_line);  //아주 큰 배열 파일에 출력
void getBigRandArray(int* array, int size, int base); //랜덤 숫자 생성
void getArrayStatistics(int* array, int size);  // 분석하여 출력
void fgetArrayStatistics(FILE* fout, int* array, int size);  //분석하여 파일에 출력
void statistics(int* arr, double* save, int size); //statistics의 중복 부분을 분리
int fgetArrayFromFile(const char* fin_name, int* array, int max_size); //파일에서 데이터를 가지고와서 저장
#endif