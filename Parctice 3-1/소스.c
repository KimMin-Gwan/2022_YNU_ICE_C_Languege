/*
*파일명 : "프로그래밍 언어_21912229_김민관_실습 3 - 1"
*프로그램의 목적 및 기본 기능: 
*      -이 프로그램은 날짜를 입력하고 입력한 날짜가 1년 1월 1일 일 때 부터
*		몇일이나 지났는지 확인하고 출력한다. 그리고 해당 날짜가 포함된 달력을
*		출력하는 프로그램이다.
*프로그램 작성자 : 김민관(2022년 03월 12일)
*최종 Update : Version 1.3, 2022년 03월 17일(김민관)
*==============================================================================
*프로그램 수정/보완 이력
*==============================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
*김민관      2022/03/14      v1.1   프로그램을 반복하여 출력하게 함
*김민관      2022/03/15		 v1.2   bool이 타입 정의
*김민관		 2022/03/17      v1.3   날짜 입력 오류 및 잘못된 날짜 재입력 시스템
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
bool isLeapYear(int year);		//윤년확인 함수선언
int getDaysFromJan01AD01(int year, int month); // 1년1월1일로부터 지난 날짜를 구하는 함수선언
void printCalendar(int year, int month); //달력을 출력하는 함수 선언
bool check_day(int year, int month, int day);  //입력한 날짜가 가능한지 확인하는 함수선언
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
		if (check_day(year, month, date) != TRUE)  //잘못된 날짜가 입력되면 다시 입력
		{
			printf(">>>>>  Wrong Input, Try Again  <<<<< \n");
			continue;
		}
		if (year == 0)  //프로그램을 종료하고싶다면 0을 입력
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


int getDaysFromJan01AD01(int year, int month) //1년1월1일부터 몇일째인지 구하는 식
{
	int daysFromAD01Jan01 = 0;
	int daysInYear = 0;
	int daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int day = 1;
	for (int y = 1; y < year; y++)
	{
		daysInYear = isLeapYear(y) ? 366 : 365;  //평년 365를 더하고, 윤년일때 366을 더한다.
		daysFromAD01Jan01 += daysInYear;
	}
	if (isLeapYear(year)) //윤년일때 2월을 29일로 한다.
		daysInMonth[2] = 29;
	for (int m = 1; m < month; m++)
	{
		daysFromAD01Jan01 += daysInMonth[m]; //달마다 날짜를 더한다.
	}
	daysFromAD01Jan01 += day; //남은 일수를 모두 더한다.
	return daysFromAD01Jan01;
}

bool isLeapYear(int year) //윤년계산 함수(400의 배수 이거나 4의 배수이고 100의 배수가 아닌 해)
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
	weekDay = daysFromJan01AD01 % DAYS_PER_WEEK; //해당 달이 무슨 요일에 시작하는지 체크
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
			if (blank < weekDay) //시작하는 날 앞까지 공백
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