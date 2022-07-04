#include "PriQ_Event.h"
#include "Event.h"
#include <mutex>

bool hasLeftChild(int pos, PriQ_Ev* pPriQ_Ev)
{
	if (pos * 2 <= pPriQ_Ev->priQ_size) //부모값에 2를 곱했을 때, 우선순의 사이즈 보다 작으면 왼쪽 자식노드가 있음
		return TRUE;
	else
		return FALSE;
}
bool hasRightChild(int pos, PriQ_Ev* pPriQ_Ev) //부모값에 2를 곱하고 1을 더했을때, 우선순위 사이즈 보다 작으면 오른쪽 자식노드가 있음
{
	if (pos * 2 + 1 <= pPriQ_Ev->priQ_size)
		return TRUE;
	else
		return FALSE;
}
PriQ_Ev* initPriQ_Event(PriQ_Ev* pPriQ_Ev, const char* name, int capacity)
{
	pPriQ_Ev->cs_PriQ.lock(); //뮤텍스 닫기
	strcpy(pPriQ_Ev->PriQ_name, name); //우선순위 구조체 배열의 이름
	pPriQ_Ev->priQ_capacity = capacity; //우선순위 구조체 배열당 크기
	pPriQ_Ev->pCBT_Ev = (CBTN_Event*)calloc((capacity + 1), sizeof(CBTN_Event)); //우선순위 구조체 배열에 메모리 할당
	pPriQ_Ev->priQ_size = 0; //우선순위구조체 배열의 크기(생성단계에선 0)
	pPriQ_Ev->pos_last = 0; //우선순위 구조체의 마지막 노드 위치(생성단계에서는 0)
	pPriQ_Ev->cs_PriQ.unlock(); //뮤텍스 열기
	return pPriQ_Ev;
}
void deletePriQ_Event(PriQ_Ev* pPriQ_Event)
{
	pPriQ_Event->cs_PriQ.lock(); //뮤텍스 닫기
	if (pPriQ_Event->pCBT_Ev != NULL)
		free(pPriQ_Event->pCBT_Ev);
	pPriQ_Event->cs_PriQ.unlock(); //뮤텍스 열기
}

Event* enPriQ_Ev(PriQ_Ev* pPriQ_Ev, Event Ev)
{
	int pos, pos_parent;
	CBTN_Event CBTN_Ev_tmp;
	pPriQ_Ev->cs_PriQ.lock();
	if (pPriQ_Ev->priQ_size >= pPriQ_Ev->priQ_capacity) //만약 큐과 꽉차서 넣을 공간이 없다면
	{
		CBTN_Event* newCBT_Event;
		int newCapacity;
		newCapacity = 2 * pPriQ_Ev->priQ_capacity;
		newCBT_Event = (CBTN_Event*)malloc((newCapacity + 1) * sizeof(CBTN_Event));
		if (newCBT_Event == NULL){ //새롭게 만든 완전 이진 트리가 할당이 안됬으면
			printf("Error in expanding CompleteBinaryTree for Priority Queue !!\n"); exit(-1);}
		for (int pos = 1; pos <= pPriQ_Ev->priQ_size; pos++)
		{
			newCBT_Event[pos] = pPriQ_Ev->pCBT_Ev[pos];//완전 이진 트리에 생성한 이벤트 할당
		}
		free(pPriQ_Ev->pCBT_Ev); //전에 있던 이벤트 배열 반납
		pPriQ_Ev->pCBT_Ev = newCBT_Event; //이진트리로 변경된 배열을 할당
		pPriQ_Ev->priQ_capacity = newCapacity; //프리큐 크기를 새롭게 지정
	} 
	/* insert at the last position */
	pos = pPriQ_Ev->pos_last = ++pPriQ_Ev->priQ_size; //마지막 위치는 priQ의 사이즈 더하기 1
	pPriQ_Ev->pCBT_Ev[pos].priority = Ev.ev_pri; //우선순위 할당
	pPriQ_Ev->pCBT_Ev[pos].event = Ev; //이벤트 할당
	while (pos != POS_ROOT) //우선순위를 기준으로 업 버블 소팅
	{
		pos_parent = pos / 2;
		if (pPriQ_Ev->pCBT_Ev[pos].priority > pPriQ_Ev->pCBT_Ev[pos_parent].priority)
		{
			break;  //더이상 교환할 노드가 없다면 브레이크
		}
		else //교환할 노드가 남았다면 계속해서 업 버블 소팅
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
	if (pPriQ_Event->priQ_size <= 0)   //PriQ가 비어있는 경우 NULL값 반환 (지울 priQ가 없음)
		return NULL;
	pPriQ_Event->cs_PriQ.lock();
	pEv = (Event*)calloc(1, sizeof(Event));

	*pEv = pPriQ_Event->pCBT_Ev[POS_ROOT].event; //현재 최상단 주소
	pos_last = pPriQ_Event->priQ_size; //현재 priQ의 사이즈는 마지막 노드 위치
	pPriQ_Event->priQ_size--;
	if (pPriQ_Event->priQ_size > 0)   //다운 버블 소팅 시작
	{
		pPriQ_Event->pCBT_Ev[POS_ROOT] = pPriQ_Event->pCBT_Ev[pos_last];   //root를 지우고 최하위 노드를 root로 가지고옴 
		pos_last--; //하나 사라졌으니 마지막 노드를 하나 지워줌
		pos = POS_ROOT;
		while (hasLeftChild(pos, pPriQ_Event))   //최상단 기준 왼쪽 자식노드 확인
		{
			pos_child = pos * 2;
			if (hasRightChild(pos, pPriQ_Event))   //오른쪽 자식노드 존재 확인
			{
				if (pPriQ_Event->pCBT_Ev[pos_child].priority > pPriQ_Event->pCBT_Ev[pos_child + 1].priority)   //형제노드 끼리 우선순위를 비교
					pos_child = pos * 2 + 1;   //오른쪽 child의 우선순위가 더 높은경우 오른쪽 child로 위치 변경
			}
			if (pPriQ_Event->pCBT_Ev[pos_child].priority < pPriQ_Event->pCBT_Ev[pos].priority)   //우선순위가 높은 자식노드와 자리바꾸기
			{
				CBTN_Event_temp = pPriQ_Event->pCBT_Ev[pos];
				pPriQ_Event->pCBT_Ev[pos] = pPriQ_Event->pCBT_Ev[pos_child];
				pPriQ_Event->pCBT_Ev[pos_child] = CBTN_Event_temp;
			}
			else //더이상 교확할 필요가 없다면 브레이크
				break;
			pos = pos_child;   //계속해서 다음 위치에서 버블 소팅
		}
	}
	pPriQ_Event->cs_PriQ.unlock();
	return pEv; //하나를 지우고 모든 소팅이 끝난 포인터 값을 반환
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
