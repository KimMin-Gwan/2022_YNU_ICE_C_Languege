#include "BigArray_Algorithms.h"

void printBigArraySample(int* array, int size, int line_size, int num_line) //������ ���� ���� ��� (�տ��� 30�� �ڿ��� 30�� ���)
{
	int count = line_size * num_line;
	if (size < 50000)  //5������ ������ ����ϴ� ���μ��� �ٲپ��� (�⺻ 2��)
	{
		num_line = size / line_size + 1;
	}
	for (int i = 0; i < num_line; i++)
	{

		for (int j = 0; j < line_size; j++, array++) //�ϳ��� ��� ���� ũ�⸸ŭ ����ϰ� \n
		{
			if (count == size + 1)
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
			for (int j = 0; j < line_size; j++, array++) //�� �ڿ��� ���� 20�� ���
			{
				printf("%8d", *(array + size - count));
			}
			printf("\n");
		}
	}
}

void genBigRandArray(int* array, int size, int base) //���� �Ŵ��� ���� ���� ������
{
	char* flag;
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand, bigRand_withOffset;

	flag = (char*)calloc(size, sizeof(char)); //�ߺ��˻縦 �Ҷ� ����ϴ� ���� �޸�
	while (count < size)
	{
		u_int32 = ((unsigned int)rand() << 15) | rand();  //15��Ʈ �о�� �ٽ� 15��Ʈ �ֱ�
		bigRand = u_int32 % size;  //bigRandSize���� ���� ũ��� ����
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

void suffleArray(int* array, int size)
{
	int i1, i2, d;
	srand((unsigned)time(NULL));

	for (int i = 0; i < size / 2; i++)
	{
		i1 = ((unsigned long)rand() << 15 | rand()) % size;
		i2 = ((unsigned long)rand() << 15 | rand()) % size;

		d = array[i1];
		array[i1] = array[i2];
		array[i2] = d;
	}
}