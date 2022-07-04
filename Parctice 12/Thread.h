#ifndef THREAD_H
#define THREAD_H
using namespace std;
enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };
#define THREAD_RETURN_CODE 7
#include "SimParam.h"
#include "PriQ_Event.h"
#include <mutex>

typedef struct //����Ʈ ����
{
	int numEventGenerated; //�߻���Ų �̺�Ʈ ����
	int numEventProcessed; //����� �̺�Ʈ ����
	int totalEventGenerated; //�� �߻���Ų �̺�Ʈ ����
	int totalEventProcessed; //�� ����� �̺�Ʈ ����
	Event eventGenerated[TOTAL_NUM_EVENTS]; // �߻���Ų �̺�Ʈ ��ġ
	Event eventProcessed[TOTAL_NUM_EVENTS]; // �۵��Ǵ� �̺�Ʈ ��ġ
	THREAD_FLAG* pFlagThreadTerminate; //���� ���� �ľǵ���
} ThreadStatusMonitor;

typedef struct //������ �Ķ���� (�����尡 �۵��� ������ �������ٰ�)
{
	mutex* pMTX_main;  //���� ���ؽ�
	mutex* pMTX_thrd_mon; //������ ���ؽ� ����͸���(�ڵ鿡�� ����Ұ�)
	PriQ_Ev* pPriQ_Event; //�۾��� �� �̺�Ʈ ������
	ROLE role; //���� �����尡 ���� ��(���� or ���)
	int myAddr; //���� �ּ�
	int maxRound; //�ִ� ���� ��
	int targetEventGen; //������ �� �̺�Ʈ ����
	ThreadStatusMonitor* pThrdMon; //������ ���¸� �ľ��� ��
} ThreadParam_Event; 

void Thread_EventHandler(ThreadParam_Event* pParam);   //�̺�Ʈ �ڵ�, �̺�Ʈ ���� ����
void Thread_EventGenerator(ThreadParam_Event* pParam); //�̺�Ʈ �߻���
#endif

