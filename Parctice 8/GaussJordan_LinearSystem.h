/* Gauss-Jordan.h*/
#ifndef GAUSS_JORDAN_H
#define GAUSS_JORDAN_H
#include "Mtrx.h"
#define EPSILON 0.000001
double** getAugmentedMatrixData(FILE * fin, double** dAugM, int pSize_N); //배열 받아오기
void pivoting(double** augMtrx, int size_N, int p, int* piv_found); //피보팅
void diagonalize_FileOut(FILE* fout, double** mtrxAug, int size_N, int* solExist);  //가우스 조던
void invMtrxGaussJordanElim_FileOut(FILE* fout, double** mA, double** mInv, int size_N, int* solExist); //역행렬을 구하는 가우스 조던
#endif