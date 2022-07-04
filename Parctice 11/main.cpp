/* main() for Priority-Queue for Events */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Event.h"
#include "CirQ_Event.h"
#include "PriQ_Event.h"
#define EVENT_GENERATOR 0
#define TOTAL_NUM_EVENTS 127
#define MAX_ROUND 100
#define INIT_PriQ_SIZE 1
void test_FIFO_CirQ_Event(FILE * fout, int max_events_per_round);
void test_PriQ_Event(FILE* fout, int max_events_per_round);

void main()
{
	FILE* fout; //파일 출력 포인터
	int menu;
	int max_events_per_round;
	fout = fopen("output.txt", "w"); //파일 출력
	if (fout == NULL)
	{
		printf("Error in creation of output.txt file !!\n");
		exit(-1);
	}
	srand(time(0));
	while (1)
	{
		printf("\nAvailable Menu : \n");
		printf(" 1. Test FIFO/CirQ Event.\n"); //선입선출 알고리즘 
		printf(" 2. Test PriQ Event.\n"); //우선 순위 큐의 처리 과정 
		printf("Input menu (0 to quit) : ");
		scanf("%d", &menu);
		if (menu == 0)
			break;
		printf("Input num_events per round :");
		scanf("%d", &max_events_per_round);
		switch (menu)
		{
		case 1:
			test_FIFO_CirQ_Event(fout, max_events_per_round);
			break;
		case 2:
			test_PriQ_Event(fout, max_events_per_round);
			break;
		default:
			break;
		}
	}
	fclose(fout);
}

