#include "HandlingBinaryFile.h"


void dumpBinaryFile(FILE* fin, FILE* fout)
{
	int nbytes;
	int tempnbytes = 0;
	unsigned char buffer[BUFFER_LEN] = { '\0' };
	for (int addr = 0; addr < MAX_FILE_SIZE; addr += BUFFER_LEN)
	{
		nbytes = fread(buffer, sizeof(unsigned char), BUFFER_LEN, fin); //�ٴ� ����
		if (addr == 0)
			tempnbytes = nbytes;
		if (nbytes <= 0)
			break;
		/*ȭ�鿡 ���*/
		printf("%08X: ", addr);
		for (int i = 0; i < nbytes; i++) //�ѱ��ھ� 16������ ���
		{
			if (i == (BUFFER_LEN / 2))
				printf(" ");
			printf("%02X ", buffer[i]); 
		}
		printf(" ");
		if (nbytes < tempnbytes) //��ĭ ü���
		{
			for (int i = 0; i < tempnbytes - nbytes; i++)
				printf("   ");
			printf(" ");
		}

		for (int i = 0; i < nbytes; i++) //������ char������ ���
		{
			if (isprint(buffer[i]))
				printf("%c", buffer[i]);
			else
				printf(".");
		}
		printf("\n");
		/*���Ͽ� ���*/
		fprintf(fout, "%08X: ", addr);
		for (int i = 0; i < nbytes; i++) //�ѱ��ھ� 16������ ���
		{
			if (i == (BUFFER_LEN / 2))
				fprintf(fout, " ");
			fprintf(fout, "%02X ", buffer[i]);
		}
		fprintf(fout, " ");
		for (int i = 0; i < nbytes; i++) //������ char������ ���
		{
			if (isprint(buffer[i]))
				fprintf(fout, "%c", buffer[i]);
			else
				fprintf(fout, ".");
		}
		fprintf(fout, "\n");
	

	}
}