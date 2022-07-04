
#include "BigArray.h" 
#define NUM_LINE 2    //�⺻ ���� ����
#define LINE_SIZE 10   //�⺻ ���� ������

void getBigRandArray(int* array, int bigRandSize, int base) //���� �Ŵ��� ���� ���� ������
{
	char* flag;
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand, bigRand_withOffset;

	flag = (char*)calloc(bigRandSize, sizeof(char)); //�ߺ��˻縦 �Ҷ� ����ϴ� ���� �޸�
	while (count < bigRandSize)
	{
		u_int32 = ((unsigned int)rand() << 15) | rand();  //15��Ʈ �о�� �ٽ� 15��Ʈ �ֱ�
		bigRand = u_int32 % bigRandSize;  //bigRandSize���� ���� ũ��� ����
		if (flag[bigRand] == 1)  //�ߺ��˻�, ���� 1�� �ִٸ�  �ٽ� ���� ������
		{
			continue;
		}
		else
		{
			flag[bigRand] = 1;
			bigRand_withOffset = bigRand + base;
			array[count++] = bigRand_withOffset;  //array�� ���� �Ҵ�
		}
	}
	free(flag);
}

void getArrayStatistics(int* array, int size, double* save) //�迭�� ��, �ּ�, �ִ�, ���, �л�, ǥ�������� ����ϰ� ���
{
	statistics(array, save, size);
	printf("Total (%3d) integer data : \n", size);
	printBigArraySample(array, size, LINE_SIZE, NUM_LINE);
	printf("min (%3.0lf), max(%3.0lf), sum(%8.2lf), average (%8.2lf), ", save[min], save[max], save[sum], save[avg]);
	printf("variance (%8.2lf), standard deviation (%8.2lf) \n", save[var], save[SD]);
}

void fgetArrayStatistics(FILE* fout, int* array, int size, double* save) // �迭�� ��, �ּ�, �ִ�, ���, �л�, ǥ�������� ����ϰ� ���Ͽ� ���
{
	fprintf(fout, "Total (%3d) integer data : \n", size);
	fprintBigArraySample(fout, array, size, LINE_SIZE, NUM_LINE);  //�迭�� ���Ͽ� ���
	fprintf(fout, "min (%3.0lf), max(%3.0lf), sum(%8.2lf), average (%8.2lf), ", save[min], save[max], save[sum], save[avg]);
	fprintf(fout, "variance (%8.2lf), standard deviation (%8.2lf) \n", save[var], save[SD]);
}

void statistics(int* arr, double* save, int size) //statistics�� �ι� ������ �ʱ� ���� ���
{
	int data = 0;
	double diff, sq_diff_sum = 0.0;

	for (int i = 0; i < size; i++)
	{
		data = arr[i];
		save[sum] += data;  //���� ���
		if (i == 0)  //�ִ� �ּҸ� �˾Ƴ�
		{
			save[min] = save[max] = arr[0];
		}
		else
		{
			if (data < save[min])
				save[min] = data;
			if (data > save[max])
				save[max] = data;
		}
	}
	save[avg] = save[sum] / (double)size;  //��հ��
	sq_diff_sum = 0.0;
	for (int i = 0; i < size; i++)  //�л���
	{
		diff = arr[i] - save[avg];
		sq_diff_sum += diff * diff;
	}
	save[var] = sq_diff_sum / (double)size;
	save[SD] = sqrt(var); //ǥ������ ���
}

void printBigArraySample(int* array, int size, int line_size, int num_line) //������ ���� ���� ��� (�տ��� 30�� �ڿ��� 30�� ���)
{
	int count = 1;
	if (size < 50000)  //5������ ������ ����ϴ� ���μ��� �ٲپ��� (�⺻ 2��)
	{
		num_line = size / line_size + 1;
	}
	for (int i = 0; i < num_line; i++)
	{

		for (int j = 0; j < line_size; j++, array++) //�ϳ��� ��� ���� ũ�⸸ŭ ����ϰ� \n
		{
			if (*array == 0 || *array == -1)
				break;
			printf("%8d", *array);
			count++;
		}
		printf("\n");
	}
	if (size > 50000)  //5������ ū ������� �ǵڿ��� ���� 20�� �� ���
	{
		printf("    .  .  .  .  .  . \n");

		for (int i = 0; i < num_line; i++)
		{
			for (int j = 0; j < line_size; j++, array--) //�� �ڿ��� ���� 20�� ���
			{
				printf("%8d", *(array + size - count));
			}
			printf("\n");
		}
	}
}

void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int num_line) //������ ���� ���� (�տ��� 30�� �ڿ��� 30�� ���)
{
	int count = 1;
	if (size < 50000)
	{
		num_line = size / line_size + 1;
	}
	for (int i = 0; i < num_line; i++)
	{
		for (int j = 0; j < line_size; j++, array++) //�ϳ��� ��� 29��° ���� �� 30��
		{
			if (*array == 0 || *array == -1)
				break;
			fprintf(fout, "%8d", *array);
			count++;
		}
		fprintf(fout, "\n");
	}
	if (size > 50000)
	{
		fprintf(fout, "    .  .  .  .  .  . \n");  //�� �Լ��� ��� 50000�� ���� ��µǹǷ� ��µǴ� ���� ������� �ʰ� ���κ��� ���

		for (int i = 0; i < num_line; i++)
		{
			for (int j = 0; j < line_size; j++, array--) //�� �ڿ��� ���� 30�� ���
			{
				fprintf(fout, "%8d", *(array + size - count));
			}
			fprintf(fout, "\n");
		}
	}
}

int fgetArrayFromFile(const char* fin_name, int* array, int max_size)
{
	FILE* fin;
	int data, num_data = 0;
	fin = fopen(fin_name, "r");  //������ �б���� ����
	if (fin == NULL)  //������ �ȷȷȴٸ� �ȿ��ȴٰ� ���
	{
		printf("Error in opening input data file !!\n");
		return 0;
	}
	while (fscanf(fin, "%d", &data) != EOF)  //���Ͽ� �ۼ��� ���� data�� �޾ƿ�
	{
		if ((data == -1) || (num_data >= max_size))  //������ ���ڰ� �� ���� ã���� �ݺ��� �ߴ�
			break;
		array[num_data] = data;  //�迭�� data ���� �Ҵ�
		num_data++;
	}
	fclose(fin);  //���� �ݱ�
	return num_data;  //�迭�� �������� ���̰�, �ʿ��� ���� data�� ������ �޾ƿ�
}