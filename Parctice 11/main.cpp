/* main() for Priority-Queue for Events */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Event.h"
#include "CirQ_Event.h"
#include "PriQ_Event.h"
#define EVENT_GENERATOR 0
#define TOTAL_NUM_EVENTS 127
#define MAX_ROUND 100
#define INIT_PriQ_SIZE 1
void test_FIFO_CirQ_Event(FILE * fout, int max_events_per_round);
void test_PriQ_Event(FILE* fout, int max_events_per_round);

void main()
{
	FILE* fout; //���� ��� ������
	int menu;
	int max_events_per_round;
	fout = fopen("output.txt", "w"); //���� ���
	if (fout == NULL)
	{
		printf("Error in creation of output.txt file !!\n");
		exit(-1);
	}
	srand(time(0));
	while (1)
	{
		printf("\nAvailable Menu : \n");
		printf(" 1. Test FIFO/CirQ Event.\n"); //���Լ��� �˰��� 
		printf(" 2. Test PriQ Event.\n"); //�켱 ���� ť�� ó�� ���� 
		printf("Input menu (0 to quit) : ");
		scanf("%d", &menu);
		if (menu == 0)
			break;
		printf("Input num_events per round :");
		scanf("%d", &max_events_per_round);
		switch (menu)
		{
		case 1:
			test_FIFO_CirQ_Event(fout, max_events_per_round);
			break;
		case 2:
			test_PriQ_Event(fout, max_events_per_round);
			break;
		default:
			break;
		}
	}
	fclose(fout);
}

