#include <Windows.h>
#include <time.h>
#include "Thread.h"
#include "PriQ_Event.h"
#include "Event.h"
void Thread_EventHandler(ThreadParam_Event* pParam)
{
	/*초기화*/
	Event* pEv;
	int myRole = pParam->role; //역할 받아옴
	int myAddr = pParam->myAddr; //address 초기화
	PriQ_Ev* pPriQ_Event = pParam->pPriQ_Event;
	ThreadStatusMonitor* pThrdMon = pParam->pThrdMon;
	int maxRound = pParam->maxRound; //최대 라운드 갯수
	int targetEventGen = pParam->targetEventGen;
	srand(time(NULL));

	for (int round = 0; round < maxRound; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE) //메인이 for문을 종료했다면 끝내라
			break;
		if ((pEv = dePriQ_Event(pPriQ_Event)) != NULL) //dePriQ시키기
		{
			//printf("Thread_EventProc::deLL_EventQ_from_HighPri_LL_EventQ : ");
			//printEvent(pEv);
			//printf("\n");
			
			pParam->pMTX_thrd_mon->lock();
			QueryPerformanceCounter(&pEv->ev_t_handle);

			pEv->ev_handler = myAddr;
			/*모니터링 증감*/
			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = *pEv;
			pThrdMon->numEventProcessed++;
			pThrdMon->totalEventProcessed++;
			pParam->pMTX_thrd_mon->unlock();
			free(pEv); //dePriQ에서 할당한 메모리 해제
		}
		Sleep(100 + rand() % 300); //싱크를 맞추기 위해 100더하기 랜덤값
	}
}

