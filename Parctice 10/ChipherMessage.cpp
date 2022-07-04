#include "CipherMessage.h"

void cipherText(FILE* fp_msg, FILE* fp_tx, unsigned char cipher_code)
{
	unsigned char str = {0};
	unsigned char upper_bit[1] = { 0 };
	unsigned char lower_bit[1] = { 0 };
	unsigned char CCUB[1] = { 0 };
	unsigned char CCLB[1] = { 0 };
	
	cipherChar(cipher_code, CCUB, CCLB); //��Ʈ �����ޱ�

	while ((str = fgetc(fp_msg)) != EOF) //���� �޾ƿ���
	{
		if (feof(fp_msg) != 0) //������ ��
			break;
		cipherChar(str, upper_bit, lower_bit); //��Ʈ �����ޱ�
		*upper_bit = *upper_bit ^ *CCUB; //������Ʈ ��ȣȭ
		*lower_bit = *lower_bit ^ *CCLB; //������Ʈ ��ȣȭ
		printf("%X%X", *upper_bit, *lower_bit);
		fprintf(fp_tx, "%X%X ", *upper_bit, *lower_bit);
		if (str == 0x0A) { //CR���� �ٹٲ�
			printf("\n");
			fprintf(fp_tx, "\n");
		}
		*upper_bit = { 0 }; //�ʱ�ȭ
		*lower_bit = { 0 };
	}
	printf("\n");

}

void deCipherText(FILE* fp_tx, FILE* fp_out, unsigned char cipher_code)
{
	char str[3] = { 0 }; //�Է¹��� ���ڿ�
	unsigned int decipher_char = 0;
	unsigned int upper_decipher = 0; //�Է¹��� ���� 10���� ����
	unsigned int lower_decipher = 0;
	unsigned char CCUB[1] = { 0 };
	unsigned char CCLB[1] = { 0 };

	cipherChar(cipher_code, CCUB, CCLB); //��Ʈ �����ޱ�
	while (1) //���� �޾ƿ���
	{
		fscanf(fp_tx, "%s", str); //�ι��ڸ� �������� ���� �޾ƿ�
	
		if (feof(fp_tx) != 0) //������ ��
			break;

		if (str == "0A") {//CR���� �ٹٲ�
			printf("\n");
			fprintf(fp_out, "\n");
		}
		else
		{
			upper_decipher = atox(str, 0);//10������ �ٲٱ�
			lower_decipher = atox(str, 1);
			upper_decipher = upper_decipher ^ *CCUB; //������Ʈ ��ȣȭ
			lower_decipher = lower_decipher ^ *CCLB; //������Ʈ ��ȣȭ

			decipher_char = ((upper_decipher << 4) | lower_decipher); //��,���� ��Ʈ�� char�� ���
			printf("%c", decipher_char); //���
			fprintf(fp_out, "%c", decipher_char);
		}
	}
	printf("\n\n");
}

void cipherChar(unsigned char ch, unsigned char* pCC_u, unsigned char* pCC_l)
{
	int bit_decrease = 2;
	int bit = 8;
	for (int i = BIT_SIZE - 1; i >= 0; i--) //������Ʈ ������Ʈ �������
	{
		if (i > 3) //���� ��Ʈ
		{
			*pCC_u += (((ch >> i) & 1) * bit); //������Ʈ ��� ���Ѱ�
			bit /= bit_decrease;
		}
		else  //������Ʈ 
		{
			if (i == 3)
				bit = 8;

			*pCC_l += (((ch >> i) & 1) * bit); //������Ʈ ��� ���Ѱ�
			bit /= bit_decrease;
		}
	}
}

unsigned int atox(char* hexStr, int num)
{
	unsigned char uc, hexChar;
	unsigned int hexVal = 0, hexSum = 0;
	//for (int i = 0; i < MAX_HEX_STR_LEN; i++)
	//{
		hexChar = hexStr[num];
		if (hexChar == NULL) //���� ����ٸ� Ż��
			return 0;
		if ((hexChar >= '0') && (hexChar <= '9')) //16������ 0~9 ����
			hexVal = hexChar - '0';
		else if ((hexChar >= 'A') && (hexChar <= 'F')) //16������ A~F����
			hexVal = hexChar - 'A' + 10;
		else if ((hexChar >= 'a') && (hexChar <= 'f')) //16������ a~f����
			hexVal = hexChar - 'a' + 10;
		else //16������ �ƴ϶�� ���
		{
			printf("Error in atox() :: given hexStr (%x) is not hex code character !!\n", hexChar);
			return 0;
		}
		hexSum = hexSum * 16 + hexVal; //10���� ������ ���
	//}
	return hexSum; //10���� �� ��ȯ
}