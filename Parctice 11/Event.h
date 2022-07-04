/**
*파일명 : "프로그래밍언어_21912229_김민관_실습_11"
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 CirQ구조와 PriQ구조의 실행과정을 구현하고
*		초대 50개의 Event를 처리하는 프로그램이다.
*프로그램 작성자 : 김민관(2022년 05월 18일)
*최종 Update : Version 1.0, 2022년 05월 18일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
*============================================================================
*/
/* Event.h */
#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>
#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5
enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
extern const char* strEventStatus[];
typedef struct
{
	int event_no; //이벤트 번호
	int event_gen_addr; //이벤트 생성 갯수
	int event_handler_addr; //이벤트 메모리의 재할당 여부
	int event_pri; //이벤트 우선순의
	EventStatus eventStatus; //현재 이벤트의 상태
} Event;
//void printEvent(Event* pEvt);
void fprintEvent(FILE* fout, Event* pEvent);//파일에 출력
Event* genEvent(Event* pEvent, int event_Gen_ID, int event_no, int event_pri); // 이벤트를 생성(빈공간)
void initEvent(Event* pEv, int ev_gen_ID, int ev_no, int ev_pri, int ev_handler_addr, EventStatus ev_status); //이벤트 구조체에 할당
#endif