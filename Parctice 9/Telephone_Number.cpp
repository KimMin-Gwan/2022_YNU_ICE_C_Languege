#include <stdio.h>
#include "Telephone_Number.h"
void printTelephoneNumber(Tel_Number telNo)
{
	printf("(+%02d-%03d-%04d-%04d)", telNo.nation_code, telNo.region_no, telNo.switch_no, telNo.line_no);
}
int compareTelNumber(Tel_Number tn1, Tel_Number tn2)
{
	if (tn1.nation_code > tn2.nation_code)
		return 1;
	else if (tn1.nation_code < tn2.nation_code)
		return -1;
	else if (tn1.region_no > tn2.region_no)
		return 1;
	else if (tn1.region_no < tn2.region_no)
		return -1;
	else if (tn1.switch_no > tn2.switch_no)
		return 1;
	else if (tn1.switch_no < tn2.switch_no)
		return -1;
	else if (tn1.line_no < tn2.line_no)
		return 1;
	else if (tn1.line_no < tn2.line_no)
		return -1;
	else
		return 0;
}