#include <Windows.h>
#include <time.h>
#include "Thread.h"
#include "PriQ_Event.h"
#include "Event.h"
#include "SimParam.h"

void Thread_EventGenerator(ThreadParam_Event* pParam)
{
	/*초기화*/
	PriQ_Ev* pPriQ_Event = pParam->pPriQ_Event;
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	int maxRound = pParam->maxRound;
	int event_gen_count = 0;
	ThreadStatusMonitor* pThrdMon = pParam->pThrdMon;
	pPriQ_Event = pParam->pPriQ_Event;
	int targetEventGen = pParam->targetEventGen;
	Event* pEv;
	srand(time(NULL));
	for (int round = 0; round < maxRound; round++)
	{
		/*만약에 priority가 0이되면 더 생성했다간 priority가 음수가 된다.
		그래서 혹시 작업이 끝난건 아닌지 if로 확인하고
		끝난게 아니라면 더이상 만들지말고 대기하라
		따라서 join이 필요없다면 break을 써서 스레드 사용을 끝내도 된다.*/
		if (event_gen_count >= targetEventGen) 
		{ 
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break;
			else {
				//break;
				Sleep(500);
				continue;
			}
		}

		pEv = (Event*)calloc(1, sizeof(Event));
		if (pEv == NULL)
		{
			break;
		}
		/*초기화*/
		pEv->ev_generator = myAddr; //0
		pEv->ev_handler = -1; //이벤트 핸들러는 없다
		pEv->ev_no = event_gen_count;  //이벤트 번호  //+ NUM_EVENTS_PER_GEN * myAddr
		//pEv->ev_pri = eventPriority = rand() % NUM_PRIORITY;
		pEv->ev_pri = targetEventGen - event_gen_count - 1; //우선순위
		QueryPerformanceCounter(&pEv->ev_t_gen); //생성 시간측정을 위한 주파수 탐색

		pThrdMon->eventGenerated[pThrdMon->totalEventGenerated] = *pEv; //모니터링용
		/*프리큐에 이벤트를 할당*/
		if (pEv == NULL)
			break;
		enPriQ_Ev(pPriQ_Event, *pEv);
		Sleep(80);
		free(pEv);
		/*증감부분*/
		pParam->pMTX_thrd_mon->lock();
		pThrdMon->numEventGenerated++;
		pThrdMon->totalEventGenerated++;
		pParam->pMTX_thrd_mon->unlock();
		event_gen_count++; 
		//Sleep(100 + rand() % 300); //싱크를 맞추기위함
		Sleep(10);
	}
}