//TelephoneNumber 구조체의 정의와 하위 CPP의 프로토타입
#ifndef TELEPHONE_NUMBER_H
#define TELEPHONE_NUMBER_H
#define U_SHORT unsigned short
typedef struct
{
	U_SHORT nation_code;
	U_SHORT region_no;
	U_SHORT switch_no;
	U_SHORT line_no;
} Tel_Number;
void printTelephoneNumber(Tel_Number telNo); //전화번호를 출력
int compareTelNumber(Tel_Number tn1, Tel_Number tn2); //전화번호를 비교
#endif