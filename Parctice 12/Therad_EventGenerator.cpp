#include <Windows.h>
#include <time.h>
#include "Thread.h"
#include "PriQ_Event.h"
#include "Event.h"
#include "SimParam.h"

void Thread_EventGenerator(ThreadParam_Event* pParam)
{
	/*�ʱ�ȭ*/
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
		/*���࿡ priority�� 0�̵Ǹ� �� �����ߴٰ� priority�� ������ �ȴ�.
		�׷��� Ȥ�� �۾��� ������ �ƴ��� if�� Ȯ���ϰ�
		������ �ƴ϶�� ���̻� ���������� ����϶�
		���� join�� �ʿ���ٸ� break�� �Ἥ ������ ����� ������ �ȴ�.*/
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
		/*�ʱ�ȭ*/
		pEv->ev_generator = myAddr; //0
		pEv->ev_handler = -1; //�̺�Ʈ �ڵ鷯�� ����
		pEv->ev_no = event_gen_count;  //�̺�Ʈ ��ȣ  //+ NUM_EVENTS_PER_GEN * myAddr
		//pEv->ev_pri = eventPriority = rand() % NUM_PRIORITY;
		pEv->ev_pri = targetEventGen - event_gen_count - 1; //�켱����
		QueryPerformanceCounter(&pEv->ev_t_gen); //���� �ð������� ���� ���ļ� Ž��

		pThrdMon->eventGenerated[pThrdMon->totalEventGenerated] = *pEv; //����͸���
		/*����ť�� �̺�Ʈ�� �Ҵ�*/
		if (pEv == NULL)
			break;
		enPriQ_Ev(pPriQ_Event, *pEv);
		Sleep(80);
		free(pEv);
		/*�����κ�*/
		pParam->pMTX_thrd_mon->lock();
		pThrdMon->numEventGenerated++;
		pThrdMon->totalEventGenerated++;
		pParam->pMTX_thrd_mon->unlock();
		event_gen_count++; 
		//Sleep(100 + rand() % 300); //��ũ�� ���߱�����
		Sleep(10);
	}
}