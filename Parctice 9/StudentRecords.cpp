/* StudentRecords */
#include "Student.h"
Student students[] =
{
{ 21911000, "Kim, G-M", { 1990, 10, 5 }, { 82, 53, 805, 1234 }, 3.57 },
{ 21822075, "Yoon, S-M", { 1990, 4, 5 }, { 82, 53, 811, 1550 }, 4.37 },
{ 21433015, "Hwang, S-S", { 1989, 1, 10 }, { 82, 53, 817, 1005 }, 2.72 },
{ 21644054, "Lee, K-M", { 1991, 5, 15 }, { 82, 10, 9112, 9876 }, 3.35 },
{ 21255340, "Hong, G-M", { 1990, 2, 5 }, { 82, 55, 810, 5678 }, 3.57 },
{ 21766056, "Zang, S-M", { 1990, 3, 15 }, { 82, 10, 9112, 1600 }, 4.45 },
{ 21177017, "Park, S-S", { 1989, 7, 10 }, { 82, 34, 817, 1098 }, 4.12 },
{ 21588053, "Choi, Y-H", { 1992, 9, 25 }, { 82, 53, 845, 5764 }, 3.85 },
{ 21399019, "Ahn, D-J", { 1988, 10, 3 }, { 82, 31, 817, 1038 }, 3.21 },
{ 21010053, "Kwak, S-B", { 1994, 11, 15 }, { 82, 2, 897, 8778 }, 4.43 },
{ 21021053, "Song, W-B", { 1993, 5, 15 }, { 82, 34, 345, 1234 }, 4.47 },
{ 21133053, "Gong, G-W", { 1992, 6, 25 }, { 82, 55, 543, 4321 }, 2.35 },
{ 20911042, "Bhang, S-H", { 1987, 12, 25 }, { 82, 2, 123, 4567 }, 3.75 },
{-1}
};

void printStudent(Student* pST)
{
	printf("Student [ID: %9d, %-10s, GPA : %5.2lf, ", pST->ST_ID, pST->name, pST->GPA);
	printDate(pST->birth_date);
	printTelephoneNumber(pST->tel_number);
}

void printStudents(Student* stArr, int num)
{
	Student* st = stArr; //�迭�� �����ϱ� ���� ������ st
	for (int i = 0; i < num; i++)
	{
		printStudent(st); //����Ʈ
		printf("\n");
		st++; //�迭�� ����
	}
}

void shuffleStudents(Student students[], int num_students) //�л� �迭�� �ڼ���
{
	int st_1, st_2;
	Student st_temp;
	srand(time(0));
	for (int i = 0; i < num_students; i++)
	{
		st_1 = rand() % num_students; //�������� ����
		st_2 = rand() % num_students;  //���� ���� ����
		/*swap*/
		st_temp = students[st_1];
		students[st_1] = students[st_2];
		students[st_2] = st_temp;
	}
}

void statisticsGPA(Student students[], int num_students) //GPA�� ���ġ ���
{
	double sum = 0;
	double avg;
	double max = 0;
	double min = students[0].GPA;
	for (int i = 0; i < num_students; i++)
	{
		if (students[i].GPA > max)
			max = students[i].GPA;
		if (students[i].GPA < min)
			min = students[i].GPA;
		sum += students[i].GPA;

	}
	avg = sum / num_students;
	printf("GPA_MAX (%2.2lf), GPA_MIN (%2.2lf), GPA_avg (%2.2lf)", min, max, avg);
}

Student* searchBestGPAStudent(Student students[], int num)  //GPA�� �ִ�ġ ���
{
	Student* pST, * pST_max;
	pST_max = pST = students; //���� ����ü�� ����Ŵ
	double GPA_max;
	GPA_max = pST->GPA; //�ʱⰪ ����
	for (int i = 1; i < num; i++)
	{
		pST = &students[i];//���� pst�� ����Ű�� ����ü �迭
		if (pST->GPA > GPA_max)//��
		{
			GPA_max = pST->GPA; //���� pst�� ������� GPA���� �ִ����� ����
			pST_max = pST; //�ִ� �����Ͱ� ����Ű�� �ּҸ� ���� pst�� ����Ű�� �ּҷ� ����
		}
	}
	return pST_max; //�ִ밪 ����
}

