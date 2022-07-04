#include "BigArray_Algorithms.h"

void printBigArraySample(int* array, int size, int line_size, int num_line) //������ ���� ���� ��� (�տ��� 30�� �ڿ��� 30�� ���)
{
	int count = 1;
	if (size < 50000)  //5������ ������ ����ϴ� ���μ��� �ٲپ��� (�⺻ 2��)
	{
		num_line = size / line_size + 1;
	}
	for (int i = 0; i < num_line; i++)
	{

		for (int j = 0; j < line_size; j++, array++) //�ϳ��� ��� ���� ũ�⸸ŭ ����ϰ� \n
		{
			if (*array == 0 || *array == -1)
				break;
			printf("%8d", *array);
			count++;
		}
		printf("\n");
	}
	if (size > 50000)  //5������ ū ������� �ǵڿ��� ���� 20�� �� ���
	{
		printf("    .  .  .  .  .  . \n");

		for (int i = 0; i < num_line; i++)
		{
			for (int j = 0; j < line_size; j++, array--) //�� �ڿ��� ���� 20�� ���
			{
				printf("%8d", *(array + size - count));
			}
			printf("\n");
		}
	}
}

void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int num_line) //������ ���� ���� (�տ��� 30�� �ڿ��� 30�� ���)
{
	int count = 1;
	if (size < 50000)
	{
		num_line = size / line_size + 1;
	}
	for (int i = 0; i < num_line; i++)
	{
		for (int j = 0; j < line_size; j++, array++) //�ϳ��� ��� 29��° ���� �� 30��
		{
			if (*array == 0 || *array == -1)
				break;
			fprintf(fout, "%8d", *array);
			count++;
		}
		fprintf(fout, "\n");
	}
	if (size > 50000)
	{
		fprintf(fout, "    .  .  .  .  .  . \n");  //�� �Լ��� ��� 50000�� ���� ��µǹǷ� ��µǴ� ���� ������� �ʰ� ���κ��� ���

		for (int i = 0; i < num_line; i++)
		{
			for (int j = 0; j < line_size; j++, array--) //�� �ڿ��� ���� 30�� ���
			{
				fprintf(fout, "%8d", *(array + size - count));
			}
			fprintf(fout, "\n");
		}
	}
}

void genBigRandArray(int* array, int size, int base) //���� �Ŵ��� ���� ���� ������
{
	char* flag;
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand, bigRand_withOffset;

	flag = (char*)calloc(size, sizeof(char)); //�ߺ��˻縦 �Ҷ� ����ϴ� ���� �޸�
	while (count < size)
	{
		u_int32 = ((unsigned int)rand() << 15) | rand();  //15��Ʈ �о�� �ٽ� 15��Ʈ �ֱ�
		bigRand = u_int32 % size;  //bigRandSize���� ���� ũ��� ����
		if (flag[bigRand] == 1)  //�ߺ��˻�, ���� 1�� �ִٸ�  �ٽ� ���� ������
		{
			continue;
		}
		else
		{
			flag[bigRand] = 1;
			bigRand_withOffset = bigRand + base;
			array[count++] = bigRand_withOffset;  //array�� ���� �Ҵ�
		}
	}
	free(flag);
}

void _mergeSort(int* array, int* tmp_array, int left, int right)
{
	//tmp_array��� �ӽ� �迭�� ���� �ְ� �м�

	if (left >= right) //���� �迭�� ���Ұ� ��ĭ�� �Ǹ� ���͸� Ż��
		return;

	int i, j, k, mid = (left + right) / 2;  //�߰��� �¿� ���ؼ� ���丷

	_mergeSort(array, tmp_array, left, mid);  //���ʳ����� ���� �߰�            �ڸ���      �����ٰ�    �ٽú���
	_mergeSort(array, tmp_array, mid + 1, right);  //�߰����� ���� �����ʳ�    �����µ�     �ڸ���
	 
	for (i = mid; i >= left; i--) //i�� �߰� ���� ��ĭ�� ��
		tmp_array[i] = array[i];  //���ʺ��� ü������

	for (j = 1; j <= right - mid; j++)  //j�� 1 ���� ������ ���� ĭ��ŭ ����
		tmp_array[right - j + 1] = array[j + mid];  //������ ���� ü������

	for (i = left, j = right, k = left; k <= right; k++) //i�� ���� ,j�� ������, k�� ����
	{											
		if (tmp_array[i] < tmp_array[j])  //���� �߸� �迭�� ó���� ��������  ���κ��� �� ũ��
			array[k] = tmp_array[i++];  //ó���� �κ��� �� ������ array�� ����ְ� ����ĭ�̵�(k++)
		else //���� ���� �� ������ ���� �� ������ array�� ����ְ� ����ĭ �̵�
			array[k] = tmp_array[j--];
	}
}//�Լ� ��
	
