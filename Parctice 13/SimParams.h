/**
*���ϸ� : "���α׷��� ���_21912229_��ΰ�_�ǽ�_13"
*���α׷��� ���� �� �⺻ ���:
*      -�� ���α׷��� ���� �����带 �̿��Ͽ� ���� ���� ����Ʈ�� �̺�Ʈ�� 
*		�����ϰų�, ����ϰ�, �� �����带 ����͸� �ϴ� ���α׷��̴�.
*���α׷� �ۼ��� : ��ΰ�(2022�� 06�� 02��)
*���� Update : Version 1.0, 2022�� 06�� 02��(��ΰ�)
*============================================================================
*���α׷� ����/���� �̷�
*============================================================================
*���α׷� ����/�����۾���   ����   ����/���ϳ���
*============================================================================
*/


#ifndef SIMULATION_PARAMETERS_H
#define SIMULATION_PARAMETERS_H
#define NUM_EVENT_GENERATORS 3 //�������� ��
#define NUM_EVENTS_PER_GEN 20 //������� ���� �̺�Ʈ ��
#define NUM_EVENT_HANDLERS 2 //������ ��
#define TOTAL_NUM_EVENTS (NUM_EVENTS_PER_GEN * NUM_EVENT_GENERATORS)
#define PLUS_INF INT_MAX
#define MAX_ROUND 1000 //�ִ� ����
#define NUM_PRIORITY 10
#define PRIORITY_THRESHOLD 3 // 0 ~ 2: ���� �켱����  3 ~ 9: ���� �켱����
#define EVENT_PER_LINE 5
#endif