#include<stdio.h>
#include<stdlib.h>
#include<time.h>
// 가위 바위 보
// 0   

/*
	가위 : 0
	바위 : 1
	보   : 2

	p : (0 + 1) % 3 -> 1
	e : 1
	=> 패배

	p : (1 + 1) % 3 -> 2
	e : 2
	=> 패배

	p : (2 + 1) % 3 -> 0
	e : 0
	=> 패배

	////////////
	p : (0 + 1) % 3 -> 1
	e : 2
	=> 

	p : (1 + 1) % 3 -> 2
	e : 0
	=> 

	p : (2 + 1) % 3 -> 0
	e : 1
*/

// p와 e가 낸 값을 받아서 승자를 출력하는 함수 CheckWinner
// p 승 -> 1 반환
// 무승부 -> 0
// e 승 -> -1 반환

#define 가위 0
#define 바위 1
#define 보 2

#define 승 1
#define 패 -1
#define 같다 0


#define 시작 0
#define 플레이어턴 1
#define 적턴 2

int CheckWinner(int p, int e)
{
	if (p == e) return 0;

	p = (p + 1) % 3;
	
	if (p == e) return -1;
	else return 1;
}

void print_rsp(int num)
{
	switch (num)
	{
	case 가위: printf("가위\n"); break;
	case 바위: printf("바위\n"); break;
	case 보: printf("보\n"); break;
	}
}

int main()
{
	printf("%d", CheckWinner(가위, 바위));
	printf("%d", CheckWinner(바위, 보));
	printf("%d", CheckWinner(보, 가위));
	printf("\n\n");

	printf("%d", CheckWinner(가위, 가위));
	printf("%d", CheckWinner(바위, 바위));
	printf("%d", CheckWinner(보, 보));
	printf("\n\n");

	printf("%d", CheckWinner(바위, 가위));
	printf("%d", CheckWinner(보, 바위));
	printf("%d", CheckWinner(가위, 보));
	printf("\n\n");

	int p_input = 0;
	int e_input = 0;

	int p_win_count = 0;
	int e_win_count = 0;

	int currnet_turn = 시작;

	srand(time(NULL));

	while (true)
	{
		do
		{
	

			printf("가위0 바위1 보2 : ");
			scanf_s("%d", &p_input);

			e_input = rand() % 3;
			printf("적 : ");
			print_rsp(e_input);

			switch (CheckWinner(p_input, e_input))
			{
			case 승: currnet_turn = 플레이어턴;	break;
			case 패: currnet_turn = 적턴;		break;
			case 같다: currnet_turn = 시작;	break;
			}
			printf("\n");
		} while (currnet_turn == 같다);

		do
		{
			if (currnet_turn == 플레이어턴)
				printf("입력(플레이어가 이긴상태) : ");
			else
				printf("입력(적이 이긴상태) : ");
			scanf_s("%d", &p_input);

			e_input = rand() % 3;
			printf("적 : ");
			print_rsp(e_input);

			switch (CheckWinner(p_input, e_input))
			{
			case 승: currnet_turn = 플레이어턴;	break;
			case 패: currnet_turn = 적턴;		break;
			case 같다:
			{
				if (currnet_turn == 플레이어턴)
				{
					printf("플레이어가 이김 %d -> %d\n", p_win_count, p_win_count + 1);
					p_win_count++;
				}
				else
				{
					printf("적이 이김 %d -> %d\n", e_win_count, e_win_count + 1);
					e_win_count++;
				}
				currnet_turn = 시작;
				break;
			} // 같다:
			} // switch (CheckWinner(p_input, e_input))  
		} while (currnet_turn != 시작);

		if (p_win_count >= 2)
		{
			printf("플레이어 승리\n");
			break;
		}

		if (e_win_count >= 2)
		{
			printf("적 승리\n");
			break;
		}
	}

	return 0;
}