void test_FIFO_CirQ_Event(FILE* fout, int max_events_per_round) //선입선출 이벤트
{
	CirQ_Event* pCirQ_Event; //환형 큐이벤트 포인터
	Event ev, * pEv = NULL; //이벤트, 이벤트 포인터
	Event processed_events[TOTAL_NUM_EVENTS]; //이벤트 처리 배열
	int total_processed_events = 0; //처리한 이벤트의 총 갯수
	int total_generated_events = 0; //생성한 이벤트의 총 갯수
	int num_events = 0; //총 이벤트 갯수
	int num_generated_round = 0; //이벤트를 생성했던 횟수
	int num_processed_round = 0; //이베트를 처리했던 횟수
	fprintf(fout, "Testing Event Handling with FIFO Circular Queue\n");
	pCirQ_Event = (CirQ_Event*)calloc(1, sizeof(CirQ_Event)); //환형 큐의 갯수만큼 동적 배열 생성
	printf("Initializing FIFO_CirQ of capacity (%d)\n", max_events_per_round);	//이번 이벤트 생성에서 초기화 시킨 환형큐
	fprintf(fout, "Initializing FIFO_CirQ of capacity (%d)\n", max_events_per_round);
	pCirQ_Event = initCirQ(pCirQ_Event, max_events_per_round);
	//fprintQueue(fout, pCirQ_Event);
	//fprintf(fout, "\nEnqueuing data into event circular queue: \n");
	for (int round = 0; round < MAX_ROUND; round++) //이벤트 생성 시작
	{
		fprintf(fout, "start of Round(%2d) ****\n", round); 
		if (total_generated_events < TOTAL_NUM_EVENTS) //정상적인 이벤트 갯수에서
		{
			num_events = max_events_per_round; // 이벤트의 갯수는 입력받은 라운드당 최대 이벤트의 갯수
			if ((total_generated_events + num_events) > TOTAL_NUM_EVENTS) //남은 라운드가 생성할 이벤트 보다 작으면
				num_events = TOTAL_NUM_EVENTS - total_generated_events;  //남은 라운드는 전체에서 남은거 전부로 실행
			fprintf(fout, "generate and enque %2d events\n", num_events);
			num_generated_round = 0; //초기화
			for (int i = 0; i < num_events; i++)
			{
				if (isCirQFull(pCirQ_Event))//환형 큐에 자리가 남아있는지 확인
				{
					fprintf(fout, " !!! CirQ_Event is full --> skip generation and enqueueing of event. \n");
						break;
				}
				pEv = genEvent(pEv, EVENT_GENERATOR, total_generated_events, TOTAL_NUM_EVENTS - total_generated_events - 1);//pEv로 이벤트 생성(임시)
				fprintf(fout, ">>> Enqueue event = "); //큐에 저장된 이벤트 출력
				fprintEvent(fout, pEv);
				fprintf(fout, "\n");
				enCirQ(fout, pCirQ_Event, *pEv); //생성된 이벤트를 환형큐에 할당
				fprintCirQ(fout, pCirQ_Event);
				free(pEv); //pEv 포인터 비우기
				total_generated_events++; //이벤트 생성했으니 증감
				num_generated_round++; //생성 라운드가 끝났으니 증감
			} // end for
		} // end if
		 //fprintf(fout, "\nDequeuing data from event circular queue: \n");
		num_events = max_events_per_round; //생성된 이벤트 갯수와 맞추기
		if ((total_processed_events + num_events) > TOTAL_NUM_EVENTS) 
			num_events = TOTAL_NUM_EVENTS - total_processed_events; 
		fprintf(fout, "dequeue %2d events\n", num_events);
		num_processed_round = 0;
		for (int i = 0; i < num_events; i++) //이벤트 처리 시작
		{
			if (isCirQEmpty(pCirQ_Event)) //처리할 환형큐가 남지 않았다면 브레이크
				break;
			pEv = deCirQ(fout, pCirQ_Event); //이벤트 처리
			if (pEv != NULL)
			{
				fprintf(fout, "<<< Dequed event = ");
				fprintEvent(fout, pEv);
				fprintf(fout, "\n");
				processed_events[total_processed_events] = *pEv; //처리가 끝난 이벤트 저장
				total_processed_events++; //처리했으니 증감
				num_processed_round++;//처리 라운드가 끝났으니 증감
			}
			fprintCirQ(fout, pCirQ_Event);
		} // end for
		/* Monitoring simulation status */
		fprintf(fout, "Round(%2d): generated_in_this_round(%3d), total_generated_events(%3d), processed_in_this_round(% 3d), total_processed_events(% 3d), \
events_in_queue(% 3d)\n\n", round, num_generated_round, total_generated_events, num_processed_round, total_processed_events, pCirQ_Event->num_elements);
		printf("Round(%2d): generated_in_this_round(%3d), total_generated(%3d), processed_in_this_round(% 3d), total_processed_events(% 3d), \
events_in_queue(% 3d)\n", round, num_generated_round, total_generated_events, num_processed_round, total_processed_events, pCirQ_Event->num_elements);
		if (total_processed_events >= TOTAL_NUM_EVENTS)
			break;
	} // end for()
	printf("Processed Events :\n");
	for (int i = 0; i < TOTAL_NUM_EVENTS; i++) //처리된 순서대로 배열에 저장된 내용 출력
	{
		printf("Ev(id:%3d, pri:%3d), ", processed_events[i].event_no, processed_events[i].event_pri);
		if ((i + 1) % 5 == 0)
			printf("\n");
	}
	printf("\n");
	delCirQ(pCirQ_Event); //큐 제거(반납)
}

