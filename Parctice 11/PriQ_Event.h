
/* PriorityQueue_Event.h */
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Event.h"
#define POS_ROOT 1
#define MAX_NAME_LEN 80
#define TRUE 1
#define FALSE 0
typedef struct CBTN_Event
{
int priority;
Event* pEvent;
} CBTN_Event;
typedef struct PriorityQueue
{
	char PriQ_name[MAX_NAME_LEN];
	int priQ_capacity; //ť�� �뷮
	//int num_entry; //������� ����
	int pos_last; //������ ť�� ��� ��ġ
	int priQ_size; //ť�� ũ��
	CBTN_Event* pCBT_Ev;
} PriQ_Event;
PriQ_Event* initPriQ_Ev(PriQ_Event* pPriQ_Ev, const char* name, int capacity = 1); //����ť �ʱ�ȭ
//int insertPriQ_Event(PriQ_Event* pPriQ_Event, Event* pEvent);
Event* removeMinPriQ_Event(PriQ_Event* pPriQ_Event); //����ť ���� ����
//void printPriQ_Event(PriQ_Event* pPriQ_Event);
void fprintPriQ_Ev(FILE* fout, PriQ_Event* pPriQ_Ev); //���
void deletePriQ_Ev(PriQ_Event* pPriQ_Ev); //����ť ����(�ݳ�)
int enPriQ_Ev(PriQ_Event* pPriQ_Ev, Event* pEv); //����ť�� �̺�Ʈ �Ҵ�
#endif