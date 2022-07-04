#include "BigArray_Sortings.h"

void _mergeSort(int* array, int* tmp_array, int left, int right)
{
	//tmp_array라는 임시 배열에 값을 넣고 분석

	if (left >= right) //만약 배열의 원소가 한칸이 되면 제귀를 탈출
		return;

	int i, j, k, mid = (left + right) / 2;  //중간은 좌우 더해서 반토막

	_mergeSort(array, tmp_array, left, mid);  //a왼쪽끝에서 부터 중간            자르고      붙히다가    다시붙힘
	_mergeSort(array, tmp_array, mid + 1, right);  //b중간에서 부터 오른쪽끝    붙히는데     자르고

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
	array[right] = pivotValue; // 피벗을 array의 가장 오른쪽 값과 바꾼다.
	newPI = left; //새로운 피벗은 가장 왼쪽 값
	for (i = left; i <= (right - 1); i++) //i는 분할된 곳의 가장 왼쪽 위치
	{
		if (array[i] <= pivotValue)  //만약 탐색하는 곳의 값이 피벗값보다 작거나 같으면
		{
			temp = array[i];			//탐색하는 곳의 값에
			array[i] = array[newPI];	//새로운 피벗의 값을 넣고 
			array[newPI] = temp;		//새로운 피벗 값에 탐색하는 곳의 값을 넣어서 교환한다.
			newPI = newPI + 1;			//교환이 끝나면 새로운 피벗의 값을 하나 늘린다.
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
	if (left >= right)  //만약에 왼쪽값이 오른쪽 값보다 크거나 같으면 제귀를 탈출
	{
		return;
	}
	else if (left < right) 
	{
		pI = (left + right) / 2; //피벗값은 size의 중간 값으로 한다. =  배열의 중간을 피벗으로 설정
	}
	newPI = _partition(array, size, left, right, pI);

	if (left < (newPI - 1)) // 만약 피벗이 left(첫번째 위치)가 아니라면
	{
		_quickSort(array, size, left, newPI - 1); // a 피벗 값을 하나 줄여서  끝값으로 설정하고 한번더 sort
	}
	if ((newPI + 1) < right) //만약 피벗이 right(젤 끝 위치)가 아니라면
	{
		_quickSort(array, size, newPI + 1, right);  // b 피벗을 하나 올려서 처음값으로 설정하고 한번더 sort
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
		for (int round = left; round < right - 1; round++) //첫번째 위치부터(array[0])에서 부터 하나하나 비교해가며 값을 체워넣는다.
		{
			index_min = round; //현재 탐색중인 구간에서 가장 작은 곳의 위치
			minElement = bigArray[round];  //현재 탐색중인 구간의 가장 작은 값
			for (int j = round + 1; j < right; j++) //현재 탐색중인 위치의 바로 다음위치 부터 한칸한칸 확인하며 탐색한다.
			{
				if (bigArray[j] < minElement) //만약 더 작은 값을 발견하면
				{
					index_min = j;  //가장 작은 곳의 위치를 바꿔주고,
					minElement = bigArray[j];  //가장 작은 곳의 값을 바꿔준다.
				}
			}
			if (index_min != round) //만약 array의 현재 탐색중인 값이 가장 작은 값이 아니라면,
			{
				bigArray[index_min] = bigArray[round];  //현재 탐색중인 값과, 찾아낸 가장 작은 값의 자리를 바꾸고
				bigArray[round] = minElement; //가장 작은 값을 현재 탐색중인 곳에 넣는다
			}
		}
		//Hy_selectionSort(bigArray, section, left, right+1);
		return;
	}
	if (left >= right)  //만약에 왼쪽값이 오른쪽 값보다 크거나 같으면 제귀를 탈출
	{
		return;
	}
	else if (left < right)
	{
		pI = (left + right) / 2; //피벗값은 size의 중간 값으로 한다. =  배열의 중간을 피벗으로 설정
	}
	pivotValue = bigArray[pI];
	bigArray[pI] = bigArray[right];
	bigArray[right] = pivotValue; // 피벗을 array의 가장 오른쪽 값과 바꾼다.
	newPI = left; //새로운 피벗은 가장 왼쪽 값
	for (i = left; i <= (right - 1); i++) //i는 분할된 곳의 가장 왼쪽 위치
	{
		if (bigArray[i] <= pivotValue)  //만약 탐색하는 곳의 값이 피벗값보다 작거나 같으면
		{
			temp = bigArray[i];			//탐색하는 곳의 값에
			bigArray[i] = bigArray[newPI];	//새로운 피벗의 값을 넣고 
			bigArray[newPI] = temp;		//새로운 피벗 값에 탐색하는 곳의 값을 넣어서 교환한다.
			newPI = newPI + 1;			//교환이 끝나면 새로운 피벗의 값을 하나 늘린다.
		}
	}
	pivotValue = bigArray[right];
	bigArray[right] = bigArray[newPI];
	bigArray[newPI] = pivotValue;

	if (left < (newPI - 1)) // 만약 피벗이 left(첫번째 위치)가 아니라면
	{
		_hybridQuickSelectionSort(bigArray, size, left, newPI - 1); // a 피벗 값을 하나 줄여서  끝값으로 설정하고 한번더 sort
	}
	if ((newPI + 1) < right) //만약 피벗이 right(젤 끝 위치)가 아니라면
	{
		_hybridQuickSelectionSort(bigArray, size, newPI + 1, right);  // b 피벗을 하나 올려서 처음값으로 설정하고 한번더 sort
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
//	for (int round = left; round < right - 1; round++) //첫번째 위치부터(array[0])에서 부터 하나하나 비교해가며 값을 체워넣는다.
//	{
//		index_min = round; //현재 탐색중인 구간에서 가장 작은 곳의 위치
//		minElement = array[round];  //현재 탐색중인 구간의 가장 작은 값
//		for (int j = round + 1; j < right; j++) //현재 탐색중인 위치의 바로 다음위치 부터 한칸한칸 확인하며 탐색한다.
//		{
//			if (array[j] < minElement) //만약 더 작은 값을 발견하면
//			{
//				index_min = j;  //가장 작은 곳의 위치를 바꿔주고,
//				minElement = array[j];  //가장 작은 곳의 값을 바꿔준다.
//			}
//		}
//		if (index_min != round) //만약 array의 현재 탐색중인 값이 가장 작은 값이 아니라면,
//		{
//			array[index_min] = array[round];  //현재 탐색중인 값과, 찾아낸 가장 작은 값의 자리를 바꾸고
//			array[round] = minElement; //가장 작은 값을 현재 탐색중인 곳에 넣는다
//		}
//	}
//}