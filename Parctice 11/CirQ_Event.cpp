#include <stdio.h>
#include <stdlib.h>
#include "CirQ_Event.h"

CirQ_Event* initCirQ(CirQ_Event* pCirQ, int capacity) //ȯ�� ť�� ����
{
	Event* pEv;
	pEv = (Event*)calloc(capacity, sizeof(Event));
	if (pEv == NULL)
	{
		printf("Error in memory allocation for Event array of size (%d)\n", capacity);
		exit;
	}
	pCirQ->pEv = pEv; //����ִ� ȯ�� ť ������
	pCirQ->capacity = capacity; //ȯ�� ť ������ �� ȯ�� ť�� �뷮
	pCirQ->front = pCirQ->end = 0; //�ֻ��� ��
	pCirQ->num_elements = 0; //����� ����(�ʱ�� ������ 0)
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
	if (pCirQ->num_elements == pCirQ->capacity) //���� ������� ������ ť �뷮�� ���ٸ�
		return true; //���� á�ٰ� ��
	else
		return false; //���� �ִٰ� ����
}
bool isCirQEmpty(CirQ* pCirQ)
{
	if (pCirQ->num_elements == 0) //������� ������ 0�̶��
		return true; //������� ��
	else
		return false; //���� á���� ����
}
Event* enCirQ(FILE* fout, CirQ_Event* pCirQ, Event ev)
{
	if (isCirQFull(pCirQ)) //���� ť�� ���� á�ٸ� �ΰ� ��ȯ
	{
		return NULL;
	}
	pCirQ->pEv[pCirQ->end] = ev;
	pCirQ->num_elements++; //�Ҵ������� ������� ���� ����
	pCirQ->end++; //�Ҵ������� ������ ĭ ��ȣ ����
	if (pCirQ->end >= pCirQ->capacity)
		pCirQ->end = pCirQ->end % pCirQ->capacity;
	return &(pCirQ->pEv[pCirQ->end]); //ȯ��ť �����͸� ȯ��ť�� ������ ��ġ�� ��ȯ
}
Event* deCirQ(FILE* fout, CirQ* pCirQ)
{
	if (isCirQEmpty(pCirQ)) //���� ť�� ����ٸ� �ΰ� ��ȯ
		return NULL;
	Event* pEv = &(pCirQ->pEv[pCirQ->front]);
	pCirQ->front++;
	if (pCirQ->front >= pCirQ->capacity)
		pCirQ->front = pCirQ->front % pCirQ->capacity; //�ֻ��� ť�� ��ȯ��
	pCirQ->num_elements--;
	return pEv; //����Ⱑ �Ϸ�� ȯ�� ť ������ ��ȯ(ȯ��ť�� �ֻ��� ť �κ�)
}
void delCirQ(CirQ* pCirQ) 
{
	if (pCirQ->pEv != NULL)  //ȯ��ť�� �ִٸ�
		free(pCirQ->pEv); //��ȯ
	pCirQ->pEv = NULL; //�ݳ��� �������� �����͸� NULL�� �ʱ�ȭ
	pCirQ->capacity = 0; //�뷮�� 0
	pCirQ->front = pCirQ->end = 0; //�ֻ��� ť�� 0
	pCirQ->num_elements = 0; //�ȿ� �������е� 0
}