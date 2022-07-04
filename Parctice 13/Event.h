#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>
#include "ConsoleDisplay.h"
#include "SimParams.h"
enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
extern const char* strEventStatus[];
typedef struct
{
	int event_no; //번호
	int event_gen_addr; //생성기 주소
	int event_handler_addr; //사용기 주소
	int event_pri; //우선순위
	LARGE_INTEGER t_gen; //시간 측정용(생성)
	LARGE_INTEGER t_proc; //시간 측정용(사용)
	double t_elapsed; //시간 측정 저장용
	EventStatus eventStatus; //이벤트 상태
} Event;
void printEvent(Event* pEvt); //이벤트 출력
void printEvent_withTime(Event* pEv); //시간과 함께 이벤트 출력
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq); //시간 측정
#endif