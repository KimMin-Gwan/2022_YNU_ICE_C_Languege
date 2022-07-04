/** main_Matrx_GaussJordan_LinearSystem.cpp */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Mtrx.h"
#include "GaussJordan_LinearSystem.h"

const char* outputFile = "OutputResult.txt";
void test_2D_DynamicArray_FileIO(FILE* fout);
void test_MatrixAdditionSubtraction(FILE* fout);
void test_MatrixMultiplication(FILE* fout);
void test_GaussJordanElimination_LinearSystem(FILE* fout);
void test_InvMtrx_GaussJordanElimination_LinearSystem(FILE* fout);

int main(void)
{
	FILE * fout;  //file out 포인터
	int menu;
	fout = fopen(outputFile, "w"); //쓰기모드로 OutputResult 열기
	if (fout == NULL)
	{
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}
	while (1)
	{
		printf("Testing Matrix Operations with 2-Dimensional Dynamic Array\n");
		printf(" 1: Test 2-D Dynamic Array Creation for Matrix with File I/O\n");
		printf(" 2: Test Matrix Addition, Subtraction\n");
		printf(" 3: Test Matrix Multiplication\n");
		printf(" 4: Test Gauss-Jordan Elimination for Linear System\n");
		printf(" 5: Test Inverse Matrix with Gauss-Jordan Elimination for Linear System\n");
		printf(" 0: Quit\n");
		printf("Input menu (0 to quit) : ");
		scanf("%d", &menu);
		if (menu == 0)
			break;
		printf("\n");
		switch (menu)
		{
		case 1:
			test_2D_DynamicArray_FileIO(fout);  //파일 받아지는지 확인하는 테스트
			break;
		case 2:
			test_MatrixAdditionSubtraction(fout);  //덧셈 뺄셈 테스트
			break;
		case 3:
			test_MatrixMultiplication(fout);  //곱셈 테스트
			break;
		case 4:
			test_GaussJordanElimination_LinearSystem(fout);  //하나의 행씩 0으로 바꿔주는 가우스 조던 선형시스템
			break;
		case 5:
			test_InvMtrx_GaussJordanElimination_LinearSystem(fout); //역행렬을 곱해주는 가우스 조던 선형시스템
			break;
		default:
			break;
		}
		printf("\n");
	} // end while
	fclose(fout);
}

void test_2D_DynamicArray_FileIO(FILE* fout)
{
	const char* matrixDataFile = "mtrxInputData.txt";
	FILE* fin; //읽을 파일 포인터
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	double** mA, ** mB;
	fin = fopen(matrixDataFile, "r");  //읽기모드로 파일 열기
	if (fin == NULL)
	{
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}

	mA = fGetMtrx(fin, &a_row_size, &a_col_size); //A배열 받아오기
	printf("Input Matrix_A ( %d x %d) : \n", a_row_size, a_col_size);
	printMtrx(mA, a_row_size, a_col_size);
	printf("\n");

	mB = fGetMtrx(fin, &b_row_size, &b_col_size); //B배열 받아오기
	printf("Input Matrix_B ( %d x %d) : \n", b_row_size, b_col_size);
	printMtrx(mB, b_row_size, b_col_size);
	printf("\n");

	deleteDynMtrx(mA, a_row_size); //동적 메모리 할당 해제
	deleteDynMtrx(mB, b_row_size);
	fclose(fin);//파일닫기
}

