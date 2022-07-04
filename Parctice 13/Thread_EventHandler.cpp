#include <Windows.h>
#include <time.h>
#include <thread>
#include <mutex>
#include "Thread.h"
#include "DLL_EvQ.h"
#include "Event.h"
using namespace std;
void Thread_EventHandler(ThreadParam_Ev* pThrdParam)
{
	//int myRole = pThrdParam->role;
	int myProcAddr = pThrdParam->myAddr; //사용 주소 받기 0 ~2
	Event* pEv;
	DLL_EvQ* priH_EvQ = pThrdParam->EvQ_PriH;
	DLL_EvQ* priL_EvQ = pThrdParam->EvQ_PriL;
	ThreadStatMon* pThrdMon = pThrdParam->pThrdMon; //모니터링
	int maxRound = pThrdParam->maxRound;
	//Event* evProc = pThrdParam->pThrdMon->eventProcessed;
	int targetEventGen = pThrdParam->targetEventGen;
	LARGE_INTEGER PC_freq = pThrdParam->PC_freq; // 주파수 측정용

	pThrdParam->pCS_main->lock();
	printf("Thread_EventHandler(%d): targetEventGen(%d)₩n", myProcAddr, targetEventGen);
	pThrdParam->pCS_main->unlock();

	for (int round = 0; round < maxRound; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE) 
			break; 
		while ((pEv = deDLL_EvQ(priH_EvQ)) != NULL) //상위 프리큐 부터 해제
		{
			pThrdParam->pCS_thrd_mon->lock(); //잠그기
			pEv->event_handler_addr = myProcAddr; //핸들러의 작동 주소
			QueryPerformanceCounter(&pEv->t_proc); //주파수 측정
			calc_elapsed_time(pEv, PC_freq); //시간 측정
			pThrdMon->eventProcessed[pThrdMon->totalEventProc] = *pEv; //모니터링 위치
			pThrdMon->eventsProc[myProcAddr]++; //작동한 이벤트 갯수 증가
			pThrdMon->totalEventProc++;  //총 작동한 이벤트 갯수 증가
			pThrdMon->numEventProcs_priH++; //상위 프리큐에서 사용한 이벤트 갯수 증가
			free(pEv); //이벤트 해제
			pThrdParam->pCS_thrd_mon->unlock();
			Sleep(200 + rand() % 300); //한번 작동시키고 잠시 대기 
		} // end while
		if ((pEv = deDLL_EvQ(priL_EvQ)) != NULL) //하위 프리큐 해제
		{
			pThrdParam->pCS_thrd_mon->lock(); //잠그기
			pEv->event_handler_addr = myProcAddr; //핸들러의 작동 주소
			QueryPerformanceCounter(&pEv->t_proc); //주파수 측정
			calc_elapsed_time(pEv, PC_freq); //시간 측정
			pThrdMon->eventProcessed[pThrdMon->totalEventProc] = *pEv; //모니터링 위치
			pThrdMon->eventsProc[myProcAddr]++; //작동한 이벤트 갯수 증가
			pThrdMon->totalEventProc++; //총 작동한 이벤트 갯수 증가
			pThrdMon->numEventProcs_priL++; //하위 프리큐에서 사용한 이벤트 갯수 증가
			free(pEv);
			pThrdParam->pCS_thrd_mon->unlock();
			Sleep(200 + rand() % 300); //한번 작동시키고 잠시 대기
		} // end if 
	}
}