#include <math.h>
#include "Matrix.h"
#include "Operation.h"

void checkAddress_2DimArray_for_Matrix(); //2차원 배열 주소 확인 테스트
void test_2D_DynamicArray_FileIO_Statistics();  //2차원 배열의 통계치
void test_Matrix_Addition_Subtraction();  //2차원 배열의 합과 차 계산
void test_Matrix_Multiplication(); //2차원 배열의 곱셈

int main(void)
{
	int menu;

	while (1)
	{
		printf("Testing Matrix Operation with 2 - Dimentsional Dynamic Array \n");
		printf(" 1:Check addresses of 2-Dim array for Matrix\n");
		printf(" 2:Test 2-D Dynamic Array Creation for Matrix with File I/O\n");
		printf(" 3:Test Matrix Addition, Subtraction\n");
		printf(" 4:Test Matrix Multiplication\n");
		printf("-1:Quit\n");
		printf("Input menu (-1 to quit) : ");
		scanf("%d", &menu);
		if (menu == -1)
			break;
		switch (menu)
		{
		case 1:
			checkAddress_2DimArray_for_Matrix();
			break;
		case 2:
			test_2D_DynamicArray_FileIO_Statistics();
			break;
		case 3:
			test_Matrix_Addition_Subtraction();
			break;
		case 4:
			test_Matrix_Multiplication();
			break;
		}
	}
	return 0;
}

void checkAddress_2DimArray_for_Matrix()
{
	double** dMA;
	int row_size = 3;
	int col_size = 3;
	dMA = createDoubleArray(row_size, col_size);
	checkAddress_2DimArray_for_Matrix(dMA, row_size, col_size);
	deleteDoubleMtrx(dMA, row_size);
}
void test_2D_DynamicArray_FileIO_Statistics()
{
	const char* matrixDataFile = "mtrxInputData.txt";
	FILE* fin;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	double** dMA, ** dMB, ** dMR;

	fin = fopen(matrixDataFile, "r");
	if (fin == NULL)
	{
		printf("Error in opening input.txt file !! \n");
		exit(-1);
	}
	fscanf(fin, "%d %d", &a_row_size, &a_col_size); //행 렬 길이 받기
	dMA = fgetDoubleMtrx(fin, a_row_size, a_col_size); //파일에서 배열 입력 받기
	printf("Input Matrix_A(%d x %d) : \n", a_row_size, a_col_size);
	printMtrx(dMA, a_row_size, a_col_size); //출력
	printf("\n");
	dMR = getStatisticsMtrx(dMA, a_row_size, a_col_size);  //배열의 통계치를 임시 배열에 넣기
	printf("Matrix_A(%d x %d) with row & col averages : \n", a_row_size, a_col_size); 
	printMtrx(dMR, a_row_size + 1, a_col_size + 1); //통계를 저장한 배열 출력
	printf("\n");
	deleteDoubleMtrx(dMR, a_row_size + 1); //배열 지우기

	fscanf(fin, "%d %d", &b_row_size, &b_col_size);
	dMB = fgetDoubleMtrx(fin, b_row_size, b_col_size);
	printf("Input Matrix_B(%d x %d) : \n", b_row_size, b_col_size);
	printMtrx(dMB, b_row_size, b_col_size);
	printf("\n");
	dMR = getStatisticsMtrx(dMB, b_row_size, b_col_size);
	printf("Matrix_B(%d x %d) with row & col averages : \n", b_row_size, b_col_size);
	printMtrx(dMR, b_row_size + 1, b_col_size + 1);
	printf("\n");
	deleteDoubleMtrx(dMR, b_row_size + 1);

	deleteDoubleMtrx(dMA, a_row_size); //동적 메모리 반납
	deleteDoubleMtrx(dMB, b_row_size);
	fclose(fin);//파일 닫기
}

