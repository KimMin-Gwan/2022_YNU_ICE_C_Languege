/* Gauss-Jordan.h*/
#ifndef GAUSS_JORDAN_H
#define GAUSS_JORDAN_H
#include "Mtrx.h"
#define EPSILON 0.000001
double** getAugmentedMatrixData(FILE * fin, double** dAugM, int pSize_N); //�迭 �޾ƿ���
void pivoting(double** augMtrx, int size_N, int p, int* piv_found); //�Ǻ���
void diagonalize_FileOut(FILE* fout, double** mtrxAug, int size_N, int* solExist);  //���콺 ����
void invMtrxGaussJordanElim_FileOut(FILE* fout, double** mA, double** mInv, int size_N, int* solExist); //������� ���ϴ� ���콺 ����
#endif