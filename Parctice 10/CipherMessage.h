#ifndef Cipher_Message_H
#define Cipher_Message_H
#define CIPHER_CODE 0x69
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENTH 10
#define BIT_SIZE 8
#define MAX_HEX_STR_LEN 16 
void cipherText(FILE* fp_msg, FILE* fp_tx, unsigned char cipher_code); //��ȣȭ
void deCipherText(FILE* fp_msg, FILE* fp_tx, unsigned char cipher_code); //��ȣȭ
void cipherChar(unsigned char ch, unsigned char* pCC_u, unsigned char* pCC_l); //������Ʈ�� ������Ʈ ������
unsigned int atox(char* hexStr, int num); //char�� Hex�� ������ �ٲ�
#endif