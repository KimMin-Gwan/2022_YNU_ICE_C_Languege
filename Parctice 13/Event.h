#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>
#include "ConsoleDisplay.h"
#include "SimParams.h"
enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
extern const char* strEventStatus[];
typedef struct
{
	int event_no; //��ȣ
	int event_gen_addr; //������ �ּ�
	int event_handler_addr; //���� �ּ�
	int event_pri; //�켱����
	LARGE_INTEGER t_gen; //�ð� ������(����)
	LARGE_INTEGER t_proc; //�ð� ������(���)
	double t_elapsed; //�ð� ���� �����
	EventStatus eventStatus; //�̺�Ʈ ����
} Event;
void printEvent(Event* pEvt); //�̺�Ʈ ���
void printEvent_withTime(Event* pEv); //�ð��� �Բ� �̺�Ʈ ���
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq); //�ð� ����
#endif