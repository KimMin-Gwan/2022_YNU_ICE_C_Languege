#include "PriQ_Event.h"
#include "Event.h"
#include <mutex>

bool hasLeftChild(int pos, PriQ_Ev* pPriQ_Ev)
{
	if (pos * 2 <= pPriQ_Ev->priQ_size) //�θ𰪿� 2�� ������ ��, �켱���� ������ ���� ������ ���� �ڽĳ�尡 ����
		return TRUE;
	else
		return FALSE;
}
bool hasRightChild(int pos, PriQ_Ev* pPriQ_Ev) //�θ𰪿� 2�� ���ϰ� 1�� ��������, �켱���� ������ ���� ������ ������ �ڽĳ�尡 ����
{
	if (pos * 2 + 1 <= pPriQ_Ev->priQ_size)
		return TRUE;
	else
		return FALSE;
}
PriQ_Ev* initPriQ_Event(PriQ_Ev* pPriQ_Ev, const char* name, int capacity)
{
	pPriQ_Ev->cs_PriQ.lock(); //���ؽ� �ݱ�
	strcpy(pPriQ_Ev->PriQ_name, name); //�켱���� ����ü �迭�� �̸�
	pPriQ_Ev->priQ_capacity = capacity; //�켱���� ����ü �迭�� ũ��
	pPriQ_Ev->pCBT_Ev = (CBTN_Event*)calloc((capacity + 1), sizeof(CBTN_Event)); //�켱���� ����ü �迭�� �޸� �Ҵ�
	pPriQ_Ev->priQ_size = 0; //�켱��������ü �迭�� ũ��(�����ܰ迡�� 0)
	pPriQ_Ev->pos_last = 0; //�켱���� ����ü�� ������ ��� ��ġ(�����ܰ迡���� 0)
	pPriQ_Ev->cs_PriQ.unlock(); //���ؽ� ����
	return pPriQ_Ev;
}
void deletePriQ_Event(PriQ_Ev* pPriQ_Event)
{
	pPriQ_Event->cs_PriQ.lock(); //���ؽ� �ݱ�
	if (pPriQ_Event->pCBT_Ev != NULL)
		free(pPriQ_Event->pCBT_Ev);
	pPriQ_Event->cs_PriQ.unlock(); //���ؽ� ����
}

Event* enPriQ_Ev(PriQ_Ev* pPriQ_Ev, Event Ev)
{
	int pos, pos_parent;
	CBTN_Event CBTN_Ev_tmp;
	pPriQ_Ev->cs_PriQ.lock();
	if (pPriQ_Ev->priQ_size >= pPriQ_Ev->priQ_capacity) //���� ť�� ������ ���� ������ ���ٸ�
	{
		CBTN_Event* newCBT_Event;
		int newCapacity;
		newCapacity = 2 * pPriQ_Ev->priQ_capacity;
		newCBT_Event = (CBTN_Event*)malloc((newCapacity + 1) * sizeof(CBTN_Event));
		if (newCBT_Event == NULL){ //���Ӱ� ���� ���� ���� Ʈ���� �Ҵ��� �ȉ�����
			printf("Error in expanding CompleteBinaryTree for Priority Queue !!\n"); exit(-1);}
		for (int pos = 1; pos <= pPriQ_Ev->priQ_size; pos++)
		{
			newCBT_Event[pos] = pPriQ_Ev->pCBT_Ev[pos];//���� ���� Ʈ���� ������ �̺�Ʈ �Ҵ�
		}
		free(pPriQ_Ev->pCBT_Ev); //���� �ִ� �̺�Ʈ �迭 �ݳ�
		pPriQ_Ev->pCBT_Ev = newCBT_Event; //����Ʈ���� ����� �迭�� �Ҵ�
		pPriQ_Ev->priQ_capacity = newCapacity; //����ť ũ�⸦ ���Ӱ� ����
	} 
	/* insert at the last position */
	pos = pPriQ_Ev->pos_last = ++pPriQ_Ev->priQ_size; //������ ��ġ�� priQ�� ������ ���ϱ� 1
	pPriQ_Ev->pCBT_Ev[pos].priority = Ev.ev_pri; //�켱���� �Ҵ�
	pPriQ_Ev->pCBT_Ev[pos].event = Ev; //�̺�Ʈ �Ҵ�
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
	pPriQ_Ev->cs_PriQ.unlock();
	return&(pPriQ_Ev->pCBT_Ev[pPriQ_Ev->pos_last].event);
}

