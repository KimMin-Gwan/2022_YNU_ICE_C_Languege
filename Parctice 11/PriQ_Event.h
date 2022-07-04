
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
	int priQ_capacity; //큐의 용량
	//int num_entry; //구성요소 갯수
	int pos_last; //마지막 큐의 노드 위치
	int priQ_size; //큐의 크기
	CBTN_Event* pCBT_Ev;
} PriQ_Event;
PriQ_Event* initPriQ_Ev(PriQ_Event* pPriQ_Ev, const char* name, int capacity = 1); //프리큐 초기화
//int insertPriQ_Event(PriQ_Event* pPriQ_Event, Event* pEvent);
Event* removeMinPriQ_Event(PriQ_Event* pPriQ_Event); //프리큐 내용 제거
//void printPriQ_Event(PriQ_Event* pPriQ_Event);
void fprintPriQ_Ev(FILE* fout, PriQ_Event* pPriQ_Ev); //출력
void deletePriQ_Ev(PriQ_Event* pPriQ_Ev); //프리큐 삭제(반납)
int enPriQ_Ev(PriQ_Event* pPriQ_Ev, Event* pEv); //프리큐에 이벤트 할당
#endif