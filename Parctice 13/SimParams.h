/**
*파일명 : "프로그래밍 언어_21912229_김민관_실습_13"
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 다중 스레드를 이용하여 이중 연결 리스트에 이벤트를 
*		생성하거나, 사용하고, 그 스레드를 모니터링 하는 프로그램이다.
*프로그램 작성자 : 김민관(2022년 06월 02일)
*최종 Update : Version 1.0, 2022년 06월 02일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
*============================================================================
*/


#ifndef SIMULATION_PARAMETERS_H
#define SIMULATION_PARAMETERS_H
#define NUM_EVENT_GENERATORS 3 //생성기의 수
#define NUM_EVENTS_PER_GEN 20 //스레드당 만들 이벤트 수
#define NUM_EVENT_HANDLERS 2 //사용기의 수
#define TOTAL_NUM_EVENTS (NUM_EVENTS_PER_GEN * NUM_EVENT_GENERATORS)
#define PLUS_INF INT_MAX
#define MAX_ROUND 1000 //최대 라운드
#define NUM_PRIORITY 10
#define PRIORITY_THRESHOLD 3 // 0 ~ 2: 상위 우선순위  3 ~ 9: 하위 우선순위
#define EVENT_PER_LINE 5
#endif