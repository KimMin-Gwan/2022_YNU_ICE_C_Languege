#include "DLL_EvQ.h"
void initDLL_EvQ(DLL_EvQ* pEvQ, int pri)
{
	pEvQ->cs_EvQ.lock();
	pEvQ->priority = pri; //�ʱ� �켱����
	pEvQ->front = pEvQ->back = NULL; //�ʱ� �հ� �� ����ü�� ����
	pEvQ->num_event = 0; //�ʱ� �̺�Ʈ ��ȣ 0
	pEvQ->cs_EvQ.unlock();
}

Event* enDLL_EvQ(DLL_EvQ* pEvQ, Event* pEv)
{
	DLLN_Ev* pLN_Ev; //���Ӱ� �߰��� ������
	if (pEv == NULL)
	{
		printf("Error in enDLL_EvQ :: DLL_EvQ is NULL !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Ev = (DLLN_Ev*)calloc(1, sizeof(DLLN_Ev)); //�Ҵ�
	if (pLN_Ev == NULL)
	{
		printf("Error in enDLL_EvQ :: memory allocation for new DLLN failed !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}

	pLN_Ev->pEv = pEv;
	pEvQ->cs_EvQ.lock();
	if (pEvQ->num_event == 0)  //�ϳ��� ������
	{
		pEvQ->front = pEvQ->back = pLN_Ev; //��ü ����Ʈ�� ó���� ���κ��� ����
		pLN_Ev->prev = pLN_Ev->next = NULL; //ù��°�� ���� ��ü�� �հ� �ڴ� �����
		pEvQ->num_event = 1; //ù��° �̺�Ʈ�� ����
	}
	else //�̿��� ��Ȳ
	{
		pLN_Ev->prev = pEvQ->back; //���ο� ��ü�� �ڸ� ����Ʈ�� ������ ����
		pEvQ->back->next = pLN_Ev; //����Ʈ�� ���� ���� ��ü�� ���ο� ��ü�� ����
		pEvQ->back = pLN_Ev; //����Ʈ�� ���� ���ο� ��ü�� ����
		pLN_Ev->next = NULL; //�״����� ������ �����
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
	if (pEvQ->num_event <= 0) //�� ���� ����Ʈ�� ���ٸ�
	{
		pEvQ->cs_EvQ.unlock();
		return NULL; //�����
	}
	else
	{
		pLN_Ev_OldFront = pEvQ->front; //�� ����� ���� �� ����Ʈ
		pEv = pEvQ->front->pEv; //���� �� ����Ʈ�� �̺�Ʈ
		pEvQ->front = pEvQ->front->next; //���� �� ����Ʈ ���� ����Ʈ�� ���� ���� ��
		if (pEvQ->front != NULL)
			pEvQ->front->prev = NULL; //�޺κ��� ���
		pEvQ->num_event--; //�̺�Ʈ ���� ���̱�
		free(pLN_Ev_OldFront); //����Ʈ ��ü�� ��ȯ
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