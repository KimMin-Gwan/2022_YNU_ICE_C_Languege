#include "CipherMessage.h"

void cipherText(FILE* fp_msg, FILE* fp_tx, unsigned char cipher_code)
{
	unsigned char str = {0};
	unsigned char upper_bit[1] = { 0 };
	unsigned char lower_bit[1] = { 0 };
	unsigned char CCUB[1] = { 0 };
	unsigned char CCLB[1] = { 0 };
	
	cipherChar(cipher_code, CCUB, CCLB); //비트 나눠받기

	while ((str = fgetc(fp_msg)) != EOF) //파일 받아오기
	{
		if (feof(fp_msg) != 0) //파일의 끝
			break;
		cipherChar(str, upper_bit, lower_bit); //비트 나눠받기
		*upper_bit = *upper_bit ^ *CCUB; //상위비트 암호화
		*lower_bit = *lower_bit ^ *CCLB; //하위비트 암호화
		printf("%X%X", *upper_bit, *lower_bit);
		fprintf(fp_tx, "%X%X ", *upper_bit, *lower_bit);
		if (str == 0x0A) { //CR에서 줄바꿈
			printf("\n");
			fprintf(fp_tx, "\n");
		}
		*upper_bit = { 0 }; //초기화
		*lower_bit = { 0 };
	}
	printf("\n");

}

void deCipherText(FILE* fp_tx, FILE* fp_out, unsigned char cipher_code)
{
	char str[3] = { 0 }; //입력받은 문자열
	unsigned int decipher_char = 0;
	unsigned int upper_decipher = 0; //입력받은 값의 10진수 형태
	unsigned int lower_decipher = 0;
	unsigned char CCUB[1] = { 0 };
	unsigned char CCLB[1] = { 0 };

	cipherChar(cipher_code, CCUB, CCLB); //비트 나눠받기
	while (1) //파일 받아오기
	{
		fscanf(fp_tx, "%s", str); //널문자를 기준으로 값을 받아옴
	
		if (feof(fp_tx) != 0) //파일의 끝
			break;

		if (str == "0A") {//CR에서 줄바꿈
			printf("\n");
			fprintf(fp_out, "\n");
		}
		else
		{
			upper_decipher = atox(str, 0);//10진수로 바꾸기
			lower_decipher = atox(str, 1);
			upper_decipher = upper_decipher ^ *CCUB; //상위비트 복호화
			lower_decipher = lower_decipher ^ *CCLB; //하위비트 복호화

			decipher_char = ((upper_decipher << 4) | lower_decipher); //상,하위 비트를 char에 담기
			printf("%c", decipher_char); //출력
			fprintf(fp_out, "%c", decipher_char);
		}
	}
	printf("\n\n");
}

void cipherChar(unsigned char ch, unsigned char* pCC_u, unsigned char* pCC_l)
{
	int bit_decrease = 2;
	int bit = 8;
	for (int i = BIT_SIZE - 1; i >= 0; i--) //상위비트 하위비트 나눠담기
	{
		if (i > 3) //상위 비트
		{
			*pCC_u += (((ch >> i) & 1) * bit); //상위비트 모두 더한값
			bit /= bit_decrease;
		}
		else  //하위비트 
		{
			if (i == 3)
				bit = 8;

			*pCC_l += (((ch >> i) & 1) * bit); //하위비트 모두 더한값
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
		if (hexChar == NULL) //만약 비었다면 탈출
			return 0;
		if ((hexChar >= '0') && (hexChar <= '9')) //16진수의 0~9 구간
			hexVal = hexChar - '0';
		else if ((hexChar >= 'A') && (hexChar <= 'F')) //16진수의 A~F구간
			hexVal = hexChar - 'A' + 10;
		else if ((hexChar >= 'a') && (hexChar <= 'f')) //16진수의 a~f구간
			hexVal = hexChar - 'a' + 10;
		else //16진수가 아니라면 출력
		{
			printf("Error in atox() :: given hexStr (%x) is not hex code character !!\n", hexChar);
			return 0;
		}
		hexSum = hexSum * 16 + hexVal; //10진수 값으로 계산
	//}
	return hexSum; //10진수 값 반환
}