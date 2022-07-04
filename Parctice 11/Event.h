/**
*���ϸ� : "���α׷��־��_21912229_��ΰ�_�ǽ�_11"
*���α׷��� ���� �� �⺻ ���:
*      -�� ���α׷��� CirQ������ PriQ������ ��������� �����ϰ�
*		�ʴ� 50���� Event�� ó���ϴ� ���α׷��̴�.
*���α׷� �ۼ��� : ��ΰ�(2022�� 05�� 18��)
*���� Update : Version 1.0, 2022�� 05�� 18��(��ΰ�)
*============================================================================
*���α׷� ����/���� �̷�
*============================================================================
*���α׷� ����/�����۾���   ����   ����/���ϳ���
*============================================================================
*/
/* Event.h */
#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>
#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5
enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
extern const char* strEventStatus[];
typedef struct
{
	int event_no; //�̺�Ʈ ��ȣ
	int event_gen_addr; //�̺�Ʈ ���� ����
	int event_handler_addr; //�̺�Ʈ �޸��� ���Ҵ� ����
	int event_pri; //�̺�Ʈ �켱����
	EventStatus eventStatus; //���� �̺�Ʈ�� ����
} Event;
//void printEvent(Event* pEvt);
void fprintEvent(FILE* fout, Event* pEvent);//���Ͽ� ���
Event* genEvent(Event* pEvent, int event_Gen_ID, int event_no, int event_pri); // �̺�Ʈ�� ����(�����)
void initEvent(Event* pEv, int ev_gen_ID, int ev_no, int ev_pri, int ev_handler_addr, EventStatus ev_status); //�̺�Ʈ ����ü�� �Ҵ�
#endif