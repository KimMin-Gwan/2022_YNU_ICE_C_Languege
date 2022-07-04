#include <stdio.h>
#include <stdlib.h>
#include "Event.h"
//const char* strEventStatus[] = { "GENERATED", "ENQUED", "PROCESSED", "UNDEFINED" };
void printEvent(Event* pEv)
{
	char str_pri[6];
	printf("Ev(no:%3d, pri:%2d) ", pEv->ev_no, pEv->ev_pri);
	if (pEv->ev_pri == 0)
		printf("���� �۾��� �������� �˸�");
}
//void fprintEvent(FILE* fout, Event* pEvent)
//{
//	//char str_pri[6];
//	fprintf(fout, "Ev(no:%3d, pri:%2d) ", pEvent->ev_no, pEvent->ev_pri);
//}
//Event* genEvent(Event* pEv, int event_Gen_ID, int ev_no, int ev_pri)
//{
//	pEv = (Event*)calloc(1, sizeof(Event)); //��ĭ �Ҵ�
//	if (pEv == NULL) //�Ҵ� �ȵǸ� �׳� �ΰ� ����
//		return NULL;
//	pEv->ev_generator = event_Gen_ID; //�̺�Ʈ �߻�Ƚ�� �Ҵ�
//	pEv->ev_handler = -1; //�ڵ��� ���� �����ؼ� -1
//	pEv->ev_no = ev_no; //�̺�Ʈ ��ȣ �Ҵ�
//	//pEv->ev_pri = eventPriority = rand() % NUM_PRIORITY;
//	pEv->ev_pri = ev_pri; //�̺�Ʈ �켱���� �Ҵ�
//	return pEv;
//}

void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq)
{
	LONGLONG t_diff; //���� ����
	t_diff = pEv->ev_t_handle.QuadPart - pEv->ev_t_gen.QuadPart; //���ð� ���
	pEv->elap_time = (double)t_diff / freq.QuadPart; //���ð� ����
}

void printEvent_withTime(Event* pEv)
{
	char str_pri[6];
	//printf("Ev(no:%3d, pri:%2d, src:%2d, proc:%2d) ", pEv->event_no, pEv->event_pri,
	// pEv->event_gen_addr, pEv->event_handler_addr);
	printf("Ev(no:%2d, pri:%2d, elap_t:%6.0lf[ms]) ", pEv->ev_no, pEv->ev_pri, pEv->elap_time * 1000);
	if (pEv->ev_pri == 1)
		printf("\n�̺�Ʈ ���� ���߿� ���μ����� �������� �˸�\n �������ʹ� ���� ���μ��� �������� �̺�Ʈ���� ó���Ұ� \n");
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