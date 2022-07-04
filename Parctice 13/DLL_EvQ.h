#ifndef LinkedList_QUEUE_H
#define LinkedList_QUEUE_H
#include <Windows.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include "Event.h"
using namespace std;
// doubly linked list node (DLLN)
typedef struct DLLN
{
	struct DLLN* next;
	struct DLLN* prev;
	Event* pEv;
} DLLN_Ev;
typedef struct
{
	mutex cs_EvQ;
	int priority;
	DLLN_Ev* front;
	DLLN_Ev* back;
	int num_event;
} DLL_EvQ;
void initDLL_EvQ(DLL_EvQ* DLL_EvQ, int priority); //초기화
Event* enDLL_EvQ(DLL_EvQ* DLL_EvQ, Event* pEv); //이벤트 할당
Event* deDLL_EvQ(DLL_EvQ* DLL_EvQ); //이벤트 사용
void printDLL_EvQ(DLL_EvQ* DLL_EvQ); //출력
#endif