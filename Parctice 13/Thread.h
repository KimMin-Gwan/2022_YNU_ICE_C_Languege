#ifndef THREAD_H
#define THREAD_H
#include <Windows.h>
#include <thread>
#include <mutex>
#include <process.h>
#include "Event.h"
#include "SimParams.h"
#include "DLL_EvQ.h"
using namespace std;
enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };
typedef struct
{
	int eventsGen[NUM_EVENT_GENERATORS]; // ������ �ε���
	int eventsProc[NUM_EVENT_HANDLERS]; // �۵��� �ε���
	int totalEventGen; //�� ���� �̺�Ʈ ��
	int totalEventProc; //�� �۵��� �̺�Ʈ ��
	int numEventProcs_priH; //���� ����ť�� �̺�Ʈ ��
	int numEventProcs_priL; //���� ����ť�� �̺�Ʈ ��
	THREAD_FLAG* pFlagThreadTerminate; //���� �÷���
	Event eventGenerated[TOTAL_NUM_EVENTS]; //���� �̺�Ʈ
	Event eventProcessed[TOTAL_NUM_EVENTS]; //������ �̺�Ʈ
} ThreadStatMon; 
typedef struct
{
	//FILE* fout;
	mutex* pCS_main; //���� ���ý�
	mutex* pCS_thrd_mon; //������ �ܼ� ���ý�
	DLL_EvQ* EvQ_PriH; //���� ����ť
	DLL_EvQ* EvQ_PriL; //���� ����ť
	ROLE role; //����
	int myAddr; //�ּ�
	int maxRound; //�ִ� ���� �� 
	int targetEventGen; //����� ���� �̺�Ʈ ��ġ
	LARGE_INTEGER PC_freq;
	// frequency of performance counter that is used to measure elapsed time
	ThreadStatMon* pThrdMon; //������ �����
} ThreadParam_Ev;
void Thread_EventHandler(ThreadParam_Ev* pParam); //����
void Thread_EventGenerator(ThreadParam_Ev* pParam); //������
#endif