void test_Matrix_Addition_Subtraction()
{
	const char* matrixDataFile = "mtrx_nxn_InputData.txt"; //3x5배열 두개가 있는 파일 받기
	FILE* fin;

	double** dMA, ** dMB, ** dMC, ** dMD;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	int c_row_size, c_col_size;
	int d_row_size, d_col_size;

	fin = fopen(matrixDataFile, "r");
	if (fin == NULL)
	{
		printf("Error in opening input.txt file !! \n");
		exit(-1);
	}
	fscanf(fin, "%d %d", &a_row_size, &a_col_size);  //행 렬 크기 가지고오기
	dMA = fgetDoubleMtrx(fin, a_row_size, a_col_size);  //파일에서 배열 받아오기
	printf("Input Matrix_A(%d x %d) : \n", a_row_size, a_col_size);
	printMtrx(dMA, a_row_size, a_col_size);
	printf("\n");

	fscanf(fin, "%d %d", &b_row_size, &b_col_size);
	dMB = fgetDoubleMtrx(fin, b_row_size, b_col_size);
	printf("Input Matrix_B(%d x %d) : \n", b_row_size, b_col_size);
	printMtrx(dMB, b_row_size, b_col_size);
	printf("\n");

	if ((a_row_size != b_row_size) || (a_col_size != b_col_size))  //만약 사이즈가 같은 배열이 아니라면 오류 출력후 함수 탈출
	{
		printf("Error in input matrix dimension:row_size and/or cool_size are not equal !!\n");
		fclose(fin);
		return;
	}
	//MC = MA + MB
	c_row_size = a_row_size;
	c_col_size = b_col_size;
	dMC = createDoubleArray(c_row_size, c_col_size);
	addMtrx(dMA, dMB, dMC, c_row_size, c_col_size); //배열 덧셈
	printf("Matrix_C(%d x %d) = Matrix_A + Matrix_B : \n", c_row_size, c_col_size);
	printMtrx(dMC, c_row_size, c_col_size);
	printf("\n");

	//MD = MA - MB
	d_row_size = a_row_size;
	d_col_size = b_col_size;
	dMD = createDoubleArray(d_row_size, d_col_size);
	subtractMtrx(dMA, dMB, dMD, d_row_size, d_col_size); //배열 뺄셈
	printf("Matrix_D(%d x %d) = Matrix_A - Matrix_B : \n", d_row_size, d_col_size);
	printMtrx(dMD, d_row_size, d_col_size);
	printf("\n");

	deleteDoubleMtrx(dMA, a_row_size);  //동적 메모리 반납
	deleteDoubleMtrx(dMB, b_row_size);
	deleteDoubleMtrx(dMC, a_row_size);
	deleteDoubleMtrx(dMD, b_row_size);
	fclose(fin);
}

void test_Matrix_Multiplication()
{
	const char* matrixDataFile = "mtrxInputData.txt";
	FILE* fin;

	double** dMA, ** dMB, ** dMC;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	int c_row_size, c_col_size;
	int d_row_size, d_col_size;

	fin = fopen(matrixDataFile, "r");
	if (fin == NULL)
	{
		printf("Error in opening input.txt file !! \n");
		exit(-1);
	}

	fscanf(fin, "%d %d", &a_row_size, &a_col_size);  //행 렬 크기 가지고오기
	dMA = fgetDoubleMtrx(fin, a_row_size, a_col_size);  //파일에서 배열 받아오기
	printf("Input Matrix_A(%d x %d) : \n", a_row_size, a_col_size);
	printMtrx(dMA, a_row_size, a_col_size);
	printf("\n");
	
	fscanf(fin, "%d %d", &b_row_size, &b_col_size);
	dMB = fgetDoubleMtrx(fin, b_row_size, b_col_size);
	printf("Input Matrix_B(%d x %d) : \n", b_row_size, b_col_size);
	printMtrx(dMB, b_row_size, b_col_size);
	printf("\n");

	//MC = MA + MB
	c_row_size = a_row_size;
	c_col_size = b_col_size;
	dMC = createDoubleArray(c_row_size, c_col_size);
	multiplyMtrx(dMA, dMB, dMC, c_row_size, c_col_size, b_row_size); //배열 덧셈
	printf("Matrix_C(%d x %d) = Matrix_A * Matrix_B : \n", c_row_size, c_col_size);
	printMtrx(dMC, c_row_size, c_col_size);
	printf("\n");

	deleteDoubleMtrx(dMA, a_row_size);  //동적 메모리 반납
	deleteDoubleMtrx(dMB, b_row_size);
	deleteDoubleMtrx(dMC, a_row_size);
	fclose(fin);
}
