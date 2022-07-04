#include <stdio.h>
#include <stdlib.h>
#include "Event.h"
const char* strEventStatus[] = { "GENERATED", "ENQUED", "PROCESSED", "UNDEFINED" };
void printEvent(Event* pEvent)
{
	printf("Ev[no:%3d, pri:%2d, gen(%2d)]) ", pEvent->event_no, pEvent->event_pri, pEvent->event_gen_addr); //번호 / 우선순위 / 발생위치
}
void printEvent_withTime(Event* pEv)
{
	printf("Ev(no:%3d, pri:%2d, %6.0lf[ms]) ", pEv->event_no, pEv->event_pri, pEv->t_elapsed * 1000); //번호 / 우선순위 / 시간
}
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq)
{
	LONGLONG t_diff_LL;
	double t_elapsed;
	t_diff_LL = pEv->t_proc.QuadPart - pEv->t_gen.QuadPart;
	t_elapsed = (double)t_diff_LL / (double)freq.QuadPart;
	pEv->t_elapsed = t_elapsed;
}