void test_PriQ_Event(FILE* fout, int max_events_per_round)
{
	PriQ_Event* pPriQ_Ev;
	Event* pEv = NULL;
	Event processed_events[TOTAL_NUM_EVENTS]; //완료한 이벤트 저장
	int data; 
	int total_processed_events = 0;
	int total_generated_events = 0;
	int num_events = 0;
	int num_generated_round = 0;
	int num_processed_round = 0;
	fprintf(fout, "Testing Event Handling with Priority Queue\n");
	pPriQ_Ev = (PriQ_Event*)malloc(sizeof(PriQ_Event));// PriQ구조체 크기 할당
	if (pPriQ_Ev == NULL) //할당 못받으면 종료
	{
		printf("Error in malloc() for PriorityQueue_Event !\n");
		fclose(fout);
		exit(-1);
	}
	printf("Initializing PriorityQueue_Event of capacity (%d)\n", INIT_PriQ_SIZE); 
	initPriQ_Ev(pPriQ_Ev, "PriorityQueue_Event", INIT_PriQ_SIZE); //이벤트 초기값 생성(각 1의 크기를 가질것)
	for (int round = 0; round < MAX_ROUND; round++)
	{
		fprintf(fout, "\n*** Start of round(%2d)...\n", round);
		num_generated_round = 0;
		if (total_generated_events < TOTAL_NUM_EVENTS)//이벤트 생성 시작
		{
			num_events = max_events_per_round;// 이벤트의 갯수는 입력받은 라운드당 최대 이벤트의 갯수
			if ((total_generated_events + num_events) > TOTAL_NUM_EVENTS) //남은 라운드가 생성할 이벤트 보다 작으면
				num_events = TOTAL_NUM_EVENTS - total_generated_events; //남은 라운드는 전체에서 남은거 전부로 실행
			fprintf(fout, ">>> enque %2d events\n", num_events);
			for (int i = 0; i < num_events; i++)
			{
				pEv = genEvent(pEv, 0, total_generated_events, TOTAL_NUM_EVENTS - total_generated_events - 1);//이벤트 생성
				if (pEv == NULL)
				{ //만약 넣을 자리가 NULL값이면 포기하고 종료
					printf("Error in generation of event !!\n");
					fclose(fout);
					exit(-1);
				}
				fprintf(fout, " *** enqued event : ");
				fprintEvent(fout, pEv);
				enPriQ_Ev(pPriQ_Ev, pEv); //생성한 이벤트 할당
				total_generated_events++; //생성된 이벤트 갯수 증감
				num_generated_round++; //라운드가 끝났으니 라운드 횟수 증감
				fprintPriQ_Ev(fout, pPriQ_Ev);
			}
		}
		//지우기 시작
		//fprintf(fout, "\n======================================================\n");
		//fprintf(fout, "\nRemoving min data from Priority Queue . . . \n");
		num_events = max_events_per_round;  //생성된 이벤트 갯수와 맞추기
		if ((total_processed_events + num_events) > TOTAL_NUM_EVENTS)
			num_events = TOTAL_NUM_EVENTS - total_processed_events;
		fprintf(fout, "<<< dequeue %2d events\n", num_events);
		num_processed_round = 0; //작동완료한 프로세스 갯수 초기화
		for (int i = 0; i < num_events; i++)
		{
			pEv = removeMinPriQ_Event(pPriQ_Ev); //가장 우선순위로 처리되야하는 이벤트 제거
			if (pEv == NULL) //만약 이벤트가 더이상 없다면 브레이크
			{
				fprintf(fout, " PriQ is empty\n");
				break;
			}
			fprintf(fout, " *** dequeued event : ");
			fprintEvent(fout, pEv);
			fprintPriQ_Ev(fout, pPriQ_Ev);
			processed_events[total_processed_events] = *pEv; //완료한 프로세스 저장
			total_processed_events++; //완료한 이벤트 횟수 증감
			num_processed_round++; //프로세스 라운드가 끝났으니 증감
		}
		/* Monitoring simulation status */
		fprintf(fout, "Round(%2d): generated_in_this_round(%3d), total_generated_events(%3d), processed_in_this_round(% 3d), total_processed_events(% 3d), events_in_queue(% 3d)\n\n",
			round, num_generated_round, total_generated_events, num_processed_round, total_processed_events, pPriQ_Ev->priQ_size);
		printf("Round(%2d): generated_in_this_round(%3d), total_generated(%3d), processed_in_this_round(% 3d), total_processed_events(% 3d), events_in_queue(% 3d)\n",
			round, num_generated_round, total_generated_events, num_processed_round, total_processed_events, pPriQ_Ev->priQ_size);
		fflush(fout); 
		if (total_processed_events >= TOTAL_NUM_EVENTS)
			break;
	}
	printf("Processed Events :\n");
	for (int i = 0; i < TOTAL_NUM_EVENTS; i++) //처리된 순서대로 배열에 저장된 내용 출력
	{
		printf("Ev(id:%3d, pri:%3d), ", processed_events[i].event_no, processed_events[i].event_pri); 
		if ((i + 1) % 5 == 0)
			printf("\n");
	}
	printf("\n");
	deletePriQ_Ev(pPriQ_Ev); //큐 제거(밥납)
	fprintf(fout, "\n");
}
