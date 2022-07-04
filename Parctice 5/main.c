#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "BigArray.h"

#define ESC 0x1B  //ESC 리턴 값
#define Data_Input_File "Data_input.txt"
#define Data_Output_File "Data_output.txt"
#define MAX_NUM_DATA 100  //최대 데이터 크기 100개

void arrayStatistics_basicArray(FILE* fout, double* save_data);
void arrayStatistics_externArray(FILE* fout, double* save_data);
void arrayStatistics_fileDataArray(FILE* fout, double* save_data);
void arrayStatistics_inputArray(FILE* fout, double* save_data);
void arrayStatistics_genBigRandArray(FILE* fout, double* save_data);

int main(void)
{
	FILE* fout;
	char menu;
	double save_data[6] = { 0 }; //statistic 값을 저장하는 배열
	enum statistics_name { min = 0, max, sum, avg, var, SD };
	fout = fopen(Data_Output_File, "w");  //output 파일을 쓰기모드로 열기, 없으면 만듦
	if (fout == NULL)  //만약 파일이 안열렸다면 프로그램을 종료
	{
		printf("Error in creation of %s !! \n", Data_Output_File);
		return -1;
	}
	while (1)  //메뉴 
	{
		for (int i = 0; i < 6; i++)
		{
			save_data[i] = 0;
		}
		printf("Test Array Handing (1: data_array; 2: extern_array; 3: data_file; 4:data_input; 5: genBigRandArray; ESC: terminate) : ");
		menu = _getche();
		if (menu == ESC)
			break;
		switch (menu)
		{
		case '1':
			arrayStatistics_basicArray(fout, save_data);//기본 배열 출력
			break;
		case '2':
			arrayStatistics_externArray(fout, save_data);//외부 소스 배열 출력
			break;
		case '3':
			arrayStatistics_fileDataArray(fout, save_data);//외부 파일 배열 출력
			break;
		case '4':
			arrayStatistics_inputArray(fout, save_data);//파일에 숫자 배열 넣기
			break;
		case '5':
			arrayStatistics_genBigRandArray(fout, save_data);//아주 거대한 랜덤 숫자 생성 후 분석 및 출력
			break;
		default:
			printf("Wrong number!! If you trying to terminate this program, press ESC\n");
			continue;
		}
		
	}
	fclose(fout);
	return 0;

}

void arrayStatistics_basicArray(FILE* fout, double *save_data)  //1 베이직 배열 데이터 분석
{
	int num_data = 10;
	int data_array1[MAX_NUM_DATA] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

	printf("\nArrayStatistics_externArray .....\n");
	fprintf(fout, "\nArrayStatistics_externArray .....\n");
	getArrayStatistics(data_array1, num_data, save_data);  //계산하고 출력
	fgetArrayStatistics(fout, data_array1, num_data, save_data);  // 계산 하고 출력
	printf("arrayStatistics_basicArray - completed. Result is also stored in output file(%s). \n", Data_Output_File);

}

void arrayStatistics_externArray(FILE* fout, double* save_data) //2 외부 배열 데이터 분석
{
	int num_data = 0;
	extern int data_array[MAX_NUM_DATA]; //외부 배열 data_array 참조
	for (int i = 0; ; i++)  //배열이 끝나는 지점까지의 갯수 계산
	{
		if (data_array[i] == -1)
			break;
		else
			num_data++;
	}
	printf("\nArrayStatistics_externArray .....\n");
	fprintf(fout, "\nArrayStatistics_externArray .....\n");
	getArrayStatistics(data_array, num_data, save_data);
	fgetArrayStatistics(fout, data_array, num_data, save_data);
	printf("arrayStatistics_fileDataArray - completed. Result is also sstored in out put file (%s). \n", Data_Output_File);
}

void arrayStatistics_fileDataArray(FILE* fout, double* save_data)  //3. 외부 파일 입출력
{
	int data, num_data = 0;
	int data_array3[MAX_NUM_DATA] = { 0 };

	printf("\nArrayStatistics_inputArray .....\n");
	fprintf(fout, "\nArrayStatistics_inputArray .....\n");
	
	num_data = fgetArrayFromFile(Data_Input_File, data_array3, MAX_NUM_DATA);  //파일 안에 숫자의 갯수를 받아옴, 데이터는 참조받음
	getArrayStatistics(data_array3, num_data, save_data);
	fgetArrayStatistics(fout, data_array3, num_data, save_data);
	printf("arrayStatistics_fileDataArray - completed. Result is also stored in output file.\n");
}

void arrayStatistics_inputArray(FILE* fout, double* save_data)  //4 데이터를 집어 넣고, 분석하여 출력
{
	int num_data = 0, data = 0;
	int data_array4[MAX_NUM_DATA] = { 0 };
	printf("\nArrayStatistics_inputArray .....\n");
	fprintf(fout, "\nArrayStatistics_inputArray .....\n");
	while (1) //잘못된 값을 넣으면 다시 입력시키기
	{
		printf("Please input the number of integers (less than %d) = ", MAX_NUM_DATA);  //입력할 숫자의 갯수를 입력
		scanf("%d", &num_data);
		if (num_data < MAX_NUM_DATA)
		{
			break;
		}
		else
		{
			printf("Thats wrong number !!\n");
			continue;
		}

	}
	
	printf("Input %d  integer data : ", num_data);  //숫자를 입력
	for (int i = 0; i < num_data; i++)
	{
		scanf("%d", &data);
		data_array4[i] = data;
	}
	getArrayStatistics(data_array4, num_data, save_data);
	fgetArrayStatistics(fout, data_array4, num_data, save_data);
	printf("arrayStatistics_inputArray - completed. Result is also stored in output file (%s). \n", Data_Output_File);
}

void arrayStatistics_genBigRandArray(FILE* fout, double* save_data) //5아주 거대한 랜덤 숫자 생성 후, 분석 및 출력
{
	int size = 0;
	int* arr;  //데이터가 들어가는 동적 메모리 배열
	int offset = 1;
	
	printf("\nArrayStatistics_genBigRandArray .....\n");
	fprintf(fout, "\nArrayStatistics_genBigRandArray .....\n");
	while (1) //잘못된 값을 넣으면 다시 입력시키기
	{
		printf("Big Array Size (bigger than 50000)  = ");
		scanf(" %d", &size);
		if (size > 50000)
		{
			break;
		}
		else
		{
			printf("Thats wrong number !!\n");
			continue;
		}
			
	}
	arr = (int*)calloc(size, sizeof(int)); //동적 메모리 배열 할당
	getBigRandArray(arr, size, offset); //아주 거대한 랜덤 숫자 생성

	getArrayStatistics(arr, size, save_data);
	fgetArrayStatistics(fout, arr, size, save_data);
	printf("arrayStatistics_genBigRandArray - completed. Result is alos stored in output file (%s). \n", Data_Output_File);
	free(arr);
}

