#include "Student.h"
#define MAX_NUM_STUDENTS 100
void main()
{
	int num_students = 0;
	int menu;
	Student* pST_GPA_max, * pST_GPA_min;
	extern Student students[];
	for (int i = 0; i < MAX_NUM_STUDENTS; i++)
	{
		if (students[i].ST_ID == -1)
			break;
		else
			num_students++;
	}
	printf("Number of studetns = %d\n", num_students);
	while (1)
	{
		printf("\n");
		printf(" 1 : print student records\n");
		printf(" 2 : calculate statistics GPA (max, min, avg) of students' \n");
		printf(" 3 : search students of best GPA and worst GPA\n");
		printf(" 4 : sort students by student ID\n");
		printf(" 5 : sort students by GPA\n");
		printf(" 6 : sort students by name\n");
		printf(" 7 : sort students by date of birth\n");
		printf(" 8 : sort studetns by telephone number\n");
		printf("0 : Quit\n");
		printf("Input menu = ");
		scanf("%d", &menu);
		if (menu == 0)
			break;
		switch (menu)
		{
		case 1: //�л� ����ü ���
			printStudents(students, num_students);
			printf("\n");
			break;
		case 2: //GPA�� ���ġ ���
			statisticsGPA(students, num_students);
			break;
		case 3: //GPA�� �ְ����� �ּ����� �˻�
			pST_GPA_max = searchBestGPAStudent(students, num_students);
			pST_GPA_min = searchWorstGPAStudent(students, num_students);
			printf("Student with best GPA : ");
			printStudent(pST_GPA_max);
			printf("\n");
			printf("Student with worst GPA : ");
			printStudent(pST_GPA_min);
			printf("\n");
			break;
		case 4: //�й��� �������� �������� ����
			sortStudents(students, num_students, ST_ID);
			printf("After sorting students by increasing order of student ID:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 5: //GPA�� �������� �������� ����
			sortStudents(students, num_students, GPA);
			printf("After sorting students by decreasing order of GPA:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 6: //�̸��� �������� �������� ����
			sortStudents(students, num_students, NAME);
			printf("After sorting students by increasing order of student name:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 7: //������ �������� �������� ����
			sortStudents(students, num_students, DOB);
			printf("After sorting students by increasing order of student birth date:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 8: //��ȭ��ȣ�� �������� �������� ����
			sortStudents(students, num_students, TEL_NUM);
			printf("After sorting students by increasing order of student's telephone number : \n");
				printStudents(students, num_students);
			printf("\n");
			break;
		default:
			break;
		}
		shuffleStudents(students, num_students); //�迭 �ڼ���
	}
}