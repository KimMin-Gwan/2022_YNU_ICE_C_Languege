#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "BigArray.h"

#define ESC 0x1B  //ESC ���� ��
#define Data_Input_File "Data_input.txt"
#define Data_Output_File "Data_output.txt"
#define MAX_NUM_DATA 100  //�ִ� ������ ũ�� 100��

void arrayStatistics_basicArray(FILE* fout, double* save_data);
void arrayStatistics_externArray(FILE* fout, double* save_data);
void arrayStatistics_fileDataArray(FILE* fout, double* save_data);
void arrayStatistics_inputArray(FILE* fout, double* save_data);
void arrayStatistics_genBigRandArray(FILE* fout, double* save_data);

int main(void)
{
	FILE* fout;
	char menu;
	double save_data[6] = { 0 }; //statistic ���� �����ϴ� �迭
	enum statistics_name { min = 0, max, sum, avg, var, SD };
	fout = fopen(Data_Output_File, "w");  //output ������ ������� ����, ������ ����
	if (fout == NULL)  //���� ������ �ȿ��ȴٸ� ���α׷��� ����
	{
		printf("Error in creation of %s !! \n", Data_Output_File);
		return -1;
	}
	while (1)  //�޴� 
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
			arrayStatistics_basicArray(fout, save_data);//�⺻ �迭 ���
			break;
		case '2':
			arrayStatistics_externArray(fout, save_data);//�ܺ� �ҽ� �迭 ���
			break;
		case '3':
			arrayStatistics_fileDataArray(fout, save_data);//�ܺ� ���� �迭 ���
			break;
		case '4':
			arrayStatistics_inputArray(fout, save_data);//���Ͽ� ���� �迭 �ֱ�
			break;
		case '5':
			arrayStatistics_genBigRandArray(fout, save_data);//���� �Ŵ��� ���� ���� ���� �� �м� �� ���
			break;
		default:
			printf("Wrong number!! If you trying to terminate this program, press ESC\n");
			continue;
		}
		
	}
	fclose(fout);
	return 0;

}

void arrayStatistics_basicArray(FILE* fout, double *save_data)  //1 ������ �迭 ������ �м�
{
	int num_data = 10;
	int data_array1[MAX_NUM_DATA] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

	printf("\nArrayStatistics_externArray .....\n");
	fprintf(fout, "\nArrayStatistics_externArray .....\n");
	getArrayStatistics(data_array1, num_data, save_data);  //����ϰ� ���
	fgetArrayStatistics(fout, data_array1, num_data, save_data);  // ��� �ϰ� ���
	printf("arrayStatistics_basicArray - completed. Result is also stored in output file(%s). \n", Data_Output_File);

}

void arrayStatistics_externArray(FILE* fout, double* save_data) //2 �ܺ� �迭 ������ �м�
{
	int num_data = 0;
	extern int data_array[MAX_NUM_DATA]; //�ܺ� �迭 data_array ����
	for (int i = 0; ; i++)  //�迭�� ������ ���������� ���� ���
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

void arrayStatistics_fileDataArray(FILE* fout, double* save_data)  //3. �ܺ� ���� �����
{
	int data, num_data = 0;
	int data_array3[MAX_NUM_DATA] = { 0 };

	printf("\nArrayStatistics_inputArray .....\n");
	fprintf(fout, "\nArrayStatistics_inputArray .....\n");
	
	num_data = fgetArrayFromFile(Data_Input_File, data_array3, MAX_NUM_DATA);  //���� �ȿ� ������ ������ �޾ƿ�, �����ʹ� ��������
	getArrayStatistics(data_array3, num_data, save_data);
	fgetArrayStatistics(fout, data_array3, num_data, save_data);
	printf("arrayStatistics_fileDataArray - completed. Result is also stored in output file.\n");
}

void arrayStatistics_inputArray(FILE* fout, double* save_data)  //4 �����͸� ���� �ְ�, �м��Ͽ� ���
{
	int num_data = 0, data = 0;
	int data_array4[MAX_NUM_DATA] = { 0 };
	printf("\nArrayStatistics_inputArray .....\n");
	fprintf(fout, "\nArrayStatistics_inputArray .....\n");
	while (1) //�߸��� ���� ������ �ٽ� �Է½�Ű��
	{
		printf("Please input the number of integers (less than %d) = ", MAX_NUM_DATA);  //�Է��� ������ ������ �Է�
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
	
	printf("Input %d  integer data : ", num_data);  //���ڸ� �Է�
	for (int i = 0; i < num_data; i++)
	{
		scanf("%d", &data);
		data_array4[i] = data;
	}
	getArrayStatistics(data_array4, num_data, save_data);
	fgetArrayStatistics(fout, data_array4, num_data, save_data);
	printf("arrayStatistics_inputArray - completed. Result is also stored in output file (%s). \n", Data_Output_File);
}

void arrayStatistics_genBigRandArray(FILE* fout, double* save_data) //5���� �Ŵ��� ���� ���� ���� ��, �м� �� ���
{
	int size = 0;
	int* arr;  //�����Ͱ� ���� ���� �޸� �迭
	int offset = 1;
	
	printf("\nArrayStatistics_genBigRandArray .....\n");
	fprintf(fout, "\nArrayStatistics_genBigRandArray .....\n");
	while (1) //�߸��� ���� ������ �ٽ� �Է½�Ű��
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
	arr = (int*)calloc(size, sizeof(int)); //���� �޸� �迭 �Ҵ�
	getBigRandArray(arr, size, offset); //���� �Ŵ��� ���� ���� ����

	getArrayStatistics(arr, size, save_data);
	fgetArrayStatistics(fout, arr, size, save_data);
	printf("arrayStatistics_genBigRandArray - completed. Result is alos stored in output file (%s). \n", Data_Output_File);
	free(arr);
}

