/**
*���ϸ� : "���α׷��� ���_21912229_10"
*���α׷��� ���� �� �⺻ ���:
*      -�� ���α׷��� ���ڸ� �����ϴ� ���, �л� ����ü�� �����ϰ�, ���Ͽ� 
*		�����Ͽ� ������ �κ��� ����ϴ� ���, file open�� ���̳ʸ� ������ ���
*		�� ���, 8��Ʈ �ڵ带 ���� ������ ��ȣȭ ��� �� �����ϴ� ���α׷��̴�.
*���α׷� �ۼ��� : ��ΰ�(2022�� 05�� 08��)
*���� Update : Version 1.4 , 2022�� 05�� 11��(��ΰ�)
*=======================================================================================
*���α׷� ����/���� �̷�
*=======================================================================================
*���α׷� ����/�����۾���   ����   ����/���ϳ���
*��ΰ�      2022/05/09      v1.1   ���ڿ� ���Ŀ��� ���� �迭�� �����ϵ��� ����
*��ΰ�      2022/05/10      v1.2   ��ȣȭ���� ������Ʈ�� ������Ʈ�� ������ ����� ����
*��ΰ�      2022/05/11      v1.3   ��ȣȭ���� ������Ʈ�� ������Ʈ�� ������ ����� ����
*��ΰ�      2022/05/11      v1.4   �Ϻ� �ּ����� ����
*========================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MyString.h"
#include "Student.h"
#include "HandlingBinaryFile.h"
#include "CipherMessage.h"
void test_SelectionSortWords();
void test_RandomFileAccess_Student();
void test_BinaryFileDump();
void test_simple_cipher_text();
int main(void)
{
	int menu;
	while (1)
	{
		printf(" 1. Test selection sort for words\n");
		printf(" 2. Test random access file for students records\n");
		printf(" 3. Test binary file dump\n");
		printf(" 4. Test cipher text\n");
		printf(" 0. Quit\n");
		printf("Input menu : ");
		scanf("%d", &menu);
		if (menu == 0)
			break;
		switch (menu)
		{
		case 1:
			test_SelectionSortWords(); //���ڿ��� ���� �� ���
			break;
		case 2:
			test_RandomFileAccess_Student(); //���Ͽ� ������ �κ��� ����
			break;
		case 3:
			test_BinaryFileDump(); //�������� ���
			break;
		case 4:
			test_simple_cipher_text(); //8��Ʈ �ڵ带 ���� ��ȣȭ�� ��ȣȭ
			break;
		default:
			break;
		}
	}
}

void test_SelectionSortWords()
{
	FILE* fin = NULL;
	FILE* fout = NULL;
	char str[MAX_WORD_LEN];
	char** word_array;

	word_array = (char**)calloc(MAX_NUM_WORDS, sizeof(char*)); // �����Ҵ� 
	for (int i = 0; i < MAX_NUM_WORDS; i++)
	{
		word_array[i] = (char*)calloc(MAX_WORD_LEN, sizeof(char)); 
	}

	int counter = 0;
	fin = fopen("words.txt", "r");
	if (fin == NULL)
	{
		printf("Error in opening Sorted_Students.txt (read mode)!!\n");
		exit;
	}
	fout = fopen("word_output.txt", "w");
	if (fout == NULL)
	{
		printf("Error in opening Sorted_Students.txt (write mode)!!\n");
		exit;
	}

	while (fscanf(fin, "%s", str) != EOF) //���� �޾ƿ���
	{
		strcpy(word_array[counter], str);
		counter++;;
	}
	selectionSortWords(word_array, counter); //������ ����
	for (int i = 0; i < counter; i++) //�ϸ鿡 ���
	{
		if (i % 10 == 0 && i > 0) //10���� ���
			printf("\n");
		printf("%-16s ", word_array[i]);

	}
	for (int i = 0; i < counter; i++) //���Ͽ� ���
	{
		if (i % 10 == 0 && i != 0)
			fprintf(fout, "\n");
		fprintf(fout, "%-16s ", word_array[i]);

	}
	printf("\n");
	for (int i = 0; i < MAX_NUM_WORDS; i++) // �� �����Ҵ� ����
		free(word_array[i]);
	free(word_array); // ��ü �����Ҵ� ����
	fclose(fin);
	fclose(fout);
}

void test_RandomFileAccess_Student()
{
	FILE* fin, * fout;
	Student* pST;
	extern Student students[];
	int record_len;
	char student_record[MAX_STRING_LEN] = { 0 };
	fout = fopen("Sorted_Students.txt", "w");
	if (fout == NULL)
	{
		printf("Error in opening Sorted_Students.txt (write mode)!!\n");
		exit;
	}
	printf("Array of students at initialization : \n");
	printStudents(students, NUM_STUDENTS); // ȭ�鿡 ���
	printf("\n");

	sortStudents_by_ST_ID(students, NUM_STUDENTS); //�л� ����ü �迭�� �й��� �������� selection sorting
	printf("Storing sorted students by increasing order of student ID into SortedStudent.txt ....\n");
	fprintStudents(fout, students, NUM_STUDENTS); //������ ���� �迭 .txt ���Ͽ� �л��� ����ü ����
	printStudents(students, NUM_STUDENTS); //������ ���� �迭 ���
	fprintf(fout, "\n");
	fclose(fout); //������ ����
	fin = fopen("Sorted_Students.txt", "r"); //�ۼ��� ���� �б���� �ٽ� ����
	if (fin == NULL)
	{
		printf("Error in opening Sorted_Students.txt (read mode)!!\n");
		exit;
	}
	int cur_pos;
	fgets(student_record, MAX_STRING_LEN, fin); //txt���Ͽ��� �л��� ���ڿ��� �ޱ�
	record_len = strlen(student_record); //���ڿ��� ���̸� ����
	rewind(fin); //������ ��ġ�� ó����ġ�� �̵�
	printf("\nRandom access to Sorted_students.txt file (Student record length: %d) ...\n", record_len); //���ڿ� ���̿� ���缭 �����ϰ� ����
	for (int i = NUM_STUDENTS - 1; i >= 0; i--)
	{
		fseek(fin, (record_len + 1) * i, SEEK_SET); //������ ��ġ�� ã�ư� �̶� ��ġ�� ������ ���ڿ��� ����
		cur_pos = ftell(fin); //���� ��ġ ��ȯ
		printf("Current file_position : %3d\n", cur_pos);
		fgets(student_record, MAX_STRING_LEN, fin); //������ġ�� �ٽ� ���ڿ� �ް� ���
		printf("Student (%2d): %s", i, student_record);
	}
	printf("\n");
	fclose(fin);
}

void test_BinaryFileDump()
{
	FILE* fin = NULL, * fout = NULL;
	const char* fname = "Sorted_Students.txt";
	if ((fin = fopen(fname, "rb")) == NULL) //������ �������� �б�
	{
		printf("Error - binary input file (%s) cannot be openned !!\n", fname);
		exit;
	}
	if ((fout = fopen("Output.txt", "w")) == NULL)
	{
		printf("Error - Output.txt cannot be created !!\n");
		exit;
	}
	printf("Dumping binary file (%s) ... \n", fname);
	dumpBinaryFile(fin, fout);
	fclose(fin);
	fclose(fout);
}

void test_simple_cipher_text()
{
	FILE* fp_msg = NULL, * fp_tx = NULL,/* * fp_rx = NULL, * fp_dump_msg = NULL,*/ *fout = NULL;
	fp_msg = fopen("Message.txt", "r");
	if (fp_msg == NULL)
	{
		printf("Error in file open - Message.txt !!\n");
		exit(-1);
	}
	fp_tx = fopen("Transmit.txt", "w");
	if (fp_tx == NULL)
	{
		printf("Error in file open - Transmit.txt !!\n");
		exit(-1);
	}
	fout = fopen("Output.txt", "w");
	if (fout == NULL)
	{
		printf("Error in file open - Output.txt !!\n");
		exit(-1);
	}

	printf("Generating cipher text with cipher-code (%#04x) ..\n", CIPHER_CODE); //��ȣ�ڵ�� �̰��Դϴ�.
	cipherText(fp_msg, fp_tx, CIPHER_CODE); //0x69�ڵ�� ��ȣȭ
	fclose(fp_tx); //��ȣȭ ���� �ݱ�

	rewind(fp_msg); //������ �ʱ�κ����� 
	fprintf(fout, "Binary dump of message.txt file: \n"); //
	dumpBinaryFile(fp_msg, fout); 

	fp_tx = fopen("Transmit.txt", "r");
	if (fp_tx == NULL)
	{
		printf("Error in file open - Transmit.txt !!\n");
		exit(-1);
	}
	fprintf(fout, "\n=========================================\n");
	fprintf(fout, "Binary dump of ciphered document: \n");
	dumpBinaryFile(fp_tx, fout);

	rewind(fp_tx);
	printf("Generating de-ciphered text with cipher-code (%#04x) ..\n", CIPHER_CODE);
	fprintf(fout, "\n=========================================\n");
	fprintf(fout, "Generating de-ciphered text with cipher-code (%#04x) ..\n", CIPHER_CODE);
	deCipherText(fp_tx, fout, CIPHER_CODE);
	fclose(fp_msg);
	fclose(fp_tx);
	fclose(fout);
}
