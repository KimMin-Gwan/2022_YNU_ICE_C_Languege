#include "Student.h"

Student students[] =
{
{ 21711000, "Kim, G-M", { 1990, 10, 5 }, { 82, 53, 805, 1234 }, 3.57 },
{ 21611075, "Yoon, S-M", { 1990, 4, 5 }, { 82, 53, 811, 1550 }, 4.37 },
{ 21411015, "Hwang, S-S", { 1989, 1, 10 }, { 82, 53, 817, 1005 }, 2.72 },
{ 21611054, "Lee, K-M", { 1991, 5, 15 }, { 82, 10, 9112, 9876 }, 3.35 },
{ 21611340, "Hong, G-M", { 1990, 2, 5 }, { 82, 55, 810, 5678 }, 3.89 },
{ 21712056, "Jang, S-M", { 1990, 3, 15 }, { 82, 10, 9112, 1600 }, 4.42 },
{ 21411017, "Park, S-S", { 1989, 7, 10 }, { 82, 34, 817, 1098 }, 4.12 },
{ 21511053, "Choi, Y-H", { 1992, 9, 25 }, { 82, 53, 845, 5764 }, 3.85 },
{ 21411017, "Shin, D-J", { 1988, 10, 3 }, { 82, 31, 817, 1038 }, 3.21 },
{ 21511053, "Kwak, S-B", { 1994, 11, 15 }, { 82, 2, 897, 8778 }, 4.45 },
{-1}
};

void printStudent(Student* pST)
{
	printf("Student [ID: %9d, %-10s, GPA : %5.2lf, ", pST->ST_ID, pST->name, pST->GPA);
	printDate(pST->birth_date);
	printTelephoneNumber(pST->tel_number);
	printf("]");
}

void printStudents(Student* stArr, int num)
{
	Student* st = stArr; //배열을 조작하기 위한 포인터 st
	for (int i = 0; i < num; i++)
	{
		printStudent(st); //프린트
		printf("\n");
		st++; //배열의 증가
	}
}

void printTelephoneNumber(Tel_Number telNo)
{
	printf("(+%02d-%03d-%04d-%04d)", telNo.nation_code, telNo.region_no, telNo.switch_no, telNo.line_no);
}

void printDate(Date date)
{
	printf("(%04d, %2d, %2d)", date.year, date.month, date.day);
}

void sortStudents_by_ST_ID(Student students[], int num)  //학번으로 오름차순 정렬
{
	Student* pST, * pST_min;
	Student temp; //임시로 값을 담을 Student형 변수
	int st_id_min_index; //index
	for (int i = 0; i < num; i++)
	{
		pST_min = pST = &students[i]; //탐색을 시작하는 위치 i
		st_id_min_index = i; //초기값
		for (int j = i + 1; j < num; j++)
		{
			pST = &students[j];
			if (pST->ST_ID < pST_min->ST_ID)//비교
			{
				st_id_min_index = j; //가장작은 인덱스의 위치 변경
				pST_min = pST; //최대 포인터가 가르키는 주소를 현재 pst가 가르키는 주소로 변경
			}
		}
		if (st_id_min_index != i) //현재 탐색중인 값과 가장 큰 값이 있는 배열을 교환
		{
			temp = students[st_id_min_index];
			students[st_id_min_index] = students[i];
			students[i] = temp;
		}
	}
}

void fprintStudent(FILE* fout, Student* pST)
{
	fprintf(fout, "Student [ID: %9d, %-10s, GPA : %5.2lf, ", pST->ST_ID, pST->name, pST->GPA);
	fprintDate(fout, pST->birth_date);
	fprintTelephoneNumber(fout, pST->tel_number);
	fprintf(fout, "]");
}

void fprintStudents(FILE* fout, Student* students, int num)
{
	Student* st = students; //배열을 조작하기 위한 포인터 st
	for (int i = 0; i < num; i++)
	{
		fprintStudent(fout, st); //프린트
		fprintf(fout, "\n");
		st++; //배열의 증가
	}
}

void fprintTelephoneNumber(FILE* fout, Tel_Number telNo)
{
	fprintf(fout, "(+%02d-%03d-%04d-%04d)", telNo.nation_code, telNo.region_no, telNo.switch_no, telNo.line_no);
}

void fprintDate(FILE* fout, Date date)
{
	fprintf(fout, "(%04d, %2d, %2d)", date.year, date.month, date.day);
}