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
	Event* pEv; //이벤트 조작용 포인터
	int myAddr = 0; //주소
	int ev_handler, eventPriority; 

	initPriQ_Event(&priQ_Event, "PriQ_Event", 1); //초기화
	ThreadParam_Event thrdParam_EventGen, thrdParam_EventHndlr;
	//HANDLE hThrd_EventGenerator, hThrd_EventHandler; // 두 스레드는 출력을 안해서 콘솔에 영향을 안줌
	mutex cs_main; // 콘솔 - 메인에서 띄울 예정인 것에 대한 뮤텍스
	mutex cs_thrd_mon; // 스레드 상태를 확인할 때 사용할 뮤텍스
	ThreadStatusMonitor thrdMon; //스레트 상태 파악용
	HANDLE consHndlr;
	THREAD_FLAG eventThreadFlag = RUN;
	int count, numEventGenerated, numEventProcessed;
	LARGE_INTEGER freq;
	consHndlr = initConsoleHandler(); //핸들 초기화(콘솔)

	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGenerated = 0;
	thrdMon.totalEventProcessed = 0;
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)//모니터링 구조체의 내용 초기화
	{
		thrdMon.eventProcessed[ev].ev_no = -1; //-1이면 아직 사용안됨
		thrdMon.eventProcessed[ev].ev_pri = -1;
	}
	QueryPerformanceFrequency(&freq); //주파수 한번 측정하고 넘어감

	/* Create and Activate Thread_EventHandler */

	thrdMon.numEventProcessed = 0; //사용한 이벤트 갯수 초기화
	/*아래는 스레드 매개변수를 초기화 시킴*/
	thrdParam_EventHndlr.role = EVENT_HANDLER; //헨들로로 사용할 스레드
	thrdParam_EventHndlr.myAddr = 1; // 이벤트 생성할 위치 초기(1) 
	thrdParam_EventHndlr.pMTX_main = &cs_main; //메인 뮤택스
	thrdParam_EventHndlr.pMTX_thrd_mon = &cs_thrd_mon; //스레드 뮤텍스
	thrdParam_EventHndlr.pPriQ_Event = &priQ_Event; //발생시킨 이벤트 포인터
	thrdParam_EventHndlr.maxRound = MAX_ROUND; //최대 라운드 수, 현재 1000으로 고정
	thrdParam_EventHndlr.pThrdMon = &thrdMon; //모니터링할 주소 받기
	/*초기화 끝*/

	thread thrd_ev_handler(Thread_EventHandler, &thrdParam_EventHndlr); 

	cs_main.lock(); // 다른 스레드에서 출력을 못하게 막고 메인에서 출력
	printf("Thread_EventHandler is created and activated ...\n");
	cs_main.unlock(); 


	/* Create and Activate Thread_EventGen */

	thrdMon.numEventGenerated = 0; //발생시킨 이벤트 갯수 초기화
	/*아래는 스레드 매개변수를 초기화 시킴*/
	thrdParam_EventGen.role = EVENT_GENERATOR; //발생기로 사용할 스레드
	thrdParam_EventGen.myAddr = 0; // my Address
	thrdParam_EventGen.pMTX_main = &cs_main; //메인 뮤택스
	thrdParam_EventGen.pMTX_thrd_mon = &cs_thrd_mon; //스레드 뮤텍스
	thrdParam_EventGen.pPriQ_Event = &priQ_Event; //발생시킨 이벤트 포인터
	thrdParam_EventGen.targetEventGen = NUM_EVENTS_PER_GEN; 
	thrdParam_EventGen.maxRound = MAX_ROUND; //최대 라운드 수, 현재 1000으로 고정
	thrdParam_EventGen.pThrdMon = &thrdMon; //모니터링할 주소 받기
	/*초기화 끝*/

	thread thrd_ev_generator(Thread_EventGenerator, &thrdParam_EventGen);

	cs_main.lock();
	printf("Thread_EventGen is created and activated ...\n");
	cs_main.unlock();

	/*출력부*/
	for (int round = 0; round < MAX_ROUND; round++)
	{
		//cs_main.lock();
		system("cls"); //화면 정리
		//printf("\n\n\n");
		gotoxy(consHndlr, 0, 0); //콘솔에서 0, 0으로 이동 
		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n",
			round, thrdMon.totalEventGenerated, thrdMon.totalEventProcessed);
		printf("\n");
		printf("Events generated: \n ");

		count = 0; //카운터 0으로 초기화
		numEventGenerated = thrdMon.totalEventGenerated;//발생시킨 이벤트 갯수

		for (int i = 0; i < numEventGenerated; i++) //출력부
		{
			pEv = &thrdMon.eventGenerated[i]; //생성한 이벤트를 찍음
			if (pEv != NULL)
			{
				printEvent(pEv); //프린팅
				if (((i + 1) % EVENT_PER_LINE) == 0) //한줄에  표현 가능한 최대 이벤트 갯수
					printf("\n "); 
			}
		}

		/*현상태 브리핑 부분*/
		printf("\n");
		printf("Event_Gen generated %2d events\n", thrdMon.numEventGenerated);
		printf("Event_Handler processed %2d events\n", thrdMon.numEventProcessed);
		printf("\n");
		printf("PriQ_Event::"); printPriQ_Event(&priQ_Event);
		printf("\n");
		printf("Events processed: \n ");

		count = 0;
		numEventProcessed = thrdMon.totalEventProcessed;//작동시킨 이벤트 갯수

		for (int i = 0; i < numEventProcessed; i++) //출력부
		{
			pEv = &thrdMon.eventProcessed[i];  //사용한 이벤트 찍음
			if (pEv != NULL)
			{
				calc_elapsed_time(pEv, freq); //시간 측정
				printEvent_withTime(pEv);
				if (((i + 1) % EVENT_PER_LINE) == 0)//한줄에  표현 가능한 최대 이벤트 갯수
					printf("\n ");
			}
		}

		printf("\n");
		if (numEventProcessed >= TOTAL_NUM_EVENTS) //사용이 모두 끝나야 for문을 탈출
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
	for (int i = 1; i < TOTAL_NUM_EVENTS; i++) //최대 최소 찾기
	{
		sum += thrdMon.eventProcessed[i].elap_time;
		if (min > thrdMon.eventProcessed[i].elap_time)
		{
			min = thrdMon.eventProcessed[i].elap_time; //최소 
			min_ev = i; //최소 부분 위치
		}
		if (max < thrdMon.eventProcessed[i].elap_time)
		{
			max = thrdMon.eventProcessed[i].elap_time; //최대
			max_ev = i; //최대 부분 위치
		}
	}
	avg = sum / TOTAL_NUM_EVENTS; //평균값
	printf("Minimum event processing time: %8.2lf[ms] for ", min * 1000);
	printEvent_withTime(&thrdMon.eventProcessed[min_ev]); printf("\n");
	printf("Maximum event processing time: %8.2lf[ms] for ", max * 1000);
	printEvent_withTime(&thrdMon.eventProcessed[max_ev]); printf("\n");
	printf("Average event processing time: %8.2lf[ms] for total %d events\n", avg * 1000,
		TOTAL_NUM_EVENTS);
	printf("\n");

	/*다른 스레드가 모두 끝날때까지 메인 스레드는 기다려야됨*/

	thrd_ev_generator.join(); 
	printf("Thread_EventGenerator is terminated !!\n");
	thrd_ev_handler.join(); 
	printf("Thread_EventHandler is terminated !!\n");

	deletePriQ_Event(&priQ_Event);

}