Student* searchWorstGPAStudent(Student students[], int num) //GPA�� �ּ�ġ ���
{
	Student* pST, * pST_min;
	pST_min = pST = students; //���� ����ü�� ����Ŵ
	double GPA_min;
	GPA_min = pST->GPA; //�ʱⰪ ����
	for (int i = 1; i < num; i++)
	{
		pST = &students[i]; //���� pst�� ����Ű�� ����ü �迭
		if (pST->GPA < GPA_min)  //��
		{
			GPA_min = pST->GPA; //���� pst�� ������� GPA���� �ּڰ����� ����
			pST_min = pST; //�ּ� �����Ͱ� ����Ű�� �ּҸ� ���� pst�� ����Ű�� �ּҷ� ����
		}
	}
	return pST_min; //�ּڰ�  ����
}

void sortStudents(Student students[], int num, ST_KEY sort_key)
{
	Student* pST, * pST_max;
	Student temp; //�ӽ÷� ���� ���� Student�� ����
	int max_index; //index
	for (int i = 0; i < num; i++)
	{
		pST_max = pST = &students[i]; //Ž���� �����ϴ� ��ġ i
		max_index = i; //�ʱⰪ
		for (int j = i + 1; j < num; j++)
		{
			pST = &students[j];
			//if (pST->GPA > pST_max->GPA)//��
			if(compareStudents(pST, pST_max, sort_key) == -1)
			{//GPA_max = pST->GPA; //���� pst�� ������� GPA���� �ִ����� ����
				max_index = j;
				pST_max = pST; //�ִ� �����Ͱ� ����Ű�� �ּҸ� ���� pst�� ����Ű�� �ּҷ� ����
			}
		}
		if (max_index != i) //���� Ž������ ���� ���� ū ���� �ִ� �迭�� ��ȯ
		{
			temp = students[max_index];
			students[max_index] = students[i];
			students[i] = temp;
		}
	}
}

int compareStudents(Student* pST1, Student* pST2, ST_KEY st_key)
{
	if (st_key == ST_ID)
	{
		if (pST1->ST_ID < pST2->ST_ID)
			return -1;
		else if (pST1->ST_ID > pST2->ST_ID)
			return 1;
		else
			return 0;
	}
	else if (st_key == NAME)
	{
		if (strcmp(pST1->name, pST2->name) < 0)
			return -1;
		else if (strcmp(pST1->name, pST2->name) > 0)
			return 1;
		else
			return 0;
	}
	else if (st_key == GPA)
	{
		if (pST1->GPA < pST2->GPA)
			return 1; 
		else if (pST1->GPA > pST2->GPA)
			return -1;
		else
			return 0;
	}
	else if (st_key == DOB)
	{
		if (compareDate(pST1->birth_date, pST2->birth_date) < 0)
			return -1;
		else if (compareDate(pST1->birth_date, pST2->birth_date) > 0)
			return 1;
		else
			return 0;
	}
	else if (st_key == TEL_NUM)
	{
		if (compareTelNumber(pST1->tel_number, pST2->tel_number) < 0)
			return -1;
		else if (compareTelNumber(pST1->tel_number, pST2->tel_number) > 0)
			return 1;
		else
			return 0;
	}
	else
	{
		printf("Sorting students with given sort_key is not defined yet !!");
		return 0;
	}
}