void test_MatrixAdditionSubtraction(FILE* fout)
{
	const char* matrixDataFile = "mtrx_nxn_InputData.txt";
	FILE* fin; //읽을 파일 포인터
	double** mA, ** mB, ** mC, ** mD;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	int c_row_size, c_col_size;
	int d_row_size, d_col_size;
	fin = fopen(matrixDataFile, "r");  //일기모드로 파일열기
	if (fin == NULL)
	{
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}

	mA = fGetMtrx(fin, &a_row_size, &a_col_size); //A배열 받아오기
	printf("Input Matrix_A ( %d x %d) : \n", a_row_size, a_col_size);
	printMtrx(mA, a_row_size, a_col_size);
	printf("\n");

	mB = fGetMtrx(fin, &b_row_size, &b_col_size); //B배열 받아오기
	printf("Input Matrix_B ( %d x %d) : \n", b_row_size, b_col_size);
	printMtrx(mB, b_row_size, b_col_size);
	printf("\n");

	if ((a_row_size != b_row_size) || (a_col_size != b_col_size)) //만약 N x N 형태의 배열이 아닐경우 파일을 닫고 해당 프로세스 종료
	{
		printf("Error in input matrix dimension: row_size and/or col_size are not equal !!\n");
		fclose(fin);
		return;
	}
	
	c_row_size = a_row_size;
	c_col_size = b_col_size;
	mC = addMatrix(mA, mB, a_row_size, a_col_size); //A행렬과 B행렬을 더하여 C에 대입
	printf("Matrix_C (%d x %d) = Matrix_A + Matrix_B : \n", c_row_size, c_col_size);
	printMtrx(mC, c_row_size, c_col_size);

	d_row_size = a_row_size;
	d_col_size = b_col_size;
	mD = subtractMatrix(mA, mB, a_row_size, a_col_size);  //A행렬과 B행렬을 더하여 C에 대입
	printf("Matrix_D (%d x %d) = Matrix_A - Matrix_B : \n", d_row_size, d_col_size);
	printMtrx(mD, d_row_size, d_col_size);

	deleteDynMtrx(mA, a_row_size); //동적 메모리 할당 해제
	deleteDynMtrx(mB, b_row_size);
	deleteDynMtrx(mC, c_row_size);
	deleteDynMtrx(mD, d_row_size);
	fclose(fin);//파일닫기
}

