#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define U_SHORT unsigned short
#define NAME_lENTH 15
#define NUM_STUDENTS 10
#define MAX_STRING_LEN 512

typedef struct
{
	int year;
	int month;
	int day;
} Date;

typedef struct
{
	U_SHORT nation_code;
	U_SHORT region_no;
	U_SHORT switch_no;
	U_SHORT line_no;
} Tel_Number;

typedef struct _Student
{
	int ST_ID;
	char name[NAME_lENTH];
	Date birth_date;
	Tel_Number tel_number;
	double GPA;

}Student;

//void fprintStudents(FILE* fout, Student students[], int num);
void printStudent(Student* pST);  //학생 출력
void printStudents(Student* stArr, int num_students); //학생 출력
void printTelephoneNumber(Tel_Number telNo); //전화번호를 출력
void printDate(Date date); //날짜를 출력
void sortStudents_by_ST_ID(Student students[], int num);  //학번으로 오름차순 정렬
//void selectionSortStudents_by_ST_ID(Student students[], int num);

void fprintDate(FILE* fout, Date date); //날짜를 파일에 출력
void fprintTelephoneNumber(FILE* fout, Tel_Number telNo); //전화번호를 파일에 출력
void fprintStudent(FILE* fout, Student* pST); //학생을 파일에 출력
void fprintStudents(FILE* fout, Student* students, int num); //학생을 파일에 출력
#endif