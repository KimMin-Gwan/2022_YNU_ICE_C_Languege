#include "BigArray_Algorithms.h"

void printBigArraySample(int* array, int size, int line_size, int num_line) //랜덤한 숫자 셈플 출력 (앞에서 30개 뒤에서 30개 출력)
{
	int count = line_size * num_line;
	if (size < 50000)  //5만보다 작으면 출력하는 라인수를 바꾸어줌 (기본 2줄)
	{
		num_line = size / line_size + 1;
	}
	for (int i = 0; i < num_line; i++)
	{

		for (int j = 0; j < line_size; j++, array++) //하나씩 출력 라인 크기만큼 출력하고 \n
		{
			if (count == size + 1)
				break;
			printf("%8d", *array);
			count++;
		}
		printf("\n");
	}
	if (size > 50000)  //5만보다 큰 사이즈면 맨뒤에서 부터 20개 더 출력
	{
		printf("    .  .  .  .  .  . \n");
		for (int i = 0; i < num_line; i++)
		{
			for (int j = 0; j < line_size; j++, array++) //맨 뒤에서 부터 20개 출력
			{
				printf("%8d", *(array + size - count));
			}
			printf("\n");
		}
	}
}

void genBigRandArray(int* array, int size, int base) //아주 거대한 랜덤 숫자 생성기
{
	char* flag;
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand, bigRand_withOffset;

	flag = (char*)calloc(size, sizeof(char)); //중복검사를 할때 사용하는 동적 메모리
	while (count < size)
	{
		u_int32 = ((unsigned int)rand() << 15) | rand();  //15비트 밀어내고 다시 15비트 넣기
		bigRand = u_int32 % size;  //bigRandSize보다 작은 크기로 만듬
		if (flag[bigRand] == 1)  //중복검사, 만약 1이 있다면  다시 값을 넣을것
		{
			continue;
		}
		else
		{
			flag[bigRand] = 1;
			bigRand_withOffset = bigRand + base;
			array[count++] = bigRand_withOffset;  //array에 값을 할당
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