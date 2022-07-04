#include <stdio.h>
#include <stdlib.h>
#include "Event.h"
const char* strEventStatus[] = { "GENERATED", "ENQUED", "PROCESSED", "UNDEFINED" };
//void printEvent(Event* pEvent)
//{
//	char str_pri[6];
//	printf("Ev(no:%3d, pri:%2d) ", pEvent->event_no, pEvent->event_pri);
//}
void fprintEvent(FILE* fout, Event* pEvent)
{
	//char str_pri[6];
	fprintf(fout, "Ev(no:%3d, pri:%2d) ", pEvent->event_no, pEvent->event_pri);
}
Event* genEvent(Event* pEv, int ev_gen_ID, int ev_no, int ev_pri)
{
	pEv = (Event*)calloc(1, sizeof(Event)); //���������
	if (pEv == NULL)
		return NULL;
	initEvent(pEv, ev_gen_ID, ev_no, ev_pri, -1, GENERATED); //���� ���� ����ü�� �Ҵ�
	return pEv;
}
void initEvent(Event* pEv, int ev_gen_ID, int ev_no, int ev_pri, int ev_handler_addr, EventStatus ev_status)
{
	pEv->event_gen_addr = ev_gen_ID; //������ �̺�Ʈ�� ��ġ �Ҵ�
	pEv->event_handler_addr = -1; // ������ �ߴ��� Ȯ���ϴ� �ڷ�(�� ���α׷����� ������ ��������)
	pEv->event_no = ev_no; //�̺�Ʈ ��ȣ �Ҵ�
	pEv->event_pri = ev_pri; //�켱���� �Ҵ�
	//pEv->event_handler_addr = ev_handler_addr; // ������ �ߴ��� Ȯ���ϴ� �ڷ�(�� ���α׷����� ������ ��������)
	pEv->eventStatus = ev_status; //���� �̺�Ʈ�� ���� (����, �۾����, �۾��Ϸ�, �̼���)
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