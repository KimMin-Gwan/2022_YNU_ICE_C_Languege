#ifndef HANDLING_BINARY_FILE_H
#define HANDLING_BINARY_FILE_H

#include <stdio.h>
#include <ctype.h>
#define BUFFER_LEN 16 //16����
#define MAX_FILE_SIZE 1000 //16 x 18
void dumpBinaryFile(FILE* fin, FILE* fout); //�������

#endif