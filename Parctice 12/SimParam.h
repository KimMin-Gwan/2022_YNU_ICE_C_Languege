/**
*파일명 : "프로그래밍 언어_21912229_김민관_실습_12"
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 우선순위에 따른 이벤트 처리를 하는 PriQueue를 다중
*		스레드를 이용하여 동작시키는 프로그램이다.
*프로그램 작성자 : 김민관(2022년 05월 22일)
*최종 Update : Version 1.0, 2022년 05월 25일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
*김민관 2022/05/24  ver 1.1 주석작성
*김민관 2022/05/25  ver 1.2 필요없는 변수, 함수 제거
*============================================================================
*/

/* SimParam.h Simulation Parameters */
#ifndef SIMULATION_PARAMETERS_H
#define SIMULATION_PARAMETERS_H
#define NUM_EVENT_GENERATORS 1
#define NUM_EVENTS_PER_GEN 50 //최대 50개 만들것
#define NUM_EVENT_HANDLERS 1
#define TOTAL_NUM_EVENTS (NUM_EVENTS_PER_GEN * NUM_EVENT_GENERATORS)
#define PRI_QUEUE_CAPACITY 1
#define PLUS_INF INT_MAX
#define MAX_ROUND 1000 //최대 1000번까지
#endif