void test_FIFO_CirQ_Event(FILE* fout, int max_events_per_round) //���Լ��� �̺�Ʈ
{
	CirQ_Event* pCirQ_Event; //ȯ�� ť�̺�Ʈ ������
	Event ev, * pEv = NULL; //�̺�Ʈ, �̺�Ʈ ������
	Event processed_events[TOTAL_NUM_EVENTS]; //�̺�Ʈ ó�� �迭
	int total_processed_events = 0; //ó���� �̺�Ʈ�� �� ����
	int total_generated_events = 0; //������ �̺�Ʈ�� �� ����
	int num_events = 0; //�� �̺�Ʈ ����
	int num_generated_round = 0; //�̺�Ʈ�� �����ߴ� Ƚ��
	int num_processed_round = 0; //�̺�Ʈ�� ó���ߴ� Ƚ��
	fprintf(fout, "Testing Event Handling with FIFO Circular Queue\n");
	pCirQ_Event = (CirQ_Event*)calloc(1, sizeof(CirQ_Event)); //ȯ�� ť�� ������ŭ ���� �迭 ����
	printf("Initializing FIFO_CirQ of capacity (%d)\n", max_events_per_round);	//�̹� �̺�Ʈ �������� �ʱ�ȭ ��Ų ȯ��ť
	fprintf(fout, "Initializing FIFO_CirQ of capacity (%d)\n", max_events_per_round);
	pCirQ_Event = initCirQ(pCirQ_Event, max_events_per_round);
	//fprintQueue(fout, pCirQ_Event);
	//fprintf(fout, "\nEnqueuing data into event circular queue: \n");
	for (int round = 0; round < MAX_ROUND; round++) //�̺�Ʈ ���� ����
	{
		fprintf(fout, "start of Round(%2d) ****\n", round); 
		if (total_generated_events < TOTAL_NUM_EVENTS) //�������� �̺�Ʈ ��������
		{
			num_events = max_events_per_round; // �̺�Ʈ�� ������ �Է¹��� ����� �ִ� �̺�Ʈ�� ����
			if ((total_generated_events + num_events) > TOTAL_NUM_EVENTS) //���� ���尡 ������ �̺�Ʈ ���� ������
				num_events = TOTAL_NUM_EVENTS - total_generated_events;  //���� ����� ��ü���� ������ ���η� ����
			fprintf(fout, "generate and enque %2d events\n", num_events);
			num_generated_round = 0; //�ʱ�ȭ
			for (int i = 0; i < num_events; i++)
			{
				if (isCirQFull(pCirQ_Event))//ȯ�� ť�� �ڸ��� �����ִ��� Ȯ��
				{
					fprintf(fout, " !!! CirQ_Event is full --> skip generation and enqueueing of event. \n");
						break;
				}
				pEv = genEvent(pEv, EVENT_GENERATOR, total_generated_events, TOTAL_NUM_EVENTS - total_generated_events - 1);//pEv�� �̺�Ʈ ����(�ӽ�)
				fprintf(fout, ">>> Enqueue event = "); //ť�� ����� �̺�Ʈ ���
				fprintEvent(fout, pEv);
				fprintf(fout, "\n");
				enCirQ(fout, pCirQ_Event, *pEv); //������ �̺�Ʈ�� ȯ��ť�� �Ҵ�
				fprintCirQ(fout, pCirQ_Event);
				free(pEv); //pEv ������ ����
				total_generated_events++; //�̺�Ʈ ���������� ����
				num_generated_round++; //���� ���尡 �������� ����
			} // end for
		} // end if
		 //fprintf(fout, "\nDequeuing data from event circular queue: \n");
		num_events = max_events_per_round; //������ �̺�Ʈ ������ ���߱�
		if ((total_processed_events + num_events) > TOTAL_NUM_EVENTS) 
			num_events = TOTAL_NUM_EVENTS - total_processed_events; 
		fprintf(fout, "dequeue %2d events\n", num_events);
		num_processed_round = 0;
		for (int i = 0; i < num_events; i++) //�̺�Ʈ ó�� ����
		{
			if (isCirQEmpty(pCirQ_Event)) //ó���� ȯ��ť�� ���� �ʾҴٸ� �극��ũ
				break;
			pEv = deCirQ(fout, pCirQ_Event); //�̺�Ʈ ó��
			if (pEv != NULL)
			{
				fprintf(fout, "<<< Dequed event = ");
				fprintEvent(fout, pEv);
				fprintf(fout, "\n");
				processed_events[total_processed_events] = *pEv; //ó���� ���� �̺�Ʈ ����
				total_processed_events++; //ó�������� ����
				num_processed_round++;//ó�� ���尡 �������� ����
			}
			fprintCirQ(fout, pCirQ_Event);
		} // end for
		/* Monitoring simulation status */
		fprintf(fout, "Round(%2d): generated_in_this_round(%3d), total_generated_events(%3d), processed_in_this_round(% 3d), total_processed_events(% 3d), \
events_in_queue(% 3d)\n\n", round, num_generated_round, total_generated_events, num_processed_round, total_processed_events, pCirQ_Event->num_elements);
		printf("Round(%2d): generated_in_this_round(%3d), total_generated(%3d), processed_in_this_round(% 3d), total_processed_events(% 3d), \
events_in_queue(% 3d)\n", round, num_generated_round, total_generated_events, num_processed_round, total_processed_events, pCirQ_Event->num_elements);
		if (total_processed_events >= TOTAL_NUM_EVENTS)
			break;
	} // end for()
	printf("Processed Events :\n");
	for (int i = 0; i < TOTAL_NUM_EVENTS; i++) //ó���� ������� �迭�� ����� ���� ���
	{
		printf("Ev(id:%3d, pri:%3d), ", processed_events[i].event_no, processed_events[i].event_pri);
		if ((i + 1) % 5 == 0)
			printf("\n");
	}
	printf("\n");
	delCirQ(pCirQ_Event); //ť ����(�ݳ�)
}

