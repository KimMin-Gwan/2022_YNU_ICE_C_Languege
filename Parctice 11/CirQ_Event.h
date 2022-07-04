/* CirQ_Event.h */
#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H
#include "Event.h"
typedef struct CirQ
{
	Event* pEv; // circular queue for events
	int capacity; //ȯ��ť�� �뷮
	int front; //ȯ��ť�� �ֻ��� ��
	int end;  //ȯ��ť�� ������ ��
	int num_elements; //����� ����
} CirQ_Event;
CirQ_Event* initCirQ(CirQ_Event* pCirQ, int capacity); //ȯ�� ť�� ����
//void printCirQ(CirQ_Event* pCirQ);
void fprintCirQ(FILE* fout, CirQ* pCirQ); //���Ͽ� ���
bool isCirQFull(CirQ* pCirQ);  //ť�� ���� á���� Ȯ��
bool isCirQEmpty(CirQ* pCirQ); //ť�� ������� Ȯ��
Event* enCirQ(FILE* fout, CirQ_Event* pCirQ, Event ev); //ť�� �Ҵ�
Event* deCirQ(FILE* fout, CirQ* pCirQ); //ȯ�� ť ���θ� ����
void delCirQ(CirQ* pCirQ); //ȯ�� ť ����
#endif