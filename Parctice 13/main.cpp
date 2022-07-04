#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <thread>
#include <mutex>
#include "Thread.h"
#include "DLL_EvQ.h"
#include "Event.h"
#include "ConsoleDisplay.h"
using namespace std;
void main()
{
	//FILE* fout;
	DLL_EvQ dll_EvQ_PriH, dll_EvQ_PriL; //���� ���� ����ť
	Event* pEvent; //�̺�Ʈ ������
	int myAddr = 0; //�ʱ� �ּ� 0
	int event_handler_addr, eventPriority;
	LARGE_INTEGER pc_freq; //�ð� ������
	//fout = fopen("SimOutput.txt", "w");
	//if (fout == NULL)
	//{
	//	printf("Error in opening SimOutput.txt file in write mode !!\n");
	//	exit;
	//}
	initDLL_EvQ(&dll_EvQ_PriH, 0); //�ʱ�ȭ
	initDLL_EvQ(&dll_EvQ_PriL, 1); //�ʱ�ȭ

	srand(time(NULL));
	ThreadParam_Ev thrdParam_EventGen[NUM_EVENT_GENERATORS], thrdParam_EventHndlr[NUM_EVENT_HANDLERS];
	thread thread_evHandlers[NUM_EVENT_HANDLERS];
	thread thread_evGens[NUM_EVENT_GENERATORS];
	mutex cs_main; //���� ���ý�
	mutex cs_thrd_mon; //������ ���ý�
	ThreadStatMon thrdMon; //����͸��� ����
	HANDLE consHndlr; //�ܼ� �����
	THREAD_FLAG eventThreadFlag = RUN; //�۵� ���� ǥ�� - �ʱⰪ : ������ 
	int count, totalEventGenerated, totalEventProcessed; //���ġ ��Ͽ�
	Event eventProcessed[TOTAL_NUM_EVENTS]; //���� ��Ͽ�

	/*���� ���� �ʱ�ȭ*/
	consHndlr = initConsoleHandler();
	QueryPerformanceFrequency(&pc_freq);
	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGen = 0;
	thrdMon.totalEventProc = 0;
	thrdMon.numEventProcs_priH = 0;
	thrdMon.numEventProcs_priL = 0;

	/*��� ����͸� �迭 �ʱ�ȭ*/
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.eventProcessed[ev].event_no = -1; 
		thrdMon.eventProcessed[ev].event_pri = -1;
	}


	/* �̺�Ʈ ���� */
	for (int p = 0; p < NUM_EVENT_HANDLERS; p++) // 0 ~ 1
	{
		thrdMon.eventsProc[p] = 0; //������ �̺�Ʈ �迭 �ʱ�ȭ
		//thrdParam_EventHndlr[p].fout = fout;
		thrdParam_EventHndlr[p].role = EVENT_HANDLER; //����
		thrdParam_EventHndlr[p].myAddr = p; // ������ �ּ� 0 ~ 1
		thrdParam_EventHndlr[p].pCS_main = &cs_main;
		thrdParam_EventHndlr[p].pCS_thrd_mon = &cs_thrd_mon;
		thrdParam_EventHndlr[p].EvQ_PriH = &dll_EvQ_PriH; //���� ����ť �ּ�
		thrdParam_EventHndlr[p].EvQ_PriL = &dll_EvQ_PriL; //���� ����ť �ּ�
		thrdParam_EventHndlr[p].maxRound = MAX_ROUND; //�ִ� ���� ��
		thrdParam_EventHndlr[p].pThrdMon = &thrdMon; //������ �����
		thrdParam_EventHndlr[p].PC_freq = pc_freq; //�۵� ���ļ� 
		thread_evHandlers[p] = thread(Thread_EventHandler, &thrdParam_EventHndlr[p]); //�����带 2�� ����
		cs_main.lock();
		printf("%d-th thread_EventHandler is created and activated (id: %d)\n", p, thread_evHandlers[p].get_id());
		cs_main.unlock();
	}


	/* �̺�Ʈ ������*/
	for (int g = 0; g < NUM_EVENT_GENERATORS; g++) //0 ~ 2
	{
		thrdMon.eventsGen[g] = 0; //���� �̺�Ʈ �迭 �ʱ�ȭ
		thrdParam_EventGen[g].role = EVENT_GENERATOR; //����
		thrdParam_EventGen[g].myAddr = g; // �߻��� �ּ� 0 ~ 2
		thrdParam_EventGen[g].pCS_main = &cs_main;
		thrdParam_EventGen[g].pCS_thrd_mon = &cs_thrd_mon;
		thrdParam_EventGen[g].EvQ_PriH = &dll_EvQ_PriH; //���� ����ť
		thrdParam_EventGen[g].EvQ_PriL = &dll_EvQ_PriL; //���� ����ť
		thrdParam_EventGen[g].targetEventGen = NUM_EVENTS_PER_GEN; //�� �����忡�� ���� �̺�Ʈ ��
		thrdParam_EventGen[g].maxRound = MAX_ROUND; //�ִ� ���� ��
		thrdParam_EventGen[g].pThrdMon = &thrdMon; //������ �����
		thrdParam_EventGen[g].PC_freq = pc_freq; //�۵� ���ļ�
		thread_evGens[g] = thread(Thread_EventGenerator, &thrdParam_EventGen[g]); //�����带 3�� ����
		cs_main.lock();
		printf("%d-th thread_EventGen is created and activated (id: %d)\n", g, thread_evGens[g].get_id());
		cs_main.unlock();
	}


	/* ���� �۵� �κ� - ���ۿ��ο� ���� ����͸� */
	for (int round = 0; round < MAX_ROUND; round++)
	{
		cs_main.lock();
		system("cls");
		gotoxy(consHndlr, 0, 0);
		printf("Thread monitoring by main() :: round(%2d): \n", round);
		cs_thrd_mon.lock();
		for (int i = 0; i < NUM_EVENT_GENERATORS; i++)
		{
			printf(" Event_Gen[%d] generated %2d events.\n", i, thrdMon.eventsGen[i]);
		}
		printf("Event_Generators have generated total %2d events\n", thrdMon.totalEventGen);
		totalEventGenerated = thrdMon.totalEventGen; //���� �̺�Ʈ ����
		printf("\nTotal Generated Events (current total %d events)\n ", totalEventGenerated);
		for (int ev = 0; ev < totalEventGenerated; ev++)
		{
			pEvent = &thrdMon.eventGenerated[ev]; //���� �̺�Ʈ�� �����ͷ� ����
			if (pEvent != NULL)
			{
				printEvent(pEvent); //���� �̺�Ʈ ���
				if (((ev + 1) % EVENT_PER_LINE) == 0) //�ٴ� �ִ� ��� 5��
					printf("\n ");
			}
		}
		printf("\n");

		printf("\nEvent_Handlers have processed total %2d events ", thrdMon.totalEventProc);
		printf("(event__PriH (%2d), event_PriL (%2d))\n", thrdMon.numEventProcs_priH, thrdMon.numEventProcs_priL);
		for (int i = 0; i < NUM_EVENT_HANDLERS; i++)
		{
			printf(" Event_Proc[%d] processed %2d events.\n", i, thrdMon.eventsProc[i]);
		}
		
		printf("\n");
		printf("DLL_EvQ_PriH (%3d events):\n ", dll_EvQ_PriH.num_event);
		printDLL_EvQ(&dll_EvQ_PriH); //���� ����ť�� �ִ� �̺�Ʈ ����
		printf("\n");
		printf("DLL_EvQ_PriL (%3d events):\n ", dll_EvQ_PriL.num_event);
		printDLL_EvQ(&dll_EvQ_PriL); //���� ����ť�� �ִ� �̺�Ʈ ����
		printf("\n");
		totalEventProcessed = thrdMon.totalEventProc; //�۵���Ų �̺�Ʈ�� �� ����
		printf("\nTotal Processed Events (current total %d events):\n ", totalEventProcessed);
		count = 0;
		for (int ev = 0; ev < totalEventProcessed; ev++)
		{
			pEvent = &thrdMon.eventProcessed[ev]; //�۵���Ų �̺�Ʈ�� �����ͷ� ����
			if (pEvent != NULL)
			{
				printEvent(pEvent); //�۵���Ų �̺�Ʈ ���
				if (((ev + 1) % EVENT_PER_LINE) == 0) //�ٴ� �ִ� ��� 5��
					printf("\n ");
			}
		}
		printf("\n");
		cs_thrd_mon.unlock();
		if (totalEventProcessed >= TOTAL_NUM_EVENTS) //�� ���� �̺�Ʈ�� ���� 60���� ������
		{
			printf("!!! TotalEventProcessed (%d) is reached to target TOTAL_NUM_EVENTS(% d)\n", totalEventProcessed, TOTAL_NUM_EVENTS);
			eventThreadFlag = TERMINATE;  //���� : ����
			cs_main.unlock();
			break;
		}
		cs_main.unlock();
		Sleep(200);
	} 


	for (int p = 0; p < NUM_EVENT_HANDLERS; p++)
	{
		thread_evHandlers[p].join(); //��� ���� �����尡 ������ ������ ���� ���
	}
	printf("All threads of event handlers are terminated !!\n");


	for (int g = 0; g < NUM_EVENT_GENERATORS; g++)
	{
		thread_evGens[g].join(); //��� �۵��� �����尡 ������ ������ ���� ���
	}
	printf("All threads of event generators are terminated !!\n"); 

	//calc_elapsed_time(thrdMon.eventProcessed, thrdMon.numPktProcs, freq);
	/*�ð� ����*/
	double min, max, avg, sum;
	int min_event, max_event;
	min = max = sum = thrdMon.eventProcessed[0].t_elapsed;
	min_event = max_event = 0;
	for (int i = 1; i < TOTAL_NUM_EVENTS; i++)
	{
		sum += thrdMon.eventProcessed[i].t_elapsed; //��
		if (min > thrdMon.eventProcessed[i].t_elapsed)
		{
			min = thrdMon.eventProcessed[i].t_elapsed; //�ּ�
			min_event = i; 
		}
		if (max < thrdMon.eventProcessed[i].t_elapsed)
		{
			max = thrdMon.eventProcessed[i].t_elapsed; //�ִ�
			max_event = i;
		}
	}
	avg = sum / (double)TOTAL_NUM_EVENTS; //���
	/*�ð� ��� ���*/
	printf("Minimum event processing time: %8.2lf[ms] for ", min * 1000);
	printEvent_withTime(&thrdMon.eventProcessed[min_event]); printf("\n");
	printf("Maximum event processing time: %8.2lf[ms] for ", max * 1000);
	printEvent_withTime(&thrdMon.eventProcessed[max_event]); printf("\n");
	printf("Average event processing time: %8.2lf[ms] for total %d events\n", avg * 1000, TOTAL_NUM_EVENTS);
	printf("\n");
}