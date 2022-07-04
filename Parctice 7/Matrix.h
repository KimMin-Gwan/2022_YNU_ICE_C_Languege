/**
*파일명 : "프로그래밍 언어_21912229_김민관_실습_7"
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 2차원 동적 메모리를 할당받고, 배열의 내부의 통계치를
*		계산, 덧셈, 뺄셈, 곱셈을 수행하는 프로그램이다.
*프로그램 작성자 : 김민관(2022년 04월 10일)
*최종 Update : Version 1.0, 2022년 04월 10일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
*============================================================================
*/


#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <stdlib.h>
double** createDoubleArray(int row_size, int col_size); //2차원 배열 만들기
void checkAddress_2DimArray_for_Matrix(double** dM, int row_size, int col_size); //2차원 배열 테스트
void deleteDoubleMtrx(double** dM, int row_size);  //2차원 배열 반납
double** fgetDoubleMtrx(FILE* fp, int row_size, int col_size); //파일에서 2차원 배열 받아오기
void printMtrx(double** mA, int row_size, int col_size);   //2차원 배열 출력
#endif