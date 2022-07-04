//DATE 구조체의 정의와 하위 CPP의 프로토타입
#ifndef DATE_H
#define DATE_H
typedef struct
{
	int year;
	int month;
	int day;
} Date;
void printDate(Date date); //날짜를 출력
int compareDate(Date d1, Date d2); //날짜를 비교
#endif