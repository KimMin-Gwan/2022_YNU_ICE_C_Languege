

#include <Windows.h>
#include <time.h>
#include <thread>
#include "Thread.h"
#include "DLL_EvQ.h" #include "Event.h"
using namespace std;
void Thread_EventGenerator(ThreadParam_Ev* pThrdParam)
{
	Event* pEv; int event_no = 0;
	int event_pri = 0; 
	int event_gen_count = 0; 
	int myRole = pThrdParam->role;
	int myGenAddr = pThrdParam->myAddr; 
	int targetEventGen = pThrdParam->targetEventGen;
	DLL_EvQ* pEvQ; 
	DLL_EvQ* priH_EvQ = pThrdParam->EvQ_PriH;
	DLL_EvQ* priL_EvQ = pThrdParam->EvQ_PriL; 
	ThreadStatMon* pThrdMon = pThrdParam->pThrdMon;
	int maxRound = pThrdParam->maxRound;
	pThrdParam->pCS_main->lock();
	printf("Thread_EventGenerator(%d): targetEventGen(%d)₩n", myGenAddr, targetEventGen); 
	pThrdParam->pCS_main->unlock();

	for (int round = 0; round < maxRound; round++)
	{
		if (event_gen_count < targetEventGen)
		{
			pEv = (Event*)calloc(1, sizeof(Event)); //한칸 할당
			pEv->event_gen_addr = myGenAddr; //지정된 주소
			pEv->event_no = event_no = event_gen_count + (NUM_EVENTS_PER_GEN * myGenAddr); //지정된 위치의 이벤트 번호를 생성한다.
			pEv->event_pri = event_pri = rand() % NUM_PRIORITY; //랜덤한 우선순위
			pEv->event_handler_addr = -1; //아직 작동을 안했으니 -1
			QueryPerformanceCounter(&pEv->t_gen); //주파수 체크
			pEvQ = (event_pri < PRIORITY_THRESHOLD) ? priH_EvQ : priL_EvQ; //만약 우선순위가 2보다 높으면 상위 프리큐로, 낮으면 하위 프리큐
			while (enDLL_EvQ(pEvQ, pEv) == NULL)  //이벤트를 할당 (이중 연결형 리스트로)
			{
				Sleep(100);
			}
			/*모니터링 증감*/
			pThrdParam->pCS_thrd_mon->lock();
			pThrdMon->eventsGen[myGenAddr]++; //이벤트 모니터링 위치 증가
			pThrdMon->eventGenerated[pThrdMon->totalEventGen] = *pEv;
			pThrdMon->totalEventGen++; //총 이벤트 생성 갯수 증가
			pThrdParam->pCS_thrd_mon->unlock();
			event_gen_count++; //카운트 증가
		}
		else
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE) //더이상 작동할 필요가 없다면 탈출
				break;
		} // end if
		Sleep(10 + rand() % 100);
	} // end for round
}