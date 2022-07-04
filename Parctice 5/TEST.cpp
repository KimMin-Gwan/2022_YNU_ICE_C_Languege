#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "BigArray.h" 

void getBigRandArray(int* array, int bigRandSize, int base) //아주 거대한 랜덤 숫자 생성기
{
	char* flag;
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand, bigRand_withOffset;

	flag = (char*)calloc(bigRandSize, sizeof(char)); //중복검사를 할때 사용하는 동적 메모리
	while (count < bigRandSize)
	{
		u_int32 = ((long)rand() << 15) | rand();  //15비트 밀어내고 다시 15비트 넣기
		bigRand = u_int32 % bigRandSize;  //bigRandSize보다 작은 크기로 만듬
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

void getArrayStatistics(int* array, int size, double* save) //배열의 합, 최소, 최대, 평균, 분산, 표준편차를 계산하고 출력
{
	statistics(array, save, size);
	printf("Total (%3d) integer data : \n", size);
	printBigArraySample(array, size, LINE_SIZE, NUM_LINE);
	printf("min (%3.0lf), max(%3.0lf), sum(%8.2lf), average (%8.2lf), ", save[min], save[max], save[sum], save[avg]);
	printf("variance (%8.2lf), standard deviation (%8.2lf) \n", save[var], save[SD]);
}

void fgetArrayStatistics(FILE* fout, int* array, int size, double* save) // 배열의 합, 최소, 최대, 평균, 분산, 표준편차를 계산하고 파일에 출력
{
	fprintf(fout, "Total (%3d) integer data : \n", size);
	fprintBigArraySample(fout, array, size, LINE_SIZE, NUM_LINE);  //배열을 파일에 출력
	fprintf(fout, "min (%3.0lf), max(%3.0lf), sum(%8.2lf), average (%8.2lf), ", save[min], save[max], save[sum], save[avg]);
	fprintf(fout, "variance (%8.2lf), standard deviation (%8.2lf) \n", save[var], save[SD]);
	free(save);
}

void statistics(int* arr, double* save, int size) //statistics를 두번 써주지 않기 위해 사용
{
	int data = 0;
	double diff, sq_diff_sum = 0.0;

	for (int i = 0; i < size; i++)
	{
		data = arr[i];
		save[sum] += data;  //합을 계산
		if (i == 0)  //최대 최소를 알아냄
		{
			save[min] = save[max] = arr[0];
		}
		else
		{
			if (data < save[min])
				save[min] = save[data];
			if (data > save[max])
				save[max] = data;
		}
	}
	save[avg] = save[sum] / (double)size;  //평균계산
	sq_diff_sum = 0.0;
	for (int i = 0; i < size; i++)  //분산계산
	{
		diff = arr[i] - save[avg];
		sq_diff_sum += diff * diff;
	}
	save[var] = sq_diff_sum / (double)size;
	save[SD] = sqrt(var); //표준편차 계산
}

void printBigArraySample(int* array, int size, int line_size, int num_line) //랜덤한 숫자 셈플 출력 (앞에서 30개 뒤에서 30개 출력)
{
	int count = 1;
	if (size > 50000)
	{
		num_line = size / line_size + 1;
	}
	for (int i = 0; i < num_line; i++)
	{
		for (int j = 0; j < line_size; j++, array++) //하나씩 출력 29번째 까지 총 30개
		{
			printf("%8d", *array);
			count++;
		}
		printf("\n");
	}
	if (size > 50000)
	{
		printf("    .  .  .  .  .  . \n");

		for (int i = 0; i < num_line; i++)
		{
			for (int j = 0; j < line_size; j++, array--) //맨 뒤에서 부터 30개 출력
			{
				printf("%8d", *(array + size - count));
			}
			printf("\n");
		}
	}
}

void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int num_line) //랜덤한 숫자 셈플 (앞에서 30개 뒤에서 30개 출력)
{
	int count = 1;
	if (size > 50000)
	{
		num_line = size / line_size + 1;
	}
	for (int i = 0; i < num_line; i++)
	{
		for (int j = 0; j < line_size; j++, array++) //하나씩 출력 29번째 까지 총 30개
		{
			fprintf(fout, "%8d", *array);
			count++;
		}
		fprintf(fout, "\n");
	}
	if (size > 50000)
	{
		fprintf(fout, "    .  .  .  .  .  . \n");  //이 함수는 적어도 50000개 부터 출력되므로 출력되는 량을 고려하지 않고 끝부분을 출력

		for (int i = 0; i < num_line; i++)
		{
			for (int j = 0; j < line_size; j++, array--) //맨 뒤에서 부터 30개 출력
			{
				fprintf(fout, "%8d", *(array + size - count));
			}
			fprintf(fout, "\n");
		}
	}
}

int fgetArrayFromFile(const char* fin_name, int* array, int max_size) //파일에 작성된 배열을 받아오는 함수
{
	FILE* fin;
	int data, num_data = 0;
	fin = fopen(fin_name, "r");  //파일을 읽기모드로 열기
	if (fin == NULL)  //파일이 안렸렸다면 안열렸다고 출력
	{
		printf("Error in opening input data file !!\n");
		return 0;
	}
	while (fscanf(fin, "%d", &data) != EOF)  //파일에 작성된 값을 data로 받아옴
	{
		if ((data == -1) || (num_data >= max_size))  //프라임 문자가 들어간 것을 찾으면 반복을 중단
			break;
		array[num_data] = data;  //배열에 data 값을 할당
		num_data++;
	}
	fclose(fin);  //파일 닫기
	return num_data;  //배열은 참조받을 것이고, 필요한 값인 data의 갯수만 받아옴
}