#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "BigArray.h"

#define ESC 0x1B
#define Data_Input_File "Data_input.txt"
#define Data_Output_File "Data_output.txt"
#define MAX_NUM_DATA 10

void arrayStatistics_basicArray(FILE* fout);
void arrayStatistics_externArray(FILE* fout);
void arrayStatistics_fileDataArray(FILE* fout);
void arryaStatistics_inputArray(FILE* fout);
void arrayStatistics_genBigRandArray(FILE* fout);


int main(void)
{
	FILE* fout;
	char menu;

	fout = fopen(Data_Output_File, "w");
	if (fout == NULL);
	{
		printf("Error in creation of %s !! \n", Data_Output_File);
		return -1;
	}
	while (1)
	{
		printf("\nTest Array Handing (1: data_array; 2: extern_array; 3: data_file; 4:data_input; 5: genBigRandArray; ESC: terminate) : ");
		menu = _getche();
		if (menu == ESC)
			break;
		switch (menu)
		{
		case '1':
			arrayStatistics_basicArray(fout);
			break;
		case '2':
			arrayStatistics_externArray(fout);
			break;
		case '3':
			arrayStatistics_fileDataArray(fout);
			break;
		case '4':
			arryaStatistics_inputArray(fout);
			break;
		case '5':
			arrayStatistics_genBigRandArray(fout);
			break;
		default:
			break;
		}
	}
	fclose(fout);
	return 0;
}

void arrayStatistics_basicArray(FILE* fout)
{
	int num_data = 10;
	int data_array[MAX_NUM_DATA] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

	printf("\nArrayStatistics_externArray .....\n");
	fprintf(fout, "\nArrayStatistics_externArray .....\n");
	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
	printf("arrayStatistics_basicArray - completed. Result is also stored in output file(%s). \n", Data_Output_File);
}

void arrayStatistics_externArray(FILE* fout)
{
	int num_data = 0;
	int data_array;

	printf("\nArrayStatistics_externArray .....\n");
	fprintf(fout, "\nArrayStatistics_externArray .....\n");
	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
	printf("arrayStatistics_fileDataArray - completed. Result is also sstored in out put file (%s). \n", Data_Output_File);
}

void arrayStatistics_fileDataArray(FILE* fout)
{

	printf("\nArrayStatistics_fileDataArray .....\n");
	fprintf(fout, "\nArrayStatistics_fileDataArray .....\n");

	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
	printf("arrayStatistics_fileDataArray - completed. Result is also stored in output fiel (%s).\n", Data_Output_File);
}

void arrayStatistics_inputArray(FILE* fout)
{

	printf("\nArrayStatistics_inputArray .....\n");
	fprintf(fout, "\nArrayStatistics_inputArray .....\n");
	printf("Please input the number of integers (less than $d) = ", MAX_NUM_DATA);
	scanf("%d", &num_data);
	printf("Input %d  integer data : ", num_data);

	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
	printf("arrayStatistics_inputArray - completed. Result is also stored in output file (%s). \n", Data_Output_File);
}

void arrayStatistics_genBigRandArray(FILE* fout)
{

	int* array1 = NULL;
	srand((unsigned)time(0));

	printf("\nArrayStatistics_genBigRandArray .....\n");
	fprintf(fout, "\nArrayStatistics_genBigRandArray .....\n");
	printf("Size of big array (bigger than 50000)  = ");
	scanf("%d", &size);
	array1 = (int*)calloc(size, sizeof(int));

	getArrayStatistics(array1, size);
	fgetArrayStatistics(fout, array1, size);
	printf("arrayStatistics_genBigRandArray - completed. Result is alos stored in output file (%s). \n", Data_Output_File);
	free(array1);
}