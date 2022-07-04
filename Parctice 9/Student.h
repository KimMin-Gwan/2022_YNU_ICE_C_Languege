/**
*���ϸ� : "���α׷��� ���_21912229_�ǽ�_9"
*���α׷��� ���� �� �⺻ ���:
*      -�� ���α׷��� ����ü�� �����ϰ� ����ü�� �л����� �����͸�
*		�����Ͽ� �����͸� �̿��� ���� ������ �����ϴ� ���α׷��̴�.
*���α׷� �ۼ��� : ��ΰ�(2022�� 05�� 01��)
*���� Update : Version 1.0, 2022�� 05�� 01��(��ΰ�)
*============================================================================
*���α׷� ����/���� �̷�
*============================================================================
*���α׷� ����/�����۾���   ����   ����/���ϳ���
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
void printStudent(Student* pST);  //�л� ���
void printStudents(Student* stArr, int num_students); //�л� ���
void shuffleStudents(Student students[], int num_students); //�л� �迭�� �ڼ���
void statisticsGPA(Student students[], int num_students);  //GPA�� ���ġ ���
Student* searchBestGPAStudent(Student students[], int num);  //GPA�� �ִ�ġ ���
Student* searchWorstGPAStudent(Student students[], int num); //GPA�� �ּ�ġ ���
/*void sortStudents_by_GPA(Student students[], int num);  //GPA�� �������� ����
void sortStudents_by_ST_ID(Student students[], int num);  //�й����� �������� ����
void sortStudents_by_name(Student students[], int num);  //�̸����� �������� ����
void sortStudents_by_BirthDate(Student students[], int num);  //���Ϸ� �������� ����
void sortStudents_by_TelNumber(Student students[], int num);  //��ȭ��ȣ�� �������� ����*/
int compareStudents(Student* pST1, Student* pST2, ST_KEY st_key);
void sortStudents(Student students[], int num, ST_KEY sort_key);
#endif