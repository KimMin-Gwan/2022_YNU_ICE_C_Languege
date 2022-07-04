#include "GaussJordan_LinearSystem.h"

double** getAugmentedMatrixData(FILE* fin, double**dAugM, int row_size)
{
	double d = 0.0;
	int col_size = row_size+1;
	if (dAugM == NULL)
	{
		printf("Error");
		exit(-1);
	}
	for (int m = 0; m < row_size; m++)
		for (int n = 0; n < col_size; n++)
		{
			if (fscanf(fin, "%lf", &d) != EOF)
				dAugM[m][n] = d;
		}
	return dAugM;
}

void pivoting(double** augMtrx, int size_N, int p, int* piv_found)
{
	double xmax = 0.0, xtemp;
	int j, k, max_row;
	xmax = fabs(augMtrx[p][p]); //부동소숫점의 절댓값 연산, (p,p)의 value를 xmax로 지정
	max_row = p; //일단 초기 값을 현재 값으로 선정
	for (j = p + 1; j < size_N; j++)
	{
		if (fabs(augMtrx[j][p]) > xmax) 
		{
			xmax = fabs(augMtrx[j][p]);//피벗 열에서 가장 절댓값이 행을 찾는다.
			max_row = j;
		} 
	} 

	if (fabs(xmax) < EPSILON) // EPSILON = 0.000001, 너무 값이 작아서 0과 같다고 판단
	{
		*piv_found = 0; //값을 찾을 수 없다. false
	}
	else 
	{
		*piv_found = 1; //값을 찾을 수 있다. true
		if (max_row != p)  //절댓값이 가장 큰 value가 있던 행을 초기 행과 교환
		{
			for (k = p; k <= size_N; k++) 
			{
				xtemp = augMtrx[p][k];
				augMtrx[p][k] = augMtrx[max_row][k];
				augMtrx[max_row][k] = xtemp;
			} 
		} 
	} 
} 

void diagonalize_FileOut(FILE* fout, double** mtrxAug, int size_N, int* solExist)
{
	int j, k, p = 0; // pivot index
	double pivWeight, w;
	// Pivoting and Scaling
	for (p = 0; (*solExist) && (p < size_N); p++)
	{
		fprintf(fout, "\nPivoting at p = %d\n", p);
		pivoting(mtrxAug, size_N, p, solExist); //피벗 포인트 설정
		fprintMtrx(fout, mtrxAug, size_N, size_N + 1);

		if (*solExist) //scailling 
		{
			if (mtrxAug[p][p] != 1.0)  //피벗의 값이 1이 아니라면 피벗값을 1로 조정
			{
				pivWeight = mtrxAug[p][p]; //pivWeight는 피벗 위치 값의 크기
				mtrxAug[p][p] = 1.0; // 우선 피벗위치의 값은 1로 변경
				for (k = p + 1; k <= size_N; k++)  //피벗행의 값을 피벗 자리에 있던 값으로 나눠줌
				{
					mtrxAug[p][k] /= pivWeight;
				} 
			} 
		}
		else //피벗행에 값이 0이면 해답이 없다.
		{
			break;
		}
		fprintf(fout, "\nAfter scaling at p = %d\n", p);
		fprintMtrx(fout, mtrxAug, size_N, size_N + 1);
		// Diagonalize
		for (j = 0; j < size_N; j++) //피벗행을 기준으로 위아래 행에서 피벗과 같은 열의 값을 모두 0으로 바꿔줌
		{ 
			if ((j != p) && (mtrxAug[j][p] != 0.0)) //행에 값이 0이 아니고, 진행되는 j가 피벗행을 지목하지 않을때
			{
				w = mtrxAug[j][p]; // 피벗행에 곱해질 해당 열의 값
				mtrxAug[j][p] = 0.0; //우선 해당 행에 피벗과 같은 열에 있는 value를 0으로 바꿔주고 
				for (k = p + 1; k <= size_N; k++)
				{
					mtrxAug[j][k] = mtrxAug[j][k] - w * mtrxAug[p][k]; // 피벗행에 크기w를 곱해서 각 행렬에 뺄셈을 진행 
				}
			}
		} 
		fprintf(fout, "\nAfter diagonalizing at p = %d\n", p);
		fprintMtrx(fout, mtrxAug, size_N, size_N + 1);
	}
}

void invMtrxGaussJordanElim_FileOut(FILE* fout, double** mA, double** mInv, int size_N, int* solExist)
{
	int j, k, p = 0; // pivot index
	double pivWeight, w;
	double** mAUG; // N x 2N크기 행렬
	//원래 행렬과 대각행렬로 이루어진 N x 2N크기의 행렬만들기
	mAUG = (double**)calloc(size_N, sizeof(double*)); //2차원 동적 메모리 배열 생성
	for (int i = 0; i < size_N; i++)
		mAUG[i] = (double*)calloc(size_N * 2, sizeof(double));

	for (j = 0; j < size_N; j++) 
	{
		for (k = 0; k < size_N; k++)//앞부분은 원래 행렬 체워넣기
			mAUG[j][k] = mA[j][k];
		for (k = size_N; k < size_N * 2; k++) //뒷부분은 1과 0으로 이루어진 대각행렬 만들기
			mAUG[j][k] = (k == (j + size_N)) ? 1.0 : 0.0;
	} 
	//scaling과 diagonalizing을 통하여 앞부분을 대각행렬로바꿔줌


	for (p = 0; p < size_N; p++) //scaling 
	{
		if (mAUG[p][p] == 0.0)
			* solExist == 0;
		if (*solExist) //scailling 
		{
			if (mAUG[p][p] != 1.0) //피벗의 값이 1이 아니라면 피벗값을 1로 조정
			{
				pivWeight = mAUG[p][p]; // 스케일링 할 피벗의 크기
				mAUG[p][p] = 1.0; //우선 피벗 위치를 1로 변경
				for (k = p + 1; k < size_N * 2; k++)
				{
					mAUG[p][k] /= pivWeight; //나머지 열을 모두 피벗의 크기로 나눠줌
				}
			}
			fprintf(fout, "After scaling at p = %d\n", p);
			fprintMtrx(fout, mAUG, size_N, size_N * 2);
		}
		else //피벗행에 값이 0이면 해답이 없다.
		{
			break;
		}

		for (j = 0; j < size_N; j++) //diagonalizing
		{
			if ((j != p) && (mAUG[j][p] != 0.0))
			{
				w = mAUG[j][p]; // 피벗행에 곱해질 해당 열의 값
				mAUG[j][p] = 0.0; //우선 해당 값을 0으로 바꿔주고
				for (k = p + 1; k < 2 * size_N; k++)
				{
					mAUG[j][k] -= w * mAUG[p][k]; // 나머지 행에 있는 값은 전부다 w를 곱해서 빼준다.
				}
			} 
		} 
		fprintf(fout, "After diagonalizing at p = %d\n", p);
		fprintMtrx(fout, mAUG, size_N, size_N * 2);
		
	} 
	//printMtrx(mAUG, size_N, size_N * 2);
	//만들어낸 역행렬을 mInv에 담아서 보낸다.
	for (j = 0; j < size_N; j++)
	{
		for (k = 0; k < size_N; k++)
		{
			mInv[j][k] = mAUG[j][k + size_N]; //앞부분 대각행렬을 재외하고 뒷부분을 mlnv에 넣어서 반환
		}
	} 
}