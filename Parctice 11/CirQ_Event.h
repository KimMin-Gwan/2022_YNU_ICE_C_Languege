/* CirQ_Event.h */
#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H
#include "Event.h"
typedef struct CirQ
{
	Event* pEv; // circular queue for events
	int capacity; //환형큐의 용량
	int front; //환형큐의 최상위 값
	int end;  //환형큐의 최하위 값
	int num_elements; //요소의 갯수
} CirQ_Event;
CirQ_Event* initCirQ(CirQ_Event* pCirQ, int capacity); //환형 큐의 생성
//void printCirQ(CirQ_Event* pCirQ);
void fprintCirQ(FILE* fout, CirQ* pCirQ); //파일에 출력
bool isCirQFull(CirQ* pCirQ);  //큐가 가득 찼는지 확인
bool isCirQEmpty(CirQ* pCirQ); //큐가 비었는지 확인
Event* enCirQ(FILE* fout, CirQ_Event* pCirQ, Event ev); //큐에 할당
Event* deCirQ(FILE* fout, CirQ* pCirQ); //환형 큐 내부를 제거
void delCirQ(CirQ* pCirQ); //환형 큐 삭제
#endif