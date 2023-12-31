// 15_2d_array.cpp

/*
	2託据 壕伸

	- 1託据 壕伸聖 据社稽 亜走澗 壕伸
	- 壕伸聖 据社稽 亜走澗 壕伸聖 陥託据 壕伸戚虞壱 採献陥.
	- 2託据聖 角嬢辞澗 陥託据 壕伸精 設 紫遂馬走 省澗陥.
	- 1託据 壕伸引 旭戚 五乞軒亜 尻紗旋生稽 細嬢赤陥.

	識情

	切戟莫 戚硯[楳][伸]
	type name[row][column];

	int arr[3][5]

	//けけけけけ 3楳 5伸
	//けけけけけ
	//けけけ』け
	』 -> 2楳 3伸

	- 楳 : 亜稽匝
	- 伸 : 室稽匝

*/

// 1 2 3
// 4 0 0
// 5 6 0
int arr1[2][3] = { 1, 2, 3, 4, 5, 6 };		// 楳 姥歳蒸戚 段奄鉢拝 井酔 楳 授辞企稽 汽戚斗 諮脊
int arr2[2][3] = { {1, 2, 3}, {4, 5, 6} };	// 楳舘是稽 段奄鉢 亜管
int arr3[2][3] = { 1, 2, 3};				// 害精 因娃 0生稽 段奄鉢				
int arr4[][3] = { 1, 2, 3};					// 楳精 持繰 亜管
int arr5[][3] = { {1, 2, 3}, {4, }, {5, 6} };
//int arr6[3][] = { {1, 2, 3}, {4, }, {5, 6} }; // error : 伸精 持繰 災亜管

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
	// 俳持税 失旋聖 壕伸拭 眼焼 域至馬壱 窒径馬澗 坪球
	// ROWS : 俳持腰硲 
	// COLS: 引鯉繊呪(厩嬢, 慎嬢, 呪俳)

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

	printf("\n厩嬢恥繊\t慎嬢恥繊\t呪俳恥繊\n");
	printf("%d\t\t%d\t\t%d\n", total_score[0], total_score[1], total_score[2]);

	printf("\n");
	for (int i = 0; i < ROWS; i++)
		printf("%d俳持税 恥繊 : %d\n", i + 1, strudent[i]);
}

void floor()
{
	//引薦
	// 焼督闘税 唖 寵原陥 硲税 昔据呪研 脊形閤壱
	// 唖寵税 恥据, 背雁 焼督闘税 恥 昔据聖 窒径馬澗 敗呪

}
