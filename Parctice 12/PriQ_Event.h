#ifndef PRIQ_EVENT_H
#define PRIQ_EVENT_H
#include <mutex>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Event.h"
using namespace std;
#define POS_ROOT 1
#define MAX_NAME_LEN 80
#define TRUE 1
#define FALSE 0
typedef struct CBTN_Event //Complete binary tree
{
	int priority; //�켱����
	Event event; //�̺�Ʈ Ȱ����
} CBTN_Event;

typedef struct PriorityQueue //�켱���� ť
{
	mutex cs_PriQ; //���ؽ� Ȱ����
	char PriQ_name[MAX_NAME_LEN]; //�̸�
	int priQ_capacity; //�뷮
	int priQ_size; //�̺�Ʈ ���κ�
	int pos_last; //������ ��ġ
	CBTN_Event* pCBT_Ev; //��������Ʈ�� ��ġ ������

} PriQ_Ev;
PriQ_Ev* initPriQ_Event(PriQ_Ev* pPriQ_Event, const char* name, int capacity = 1); //����ť ������
Event* enPriQ_Ev(PriQ_Ev* pPriQ_Ev, Event Ev);  //����ť�� �̺�Ʈ ����
Event* dePriQ_Event(PriQ_Ev* pPriQ_Event);      //����ť�� �̺�Ʈ ���
void printPriQ_Event(PriQ_Ev* pPriQ_Event); //����ť ���
//void fprintPriQ_Ev(FILE* fout, PriQ_Ev* pPriQ_Ev); //���Ͽ� ���
void deletePriQ_Event(PriQ_Ev* pPriQ_Event); //����ť ����
#endif
