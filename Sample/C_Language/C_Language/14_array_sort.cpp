// 14_array_sort.cpp


#include<stdio.h>

void print_arr(int arr[], int arr_size);

// 버블 정렬
// 서로 인접한 두 원소를 비교하며 정렬하는 알고리즘
// [3 5] 4 1 2
// 3 [5 4] 1 2
// 3 4 [5 1] 2
// 3 4 1 [5 2]
// 3 4 1 2 5

void bubble_sort(int arr[], int arr_size);

// 선택 정렬
// 회차마다 자리는 정해져 있고 해당 자리에 들어갈
// 원소를 찾아 넣어주는 알고리즘

// 3 5 4 1 2
// 1 5 4 3 2
// 1 2 4 3 5
// 1 2 3 4 5
// 1 2 3 4 5

void selection_sort(int arr[], int arr_size);

int main()
{
	int arr[5] = { 3,5,4,1,2 };

	print_arr(arr, sizeof(arr) / sizeof(arr[0]));
	//bubble_sort(arr, sizeof(arr) / sizeof(int));
	selection_sort(arr, sizeof(arr) / sizeof(int));
	print_arr(arr, sizeof(arr) / sizeof(int));

	return 0;
}

void print_arr(int arr[], int arr_size)
{
	for (int i = 0; i < arr_size; i++)
		printf("%d, ", arr[i]);
	printf("\n");
}

void bubble_sort(int arr[], int arr_size)
{
	int temp = 0;
	for (int i = 0; i < arr_size; i++)
	{
		for (int j = 0; j < (arr_size - 1); j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void selection_sort(int arr[], int arr_size)
{
	int min_index = 0;
	int temp = 0;

	for (int i = 0; i < arr_size; i++)
	{
		min_index = i;
		for (int j = i + 1; j < arr_size; j++)
			if (arr[j] < arr[min_index])
				min_index = j;

		temp = arr[i];
		arr[i] = arr[min_index];
		arr[min_index] = temp;
	}
}
