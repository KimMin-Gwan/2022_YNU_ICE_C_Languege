/**
*파일명 : "프로그램밍 언어_21912229_김민관_실습_8"
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 파일로 부터 배열을 입력받아 출력하고
*		덧셈과 뺄셈을 계산, 곱셈을 연산한다. 또,
*		가우스 조던을 이용한 연립다항식의 해를 구하고, 역행렬을 이용하여
*		계산하는 과정과 비교하는 프로그램이다.
*프로그램 작성자 : 김민관(2022년 04월 21일)
*============================================================================
*/

#ifndef MYMTRX_H
#define MYMTRX_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 10
double** createDoubleArray(int row_size, int col_size); //2차원 배열 만들기
void deleteDynMtrx(double** dM, int row_size);  //2차원 배열 반납
void printMtrx(double** mA, int row_size, int col_size);   //2차원 배열 출력
double** fGetMtrx(FILE* fin, int* row_size, int* col_size = 0); //배열 받아오는 함수
double** fgetDoubleMtrx(FILE* fp, int row_size, int col_size); //파일에서 2차원 배열 받아오기
void fprintMtrx(FILE* fout, double** mA, int row_size, int col_size);   //2차원 배열 출력
double** addMatrix(double** mA, double** mB, int row_size, int col_size);  //배열합
double** subtractMatrix(double** mA, double** mB, int row_size, int col_size);  //배열차
double** multiplyMatrix(double** mA, double** mB, int row_size, int col_size, int n_col_size);  //배열곱

#endif