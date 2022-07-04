#include <stdio.h>
#include <stdlib.h>
#include "Event.h"
const char* strEventStatus[] = { "GENERATED", "ENQUED", "PROCESSED", "UNDEFINED" };
//void printEvent(Event* pEvent)
//{
//	char str_pri[6];
//	printf("Ev(no:%3d, pri:%2d) ", pEvent->event_no, pEvent->event_pri);
//}
void fprintEvent(FILE* fout, Event* pEvent)
{
	//char str_pri[6];
	fprintf(fout, "Ev(no:%3d, pri:%2d) ", pEvent->event_no, pEvent->event_pri);
}
Event* genEvent(Event* pEv, int ev_gen_ID, int ev_no, int ev_pri)
{
	pEv = (Event*)calloc(1, sizeof(Event)); //빈공간생성
	if (pEv == NULL)
		return NULL;
	initEvent(pEv, ev_gen_ID, ev_no, ev_pri, -1, GENERATED); //값을 각각 구조체에 할당
	return pEv;
}
void initEvent(Event* pEv, int ev_gen_ID, int ev_no, int ev_pri, int ev_handler_addr, EventStatus ev_status)
{
	pEv->event_gen_addr = ev_gen_ID; //생성된 이벤트의 위치 할당
	pEv->event_handler_addr = -1; // 재정의 했는지 확인하는 자료(이 프로그램에는 재정의 하지않음)
	pEv->event_no = ev_no; //이벤트 번호 할당
	pEv->event_pri = ev_pri; //우선순위 할당
	//pEv->event_handler_addr = ev_handler_addr; // 재정의 했는지 확인하는 자료(이 프로그램에는 재정의 하지않음)
	pEv->eventStatus = ev_status; //현재 이벤트의 상태 (생성, 작업대기, 작업완료, 미설정)
}
//void printEventArray(Event* pEv, int size, int items_per_line)
//{
//	for (int i = 0; i < size; i++)
//	{
//		printEvent(&pEv[i]);
//		if (((i + 1) % items_per_line) == 0)
//			printf("?n ");
//	}
//}