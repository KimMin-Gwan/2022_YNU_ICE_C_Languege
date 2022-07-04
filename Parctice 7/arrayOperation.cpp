#include "Matrix.h"
#include "Operation.h"


double** getStatisticsMtrx(double** mA, int row_size, int col_size)
{
	double** dM;
	double row_avg[SIZE] = { 0 };
	double col_avg[SIZE] = { 0 };
	double total_avg = 0;

	for (int i = 0; i < row_size; i++)
	{
		row_avg[i] = getRow_avg(mA, i, col_size); //행의 평균
	}
	for (int i = 0; i < col_size; i++)
	{
		col_avg[i] = getcol_avg(mA, row_size, i);  //열의 평균
	}

	total_avg = gettotal_avg(mA, row_size, col_size); // 전체 평균

	dM = createDoubleArray(row_size+1, col_size+1); //반납할 배열 만들기
	int i = 0;
	int j = 0;
	int m = 0;
	for (; m < row_size+1; m++)
	{
		for (int n = 0; n < col_size+1; n++)
		{
			if ((m != row_size) && (n != col_size)) //값을 복사
			{
				dM[m][n] = mA[m][n];
			}
			else if ((m == row_size) && (n == col_size)) //전체 값은 맨마지막 칸
			{
				dM[m][n] = total_avg;
			}
			else if ((m != row_size) && (n == col_size)) //행이 끝날때마다 행 평균
			{
				dM[m][n] = row_avg[i];
				i++;
			}
			else if ((m == row_size) && (n != col_size)) //마지막 열에는 열 평균 나열
			{
				dM[m][n] = col_avg[j];
				j++;
			}
		}
	}
	return dM;
	
}

double getRow_avg(double** array, int row, int col_size)
{
	double sum = 0.0, row_avg;

	for (int c = 0; c < col_size; c++)
	{
		sum += array[row][c];
	}
	row_avg = sum / (double)col_size;
	return row_avg;
}
double getcol_avg(double** array, int row_size, int col)
{
	double sum = 0.0, col_avg;

	for (int r = 0; r < row_size; r++)
	{
		sum += array[r][col];
	}
	col_avg = sum / (double)row_size;
	return col_avg;
}
double gettotal_avg(double** array, int row_size, int col_size)
{
	double sum = 0.0, avg;

	for (int r = 0; r < row_size; r++)
	{
		for (int c = 0; c < col_size; c++)
		{
			sum += array[r][c];
		}
	}
	avg = sum / (double)(row_size * col_size);
	return avg;
}

void addMtrx(double** mA, double** mB, double** mR, int row_size, int col_size)
{
	for (int r = 0; r < row_size; r++)
	{
		for (int c = 0; c < col_size; c++)
		{
			mR[r][c] = mA[r][c] + mB[r][c];
		}
	}
}

void subtractMtrx(double** mA, double** mB, double** mR, int row_size, int col_size)
{
	for (int r = 0; r < row_size; r++)
	{
		for (int c = 0; c < col_size; c++)
		{
			mR[r][c] = mA[r][c] - mB[r][c];
		}
	}
}

void multiplyMtrx(double** mA, double** mB, double** mR, int row_size, int col_size, int n_col_size)
{
	for (int r = 0; r < row_size; r++)
	{
		for (int c = 0; c < col_size; c++)
		{
			mR[r][c] = 0;
			printf("계산위치 :( %d , %d )\n", r, c);
			for (int k = 0; k < n_col_size; k++) {
				mR[r][c] += mA[r][k] * mB[k][c];
				printf("\n%5.2lf * %5.2lf = %5.2lf", mA[r][k], mB[k][c], mA[r][k] * mB[k][c]);
				printf("\n현재 곱셈의합 : %5.2lf", mR[r][c]);
			}
			
			printf("\n행 계산 끝 결과 : %5.2lf\n", mR[r][c]);
			printf("\n");
		}
		printf("\n");
	}
}