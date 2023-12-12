// 15_2d_array.cpp

/*
	2���� �迭

	- 1���� �迭�� ���ҷ� ������ �迭
	- �迭�� ���ҷ� ������ �迭�� ������ �迭�̶�� �θ���.
	- 2������ �Ѿ�� ������ �迭�� �� ������� �ʴ´�.
	- 1���� �迭�� ���� �޸𸮰� ���������� �پ��ִ�.

	����

	�ڷ��� �̸�[��][��]
	type name[row][column];

	int arr[3][5]

	//���������� 3�� 5��
	//����������
	//�������٤�
	�� -> 2�� 3��

	- �� : ������
	- �� : ������

*/

// 1 2 3
// 4 0 0
// 5 6 0
int arr1[2][3] = { 1, 2, 3, 4, 5, 6 };		// �� ���о��� �ʱ�ȭ�� ��� �� ������� ������ ����
int arr2[2][3] = { {1, 2, 3}, {4, 5, 6} };	// ������� �ʱ�ȭ ����
int arr3[2][3] = { 1, 2, 3};				// ���� ���� 0���� �ʱ�ȭ				
int arr4[][3] = { 1, 2, 3};					// ���� ���� ����
int arr5[][3] = { {1, 2, 3}, {4, }, {5, 6} };
//int arr6[3][] = { {1, 2, 3}, {4, }, {5, 6} }; // error : ���� ���� �Ұ���

#include<stdio.h>

void print_arr();
void print_score();
void floor();

int main()
{
	//print_arr();
	print_score();

	return 0;
}

void print_arr()
{
	// 1 2 3
	// 4 5 6

	//arr1
	printf("*** arr1 ***\n");

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", arr1[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//arr2
	printf("*** arr2 ***\n");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", arr2[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//arr3
	printf("*** arr3 ***\n");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", arr3[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//arr4
	printf("*** arr4 ***\n");
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", arr4[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//arr5
	printf("*** arr5 ***\n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", arr5[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

#define ROWS 5
#define COLS 3

void print_score()
{
	// �л��� ������ �迭�� ��� ����ϰ� ����ϴ� �ڵ�
	// ROWS : �л���ȣ 
	// COLS: ��������(����, ����, ����)

	int score[ROWS][COLS] = {
		{85, 60, 70},
		{90, 85, 77},
		{85, 64, 75},
		{96, 100, 97},
		{55, 60, 70}
	};

	int total_score[COLS] = {};
	int strudent[ROWS] = {};

	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
		{
			total_score[j] += score[i][j];
			strudent[i] += score[i][j];
		}

	printf("\n��������\t��������\t��������\n");
	printf("%d\t\t%d\t\t%d\n", total_score[0], total_score[1], total_score[2]);

	printf("\n");
	for (int i = 0; i < ROWS; i++)
		printf("%d�л��� ���� : %d\n", i + 1, strudent[i]);
}

void floor()
{
	//����
	// ����Ʈ�� �� ������ ȣ�� �ο����� �Է��ް�
	// ������ �ѿ�, �ش� ����Ʈ�� �� �ο��� ����ϴ� �Լ�

}
