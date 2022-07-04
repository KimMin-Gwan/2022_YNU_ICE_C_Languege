#include "PriQ_Event.h"
#include "Event.h"
bool hasLeftChild(int pos, PriQ_Event* pPriQ_Ev)
{
	if (pos * 2 <= pPriQ_Ev->priQ_size) //�θ𰪿� 2�� ������ ��, �켱���� ������ ���� ������ ���� �ڽĳ�尡 ����
		return TRUE;
	else
		return FALSE;
}
bool hasRightChild(int pos, PriQ_Event* pPriQ_Ev) //�θ𰪿� 2�� ���ϰ� 1�� ��������, �켱���� ������ ���� ������ ������ �ڽĳ�尡 ����
{
	if (pos * 2 + 1 <= pPriQ_Ev->priQ_size)
		return TRUE;
	else
		return FALSE;
}
PriQ_Event* initPriQ_Ev(PriQ_Event* pPriQ_Ev, const char* name, int capacity)
{
	strcpy(pPriQ_Ev->PriQ_name, name); //�켱���� ����ü �迭�� �̸�
	pPriQ_Ev->priQ_capacity = capacity; //�켱���� ����ü �迭�� ũ��
	pPriQ_Ev->pCBT_Ev = (CBTN_Event*)calloc((capacity + 1), sizeof(CBTN_Event)); //�켱���� ����ü �迭�� �޸� �Ҵ�
	pPriQ_Ev->priQ_size = 0; //�켱��������ü �迭�� ũ��(�����ܰ迡�� 0)
	pPriQ_Ev->pos_last = 0; //�켱���� ����ü�� ������ ��� ��ġ(�����ܰ迡���� 0)
	return pPriQ_Ev;
}
void deletePriQ_Ev(PriQ_Event* pPriQ_Ev)
{
	CBTN_Event* pCBTN_Ev;
	for (int i = 0; i < pPriQ_Ev->priQ_size; i++)
	{
		pCBTN_Ev = &(pPriQ_Ev->pCBT_Ev)[i]; //������ �켱����ť�� �̺�Ʈ�� ����Ų��
		if (pCBTN_Ev != NULL) //���� �켱���� ť�� �����,
		{
			if (pCBTN_Ev->pEvent != NULL) //�켱���� �̺�Ʈ�� ����ٸ�
				free(pCBTN_Ev->pEvent); //�̺�Ʈ�� �Ҵ����� �޸𸮸� ��ȯ
			free(pCBTN_Ev); //�켱����ť ��ȯ
		}
	}
}
int enPriQ_Ev(PriQ_Event* pPriQ_Ev, Event* pEv)
{
	int pos, pos_parent;
	CBTN_Event CBTN_Ev_tmp;
	if (pPriQ_Ev->priQ_size >= pPriQ_Ev->priQ_capacity) //���� ť�� ������ ���� ������ ���ٸ�
	{
		// Priority Queue is full
		/* Expand the capacity twice, and copy the entries */
		CBTN_Event* newCBT_Event;
		int newCapacity;
		newCapacity = 2 * pPriQ_Ev->priQ_capacity;
		newCBT_Event = (CBTN_Event*)malloc((newCapacity + 1) * sizeof(CBTN_Event));
		if (newCBT_Event == NULL) //���Ӱ� ���� ���� ���� Ʈ���� �Ҵ��� �ȉ�����
		{
			printf("Error in expanding CompleteBinaryTree for Priority Queue !!\n");
			exit(-1);
		}
		for (int pos = 1; pos <= pPriQ_Ev->priQ_size; pos++)
		{
			newCBT_Event[pos] = pPriQ_Ev->pCBT_Ev[pos];//���� ���� Ʈ���� ������ �̺�Ʈ �Ҵ�
		}
		free(pPriQ_Ev->pCBT_Ev); //���� �ִ� �̺�Ʈ �迭 �ݳ�
		pPriQ_Ev->pCBT_Ev = newCBT_Event; //����Ʈ���� ����� �迭�� �Ҵ�
		pPriQ_Ev->priQ_capacity = newCapacity; //����ť ũ�⸦ ���Ӱ� ����
	} // end - if
	/* insert at the last position */
	pos = pPriQ_Ev->pos_last = ++pPriQ_Ev->priQ_size; //������ ��ġ�� priQ�� ������ ���ϱ� 1
	pPriQ_Ev->pCBT_Ev[pos].priority = pEv->event_pri; //�켱���� �Ҵ�
	pPriQ_Ev->pCBT_Ev[pos].pEvent = pEv; //�̺�Ʈ �Ҵ�
	while (pos != POS_ROOT) //�켱������ �������� �� ���� ����
	{
		pos_parent = pos / 2;
		if (pPriQ_Ev->pCBT_Ev[pos].priority > pPriQ_Ev->pCBT_Ev[pos_parent].priority)
		{
			break;  //���̻� ��ȯ�� ��尡 ���ٸ� �극��ũ
		}
		else //��ȯ�� ��尡 ���Ҵٸ� ����ؼ� �� ���� ����
		{
			CBTN_Ev_tmp = pPriQ_Ev->pCBT_Ev[pos_parent]; 
			pPriQ_Ev->pCBT_Ev[pos_parent] = pPriQ_Ev->pCBT_Ev[pos];
			pPriQ_Ev->pCBT_Ev[pos] = CBTN_Ev_tmp;
			pos = pos_parent;
		}
	} 
}

