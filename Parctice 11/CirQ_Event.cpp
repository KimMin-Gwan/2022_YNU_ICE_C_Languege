#include <stdio.h>
#include <stdlib.h>
#include "CirQ_Event.h"

CirQ_Event* initCirQ(CirQ_Event* pCirQ, int capacity) //환형 큐의 생성
{
	Event* pEv;
	pEv = (Event*)calloc(capacity, sizeof(Event));
	if (pEv == NULL)
	{
		printf("Error in memory allocation for Event array of size (%d)\n", capacity);
		exit;
	}
	pCirQ->pEv = pEv; //비어있는 환형 큐 포인터
	pCirQ->capacity = capacity; //환형 큐 생성할 때 환형 큐의 용량
	pCirQ->front = pCirQ->end = 0; //최상위 값
	pCirQ->num_elements = 0; //요소의 갯수(초기는 없으니 0)
	return pCirQ;
} 

void fprintCirQ(FILE* fout, CirQ* pCirQ) 
{
	Event ev;
	int index;
	if ((pCirQ == NULL) || (pCirQ->pEv == NULL))
	{
		printf("Error in printArrayQueue: pCirQ is NULL or pCirQ->array is NULL");
		exit;
	}
	fprintf(fout, " %2d Elements in CirQ_Event (index_front:%2d) :\n ",
		pCirQ->num_elements, pCirQ->front);
	if (isCirQEmpty(pCirQ))
	{
		fprintf(fout, "pCirQ_Event is Empty");
	}
	else
	{
		for (int i = 0; i < pCirQ->num_elements; i++)
		{
			index = pCirQ->front + i;
			if (index >= pCirQ->capacity)
				index = index % pCirQ->capacity;
			ev = pCirQ->pEv[index];
			fprintEvent(fout, &ev);
			if ((((i + 1) % EVENT_PER_LINE) == 0) && ((i + 1) != pCirQ->num_elements))
				fprintf(fout, "\n ");
		}
	}
	fprintf(fout, "\n");
}
bool isCirQFull(CirQ* pCirQ)
{
	if (pCirQ->num_elements == pCirQ->capacity) //만약 구성요소 갯수가 큐 용량과 같다면
		return true; //가득 찼다고 참
	else
		return false; //남아 있다고 거짓
}
bool isCirQEmpty(CirQ* pCirQ)
{
	if (pCirQ->num_elements == 0) //구성요소 갯수가 0이라면
		return true; //비엇으니 참
	else
		return false; //가득 찼으니 거짓
}
Event* enCirQ(FILE* fout, CirQ_Event* pCirQ, Event ev)
{
	if (isCirQFull(pCirQ)) //만약 큐가 가득 찼다면 널값 반환
	{
		return NULL;
	}
	pCirQ->pEv[pCirQ->end] = ev;
	pCirQ->num_elements++; //할당했으니 구성요소 갯수 증감
	pCirQ->end++; //할당했으니 마지막 칸 번호 증감
	if (pCirQ->end >= pCirQ->capacity)
		pCirQ->end = pCirQ->end % pCirQ->capacity;
	return &(pCirQ->pEv[pCirQ->end]); //환형큐 포인터를 환형큐의 마지막 위치로 반환
}
Event* deCirQ(FILE* fout, CirQ* pCirQ)
{
	if (isCirQEmpty(pCirQ)) //만약 큐가 비었다면 널값 반환
		return NULL;
	Event* pEv = &(pCirQ->pEv[pCirQ->front]);
	pCirQ->front++;
	if (pCirQ->front >= pCirQ->capacity)
		pCirQ->front = pCirQ->front % pCirQ->capacity; //최상위 큐가 교환됨
	pCirQ->num_elements--;
	return pEv; //지우기가 완료된 환형 큐 포인터 반환(환형큐의 최상위 큐 부분)
}
void delCirQ(CirQ* pCirQ) 
{
	if (pCirQ->pEv != NULL)  //환형큐가 있다면
		free(pCirQ->pEv); //반환
	pCirQ->pEv = NULL; //반납이 끝났으니 포인터를 NULL로 초기화
	pCirQ->capacity = 0; //용량은 0
	pCirQ->front = pCirQ->end = 0; //최상위 큐도 0
	pCirQ->num_elements = 0; //안에 구성성분도 0
}