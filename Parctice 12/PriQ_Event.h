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
	int priority; //우선순위
	Event event; //이벤트 활용자
} CBTN_Event;

typedef struct PriorityQueue //우선순위 큐
{
	mutex cs_PriQ; //뮤텍스 활용자
	char PriQ_name[MAX_NAME_LEN]; //이름
	int priQ_capacity; //용량
	int priQ_size; //이벤트 끝부분
	int pos_last; //마지막 위치
	CBTN_Event* pCBT_Ev; //완전이진트리 위치 포인터

} PriQ_Ev;
PriQ_Ev* initPriQ_Event(PriQ_Ev* pPriQ_Event, const char* name, int capacity = 1); //프리큐 프리셋
Event* enPriQ_Ev(PriQ_Ev* pPriQ_Ev, Event Ev);  //프리큐에 이벤트 삽입
Event* dePriQ_Event(PriQ_Ev* pPriQ_Event);      //프리큐의 이벤트 사용
void printPriQ_Event(PriQ_Ev* pPriQ_Event); //프리큐 출력
//void fprintPriQ_Ev(FILE* fout, PriQ_Ev* pPriQ_Ev); //파일에 출력
void deletePriQ_Event(PriQ_Ev* pPriQ_Event); //프리큐 삭제
#endif