Event* dePriQ_Event(PriQ_Ev* pPriQ_Event)
{
	Event* pEv;
	CBTN_Event CBTN_Event_temp;
	int pos, pos_last, pos_child;
	if (pPriQ_Event->priQ_size <= 0)   //PriQ�� ����ִ� ��� NULL�� ��ȯ (���� priQ�� ����)
		return NULL;
	pPriQ_Event->cs_PriQ.lock();
	pEv = (Event*)calloc(1, sizeof(Event));

	*pEv = pPriQ_Event->pCBT_Ev[POS_ROOT].event; //���� �ֻ�� �ּ�
	pos_last = pPriQ_Event->priQ_size; //���� priQ�� ������� ������ ��� ��ġ
	pPriQ_Event->priQ_size--;
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
	pPriQ_Event->cs_PriQ.unlock();
	return pEv; //�ϳ��� ����� ��� ������ ���� ������ ���� ��ȯ
}

//void fprintPriQ_Ev(FILE* fout, PriQ_Ev* pPriQ_Event)
//{
//	int pos, count;
//	int eventPriority;
//	int level = 0, level_count = 1;
//	Event* pEv;
//	if (pPriQ_Event->priQ_size == 0)
//	{
//		fprintf(fout, " PriorityQueue_Event is empty !!\n");
//		return;
//	}
//	pos = 1;
//	count = 1;
//	level = 0;
//	level_count = 1; // level_count = pow(level, 2)
//	fprintf(fout, "\n CompBinTree :\n ");
//	while (count <= pPriQ_Event->priQ_size)
//	{
//		fprintf(fout, " level%2d : ", level);
//		for (int i = 0; i < level_count; i++)
//		{
//			pEv = &(pPriQ_Event->pCBT_Ev[pos].event);
//			eventPriority = pEv->ev_pri;
//			//printf("Event(pri: %2d, id:%2d, src:%2d, dst: %2d) ", eventPriority, pEvent->event_no, pEvent->event_gen_addr, pEvent->event_handler_addr);
//			//printf("Event(pri:%2d, src:%2d, id:%3d) ", eventPriority, pEvent->event_gen_addr,pEvent->event_no);
//			printEvent(pEv);
//			pos++;
//			if ((count % EVENT_PER_LINE) == 0)
//				fprintf(fout, "\n ");
//			count++;
//			if (count > pPriQ_Event->priQ_size)
//				break;
//		}
//		fprintf(fout, "\n");
//		level++;
//		level_count *= 2;
//	} // end - while
//	fprintf(fout, "\n");
//}

void printPriQ_Event(PriQ_Ev* pPriQ_Event)
{
	int pos, count;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;
	if (pPriQ_Event->priQ_size == 0)
	{
		printf(" PriorityQueue_Event is empty !!\n");
		return;
	}
	pos = 1;
	count = 1;
	level = 0;
	level_count = 1; // level_count = pow(level, 2)
	printf("\n CompBinTree :\n ");
	while (count <= pPriQ_Event->priQ_size)
	{
		printf(" level%2d : ", level);
		for (int i = 0; i < level_count; i++)
		{
			pEv = &(pPriQ_Event->pCBT_Ev[pos].event);
			eventPriority = pEv->ev_pri;
			//printf("Event(pri: %2d, id:%2d, src:%2d, dst: %2d) ", eventPriority, pEvent->event_no, pEvent->event_gen_addr, pEvent->event_handler_addr);
			//printf("Event(pri:%2d, src:%2d, id:%3d) ", eventPriority, pEvent->event_gen_addr,pEvent->event_no);
			printEvent(pEv);
			pos++;
			if ((count % EVENT_PER_LINE) == 0)
				printf("\n ");
			count++;
			if (count > pPriQ_Event->priQ_size)
				break;
		}
		printf("\n");
		level++;
		level_count *= 2;
	} // end - while
	printf("\n");

}
