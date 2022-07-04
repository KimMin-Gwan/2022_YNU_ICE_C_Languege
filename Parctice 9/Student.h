/**
*파일명 : "프로그래밍 언어_21912229_실습_9"
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 구조체를 생성하고 구조체에 학생들의 데이터를
*		저장하여 포인터를 이용해 통계와 정렬을 시행하는 프로그램이다.
*프로그램 작성자 : 김민관(2022년 05월 01일)
*최종 Update : Version 1.0, 2022년 05월 01일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
*============================================================================
*/

#ifndef STUDENT_H
#define STUDENT_H

#include "Date.h"
#include "Telephone_number.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NAME_lENTH 15
#define NUM_STUDENTS 10

typedef struct _Student
{
	int ST_ID;
	char name[NAME_lENTH];
	Date birth_date;
	Tel_Number tel_number;
	double GPA;

}Student;
enum ST_KEY { ST_ID, NAME, GPA, DOB, TEL_NUM };
void printStudent(Student* pST);  //학생 출력
void printStudents(Student* stArr, int num_students); //학생 출력
void shuffleStudents(Student students[], int num_students); //학생 배열을 뒤섞기
void statisticsGPA(Student students[], int num_students);  //GPA의 통계치 계산
Student* searchBestGPAStudent(Student students[], int num);  //GPA의 최대치 계산
Student* searchWorstGPAStudent(Student students[], int num); //GPA의 최소치 계산
/*void sortStudents_by_GPA(Student students[], int num);  //GPA로 내림차순 정렬
void sortStudents_by_ST_ID(Student students[], int num);  //학번으로 오름차순 정렬
void sortStudents_by_name(Student students[], int num);  //이름으로 오름차순 정렬
void sortStudents_by_BirthDate(Student students[], int num);  //생일로 오름차순 정렬
void sortStudents_by_TelNumber(Student students[], int num);  //전화번호로 오름차순 정렬*/
int compareStudents(Student* pST1, Student* pST2, ST_KEY st_key);
void sortStudents(Student students[], int num, ST_KEY sort_key);
#endif