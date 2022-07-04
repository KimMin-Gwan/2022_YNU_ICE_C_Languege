#include "Mtrx.h"

double** fGetMtrx(FILE* fin, int* row_size, int* col_size)
{
	double** dMA;
	int row = 0;
	int col = 0;
	fscanf(fin, "%d", &row);
	*row_size = row;
	if (col_size == NULL)
		col = row;
	else
	{
		fscanf(fin, "%d", &col);
		*col_size = col;
	}
	dMA = fgetDoubleMtrx(fin, row, col); //파일에서 배열 입력 받기
	return dMA;
}

double** fgetDoubleMtrx(FILE* fp, int row_size, int col_size) //파일에서 2차원 배열 받아오기
{
	double data = 0.0; //임시로 값을 받을 변수
	double** dM; //배열 포인터
	if (fp == NULL)
	{
		printf("Error in getDoubleMatrixData() - file pointer is NULL !!\n");
		exit(-1);
	}
	dM = createDoubleArray(row_size, col_size);  //2차원 배열 할당
	for (int m = 0; m < row_size; m++)
	{
		for (int n = 0; n < col_size; n++)
		{
			if (fscanf(fp, "%lf", &data) != EOF)
				dM[m][n] = data; //한칸씩 데이터 받아 넣기
		}
	}
	return dM; //만들어낸 2차원 동적 배열 반환
}

double** createDoubleArray(int row_size, int col_size)
{
	double** ppDA; //할당된 메모리를 가르킬 이중 포인터 ppDA
	ppDA = (double**)calloc(row_size, sizeof(double*)); //행들의 배열을 할당
	for (int r = 0; r < row_size; r++)
	{
		*(ppDA + r) = (double*)calloc(col_size, sizeof(double)); //행마다 1차원 배열을 할당
	}
	return ppDA; //할당된 메모리를 가르키는  이중포인터 ppDA를 이중 포인터 형태로 반환
}

void deleteDynMtrx(double** dM, int row_size)
{
	for (int r = 0; r < row_size; r++)
	{
		free(*(dM + r)); //각 행마다 배열을 반환(각각 열을 반환)
	}
	free(dM); //행을 반환
}

void printMtrx(double** mA, int row_size, int col_size)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
	for (int i = 0; i < row_size; i++) 
	{
		for (int j = 0; j < col_size; j++)
		{
			if ((i == 0) && (j == 0))
				printf("%c%c%9.2lf", a6, a3, mA[i][j]); //첫부분
			else if ((i == 0) && j == (col_size - 1))
				printf("%9.2lf%c%c", mA[i][j], a6, a4); //첫줄의 끝부분
			else if ((i > 0) && (i < row_size - 1) && (j == 0))
				printf("%c%c%9.2lf", a6, a2, mA[i][j]);  //세로 막대기
			else if ((i > 0) && (i < row_size - 1) && (j == (col_size - 1)))
				printf("%9.2lf%c%c", mA[i][j], a6, a2);  //세로 막대기
			else if ((i == (row_size - 1)) && (j == 0))
				printf("%c%c%9.2lf", a6, a6, mA[i][j]);  //끝줄의 첫부분
			else if ((i == (row_size - 1)) && (j == (col_size - 1)))
				printf("%9.2lf%c%c", mA[i][j], a6, a5);  //끝줄의 끝부분
			else
				printf("%9.2lf", mA[i][j]);  //이외 위치 숫자 출력
		}
		printf("\n");
	}
	printf("\n");
}

void fprintMtrx(FILE* fout, double** mA, int row_size, int col_size)   //2차원 배열 출력
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++)
		{
			if ((i == 0) && (j == 0))
				fprintf(fout, "%c%c%9.2lf", a6, a3, mA[i][j]); //첫부분
			else if ((i == 0) && j == (col_size - 1))
				fprintf(fout, "%9.2lf%c%c", mA[i][j], a6, a4); //첫줄의 끝부분
			else if ((i > 0) && (i < row_size - 1) && (j == 0))
				fprintf(fout, "%c%c%9.2lf", a6, a2, mA[i][j]);  //세로 막대기
			else if ((i > 0) && (i < row_size - 1) && (j == (col_size - 1)))
				fprintf(fout, "%9.2lf%c%c", mA[i][j], a6, a2);  //세로 막대기
			else if ((i == (row_size - 1)) && (j == 0))
				fprintf(fout, "%c%c%9.2lf", a6, a6, mA[i][j]);  //끝줄의 첫부분
			else if ((i == (row_size - 1)) && (j == (col_size - 1)))
				fprintf(fout, "%9.2lf%c%c", mA[i][j], a6, a5);  //끝줄의 끝부분
			else
				fprintf(fout, "%9.2lf", mA[i][j]);  //이외 위치 숫자 출력
		}
		fprintf(fout, "\n");
	}
}

double** addMatrix(double** mA, double** mB, int row_size, int col_size)  //배열합
{
	double** mR = createDoubleArray(row_size, col_size);
	for (int r = 0; r < row_size; r++)
	{
		for (int c = 0; c < col_size; c++)
		{
			mR[r][c] = mA[r][c] + mB[r][c];
		}
	}
	return mR;
}

double** subtractMatrix(double** mA, double** mB, int row_size, int col_size)  //배열차
{
	double** mR = createDoubleArray(row_size, col_size);
	for (int r = 0; r < row_size; r++)
	{
		for (int c = 0; c < col_size; c++)
		{
			mR[r][c] = mA[r][c] - mB[r][c];
		}
	}
	return mR;
}

double** multiplyMatrix(double** mA, double** mB, int row_size, int col_size, int n_col_size)
{
	double** mR = createDoubleArray(row_size, col_size);
	for (int r = 0; r < row_size; r++)
	{
		for (int c = 0; c < col_size; c++)
		{
			mR[r][c] = 0;
			for (int k = 0; k < n_col_size; k++)
				mR[r][c] += mA[r][k] * mB[k][c];
		}
	}
	return mR;
}
