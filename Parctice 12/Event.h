#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>
#include <Windows.h>
#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5
enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
//extern const char* strEventStatus[];
typedef struct
{
	int ev_no; //이벤트 번호
	int ev_generator; //이벤트 발생횟수
	int ev_handler; //이벤트 핸들
	int ev_pri; // 이벤트 우선순위
	LARGE_INTEGER ev_t_gen; // 동작 모니터링(이벤트 생성)
	LARGE_INTEGER ev_t_handle; // 동작 모니터링(이벤트 핸들)
	double elap_time; // 동작 모니터링(작동 시간)
	EventStatus eventStatus;
} Event;
void printEvent(Event* pEv); //이벤트 출력
//void fprintEvent(FILE* fout, Event* pEv); //파일에 출력
//Event* genEvent(Event* pEv, int event_Gen_ID, int ev_no, int ev_pri); //이벤트 생성
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq); //이벤트 사용시간 측정
void printEvent_withTime(Event* pEv); //이벤트 사용시간 출력
#endif




