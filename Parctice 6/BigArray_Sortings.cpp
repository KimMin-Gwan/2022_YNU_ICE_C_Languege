#include "BigArray_Sortings.h"

void _mergeSort(int* array, int* tmp_array, int left, int right)
{
	//tmp_array��� �ӽ� �迭�� ���� �ְ� �м�

	if (left >= right) //���� �迭�� ���Ұ� ��ĭ�� �Ǹ� ���͸� Ż��
		return;

	int i, j, k, mid = (left + right) / 2;  //�߰��� �¿� ���ؼ� ���丷

	_mergeSort(array, tmp_array, left, mid);  //a���ʳ����� ���� �߰�            �ڸ���      �����ٰ�    �ٽú���
	_mergeSort(array, tmp_array, mid + 1, right);  //b�߰����� ���� �����ʳ�    �����µ�     �ڸ���

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
	array[right] = pivotValue; // �ǹ��� array�� ���� ������ ���� �ٲ۴�.
	newPI = left; //���ο� �ǹ��� ���� ���� ��
	for (i = left; i <= (right - 1); i++) //i�� ���ҵ� ���� ���� ���� ��ġ
	{
		if (array[i] <= pivotValue)  //���� Ž���ϴ� ���� ���� �ǹ������� �۰ų� ������
		{
			temp = array[i];			//Ž���ϴ� ���� ����
			array[i] = array[newPI];	//���ο� �ǹ��� ���� �ְ� 
			array[newPI] = temp;		//���ο� �ǹ� ���� Ž���ϴ� ���� ���� �־ ��ȯ�Ѵ�.
			newPI = newPI + 1;			//��ȯ�� ������ ���ο� �ǹ��� ���� �ϳ� �ø���.
		}
	}
	pivotValue = array[right];		
	array[right] = array[newPI];
	array[newPI] = pivotValue;
	return newPI;
}

void _quickSort(int* array, int size, int left, int right)
{
	int pivotValue;
	int newPI;
	int temp, i;
	int pI; // pivot index
	//int pI, newPI; // pivot index
	if (left >= right)  //���࿡ ���ʰ��� ������ ������ ũ�ų� ������ ���͸� Ż��
	{
		return;
	}
	else if (left < right) 
	{
		pI = (left + right) / 2; //�ǹ����� size�� �߰� ������ �Ѵ�. =  �迭�� �߰��� �ǹ����� ����
	}
	newPI = _partition(array, size, left, right, pI);

	if (left < (newPI - 1)) // ���� �ǹ��� left(ù��° ��ġ)�� �ƴ϶��
	{
		_quickSort(array, size, left, newPI - 1); // a �ǹ� ���� �ϳ� �ٿ���  �������� �����ϰ� �ѹ��� sort
	}
	if ((newPI + 1) < right) //���� �ǹ��� right(�� �� ��ġ)�� �ƴ϶��
	{
		_quickSort(array, size, newPI + 1, right);  // b �ǹ��� �ϳ� �÷��� ó�������� �����ϰ� �ѹ��� sort
	}
}

void quickSort(int* array, int size)
{
	_quickSort(array, size, 0, size - 1);
}

