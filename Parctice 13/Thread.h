#ifndef THREAD_H
#define THREAD_H
#include <Windows.h>
#include <thread>
#include <mutex>
#include <process.h>
#include "Event.h"
#include "SimParams.h"
#include "DLL_EvQ.h"
using namespace std;
enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };
typedef struct
{
	int eventsGen[NUM_EVENT_GENERATORS]; // 생성기 인덱스
	int eventsProc[NUM_EVENT_HANDLERS]; // 작동기 인덱스
	int totalEventGen; //총 만들어낸 이벤트 수
	int totalEventProc; //총 작동한 이벤트 수
	int numEventProcs_priH; //상위 프리큐의 이벤트 수
	int numEventProcs_priL; //하위 프리큐의 이벤트 수
	THREAD_FLAG* pFlagThreadTerminate; //상태 플래그
	Event eventGenerated[TOTAL_NUM_EVENTS]; //만든 이벤트
	Event eventProcessed[TOTAL_NUM_EVENTS]; //동작한 이벤트
} ThreadStatMon; 
typedef struct
{
	//FILE* fout;
	mutex* pCS_main; //메인 뮤택스
	mutex* pCS_thrd_mon; //스레드 콘솔 뮤택스
	DLL_EvQ* EvQ_PriH; //상위 프리큐
	DLL_EvQ* EvQ_PriL; //하위 프리큐
	ROLE role; //역할
	int myAddr; //주소
	int maxRound; //최대 라운드 수 
	int targetEventGen; //라운드당 만들 이벤트 위치
	LARGE_INTEGER PC_freq;
	// frequency of performance counter that is used to measure elapsed time
	ThreadStatMon* pThrdMon; //스레드 모니터
} ThreadParam_Ev;
void Thread_EventHandler(ThreadParam_Ev* pParam); //사용기
void Thread_EventGenerator(ThreadParam_Ev* pParam); //생성기
#endif