// 15_2d_array.cpp

/*
	2차원 배열

	- 1차원 배열을 원소로 가지는 배열
	- 배열을 원소로 가지는 배열을 다차원 배열이라고 부른다.
	- 2차원을 넘어서는 다차원 배열은 잘 사용하지 않는다.
	- 1차원 배열과 같이 메모리가 연속적으로 붙어있다.

	선언

	자료형 이름[행][열]
	type name[row][column];

	int arr[3][5]

	//ㅁㅁㅁㅁㅁ 3행 5열
	//ㅁㅁㅁㅁㅁ
	//ㅁㅁㅁ☆ㅁ
	☆ -> 2행 3열

	- 행 : 가로줄
	- 열 : 세로줄

*/

// 1 2 3
// 4 0 0
// 5 6 0
int arr1[2][3] = { 1, 2, 3, 4, 5, 6 };		// 행 구분없이 초기화할 경우 행 순서대로 데이터 삽입
int arr2[2][3] = { {1, 2, 3}, {4, 5, 6} };	// 행단위로 초기화 가능
int arr3[2][3] = { 1, 2, 3};				// 남은 공간 0으로 초기화				
int arr4[][3] = { 1, 2, 3};					// 행은 생략 가능
int arr5[][3] = { {1, 2, 3}, {4, }, {5, 6} };
//int arr6[3][] = { {1, 2, 3}, {4, }, {5, 6} }; // error : 열은 생략 불가능

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
	// 학생의 성적을 배열에 담아 계산하고 출력하는 코드
	// ROWS : 학생번호 
	// COLS: 과목점수(국어, 영어, 수학)

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

	printf("\n국어총점\t영어총점\t수학총점\n");
	printf("%d\t\t%d\t\t%d\n", total_score[0], total_score[1], total_score[2]);

	printf("\n");
	for (int i = 0; i < ROWS; i++)
		printf("%d학생의 총점 : %d\n", i + 1, strudent[i]);
}

void floor()
{
	//과제
	// 아파트의 각 층마다 호의 인원수를 입려받고
	// 각층의 총원, 해당 아파트의 총 인원을 출력하는 함수

}
