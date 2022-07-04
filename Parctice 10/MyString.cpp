#include "MyString.h"

void selectionSortWords(char**word, int num_words)
{
	char* temp_word;
	int i, j, min;
	temp_word = (char*)calloc(MAX_WORD_LEN, sizeof(char));
	if (temp_word == NULL)
	{
		printf("Error in dynamic allocation of memory for temp_word !!\n");
		exit;
	}
	/* selection sorting of words */
	for (i = 0; i < num_words; i++)
	{
		strcpy(temp_word, word[i]);
		min = i;
		for (j = i + 1; j < num_words; j++)
		{
			if (strcmp(temp_word, word[j]) > 0)
			{
				min = j;
				strcpy(temp_word, word[j]);
			}
		}
		if (min != i)
		{ /* temp_word contains words[min] already !! */
			strcpy(word[min], word[i]);
			strcpy(word[i], temp_word);
		}
	}
	free(temp_word);
}