void mergeSort(int* array, int size)
{
	int* tmp_array = (int*)calloc(size, sizeof(int));
	if (tmp_array == NULL)
	{
		printf("Error in creation of tmp_array (size = %d) in mergeSort() !!!\n");
		exit;
	}
	_mergeSort(array, tmp_array, 0, size - 1);
	free(tmp_array);
}

void selectionSort(int* array, int size)
{
	int index_min;
	int minElement;
	for (int round = 0; round < size - 1; round++) //ù��° ��ġ����(array[0])���� ���� �ϳ��ϳ� ���ذ��� ���� ü���ִ´�.
	{
		index_min = round; //���� Ž������ �������� ���� ���� ���� ��ġ
		minElement = array[round];  //���� Ž������ ������ ���� ���� ��
		for (int j = round + 1; j < size; j++) //���� Ž������ ��ġ�� �ٷ� ������ġ ���� ��ĭ��ĭ Ȯ���ϸ� Ž���Ѵ�.
		{
			if (array[j] < minElement) //���� �� ���� ���� �߰��ϸ�
			{
				index_min = j;  //���� ���� ���� ��ġ�� �ٲ��ְ�,
				minElement = array[j];  //���� ���� ���� ���� �ٲ��ش�.
			}
		}
		if (index_min != round) //���� array�� ���� Ž������ ���� ���� ���� ���� �ƴ϶��,
		{
			array[index_min] = array[round];  //���� Ž������ ����, ã�Ƴ� ���� ���� ���� �ڸ��� �ٲٰ�
			array[round] = minElement; //���� ���� ���� ���� Ž������ ���� �ִ´�
		}
	}
}

int _partition(int* array, int size, int left, int right, int pivotIndex)
{
	int pivotValue; // pivot value
	int newPI; // new pivot index
	int temp, i;
	pivotValue = array[pivotIndex];
	array[pivotIndex] = array[right];
	array[right] = pivotValue; // Move pivot element to end
	newPI = left;
	for (i = left; i <= (right - 1); i++) {
		if (array[i] <= pivotValue) {
			temp = array[i];
			array[i] = array[newPI];
			array[newPI] = temp;
			newPI = newPI + 1;
		}
	}
	// swap array[newPI] and array[right]; Move pivot to its final place
	pivotValue = array[right];
	array[right] = array[newPI];
	array[newPI] = pivotValue;
	return newPI;
}

void _quickSort(int* array, int size, int left, int right)
{
	int pI, newPI; // pivot index
	if (left >= right) {
		return;
	}
	else if (left < right) { // subarray of 0 or 1 elements already sorted
	//select a pI (pivotIndex) in the range left �� pI �� right
		pI = (left + right) / 2;
	}
	newPI = _partition(array, size, left, right, pI);
	// element at newPivotIndex (newPI) is now at its final position
	if (left < (newPI - 1)) {
		_quickSort(array, size, left, newPI - 1);
		// recursively sort elements on the left of pivotNewIndex
	}
	if ((newPI + 1) < right) {
		_quickSort(array, size, newPI + 1, right);
		// recursively sort elements on the right of pivotNewIndex
	}
}

void quickSort(int* array, int size)
{
	_quickSort(array, size, 0, size - 1);
}

void hybridQuickSelectionSort(int* bigArray, int size)
{

}

void suffleArray(int* array, int size)
{
	int i1, i2, d;
	srand((unsigned)time(NULL));

	for (int i = 0; i < size / 2; i++)
	{
		i1 = ((unsigned long)rand() << 15 | rand()) % size;
		i2 = ((unsigned long)rand() << 15 | rand()) % size;

		d = array[i1];
		array[i1] = array[i2];
		array[i2] = d;
	}
}