void test_MatrixMultiplication(FILE* fout)
{
	const char* matrixDataFile = "mtrxInputData.txt";
	FILE* fin; //읽을 파일 포인터
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	int c_row_size, c_col_size;
	double** mA, ** mB, ** mC;
	fin = fopen(matrixDataFile, "r"); //읽기모드로 파일 열기
	if (fin == NULL)
	{
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}
	mA = fGetMtrx(fin, &a_row_size, &a_col_size); //A배열 받아오기
	printf("Input Matrix_A ( %d x %d) : \n", a_row_size, a_col_size);
	printMtrx(mA, a_row_size, a_col_size);

	mB = fGetMtrx(fin, &b_row_size, &b_col_size); //B배열 받아오기
	printf("Input Matrix_B ( %d x %d) : \n", b_row_size, b_col_size);
	printMtrx(mB, b_row_size, b_col_size);

	c_row_size = a_row_size;
	c_col_size = b_col_size;
	mC = multiplyMatrix(mA, mB, a_row_size, a_col_size, b_col_size); //A와 B를 곱해서 C에 대입
	printf("Matrix_C (%d x %d) = Matrix_A x Matrix_B : \n", c_row_size, c_col_size);
	printMtrx(mC, c_row_size, c_col_size);

	deleteDynMtrx(mA, a_row_size); //동적 메모리 할당 해제
	deleteDynMtrx(mB, b_row_size);
	deleteDynMtrx(mC, c_row_size);
	fclose(fin);//파일닫기
}
void test_GaussJordanElimination_LinearSystem(FILE* fout)
{
	const char* augMatrix_inputFile = "AugMtrx_ElectronicCircuit_B_5x5.txt";
	FILE* fin;
	int size_N;
	double* solution;
	double** augMtrx = NULL;
	int i, j, solExist = 1, error = 0;
	double d;
	fin = fopen(augMatrix_inputFile, "r");
	if (fin == NULL)
	{
		printf("Error in opening input.txt file (%s)!!\n", augMatrix_inputFile);
		exit(-1);
	}

	fscanf(fin, "%d", &size_N);
	augMtrx = createDoubleArray(size_N, size_N + 1); //배열 생성
	solution = (double*)calloc(size_N, sizeof(double)); // 미지수 값을 넣을 배열
	fprintf(fout, "Augmented Matrix size_N : %d\n", size_N);

	getAugmentedMatrixData(fin, augMtrx, size_N); //행렬 받아오기
	fprintf(fout, "Augmented Matrix : \n");
	fprintMtrx(fout, augMtrx, size_N, size_N + 1);
	printf("Augmented Matrix : \n");
	printMtrx(augMtrx, size_N, size_N + 1);

	diagonalize_FileOut(fout, augMtrx, size_N, &solExist); //행렬의 대각화 진행
	//printMtrx(augMtrx, size_N, size_N + 1);
	if (solExist) 
	{
		fprintf(fout, "The solution of the given linear system:\n");
		printf("The solution of the given linear system:\n");
		for (i = 0; i < size_N; i++) 
		{
			solution[i] = augMtrx[i][size_N];  //각 행의 마지막 열에는 미지수 값이다. solution에 대입해준다.
			fprintf(fout, " x[%d] : %4f\n", i, solution[i]);
			printf(" x[%d] : %4f\n", i, solution[i]);
		}
	}
	else //너무많은 해가 있거나, 해가 없다.
	{
		fprintf(fout, "No unique solution\n"); 
		printf("No unique solution\n");
	}
	deleteDynMtrx(augMtrx, size_N); //동적 메모리 할당 해제
	free(solution);
	fclose(fin); //파일닫기
}
void test_InvMtrx_GaussJordanElimination_LinearSystem(FILE* fout)
{
	const char* linearSystem_inputFile = "ElectronicCircuit_B_5x5.txt";

	FILE* fin;  //읽을 파일 포인터
	double** mA, ** inv_A, ** res, ** mE;
	int size_N = 0, solExist = 1; //행과 열의 사이즈는 같음
	double data; //E행렬을 받을 때 임시로 사용할 실수형 변수
	int a_row_size, a_col_size;
	fin = fopen(linearSystem_inputFile, "r"); //읽기모드로 파일 열기
	if (fin == NULL)
	{
		printf("Error in openning %s input file !!\n", linearSystem_inputFile);
		exit(-1);
	}
	
	mA = fGetMtrx(fin, &size_N); //A배열 받아오기
	fprintf(fout, "Matrix A: \n");
	fprintMtrx(fout, mA, size_N, size_N);
	printf("Matrix A: \n");
	printMtrx(mA, size_N, size_N);

	inv_A = createDoubleArray(size_N, size_N); //역행렬 생성
	invMtrxGaussJordanElim_FileOut(fout, mA, inv_A, size_N, &solExist); //역행렬 계산 후 inv_A에 대입
	fprintf(fout, " Inverse A: \n");
	fprintMtrx(fout, inv_A, size_N, size_N);
	printf(" Inverse A: \n");
	printMtrx(inv_A, size_N, size_N);

	if (solExist == 0)
		return;

	mE = createDoubleArray(size_N, size_N); //AX = E에서 E행렬 생성
	for (int i = 0; i < size_N; i++) 
	{
		fscanf(fin, "%lf", &data);
		mE[i][0] = data;
	}
	fprintf(fout, " mE: \n");
	fprintMtrx(fout, mE, size_N, 1);
	printf(" mE: \n");
	printMtrx(mE, size_N, 1);

	res = createDoubleArray(size_N, size_N); //결과행렬 생성
	res = multiplyMatrix(inv_A, mE, size_N, size_N, 1); //AX = E이므로 X = E*A^-1
	fprintf(fout, " Res = Inv_A x mE: \n");
	fprintMtrx(fout, res, size_N, 1);
	printf(" Res = Inv_A x mE: \n");
	printMtrx(res, size_N, 1);

	deleteDynMtrx(mA, size_N); //동적 메모리 할당 해제
	deleteDynMtrx(inv_A, size_N);
	deleteDynMtrx(mE, size_N); 
	deleteDynMtrx(res, size_N); 
	fclose(fin); //파일 닫기
}