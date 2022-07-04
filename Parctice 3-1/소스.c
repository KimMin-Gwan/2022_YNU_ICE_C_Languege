/*
*���ϸ� : "���α׷��� ���_21912229_��ΰ�_�ǽ� 3 - 1"
*���α׷��� ���� �� �⺻ ���: 
*      -�� ���α׷��� ��¥�� �Է��ϰ� �Է��� ��¥�� 1�� 1�� 1�� �� �� ����
*		�����̳� �������� Ȯ���ϰ� ����Ѵ�. �׸��� �ش� ��¥�� ���Ե� �޷���
*		����ϴ� ���α׷��̴�.
*���α׷� �ۼ��� : ��ΰ�(2022�� 03�� 12��)
*���� Update : Version 1.3, 2022�� 03�� 17��(��ΰ�)
*==============================================================================
*���α׷� ����/���� �̷�
*==============================================================================
*���α׷� ����/�����۾���   ����   ����/���ϳ���
*��ΰ�      2022/03/14      v1.1   ���α׷��� �ݺ��Ͽ� ����ϰ� ��
*��ΰ�      2022/03/15		 v1.2   bool�� Ÿ�� ����
*��ΰ�		 2022/03/17      v1.3   ��¥ �Է� ���� �� �߸��� ��¥ ���Է� �ý���
*==============================================================================
*/
#include<stdio.h>
#define WEEKDAY_AD01Jan01 MON // the weekday of AD Jan 1.
#define DAYS_PER_WEEK 7
#define NUM_MONTHS 13
#define FALSE 0
#define TRUE 1
typedef int bool;
enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT };
enum MONTH { JAN = 1, FED, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
const char* weekDayName[DAYS_PER_WEEK] = { "SUN", "MON", "TUE", "WED", "THR", "FRI", "SAT" };
const char* monthName[NUM_MONTHS] = { "", "January", "February",
"March", "April","May", "June", "July", "August", "September", "October", "November", "December" };
bool isLeapYear(int year);		//����Ȯ�� �Լ�����
int getDaysFromJan01AD01(int year, int month); // 1��1��1�Ϸκ��� ���� ��¥�� ���ϴ� �Լ�����
void printCalendar(int year, int month); //�޷��� ����ϴ� �Լ� ����
bool check_day(int year, int month, int day);  //�Է��� ��¥�� �������� Ȯ���ϴ� �Լ�����
int main(void)
{
		int year = 0;
		int month = 0;
		int date = 1;
		int days = 0;


	while (TRUE)
	{
		
		printf("Input year (0 to quit) and month for print_calender() :");
		scanf_s("%d %d", &year, &month);
		if (check_day(year, month, date) != TRUE)  //�߸��� ��¥�� �ԷµǸ� �ٽ� �Է�
		{
			printf(">>>>>  Wrong Input, Try Again  <<<<< \n");
			continue;
		}
		if (year == 0)  //���α׷��� �����ϰ�ʹٸ� 0�� �Է�
			break;
		days = getDaysFromJan01AD01(year, month);
		printCalendar(year, month);
	}
	printf("quit the process");
	return 0;
}

bool check_day(int year, int month, int day)
{
	int daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int check = 0;
	if (isLeapYear(year))
		daysInMonth[2] = 29;
	if ((year >= 1) || (year == 0))
		check += TRUE;
	if ((month >= 1) && (month <= 12))
		check += TRUE;
	if ((day >= 1) && (day <= daysInMonth[month])) 
		check += TRUE;
	if (check == 3)
		return TRUE;
	else
		return FALSE;
}


int getDaysFromJan01AD01(int year, int month) //1��1��1�Ϻ��� ����°���� ���ϴ� ��
{
	int daysFromAD01Jan01 = 0;
	int daysInYear = 0;
	int daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int day = 1;
	for (int y = 1; y < year; y++)
	{
		daysInYear = isLeapYear(y) ? 366 : 365;  //��� 365�� ���ϰ�, �����϶� 366�� ���Ѵ�.
		daysFromAD01Jan01 += daysInYear;
	}
	if (isLeapYear(year)) //�����϶� 2���� 29�Ϸ� �Ѵ�.
		daysInMonth[2] = 29;
	for (int m = 1; m < month; m++)
	{
		daysFromAD01Jan01 += daysInMonth[m]; //�޸��� ��¥�� ���Ѵ�.
	}
	daysFromAD01Jan01 += day; //���� �ϼ��� ��� ���Ѵ�.
	return daysFromAD01Jan01;
}

bool isLeapYear(int year) //������ �Լ�(400�� ��� �̰ų� 4�� ����̰� 100�� ����� �ƴ� ��)
{
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return TRUE;
	else
		return FALSE;
}

void printCalendar(int year, int month)
{
	int weekDay;
	int daysFromJan01AD01 = 0;
	int daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	daysFromJan01AD01 = getDaysFromJan01AD01(year, month, 1);
	weekDay = daysFromJan01AD01 % DAYS_PER_WEEK; //�ش� ���� ���� ���Ͽ� �����ϴ��� üũ
	if (isLeapYear(year))
		daysInMonth[2] = 29;
	printf("%d", daysFromJan01AD01);
	printf(">>>>>>> %s of %d <<<<<<<<\n", monthName[month], year);
	printf("=====================================\n");
	for (int wk = SUN; wk <= SAT; wk++)
	{
		printf("%5s", weekDayName[wk]);
	}
	printf("\n-------------------------------------\n");
	int line, date, block;
	int blank = 0;
	for (line = 0, date = 1; line < 6; line++)
	{
		for (block = 0; block < DAYS_PER_WEEK; block++)
		{
			if (blank < weekDay) //�����ϴ� �� �ձ��� ����
			{
				printf("     ");
				blank++;
			}
			else if (date <= daysInMonth[month])
			{
				printf(" %3d ", date);
				date++;
			}
			else
				break;

		}
		printf(" \n");
	}
	printf("=====================================\n");
}