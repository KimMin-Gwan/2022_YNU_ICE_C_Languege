#ifndef OPERATION_H
#define OPERATION_H
#include <stdio.h>
#include <stdlib.h>
#define SIZE 5
double** getStatisticsMtrx(double** mA, int row_size, int col_size);  //�迭�� ��豸�ϱ�
double getRow_avg(double** array, int row, int col_size);  //���� ���
double getcol_avg(double** array, int row_size, int col);  //���� ���
double gettotal_avg(double** array, int col_size, int row);  //��ü ���
void addMtrx(double** mA, double** mB, double** mR, int row_size, int col_size);  //�迭��
void subtractMtrx(double** mA, double** mB, double** mR, int row_size, int col_size);  //�迭��
void multiplyMtrx(double** mA, double** mB, double** mR, int row_size, int col_size, int n_col_size);  //�迭��
#endif