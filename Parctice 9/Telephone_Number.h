//TelephoneNumber ����ü�� ���ǿ� ���� CPP�� ������Ÿ��
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
void printTelephoneNumber(Tel_Number telNo); //��ȭ��ȣ�� ���
int compareTelNumber(Tel_Number tn1, Tel_Number tn2); //��ȭ��ȣ�� ��
#endif