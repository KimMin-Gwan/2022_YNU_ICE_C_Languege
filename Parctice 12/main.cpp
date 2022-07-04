#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <mutex>
#include "Thread.h"
#include "PriQ_Event.h"
#include "Event.h"
#include "ConsoleDisplay.h"
#include "SimParam.h"

using namespace std;

void main()
{
	PriQ_Ev priQ_Event;
	Event* pEv; //�̺�Ʈ ���ۿ� ������
	int myAddr = 0; //�ּ�
	int ev_handler, eventPriority; 

	initPriQ_Event(&priQ_Event, "PriQ_Event", 1); //�ʱ�ȭ
	ThreadParam_Event thrdParam_EventGen, thrdParam_EventHndlr;
	//HANDLE hThrd_EventGenerator, hThrd_EventHandler; // �� ������� ����� ���ؼ� �ֿܼ� ������ ����
	mutex cs_main; // �ܼ� - ���ο��� ��� ������ �Ϳ� ���� ���ؽ�
	mutex cs_thrd_mon; // ������ ���¸� Ȯ���� �� ����� ���ؽ�
	ThreadStatusMonitor thrdMon; //����Ʈ ���� �ľǿ�
	HANDLE consHndlr;
	THREAD_FLAG eventThreadFlag = RUN;
	int count, numEventGenerated, numEventProcessed;
	LARGE_INTEGER freq;
	consHndlr = initConsoleHandler(); //�ڵ� �ʱ�ȭ(�ܼ�)

	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGenerated = 0;
	thrdMon.totalEventProcessed = 0;
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)//����͸� ����ü�� ���� �ʱ�ȭ
	{
		thrdMon.eventProcessed[ev].ev_no = -1; //-1�̸� ���� ���ȵ�
		thrdMon.eventProcessed[ev].ev_pri = -1;
	}
	QueryPerformanceFrequency(&freq); //���ļ� �ѹ� �����ϰ� �Ѿ

	/* Create and Activate Thread_EventHandler */

	thrdMon.numEventProcessed = 0; //����� �̺�Ʈ ���� �ʱ�ȭ
	/*�Ʒ��� ������ �Ű������� �ʱ�ȭ ��Ŵ*/
	thrdParam_EventHndlr.role = EVENT_HANDLER; //���η� ����� ������
	thrdParam_EventHndlr.myAddr = 1; // �̺�Ʈ ������ ��ġ �ʱ�(1) 
	thrdParam_EventHndlr.pMTX_main = &cs_main; //���� ���ý�
	thrdParam_EventHndlr.pMTX_thrd_mon = &cs_thrd_mon; //������ ���ؽ�
	thrdParam_EventHndlr.pPriQ_Event = &priQ_Event; //�߻���Ų �̺�Ʈ ������
	thrdParam_EventHndlr.maxRound = MAX_ROUND; //�ִ� ���� ��, ���� 1000���� ����
	thrdParam_EventHndlr.pThrdMon = &thrdMon; //����͸��� �ּ� �ޱ�
	/*�ʱ�ȭ ��*/

	thread thrd_ev_handler(Thread_EventHandler, &thrdParam_EventHndlr); 

	cs_main.lock(); // �ٸ� �����忡�� ����� ���ϰ� ���� ���ο��� ���
	printf("Thread_EventHandler is created and activated ...\n");
	cs_main.unlock(); 


	/* Create and Activate Thread_EventGen */

	thrdMon.numEventGenerated = 0; //�߻���Ų �̺�Ʈ ���� �ʱ�ȭ
	/*�Ʒ��� ������ �Ű������� �ʱ�ȭ ��Ŵ*/
	thrdParam_EventGen.role = EVENT_GENERATOR; //�߻���� ����� ������
	thrdParam_EventGen.myAddr = 0; // my Address
	thrdParam_EventGen.pMTX_main = &cs_main; //���� ���ý�
	thrdParam_EventGen.pMTX_thrd_mon = &cs_thrd_mon; //������ ���ؽ�
	thrdParam_EventGen.pPriQ_Event = &priQ_Event; //�߻���Ų �̺�Ʈ ������
	thrdParam_EventGen.targetEventGen = NUM_EVENTS_PER_GEN; 
	thrdParam_EventGen.maxRound = MAX_ROUND; //�ִ� ���� ��, ���� 1000���� ����
	thrdParam_EventGen.pThrdMon = &thrdMon; //����͸��� �ּ� �ޱ�
	/*�ʱ�ȭ ��*/

	thread thrd_ev_generator(Thread_EventGenerator, &thrdParam_EventGen);

	cs_main.lock();
	printf("Thread_EventGen is created and activated ...\n");
	cs_main.unlock();

	/*��º�*/
	for (int round = 0; round < MAX_ROUND; round++)
	{
		//cs_main.lock();
		system("cls"); //ȭ�� ����
		//printf("\n\n\n");
		gotoxy(consHndlr, 0, 0); //�ֿܼ��� 0, 0���� �̵� 
		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n",
			round, thrdMon.totalEventGenerated, thrdMon.totalEventProcessed);
		printf("\n");
		printf("Events generated: \n ");

		count = 0; //ī���� 0���� �ʱ�ȭ
		numEventGenerated = thrdMon.totalEventGenerated;//�߻���Ų �̺�Ʈ ����

		for (int i = 0; i < numEventGenerated; i++) //��º�
		{
			pEv = &thrdMon.eventGenerated[i]; //������ �̺�Ʈ�� ����
			if (pEv != NULL)
			{
				printEvent(pEv); //������
				if (((i + 1) % EVENT_PER_LINE) == 0) //���ٿ�  ǥ�� ������ �ִ� �̺�Ʈ ����
					printf("\n "); 
			}
		}

		/*������ �긮�� �κ�*/
		printf("\n");
		printf("Event_Gen generated %2d events\n", thrdMon.numEventGenerated);
		printf("Event_Handler processed %2d events\n", thrdMon.numEventProcessed);
		printf("\n");
		printf("PriQ_Event::"); printPriQ_Event(&priQ_Event);
		printf("\n");
		printf("Events processed: \n ");

		count = 0;
		numEventProcessed = thrdMon.totalEventProcessed;//�۵���Ų �̺�Ʈ ����

		for (int i = 0; i < numEventProcessed; i++) //��º�
		{
			pEv = &thrdMon.eventProcessed[i];  //����� �̺�Ʈ ����
			if (pEv != NULL)
			{
				calc_elapsed_time(pEv, freq); //�ð� ����
				printEvent_withTime(pEv);
				if (((i + 1) % EVENT_PER_LINE) == 0)//���ٿ�  ǥ�� ������ �ִ� �̺�Ʈ ����
					printf("\n ");
			}
		}

		printf("\n");
		if (numEventProcessed >= TOTAL_NUM_EVENTS) //����� ��� ������ for���� Ż��
		{
			eventThreadFlag = TERMINATE; // set 1 to terminate threads
			break;
		}

		//cs_main.unlock();
		Sleep(100);
	}

	/* Analyze the event processing times */

	double min, max, avg, sum;
	int min_ev, max_ev;
	min = max = sum = thrdMon.eventProcessed[0].elap_time;
	min_ev = max_ev = 0;
	for (int i = 1; i < TOTAL_NUM_EVENTS; i++) //�ִ� �ּ� ã��
	{
		sum += thrdMon.eventProcessed[i].elap_time;
		if (min > thrdMon.eventProcessed[i].elap_time)
		{
			min = thrdMon.eventProcessed[i].elap_time; //�ּ� 
			min_ev = i; //�ּ� �κ� ��ġ
		}
		if (max < thrdMon.eventProcessed[i].elap_time)
		{
			max = thrdMon.eventProcessed[i].elap_time; //�ִ�
			max_ev = i; //�ִ� �κ� ��ġ
		}
	}
	avg = sum / TOTAL_NUM_EVENTS; //��հ�
	printf("Minimum event processing time: %8.2lf[ms] for ", min * 1000);
	printEvent_withTime(&thrdMon.eventProcessed[min_ev]); printf("\n");
	printf("Maximum event processing time: %8.2lf[ms] for ", max * 1000);
	printEvent_withTime(&thrdMon.eventProcessed[max_ev]); printf("\n");
	printf("Average event processing time: %8.2lf[ms] for total %d events\n", avg * 1000,
		TOTAL_NUM_EVENTS);
	printf("\n");

	/*�ٸ� �����尡 ��� ���������� ���� ������� ��ٷ��ߵ�*/

	thrd_ev_generator.join(); 
	printf("Thread_EventGenerator is terminated !!\n");
	thrd_ev_handler.join(); 
	printf("Thread_EventHandler is terminated !!\n");

	deletePriQ_Event(&priQ_Event);

}