/*void sortStudents_by_GPA(Student students[], int num) //GPA�� �������� ����
{

*/
/*
void sortStudents_by_ST_ID(Student students[], int num)  //�й����� �������� ����
{
	Student* pST, * pST_min;
	Student temp; //�ӽ÷� ���� ���� Student�� ����
	int st_id_min_index; //index
	for (int i = 0; i < num; i++)
	{
		pST_min = pST = &students[i]; //Ž���� �����ϴ� ��ġ i
		st_id_min_index = i; //�ʱⰪ
		for (int j = i + 1; j < num; j++)
		{
			pST = &students[j];
			if (pST->ST_ID < pST_min->ST_ID)//��
			{
				st_id_min_index = j; //�������� �ε����� ��ġ ����
				pST_min = pST; //�ִ� �����Ͱ� ����Ű�� �ּҸ� ���� pst�� ����Ű�� �ּҷ� ����
			}
		}
		if (st_id_min_index != i) //���� Ž������ ���� ���� ū ���� �ִ� �迭�� ��ȯ
		{
			temp = students[st_id_min_index];
			students[st_id_min_index] = students[i];
			students[i] = temp;
		}
	}
}

void sortStudents_by_name(Student students[], int num)  //�̸����� �������� ����
{
	Student* pST, * pST_min;
	Student temp; //�ӽ÷� ���� ���� Student�� ����
	int name_min_index; //index
	for (int i = 0; i < num; i++)
	{
		pST_min = pST = &students[i]; //Ž���� �����ϴ� ��ġ i
		name_min_index = i; //�ʱⰪ
		for (int j = i + 1; j < num; j++)
		{
			pST = &students[j];
			if (strcmp(pST->name, pST_min->name) < 0)//�� ���� �μ��� �� ������ ������ ��ȯ
			{
				name_min_index = j;//�������� �ε����� ��ġ ����
				pST_min = pST; //�ִ� �����Ͱ� ����Ű�� �ּҸ� ���� pst�� ����Ű�� �ּҷ� ����
			}
		}
		if (name_min_index != i) //���� Ž������ ���� ���� ū ���� �ִ� �迭�� ��ȯ
		{
			temp = students[name_min_index];
			students[name_min_index] = students[i];
			students[i] = temp;
		}
	}
}

void sortStudents_by_BirthDate(Student students[], int num)  //���Ϸ� �������� ����
{
	Student* pST, * pST_min;
	Student temp; //�ӽ÷� ���� ���� Student�� ����
	int Min_Birthdate_id; //index
	for (int i = 0; i < num; i++)
	{
		pST_min = pST = &students[i]; //Ž���� �����ϴ� ��ġ i
		Min_Birthdate_id = i; //�ʱⰪ
		for (int j = i + 1; j < num; j++)
		{
			pST = &students[j];
			if (compareDate(pST->birth_date, pST_min->birth_date) == -1 )//�� ���� �μ��� �������� -1�� ��ȯ
			{
				Min_Birthdate_id = j; //�������� �ε����� ��ġ ����
				pST_min = pST; //�ִ� �����Ͱ� ����Ű�� �ּҸ� ���� pst�� ����Ű�� �ּҷ� ����
			}
		}
		if (Min_Birthdate_id != i) //���� Ž������ ���� ���� ū ���� �ִ� �迭�� ��ȯ
		{
			temp = students[Min_Birthdate_id];
			students[Min_Birthdate_id] = students[i];
			students[i] = temp;
		}
	}
}
	
void sortStudents_by_TelNumber(Student students[], int num)  //��ȭ��ȣ�� �������� ����
{
	Student* pST, * pST_min;
	Student temp; //�ӽ÷� ���� ���� Student�� ����
	int Min_TelNumber_index; //index
	for (int i = 0; i < num; i++)
	{
		pST_min = pST = &students[i]; //Ž���� �����ϴ� ��ġ i
		Min_TelNumber_index = i; //�ʱⰪ
		for (int j = i + 1; j < num; j++)
		{
			pST = &students[j];
			if (compareTelNumber(pST->tel_number, pST_min->tel_number) == -1)//�� ���� �μ��� �������� -1�� ��ȯ
			{
				Min_TelNumber_index = j; //�������� �ε����� ��ġ ����
				pST_min = pST; //�ִ� �����Ͱ� ����Ű�� �ּҸ� ���� pst�� ����Ű�� �ּҷ� ����
			}
		}
		if (Min_TelNumber_index != i) //���� Ž������ ���� ���� ū ���� �ִ� �迭�� ��ȯ
		{
			temp = students[Min_TelNumber_index];
			students[Min_TelNumber_index] = students[i];
			students[i] = temp;
		}
	}
}

*/