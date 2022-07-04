#include "Matrix.h"
void checkAddress_2DimArray_for_Matrix(double** m, int row_size, int col_size)
{
	printf("m        = %p\n", m);  //m 동적 배열의 첫번째 열의 주소
	printf("m[0]     = %p\n", m[0]);  //m 동적 배열의 첫번째 열의 주소
	printf("m[1]     = %p\n", m[1]);  
	printf("m[2]     = %p\n", m[2]);
	printf("&m[0][0] = %p\n", &m[0][0]); //m 동적 배열의 첫번째 열의 주소
	printf("&m[1][0] = %p\n", &m[1][0]);
	printf("&m[2][0] = %p\n", &m[2][0]);
	printf("\n");
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

void deleteDoubleMtrx(double** dM, int row_size)
{
	for (int r = 0; r < row_size; r++)
	{
		free(*(dM + r)); //각 행마다 배열을 반환(각각 열을 반환)
	}
	free(dM); //행을 반환
}

double** fgetDoubleMtrx(FILE* fp, int row_size, int col_size)
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

void printMtrx(double** mA, int row_size, int col_size)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
	for (int i = 0; i < row_size; i++) {
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
}