void test_PriQ_Event(FILE* fout, int max_events_per_round)
{
	PriQ_Event* pPriQ_Ev;
	Event* pEv = NULL;
	Event processed_events[TOTAL_NUM_EVENTS]; //�Ϸ��� �̺�Ʈ ����
	int data; 
	int total_processed_events = 0;
	int total_generated_events = 0;
	int num_events = 0;
	int num_generated_round = 0;
	int num_processed_round = 0;
	fprintf(fout, "Testing Event Handling with Priority Queue\n");
	pPriQ_Ev = (PriQ_Event*)malloc(sizeof(PriQ_Event));// PriQ����ü ũ�� �Ҵ�
	if (pPriQ_Ev == NULL) //�Ҵ� �������� ����
	{
		printf("Error in malloc() for PriorityQueue_Event !\n");
		fclose(fout);
		exit(-1);
	}
	printf("Initializing PriorityQueue_Event of capacity (%d)\n", INIT_PriQ_SIZE); 
	initPriQ_Ev(pPriQ_Ev, "PriorityQueue_Event", INIT_PriQ_SIZE); //�̺�Ʈ �ʱⰪ ����(�� 1�� ũ�⸦ ������)
	for (int round = 0; round < MAX_ROUND; round++)
	{
		fprintf(fout, "\n*** Start of round(%2d)...\n", round);
		num_generated_round = 0;
		if (total_generated_events < TOTAL_NUM_EVENTS)//�̺�Ʈ ���� ����
		{
			num_events = max_events_per_round;// �̺�Ʈ�� ������ �Է¹��� ����� �ִ� �̺�Ʈ�� ����
			if ((total_generated_events + num_events) > TOTAL_NUM_EVENTS) //���� ���尡 ������ �̺�Ʈ ���� ������
				num_events = TOTAL_NUM_EVENTS - total_generated_events; //���� ����� ��ü���� ������ ���η� ����
			fprintf(fout, ">>> enque %2d events\n", num_events);
			for (int i = 0; i < num_events; i++)
			{
				pEv = genEvent(pEv, 0, total_generated_events, TOTAL_NUM_EVENTS - total_generated_events - 1);//�̺�Ʈ ����
				if (pEv == NULL)
				{ //���� ���� �ڸ��� NULL���̸� �����ϰ� ����
					printf("Error in generation of event !!\n");
					fclose(fout);
					exit(-1);
				}
				fprintf(fout, " *** enqued event : ");
				fprintEvent(fout, pEv);
				enPriQ_Ev(pPriQ_Ev, pEv); //������ �̺�Ʈ �Ҵ�
				total_generated_events++; //������ �̺�Ʈ ���� ����
				num_generated_round++; //���尡 �������� ���� Ƚ�� ����
				fprintPriQ_Ev(fout, pPriQ_Ev);
			}
		}
		//����� ����
		//fprintf(fout, "\n======================================================\n");
		//fprintf(fout, "\nRemoving min data from Priority Queue . . . \n");
		num_events = max_events_per_round;  //������ �̺�Ʈ ������ ���߱�
		if ((total_processed_events + num_events) > TOTAL_NUM_EVENTS)
			num_events = TOTAL_NUM_EVENTS - total_processed_events;
		fprintf(fout, "<<< dequeue %2d events\n", num_events);
		num_processed_round = 0; //�۵��Ϸ��� ���μ��� ���� �ʱ�ȭ
		for (int i = 0; i < num_events; i++)
		{
			pEv = removeMinPriQ_Event(pPriQ_Ev); //���� �켱������ ó���Ǿ��ϴ� �̺�Ʈ ����
			if (pEv == NULL) //���� �̺�Ʈ�� ���̻� ���ٸ� �극��ũ
			{
				fprintf(fout, " PriQ is empty\n");
				break;
			}
			fprintf(fout, " *** dequeued event : ");
			fprintEvent(fout, pEv);
			fprintPriQ_Ev(fout, pPriQ_Ev);
			processed_events[total_processed_events] = *pEv; //�Ϸ��� ���μ��� ����
			total_processed_events++; //�Ϸ��� �̺�Ʈ Ƚ�� ����
			num_processed_round++; //���μ��� ���尡 �������� ����
		}
		/* Monitoring simulation status */
		fprintf(fout, "Round(%2d): generated_in_this_round(%3d), total_generated_events(%3d), processed_in_this_round(% 3d), total_processed_events(% 3d), events_in_queue(% 3d)\n\n",
			round, num_generated_round, total_generated_events, num_processed_round, total_processed_events, pPriQ_Ev->priQ_size);
		printf("Round(%2d): generated_in_this_round(%3d), total_generated(%3d), processed_in_this_round(% 3d), total_processed_events(% 3d), events_in_queue(% 3d)\n",
			round, num_generated_round, total_generated_events, num_processed_round, total_processed_events, pPriQ_Ev->priQ_size);
		fflush(fout); 
		if (total_processed_events >= TOTAL_NUM_EVENTS)
			break;
	}
	printf("Processed Events :\n");
	for (int i = 0; i < TOTAL_NUM_EVENTS; i++) //ó���� ������� �迭�� ����� ���� ���
	{
		printf("Ev(id:%3d, pri:%3d), ", processed_events[i].event_no, processed_events[i].event_pri); 
		if ((i + 1) % 5 == 0)
			printf("\n");
	}
	printf("\n");
	deletePriQ_Ev(pPriQ_Ev); //ť ����(�䳳)
	fprintf(fout, "\n");
}
