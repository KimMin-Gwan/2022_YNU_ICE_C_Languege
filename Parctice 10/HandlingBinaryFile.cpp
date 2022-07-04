#include "HandlingBinaryFile.h"


void dumpBinaryFile(FILE* fin, FILE* fout)
{
	int nbytes;
	int tempnbytes = 0;
	unsigned char buffer[BUFFER_LEN] = { '\0' };
	for (int addr = 0; addr < MAX_FILE_SIZE; addr += BUFFER_LEN)
	{
		nbytes = fread(buffer, sizeof(unsigned char), BUFFER_LEN, fin); //줄당 길이
		if (addr == 0)
			tempnbytes = nbytes;
		if (nbytes <= 0)
			break;
		/*화면에 출력*/
		printf("%08X: ", addr);
		for (int i = 0; i < nbytes; i++) //한글자씩 16진수로 출력
		{
			if (i == (BUFFER_LEN / 2))
				printf(" ");
			printf("%02X ", buffer[i]); 
		}
		printf(" ");
		if (nbytes < tempnbytes) //빈칸 체우기
		{
			for (int i = 0; i < tempnbytes - nbytes; i++)
				printf("   ");
			printf(" ");
		}

		for (int i = 0; i < nbytes; i++) //원본을 char형으로 출력
		{
			if (isprint(buffer[i]))
				printf("%c", buffer[i]);
			else
				printf(".");
		}
		printf("\n");
		/*파일에 출력*/
		fprintf(fout, "%08X: ", addr);
		for (int i = 0; i < nbytes; i++) //한글자씩 16진수로 출력
		{
			if (i == (BUFFER_LEN / 2))
				fprintf(fout, " ");
			fprintf(fout, "%02X ", buffer[i]);
		}
		fprintf(fout, " ");
		for (int i = 0; i < nbytes; i++) //원본을 char형으로 출력
		{
			if (isprint(buffer[i]))
				fprintf(fout, "%c", buffer[i]);
			else
				fprintf(fout, ".");
		}
		fprintf(fout, "\n");
	

	}
}