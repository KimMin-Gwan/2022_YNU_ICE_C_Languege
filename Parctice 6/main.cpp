/* main() for Algorithms_on_Arrays */
#pragma warning(disable: 4996)
#include "BigArray_Algorithms.h"
#include "BigArray_Sortings.h"
#define SMALL_ARRAY_SIZE 100
#define BIG_ARRAY_SIZE 5000000
void Compare_Sorting_Algorithms_SmallIntArray();
void testBigRandArray();
void PM_Hybrid_QS_SS_IntArray();

int main()
{
	int menu;
	srand(0);
	while (1)
	{
		printf("\nTest Array Algorithms :\n");
		printf(" 1: Performance Comparison of Selection Sort and Quick Sort for Small IntegerArray\n");
		printf(" 2: Test bigRandArray (Array_size : 1,000,000 ~ 50,000,000)\n");
		printf(" 3: Performance Measurements of hybrid_QS_SS for Integer Array\n");
		printf("Input menu (0 to terminate) : ");
		scanf("%d", &menu);
		if (menu == 0)
			break;
		switch (menu)
		{
		case 1:
			Compare_Sorting_Algorithms_SmallIntArray();
			break;
		case 2:
			testBigRandArray();
			break;
		case 3:
			PM_Hybrid_QS_SS_IntArray();
			break;
		default:
			break;
		}
	}
	return 0;
}

void Compare_Sorting_Algorithms_SmallIntArray()
{
	int* array;
	int array_size;
	int base = 0;
	LARGE_INTEGER freq, t_before, t_after;
	LONGLONG t_diff;
	double elapsed_time_us;
	double elps_time_quickSort_us, elps_time_selectSort_us, elps_time_mergeSort_us;
	QueryPerformanceFrequency(&freq);

	printf("Compare the performance of sorting algorithms for small array\n");
	printf("==================================================================\n");
	printf(" Array size QuickSort[us]   MergeSort[us]   SelectionSort[us]\n");
	printf("------------------------------------------------------------------\n");

	for (int size = 10; size <= SMALL_ARRAY_SIZE; size += 5)
	{
		array = (int*)calloc(size, sizeof(int));
		genBigRandArray(array, size, base);

		QueryPerformanceCounter(&t_before);
		quickSort(array, size);
		QueryPerformanceCounter(&t_after);
		t_diff = t_after.QuadPart - t_before.QuadPart;
		elapsed_time_us = ((double)t_diff * 1000000 / freq.QuadPart); // in micro-second
		elps_time_quickSort_us = elapsed_time_us;
		suffleArray(array, size);

		QueryPerformanceCounter(&t_before);
		mergeSort(array, size);
		QueryPerformanceCounter(&t_after);
		t_diff = t_after.QuadPart - t_before.QuadPart;
		elapsed_time_us = ((double)t_diff * 1000000 / freq.QuadPart); // in micro-second
		elps_time_mergeSort_us = elapsed_time_us;
		suffleArray(array, size);

		QueryPerformanceCounter(&t_before);
		selectionSort(array, size);
		QueryPerformanceCounter(&t_after);
		t_diff = t_after.QuadPart - t_before.QuadPart;
		elapsed_time_us = ((double)t_diff * 1000000 / freq.QuadPart); // in micro-second
		elps_time_selectSort_us = elapsed_time_us;
		printf("%10d %15.2lf %15.2lf %15.2lf\n", size, elps_time_quickSort_us, elps_time_mergeSort_us, elps_time_selectSort_us);

		free(array);
	}
}

void testBigRandArray()
{
	int* array;
	int size = 0;;
	int base = 1;

	printf("Input bigRandArray_size (0 to quit) and offset : ");
	scanf("%d  %d", &size, &base);
	array = (int*)calloc(size, sizeof(int));
	genBigRandArray(array, size, base);
	printf("Generated non-duplicated random array : \n");
	printBigArraySample(array, size);
	hybridQuickSelectionSort(array, size);
	printf("Sorted array : \n");
	printBigArraySample(array, size);
	free(array);
}

void PM_Hybrid_QS_SS_IntArray()
{
	int* array;
	int array_size;
	LARGE_INTEGER freq, t_before, t_after;
	LONGLONG t_diff;
	double elapsed_time_us;
	double elps_time_quickSort_us, elps_time_hybridQuickSelectionSort_us;
	QueryPerformanceFrequency(&freq);

	printf("Compare the performance of sorting algorithms for small array\n");
	printf("==================================================================\n");
	printf(" Array size      QuickSort[ms]      HybridQuickSelectionSort[ms]\n");
	printf("------------------------------------------------------------------\n");

	for (int size = 1000000; size <= BIG_ARRAY_SIZE; size += 1000000)
	{
		array = (int*)calloc(size, sizeof(int));
		genBigRandArray(array, size, 0);

		QueryPerformanceCounter(&t_before);
		hybridQuickSelectionSort(array, size);
		QueryPerformanceCounter(&t_after);
		t_diff = t_after.QuadPart - t_before.QuadPart;
		elapsed_time_us = ((double)t_diff * 1000 / freq.QuadPart); // in milli-second
		elps_time_hybridQuickSelectionSort_us = elapsed_time_us;
		//suffleArray(array, size); //정확하게 측정이 안되서 주석처리
		free(array);

		array = (int*)calloc(size, sizeof(int));
		genBigRandArray(array, size, 0);

		QueryPerformanceCounter(&t_before);
		quickSort(array, size);
		QueryPerformanceCounter(&t_after);
		t_diff = t_after.QuadPart - t_before.QuadPart;
		elapsed_time_us = ((double)t_diff * 1000 / freq.QuadPart); // in milli-second
		elps_time_quickSort_us = elapsed_time_us;
		printf("%10d   %15.2lf     %15.2lf\n", size, elps_time_quickSort_us, elps_time_hybridQuickSelectionSort_us);
		free(array);
	}
}
