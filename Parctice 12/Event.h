#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>
#include <Windows.h>
#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5
enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
//extern const char* strEventStatus[];
typedef struct
{
	int ev_no; //�̺�Ʈ ��ȣ
	int ev_generator; //�̺�Ʈ �߻�Ƚ��
	int ev_handler; //�̺�Ʈ �ڵ�
	int ev_pri; // �̺�Ʈ �켱����
	LARGE_INTEGER ev_t_gen; // ���� ����͸�(�̺�Ʈ ����)
	LARGE_INTEGER ev_t_handle; // ���� ����͸�(�̺�Ʈ �ڵ�)
	double elap_time; // ���� ����͸�(�۵� �ð�)
	EventStatus eventStatus;
} Event;
void printEvent(Event* pEv); //�̺�Ʈ ���
//void fprintEvent(FILE* fout, Event* pEv); //���Ͽ� ���
//Event* genEvent(Event* pEv, int event_Gen_ID, int ev_no, int ev_pri); //�̺�Ʈ ����
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq); //�̺�Ʈ ���ð� ����
void printEvent_withTime(Event* pEv); //�̺�Ʈ ���ð� ���
#endif




