/**
*파일명 : "프로그래밍 언어_21912229_10"
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 문자를 정렬하는 기능, 학생 구조체를 정렬하고, 파일에 
*		저장하여 랜덤한 부분을 출력하는 기능, file open의 바이너리 형식의 사용
*		및 출력, 8비트 코드를 통한 간단한 암호화 기능 을 수행하는 프로그램이다.
*프로그램 작성자 : 김민관(2022년 05월 08일)
*최종 Update : Version 1.4 , 2022년 05월 11일(김민관)
*=======================================================================================
*프로그램 수정/보완 이력
*=======================================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
*김민관      2022/05/09      v1.1   문자열 정렬에서 동적 배열을 생성하도록 변경
*김민관      2022/05/10      v1.2   암호화에서 상위비트와 하위비트로 나눠서 계산을 수행
*김민관      2022/05/11      v1.3   복호화에서 상위비트와 하위비트로 나눠서 계산을 수행
*김민관      2022/05/11      v1.4   일부 주석문의 수정
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
			test_SelectionSortWords(); //문자열의 정렬 및 출력
			break;
		case 2:
			test_RandomFileAccess_Student(); //파일에 랜던한 부분의 접근
			break;
		case 3:
			test_BinaryFileDump(); //이진파일 출력
			break;
		case 4:
			test_simple_cipher_text(); //8비트 코드를 통한 암호화와 복호화
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

	word_array = (char**)calloc(MAX_NUM_WORDS, sizeof(char*)); // 동적할당 
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

	while (fscanf(fin, "%s", str) != EOF) //파일 받아오기
	{
		strcpy(word_array[counter], str);
		counter++;;
	}
	selectionSortWords(word_array, counter); //설렉션 소팅
	for (int i = 0; i < counter; i++) //하면에 출력
	{
		if (i % 10 == 0 && i > 0) //10개씩 출력
			printf("\n");
		printf("%-16s ", word_array[i]);

	}
	for (int i = 0; i < counter; i++) //파일에 출력
	{
		if (i % 10 == 0 && i != 0)
			fprintf(fout, "\n");
		fprintf(fout, "%-16s ", word_array[i]);

	}
	printf("\n");
	for (int i = 0; i < MAX_NUM_WORDS; i++) // 행 동적할당 해제
		free(word_array[i]);
	free(word_array); // 전체 동적할당 해제
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
	printStudents(students, NUM_STUDENTS); // 화면에 출력
	printf("\n");

	sortStudents_by_ST_ID(students, NUM_STUDENTS); //학생 구조체 배열을 학번을 기준으로 selection sorting
	printf("Storing sorted students by increasing order of student ID into SortedStudent.txt ....\n");
	fprintStudents(fout, students, NUM_STUDENTS); //정렬이 끝난 배열 .txt 파일에 학생들 구조체 저장
	printStudents(students, NUM_STUDENTS); //정렬이 끝난 배열 출력
	fprintf(fout, "\n");
	fclose(fout); //쓰기모드 끄기
	fin = fopen("Sorted_Students.txt", "r"); //작성한 파일 읽기모드로 다시 열기
	if (fin == NULL)
	{
		printf("Error in opening Sorted_Students.txt (read mode)!!\n");
		exit;
	}
	int cur_pos;
	fgets(student_record, MAX_STRING_LEN, fin); //txt파일에서 학생들 문자열에 받기
	record_len = strlen(student_record); //문자열의 길이를 측정
	rewind(fin); //포인터 위치를 처음위치로 이동
	printf("\nRandom access to Sorted_students.txt file (Student record length: %d) ...\n", record_len); //문자열 길이에 맞춰서 랜던하게 접근
	for (int i = NUM_STUDENTS - 1; i >= 0; i--)
	{
		fseek(fin, (record_len + 1) * i, SEEK_SET); //랜던한 위치로 찾아감 이때 위치의 기준은 문자열의 길이
		cur_pos = ftell(fin); //현재 위치 반환
		printf("Current file_position : %3d\n", cur_pos);
		fgets(student_record, MAX_STRING_LEN, fin); //현재위치로 다시 문자열 받고 출력
		printf("Student (%2d): %s", i, student_record);
	}
	printf("\n");
	fclose(fin);
}

void test_BinaryFileDump()
{
	FILE* fin = NULL, * fout = NULL;
	const char* fname = "Sorted_Students.txt";
	if ((fin = fopen(fname, "rb")) == NULL) //파일을 이진모드로 읽기
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

	printf("Generating cipher text with cipher-code (%#04x) ..\n", CIPHER_CODE); //암호코드는 이것입니다.
	cipherText(fp_msg, fp_tx, CIPHER_CODE); //0x69코드로 암호화
	fclose(fp_tx); //암호화 파일 닫기

	rewind(fp_msg); //파일의 초기부분으로 
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