void _hybridQuickSelectionSort(int* bigArray, int size, int left, int right)
{
	int pivotValue;
	int newPI;
	int temp, i;
	int pI; // pivot index
	int section = right - left;
	if (section < QUICK_SELECTION_THRESHOLD)
	{
		right += 1;
		int index_min;
		int minElement;
		for (int round = left; round < right - 1; round++) //ù��° ��ġ����(array[0])���� ���� �ϳ��ϳ� ���ذ��� ���� ü���ִ´�.
		{
			index_min = round; //���� Ž������ �������� ���� ���� ���� ��ġ
			minElement = bigArray[round];  //���� Ž������ ������ ���� ���� ��
			for (int j = round + 1; j < right; j++) //���� Ž������ ��ġ�� �ٷ� ������ġ ���� ��ĭ��ĭ Ȯ���ϸ� Ž���Ѵ�.
			{
				if (bigArray[j] < minElement) //���� �� ���� ���� �߰��ϸ�
				{
					index_min = j;  //���� ���� ���� ��ġ�� �ٲ��ְ�,
					minElement = bigArray[j];  //���� ���� ���� ���� �ٲ��ش�.
				}
			}
			if (index_min != round) //���� array�� ���� Ž������ ���� ���� ���� ���� �ƴ϶��,
			{
				bigArray[index_min] = bigArray[round];  //���� Ž������ ����, ã�Ƴ� ���� ���� ���� �ڸ��� �ٲٰ�
				bigArray[round] = minElement; //���� ���� ���� ���� Ž������ ���� �ִ´�
			}
		}
		//Hy_selectionSort(bigArray, section, left, right+1);
		return;
	}
	if (left >= right)  //���࿡ ���ʰ��� ������ ������ ũ�ų� ������ ���͸� Ż��
	{
		return;
	}
	else if (left < right)
	{
		pI = (left + right) / 2; //�ǹ����� size�� �߰� ������ �Ѵ�. =  �迭�� �߰��� �ǹ����� ����
	}
	pivotValue = bigArray[pI];
	bigArray[pI] = bigArray[right];
	bigArray[right] = pivotValue; // �ǹ��� array�� ���� ������ ���� �ٲ۴�.
	newPI = left; //���ο� �ǹ��� ���� ���� ��
	for (i = left; i <= (right - 1); i++) //i�� ���ҵ� ���� ���� ���� ��ġ
	{
		if (bigArray[i] <= pivotValue)  //���� Ž���ϴ� ���� ���� �ǹ������� �۰ų� ������
		{
			temp = bigArray[i];			//Ž���ϴ� ���� ����
			bigArray[i] = bigArray[newPI];	//���ο� �ǹ��� ���� �ְ� 
			bigArray[newPI] = temp;		//���ο� �ǹ� ���� Ž���ϴ� ���� ���� �־ ��ȯ�Ѵ�.
			newPI = newPI + 1;			//��ȯ�� ������ ���ο� �ǹ��� ���� �ϳ� �ø���.
		}
	}
	pivotValue = bigArray[right];
	bigArray[right] = bigArray[newPI];
	bigArray[newPI] = pivotValue;

	if (left < (newPI - 1)) // ���� �ǹ��� left(ù��° ��ġ)�� �ƴ϶��
	{
		_hybridQuickSelectionSort(bigArray, size, left, newPI - 1); // a �ǹ� ���� �ϳ� �ٿ���  �������� �����ϰ� �ѹ��� sort
	}
	if ((newPI + 1) < right) //���� �ǹ��� right(�� �� ��ġ)�� �ƴ϶��
	{
		_hybridQuickSelectionSort(bigArray, size, newPI + 1, right);  // b �ǹ��� �ϳ� �÷��� ó�������� �����ϰ� �ѹ��� sort
	}

}

void hybridQuickSelectionSort(int* bigArray, int size)
{
	_hybridQuickSelectionSort(bigArray, size, 0, size - 1);
}

//void Hy_selectionSort(int* array, int size, int left, int right)
//{
//	int index_min;
//	int minElement;
//	for (int round = left; round < right - 1; round++) //ù��° ��ġ����(array[0])���� ���� �ϳ��ϳ� ���ذ��� ���� ü���ִ´�.
//	{
//		index_min = round; //���� Ž������ �������� ���� ���� ���� ��ġ
//		minElement = array[round];  //���� Ž������ ������ ���� ���� ��
//		for (int j = round + 1; j < right; j++) //���� Ž������ ��ġ�� �ٷ� ������ġ ���� ��ĭ��ĭ Ȯ���ϸ� Ž���Ѵ�.
//		{
//			if (array[j] < minElement) //���� �� ���� ���� �߰��ϸ�
//			{
//				index_min = j;  //���� ���� ���� ��ġ�� �ٲ��ְ�,
//				minElement = array[j];  //���� ���� ���� ���� �ٲ��ش�.
//			}
//		}
//		if (index_min != round) //���� array�� ���� Ž������ ���� ���� ���� ���� �ƴ϶��,
//		{
//			array[index_min] = array[round];  //���� Ž������ ����, ã�Ƴ� ���� ���� ���� �ڸ��� �ٲٰ�
//			array[round] = minElement; //���� ���� ���� ���� Ž������ ���� �ִ´�
//		}
//	}
//}