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
	DLL_EvQ dll_EvQ_PriH, dll_EvQ_PriL; //상위 하위 프리큐
	Event* pEvent; //이벤트 포인터
	int myAddr = 0; //초기 주소 0
	int event_handler_addr, eventPriority;
	LARGE_INTEGER pc_freq; //시간 측정용
	//fout = fopen("SimOutput.txt", "w");
	//if (fout == NULL)
	//{
	//	printf("Error in opening SimOutput.txt file in write mode !!\n");
	//	exit;
	//}
	initDLL_EvQ(&dll_EvQ_PriH, 0); //초기화
	initDLL_EvQ(&dll_EvQ_PriL, 1); //초기화

	srand(time(NULL));
	ThreadParam_Ev thrdParam_EventGen[NUM_EVENT_GENERATORS], thrdParam_EventHndlr[NUM_EVENT_HANDLERS];
	thread thread_evHandlers[NUM_EVENT_HANDLERS];
	thread thread_evGens[NUM_EVENT_GENERATORS];
	mutex cs_main; //매인 뮤택스
	mutex cs_thrd_mon; //스레드 뮤택스
	ThreadStatMon thrdMon; //모니터링용 변수
	HANDLE consHndlr; //콘솔 제어용
	THREAD_FLAG eventThreadFlag = RUN; //작동 상태 표시 - 초기값 : 동작중 
	int count, totalEventGenerated, totalEventProcessed; //통계치 기록용
	Event eventProcessed[TOTAL_NUM_EVENTS]; //상태 기록용

	/*지역 변수 초기화*/
	consHndlr = initConsoleHandler();
	QueryPerformanceFrequency(&pc_freq);
	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGen = 0;
	thrdMon.totalEventProc = 0;
	thrdMon.numEventProcs_priH = 0;
	thrdMon.numEventProcs_priL = 0;

	/*모든 모니터링 배열 초기화*/
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.eventProcessed[ev].event_no = -1; 
		thrdMon.eventProcessed[ev].event_pri = -1;
	}


	/* 이벤트 사용기 */
	for (int p = 0; p < NUM_EVENT_HANDLERS; p++) // 0 ~ 1
	{
		thrdMon.eventsProc[p] = 0; //동작한 이벤트 배열 초기화
		//thrdParam_EventHndlr[p].fout = fout;
		thrdParam_EventHndlr[p].role = EVENT_HANDLER; //역할
		thrdParam_EventHndlr[p].myAddr = p; // 사용기의 주소 0 ~ 1
		thrdParam_EventHndlr[p].pCS_main = &cs_main;
		thrdParam_EventHndlr[p].pCS_thrd_mon = &cs_thrd_mon;
		thrdParam_EventHndlr[p].EvQ_PriH = &dll_EvQ_PriH; //상위 프리큐 주소
		thrdParam_EventHndlr[p].EvQ_PriL = &dll_EvQ_PriL; //하위 프리큐 주소
		thrdParam_EventHndlr[p].maxRound = MAX_ROUND; //최대 라운드 수
		thrdParam_EventHndlr[p].pThrdMon = &thrdMon; //스레드 모니터
		thrdParam_EventHndlr[p].PC_freq = pc_freq; //작동 주파수 
		thread_evHandlers[p] = thread(Thread_EventHandler, &thrdParam_EventHndlr[p]); //스레드를 2개 생성
		cs_main.lock();
		printf("%d-th thread_EventHandler is created and activated (id: %d)\n", p, thread_evHandlers[p].get_id());
		cs_main.unlock();
	}


	/* 이벤트 생성기*/
	for (int g = 0; g < NUM_EVENT_GENERATORS; g++) //0 ~ 2
	{
		thrdMon.eventsGen[g] = 0; //만들 이벤트 배열 초기화
		thrdParam_EventGen[g].role = EVENT_GENERATOR; //역할
		thrdParam_EventGen[g].myAddr = g; // 발생기 주소 0 ~ 2
		thrdParam_EventGen[g].pCS_main = &cs_main;
		thrdParam_EventGen[g].pCS_thrd_mon = &cs_thrd_mon;
		thrdParam_EventGen[g].EvQ_PriH = &dll_EvQ_PriH; //상위 프리큐
		thrdParam_EventGen[g].EvQ_PriL = &dll_EvQ_PriL; //하위 프리큐
		thrdParam_EventGen[g].targetEventGen = NUM_EVENTS_PER_GEN; //각 스레드에서 만들 이벤트 수
		thrdParam_EventGen[g].maxRound = MAX_ROUND; //최대 라운드 수
		thrdParam_EventGen[g].pThrdMon = &thrdMon; //스레드 모니터
		thrdParam_EventGen[g].PC_freq = pc_freq; //작동 주파수
		thread_evGens[g] = thread(Thread_EventGenerator, &thrdParam_EventGen[g]); //스레드를 3개 생성
		cs_main.lock();
		printf("%d-th thread_EventGen is created and activated (id: %d)\n", g, thread_evGens[g].get_id());
		cs_main.unlock();
	}


	/* 메인 작동 부분 - 동작여부에 대한 모니터링 */
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
		totalEventGenerated = thrdMon.totalEventGen; //만든 이벤트 갯수
		printf("\nTotal Generated Events (current total %d events)\n ", totalEventGenerated);
		for (int ev = 0; ev < totalEventGenerated; ev++)
		{
			pEvent = &thrdMon.eventGenerated[ev]; //만든 이벤트를 포인터로 찍음
			if (pEvent != NULL)
			{
				printEvent(pEvent); //만든 이벤트 출력
				if (((ev + 1) % EVENT_PER_LINE) == 0) //줄당 최대 출력 5개
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
		printDLL_EvQ(&dll_EvQ_PriH); //상위 프리큐에 있는 이벤트 나열
		printf("\n");
		printf("DLL_EvQ_PriL (%3d events):\n ", dll_EvQ_PriL.num_event);
		printDLL_EvQ(&dll_EvQ_PriL); //하위 프리큐에 있는 이벤트 나열
		printf("\n");
		totalEventProcessed = thrdMon.totalEventProc; //작동시킨 이벤트의 총 갯수
		printf("\nTotal Processed Events (current total %d events):\n ", totalEventProcessed);
		count = 0;
		for (int ev = 0; ev < totalEventProcessed; ev++)
		{
			pEvent = &thrdMon.eventProcessed[ev]; //작동시킨 이벤트를 포인터로 찍음
			if (pEvent != NULL)
			{
				printEvent(pEvent); //작동시킨 이벤트 출력
				if (((ev + 1) % EVENT_PER_LINE) == 0) //줄당 최대 출력 5개
					printf("\n ");
			}
		}
		printf("\n");
		cs_thrd_mon.unlock();
		if (totalEventProcessed >= TOTAL_NUM_EVENTS) //총 만든 이벤트의 수가 60개가 넘으면
		{
			printf("!!! TotalEventProcessed (%d) is reached to target TOTAL_NUM_EVENTS(% d)\n", totalEventProcessed, TOTAL_NUM_EVENTS);
			eventThreadFlag = TERMINATE;  //상태 : 종료
			cs_main.unlock();
			break;
		}
		cs_main.unlock();
		Sleep(200);
	} 


	for (int p = 0; p < NUM_EVENT_HANDLERS; p++)
	{
		thread_evHandlers[p].join(); //모든 사용기 스레드가 동작을 끝낼때 까지 대기
	}
	printf("All threads of event handlers are terminated !!\n");


	for (int g = 0; g < NUM_EVENT_GENERATORS; g++)
	{
		thread_evGens[g].join(); //모든 작동기 스레드가 동작을 끝낼때 까지 대기
	}
	printf("All threads of event generators are terminated !!\n"); 

	//calc_elapsed_time(thrdMon.eventProcessed, thrdMon.numPktProcs, freq);
	/*시간 측정*/
	double min, max, avg, sum;
	int min_event, max_event;
	min = max = sum = thrdMon.eventProcessed[0].t_elapsed;
	min_event = max_event = 0;
	for (int i = 1; i < TOTAL_NUM_EVENTS; i++)
	{
		sum += thrdMon.eventProcessed[i].t_elapsed; //합
		if (min > thrdMon.eventProcessed[i].t_elapsed)
		{
			min = thrdMon.eventProcessed[i].t_elapsed; //최소
			min_event = i; 
		}
		if (max < thrdMon.eventProcessed[i].t_elapsed)
		{
			max = thrdMon.eventProcessed[i].t_elapsed; //최대
			max_event = i;
		}
	}
	avg = sum / (double)TOTAL_NUM_EVENTS; //평균
	/*시간 통계 출력*/
	printf("Minimum event processing time: %8.2lf[ms] for ", min * 1000);
	printEvent_withTime(&thrdMon.eventProcessed[min_event]); printf("\n");
	printf("Maximum event processing time: %8.2lf[ms] for ", max * 1000);
	printEvent_withTime(&thrdMon.eventProcessed[max_event]); printf("\n");
	printf("Average event processing time: %8.2lf[ms] for total %d events\n", avg * 1000, TOTAL_NUM_EVENTS);
	printf("\n");
}