Event* removeMinPriQ_Event(PriQ_Event* pPriQ_Event)  
{
	Event* pEv;
	CBTN_Event CBTN_Event_temp;
	int pos, pos_last, pos_child;
	if (pPriQ_Event->priQ_size <= 0)   //PriQ�� ����ִ� ��� NULL�� ��ȯ (���� priQ�� ����)
		return NULL;
	pEv = pPriQ_Event->pCBT_Ev[1].pEvent; //���� �ֻ�� �ּ�
	pos_last = pPriQ_Event->priQ_size; //���� priQ�� ������� ������ ��� ��ġ
	--pPriQ_Event->priQ_size;
	if (pPriQ_Event->priQ_size > 0)   //�ٿ� ���� ���� ����
	{
		pPriQ_Event->pCBT_Ev[POS_ROOT] = pPriQ_Event->pCBT_Ev[pos_last];   //root�� ����� ������ ��带 root�� ������� 
		pos_last--; //�ϳ� ��������� ������ ��带 �ϳ� ������
		pos = POS_ROOT;
		while (hasLeftChild(pos, pPriQ_Event))   //�ֻ�� ���� ���� �ڽĳ�� Ȯ��
		{
			pos_child = pos * 2;
			if (hasRightChild(pos, pPriQ_Event))   //������ �ڽĳ�� ���� Ȯ��
			{
				if (pPriQ_Event->pCBT_Ev[pos_child].priority > pPriQ_Event->pCBT_Ev[pos_child + 1].priority)   //������� ���� �켱������ ��
					pos_child = pos * 2 + 1;   //������ child�� �켱������ �� ������� ������ child�� ��ġ ����
			}
			if (pPriQ_Event->pCBT_Ev[pos_child].priority < pPriQ_Event->pCBT_Ev[pos].priority)   //�켱������ ���� �ڽĳ��� �ڸ��ٲٱ�
			{
				CBTN_Event_temp = pPriQ_Event->pCBT_Ev[pos];
				pPriQ_Event->pCBT_Ev[pos] = pPriQ_Event->pCBT_Ev[pos_child];
				pPriQ_Event->pCBT_Ev[pos_child] = CBTN_Event_temp;
			}
			else //���̻� ��Ȯ�� �ʿ䰡 ���ٸ� �극��ũ
				break;
			pos = pos_child;   //����ؼ� ���� ��ġ���� ���� ����
		}
	}
	return pEv; //�ϳ��� ����� ��� ������ ���� ������ ���� ��ȯ
}
void fprintPriQ_Ev(FILE* fout, PriQ_Event* pPriQ_Ev)
{
	int pos, count, count_per_line;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;
	if (pPriQ_Ev->priQ_size == 0)
	{
		fprintf(fout, "PriorityQueue_Event is empty !!\n");
		return;
	}
	pos = 1;
	count = 1;
	level = 0;
	level_count = 1; // level_count = 2^^level
	fprintf(fout, "\n CompBinTree :\n", level);
	while (count <= pPriQ_Ev->priQ_size)
	{
		fprintf(fout, " level%2d : ", level);
		count_per_line = 0;
		while (count_per_line < level_count)
		{
			pEv = pPriQ_Ev->pCBT_Ev[pos].pEvent;
			eventPriority = pPriQ_Ev->pCBT_Ev[pos].priority;
			fprintEvent(fout, pEv);
			pos++;
			count++;
			if (count > pPriQ_Ev->priQ_size)
				break;
			count_per_line++;
			if ((count_per_line % EVENT_PER_LINE) == 0)
			{
				if (count_per_line < level_count)
					fprintf(fout, "\n ");
				else
					fprintf(fout, "\n");
			}
		} // end - while
		if ((count_per_line % EVENT_PER_LINE) != 0)
			fprintf(fout, "\n");
		level++;
		level_count *= 2;
	} // end - while
	fprintf(fout, "\n");
}