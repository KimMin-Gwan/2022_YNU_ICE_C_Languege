#ifndef OPERATION_H
#define OPERATION_H
#include <stdio.h>
#include <stdlib.h>
#define SIZE 5
double** getStatisticsMtrx(double** mA, int row_size, int col_size);  //배열의 통계구하기
double getRow_avg(double** array, int row, int col_size);  //행의 평균
double getcol_avg(double** array, int row_size, int col);  //열의 평균
double gettotal_avg(double** array, int col_size, int row);  //전체 평균
void addMtrx(double** mA, double** mB, double** mR, int row_size, int col_size);  //배열합
void subtractMtrx(double** mA, double** mB, double** mR, int row_size, int col_size);  //배열차
void multiplyMtrx(double** mA, double** mB, double** mR, int row_size, int col_size, int n_col_size);  //배열곱
#endif