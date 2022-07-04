#include "Matrix.h"
void checkAddress_2DimArray_for_Matrix(double** m, int row_size, int col_size)
{
	printf("m        = %p\n", m);  //m ���� �迭�� ù��° ���� �ּ�
	printf("m[0]     = %p\n", m[0]);  //m ���� �迭�� ù��° ���� �ּ�
	printf("m[1]     = %p\n", m[1]);  
	printf("m[2]     = %p\n", m[2]);
	printf("&m[0][0] = %p\n", &m[0][0]); //m ���� �迭�� ù��° ���� �ּ�
	printf("&m[1][0] = %p\n", &m[1][0]);
	printf("&m[2][0] = %p\n", &m[2][0]);
	printf("\n");
}

double** createDoubleArray(int row_size, int col_size)
{
	double** ppDA; //�Ҵ�� �޸𸮸� ����ų ���� ������ ppDA
	ppDA = (double**)calloc(row_size, sizeof(double*)); //����� �迭�� �Ҵ�
	for (int r = 0; r < row_size; r++)
	{
		*(ppDA + r) = (double*)calloc(col_size, sizeof(double)); //�ึ�� 1���� �迭�� �Ҵ�
	}
	return ppDA; //�Ҵ�� �޸𸮸� ����Ű��  ���������� ppDA�� ���� ������ ���·� ��ȯ
}

void deleteDoubleMtrx(double** dM, int row_size)
{
	for (int r = 0; r < row_size; r++)
	{
		free(*(dM + r)); //�� �ึ�� �迭�� ��ȯ(���� ���� ��ȯ)
	}
	free(dM); //���� ��ȯ
}

double** fgetDoubleMtrx(FILE* fp, int row_size, int col_size)
{
	double data = 0.0; //�ӽ÷� ���� ���� ����
	double** dM; //�迭 ������

	if (fp == NULL)
	{
		printf("Error in getDoubleMatrixData() - file pointer is NULL !!\n");
		exit(-1);
	}
	dM = createDoubleArray(row_size, col_size);  //2���� �迭 �Ҵ�
	for (int m = 0; m < row_size; m++)
	{
		for (int n = 0; n < col_size; n++)
		{
			if (fscanf(fp, "%lf", &data) != EOF)
				dM[m][n] = data; //��ĭ�� ������ �޾� �ֱ�
		}
	}
	return dM; //���� 2���� ���� �迭 ��ȯ
}

void printMtrx(double** mA, int row_size, int col_size)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++)
		{
			if ((i == 0) && (j == 0))
				printf("%c%c%9.2lf", a6, a3, mA[i][j]); //ù�κ�
			else if ((i == 0) && j == (col_size - 1))
				printf("%9.2lf%c%c", mA[i][j], a6, a4); //ù���� ���κ�
			else if ((i > 0) && (i < row_size - 1) && (j == 0))
				printf("%c%c%9.2lf", a6, a2, mA[i][j]);  //���� �����
			else if ((i > 0) && (i < row_size - 1) && (j == (col_size - 1)))
				printf("%9.2lf%c%c", mA[i][j], a6, a2);  //���� �����
			else if ((i == (row_size - 1)) && (j == 0))
				printf("%c%c%9.2lf", a6, a6, mA[i][j]);  //������ ù�κ�
			else if ((i == (row_size - 1)) && (j == (col_size - 1)))
				printf("%9.2lf%c%c", mA[i][j], a6, a5);  //������ ���κ�
			else
				printf("%9.2lf", mA[i][j]);  //�̿� ��ġ ���� ���
		}
		printf("\n");
	}
}

