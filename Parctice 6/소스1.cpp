#include "BigArray_Algorithms.h"

void printBigArraySample(int* array, int size, int line_size, int num_line) //랜덤한 숫자 셈플 출력 (앞에서 30개 뒤에서 30개 출력)
{
	int count = 1;
	if (size < 50000)  //5만보다 작으면 출력하는 라인수를 바꾸어줌 (기본 2줄)
	{
		num_line = size / line_size + 1;
	}
	for (int i = 0; i < num_line; i++)
	{

		for (int j = 0; j < line_size; j++, array++) //하나씩 출력 라인 크기만큼 출력하고 \n
		{
			if (*array == 0 || *array == -1)
				break;
			printf("%8d", *array);
			count++;
		}
		printf("\n");
	}
	if (size > 50000)  //5만보다 큰 사이즈면 맨뒤에서 부터 20개 더 출력
	{
		printf("    .  .  .  .  .  . \n");

		for (int i = 0; i < num_line; i++)
		{
			for (int j = 0; j < line_size; j++, array--) //맨 뒤에서 부터 20개 출력
			{
				printf("%8d", *(array + size - count));
			}
			printf("\n");
		}
	}
}

void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int num_line) //랜덤한 숫자 셈플 (앞에서 30개 뒤에서 30개 출력)
{
	int count = 1;
	if (size < 50000)
	{
		num_line = size / line_size + 1;
	}
	for (int i = 0; i < num_line; i++)
	{
		for (int j = 0; j < line_size; j++, array++) //하나씩 출력 29번째 까지 총 30개
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
		fprintf(fout, "    .  .  .  .  .  . \n");  //이 함수는 적어도 50000개 부터 출력되므로 출력되는 량을 고려하지 않고 끝부분을 출력

		for (int i = 0; i < num_line; i++)
		{
			for (int j = 0; j < line_size; j++, array--) //맨 뒤에서 부터 30개 출력
			{
				fprintf(fout, "%8d", *(array + size - count));
			}
			fprintf(fout, "\n");
		}
	}
}

void genBigRandArray(int* array, int size, int base) //아주 거대한 랜덤 숫자 생성기
{
	char* flag;
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand, bigRand_withOffset;

	flag = (char*)calloc(size, sizeof(char)); //중복검사를 할때 사용하는 동적 메모리
	while (count < size)
	{
		u_int32 = ((unsigned int)rand() << 15) | rand();  //15비트 밀어내고 다시 15비트 넣기
		bigRand = u_int32 % size;  //bigRandSize보다 작은 크기로 만듬
		if (flag[bigRand] == 1)  //중복검사, 만약 1이 있다면  다시 값을 넣을것
		{
			continue;
		}
		else
		{
			flag[bigRand] = 1;
			bigRand_withOffset = bigRand + base;
			array[count++] = bigRand_withOffset;  //array에 값을 할당
		}
	}
	free(flag);
}

void _mergeSort(int* array, int* tmp_array, int left, int right)
{
	//tmp_array라는 임시 배열에 값을 넣고 분석

	if (left >= right) //만약 배열의 원소가 한칸이 되면 제귀를 탈출
		return;

	int i, j, k, mid = (left + right) / 2;  //중간은 좌우 더해서 반토막

	_mergeSort(array, tmp_array, left, mid);  //왼쪽끝에서 부터 중간            자르고      붙히다가    다시붙힘
	_mergeSort(array, tmp_array, mid + 1, right);  //중간에서 부터 오른쪽끝    붙히는데     자르고
	 
	for (i = mid; i >= left; i--) //i는 중간 부터 한칸씩 줌
		tmp_array[i] = array[i];  //왼쪽부터 체워넣음

	for (j = 1; j <= right - mid; j++)  //j는 1 부터 오른쪽 남은 칸만큼 증가
		tmp_array[right - j + 1] = array[j + mid];  //오른쪽 부터 체워넣음

	for (i = left, j = right, k = left; k <= right; k++) //i는 왼쪽 ,j는 오른쪽, k는 왼쪽
	{											
		if (tmp_array[i] < tmp_array[j])  //만약 잘린 배열의 처음과 비교했을때  끝부분이 더 크면
			array[k] = tmp_array[i++];  //처음이 부분이 젤 작으니 array에 집어넣고 다음칸이동(k++)
		else //만약 끝이 더 작으면 끝이 젤 작으니 array에 집어넣고 다음칸 이동
			array[k] = tmp_array[j--];
	}
}//함수 끝
	
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
	for (int round = 0; round < size - 1; round++) //첫번째 위치부터(array[0])에서 부터 하나하나 비교해가며 값을 체워넣는다.
	{
		index_min = round; //현재 탐색중인 구간에서 가장 작은 곳의 위치
		minElement = array[round];  //현재 탐색중인 구간의 가장 작은 값
		for (int j = round + 1; j < size; j++) //현재 탐색중인 위치의 바로 다음위치 부터 한칸한칸 확인하며 탐색한다.
		{
			if (array[j] < minElement) //만약 더 작은 값을 발견하면
			{
				index_min = j;  //가장 작은 곳의 위치를 바꿔주고,
				minElement = array[j];  //가장 작은 곳의 값을 바꿔준다.
			}
		}
		if (index_min != round) //만약 array의 현재 탐색중인 값이 가장 작은 값이 아니라면,
		{
			array[index_min] = array[round];  //현재 탐색중인 값과, 찾아낸 가장 작은 값의 자리를 바꾸고
			array[round] = minElement; //가장 작은 값을 현재 탐색중인 곳에 넣는다
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
	//select a pI (pivotIndex) in the range left ≤ pI ≤ right
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