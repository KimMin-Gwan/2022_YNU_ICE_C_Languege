#ifndef THREAD_H
#define THREAD_H
using namespace std;
enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };
#define THREAD_RETURN_CODE 7
#include "SimParam.h"
#include "PriQ_Event.h"
#include <mutex>

typedef struct //스레트 상태
{
	int numEventGenerated; //발생시킨 이벤트 갯수
	int numEventProcessed; //사용한 이벤트 갯수
	int totalEventGenerated; //총 발생시킨 이벤트 갯수
	int totalEventProcessed; //총 사용한 이벤트 갯수
	Event eventGenerated[TOTAL_NUM_EVENTS]; // 발생시킨 이벤트 위치
	Event eventProcessed[TOTAL_NUM_EVENTS]; // 작동되는 이벤트 위치
	THREAD_FLAG* pFlagThreadTerminate; //현재 상태 파악도구
} ThreadStatusMonitor;

typedef struct //스레드 파라미터 (스레드가 작동할 영역을 지정해줄것)
{
	mutex* pMTX_main;  //메인 뮤텍스
	mutex* pMTX_thrd_mon; //스레드 뮤텍스 모니터링용(핸들에서 사용할것)
	PriQ_Ev* pPriQ_Event; //작업에 들어갈 이벤트 포인터
	ROLE role; //현재 스레드가 맡은 일(생성 or 사용)
	int myAddr; //현재 주소
	int maxRound; //최대 라운드 수
	int targetEventGen; //생성할 총 이벤트 갯수
	ThreadStatusMonitor* pThrdMon; //스레드 상태를 파악할 것
} ThreadParam_Event; 

void Thread_EventHandler(ThreadParam_Event* pParam);   //이벤트 핸들, 이벤트 끼리 연동
void Thread_EventGenerator(ThreadParam_Event* pParam); //이벤트 발생기
#endif

