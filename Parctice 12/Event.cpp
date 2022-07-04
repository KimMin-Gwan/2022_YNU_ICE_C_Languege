#include <stdio.h>
#include <stdlib.h>
#include "Event.h"
//const char* strEventStatus[] = { "GENERATED", "ENQUED", "PROCESSED", "UNDEFINED" };
void printEvent(Event* pEv)
{
	char str_pri[6];
	printf("Ev(no:%3d, pri:%2d) ", pEv->ev_no, pEv->ev_pri);
	if (pEv->ev_pri == 0)
		printf("생성 작업은 끝났음을 알림");
}
//void fprintEvent(FILE* fout, Event* pEvent)
//{
//	//char str_pri[6];
//	fprintf(fout, "Ev(no:%3d, pri:%2d) ", pEvent->ev_no, pEvent->ev_pri);
//}
//Event* genEvent(Event* pEv, int event_Gen_ID, int ev_no, int ev_pri)
//{
//	pEv = (Event*)calloc(1, sizeof(Event)); //한칸 할당
//	if (pEv == NULL) //할당 안되면 그냥 널값 리턴
//		return NULL;
//	pEv->ev_generator = event_Gen_ID; //이벤트 발생횟수 할당
//	pEv->ev_handler = -1; //핸들은 아직 사용안해서 -1
//	pEv->ev_no = ev_no; //이벤트 번호 할당
//	//pEv->ev_pri = eventPriority = rand() % NUM_PRIORITY;
//	pEv->ev_pri = ev_pri; //이벤트 우선순위 할당
//	return pEv;
//}

void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq)
{
	LONGLONG t_diff; //차이 계산용
	t_diff = pEv->ev_t_handle.QuadPart - pEv->ev_t_gen.QuadPart; //사용시간 계산
	pEv->elap_time = (double)t_diff / freq.QuadPart; //사용시간 대입
}

void printEvent_withTime(Event* pEv)
{
	char str_pri[6];
	//printf("Ev(no:%3d, pri:%2d, src:%2d, proc:%2d) ", pEv->event_no, pEv->event_pri,
	// pEv->event_gen_addr, pEv->event_handler_addr);
	printf("Ev(no:%2d, pri:%2d, elap_t:%6.0lf[ms]) ", pEv->ev_no, pEv->ev_pri, pEv->elap_time * 1000);
	if (pEv->ev_pri == 1)
		printf("\n이벤트 생성 도중에 프로세싱은 끝났음을 알림\n 이제부터는 아직 프로세싱 하지않은 이벤트들을 처리할것 \n");
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