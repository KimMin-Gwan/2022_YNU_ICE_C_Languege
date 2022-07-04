#include "DLL_EvQ.h"
void initDLL_EvQ(DLL_EvQ* pEvQ, int pri)
{
	pEvQ->cs_EvQ.lock();
	pEvQ->priority = pri; //초기 우선순위
	pEvQ->front = pEvQ->back = NULL; //초기 앞과 뒤 구조체는 없음
	pEvQ->num_event = 0; //초기 이벤트 번호 0
	pEvQ->cs_EvQ.unlock();
}

Event* enDLL_EvQ(DLL_EvQ* pEvQ, Event* pEv)
{
	DLLN_Ev* pLN_Ev; //새롭게 추가될 포인터
	if (pEv == NULL)
	{
		printf("Error in enDLL_EvQ :: DLL_EvQ is NULL !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Ev = (DLLN_Ev*)calloc(1, sizeof(DLLN_Ev)); //할당
	if (pLN_Ev == NULL)
	{
		printf("Error in enDLL_EvQ :: memory allocation for new DLLN failed !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}

	pLN_Ev->pEv = pEv;
	pEvQ->cs_EvQ.lock();
	if (pEvQ->num_event == 0)  //하나도 없을때
	{
		pEvQ->front = pEvQ->back = pLN_Ev; //전체 리스트의 처음과 끝부분을 지정
		pLN_Ev->prev = pLN_Ev->next = NULL; //첫번째로 들어온 개체의 앞과 뒤는 비엇음
		pEvQ->num_event = 1; //첫번째 이벤트로 설정
	}
	else //이외의 상황
	{
		pLN_Ev->prev = pEvQ->back; //새로운 개체의 뒤를 리스트의 끝으로 지정
		pEvQ->back->next = pLN_Ev; //리스트의 끝의 다음 개체를 새로운 개체로 지정
		pEvQ->back = pLN_Ev; //리스트의 끝을 새로운 개체로 지정
		pLN_Ev->next = NULL; //그다음은 없으니 비엇음
		pEvQ->num_event++; 
	}
	pEvQ->cs_EvQ.unlock();
	return pLN_Ev->pEv;
}

Event* deDLL_EvQ(DLL_EvQ* pEvQ)
{
	Event* pEv;
	DLLN_Ev* pLN_Ev_OldFront;
	pEvQ->cs_EvQ.lock();
	if (pEvQ->num_event <= 0) //더 지울 리스트가 없다면
	{
		pEvQ->cs_EvQ.unlock();
		return NULL; //비었음
	}
	else
	{
		pLN_Ev_OldFront = pEvQ->front; //곧 사라질 가장 앞 리스트
		pEv = pEvQ->front->pEv; //가장 앞 리스트의 이벤트
		pEvQ->front = pEvQ->front->next; //가장 앞 리스트 다음 리스트가 가장 앞이 됨
		if (pEvQ->front != NULL)
			pEvQ->front->prev = NULL; //뒷부분을 비움
		pEvQ->num_event--; //이벤트 갯수 줄이기
		free(pLN_Ev_OldFront); //리스트 자체를 반환
		pEvQ->cs_EvQ.unlock();
		return pEv;
	}
}

void printDLL_EvQ(DLL_EvQ* pEvQ)
{
	int index = 0;
	int count;
	Event* pEv;
	DLLN_Ev* pLN_Ev; 
	if (pEvQ == NULL)
	{
		printf("Error in printDLL_EvQ :: DLL_EvQ is NULL !!"); 
		printf("Press any key to continue ...\n"); 
		getc(stdin);
	}//printf("DLL_EvQ(num_event: %2d):\n ", pEvQ->num_event); 
	if (pEvQ->num_event <= 0)
		return; 
	pLN_Ev = pEvQ->front;
	count = 0;
	while (pLN_Ev != NULL)
	{
		pEv = pLN_Ev->pEv;
		if (pEv == NULL) 
			break;
		printEvent(pEv); 
		printf(" ");
		count++; 
		if ((count % 5) == 0) 
			printf("\n ");
		pLN_Ev = pLN_Ev->next;
	}
}