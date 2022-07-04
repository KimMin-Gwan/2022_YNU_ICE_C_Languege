#include <Windows.h>
#include <time.h>
#include "Thread.h"
#include "PriQ_Event.h"
#include "Event.h"
void Thread_EventHandler(ThreadParam_Event* pParam)
{
	/*�ʱ�ȭ*/
	Event* pEv;
	int myRole = pParam->role; //���� �޾ƿ�
	int myAddr = pParam->myAddr; //address �ʱ�ȭ
	PriQ_Ev* pPriQ_Event = pParam->pPriQ_Event;
	ThreadStatusMonitor* pThrdMon = pParam->pThrdMon;
	int maxRound = pParam->maxRound; //�ִ� ���� ����
	int targetEventGen = pParam->targetEventGen;
	srand(time(NULL));

	for (int round = 0; round < maxRound; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE) //������ for���� �����ߴٸ� ������
			break;
		if ((pEv = dePriQ_Event(pPriQ_Event)) != NULL) //dePriQ��Ű��
		{
			//printf("Thread_EventProc::deLL_EventQ_from_HighPri_LL_EventQ : ");
			//printEvent(pEv);
			//printf("\n");
			
			pParam->pMTX_thrd_mon->lock();
			QueryPerformanceCounter(&pEv->ev_t_handle);

			pEv->ev_handler = myAddr;
			/*����͸� ����*/
			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = *pEv;
			pThrdMon->numEventProcessed++;
			pThrdMon->totalEventProcessed++;
			pParam->pMTX_thrd_mon->unlock();
			free(pEv); //dePriQ���� �Ҵ��� �޸� ����
		}
		Sleep(100 + rand() % 300); //��ũ�� ���߱� ���� 100���ϱ� ������
	}
}

