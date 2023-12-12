#include<stdio.h>
#include<stdlib.h>
#include<time.h>
// ���� ���� ��
// 0   

/*
	���� : 0
	���� : 1
	��   : 2

	p : (0 + 1) % 3 -> 1
	e : 1
	=> �й�

	p : (1 + 1) % 3 -> 2
	e : 2
	=> �й�

	p : (2 + 1) % 3 -> 0
	e : 0
	=> �й�

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

// p�� e�� �� ���� �޾Ƽ� ���ڸ� ����ϴ� �Լ� CheckWinner
// p �� -> 1 ��ȯ
// ���º� -> 0
// e �� -> -1 ��ȯ

#define ���� 0
#define ���� 1
#define �� 2

#define �� 1
#define �� -1
#define ���� 0


#define ���� 0
#define �÷��̾��� 1
#define ���� 2

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
	case ����: printf("����\n"); break;
	case ����: printf("����\n"); break;
	case ��: printf("��\n"); break;
	}
}

int main()
{
	printf("%d", CheckWinner(����, ����));
	printf("%d", CheckWinner(����, ��));
	printf("%d", CheckWinner(��, ����));
	printf("\n\n");

	printf("%d", CheckWinner(����, ����));
	printf("%d", CheckWinner(����, ����));
	printf("%d", CheckWinner(��, ��));
	printf("\n\n");

	printf("%d", CheckWinner(����, ����));
	printf("%d", CheckWinner(��, ����));
	printf("%d", CheckWinner(����, ��));
	printf("\n\n");

	int p_input = 0;
	int e_input = 0;

	int p_win_count = 0;
	int e_win_count = 0;

	int currnet_turn = ����;

	srand(time(NULL));

	while (true)
	{
		do
		{
	

			printf("����0 ����1 ��2 : ");
			scanf_s("%d", &p_input);

			e_input = rand() % 3;
			printf("�� : ");
			print_rsp(e_input);

			switch (CheckWinner(p_input, e_input))
			{
			case ��: currnet_turn = �÷��̾���;	break;
			case ��: currnet_turn = ����;		break;
			case ����: currnet_turn = ����;	break;
			}
			printf("\n");
		} while (currnet_turn == ����);

		do
		{
			if (currnet_turn == �÷��̾���)
				printf("�Է�(�÷��̾ �̱����) : ");
			else
				printf("�Է�(���� �̱����) : ");
			scanf_s("%d", &p_input);

			e_input = rand() % 3;
			printf("�� : ");
			print_rsp(e_input);

			switch (CheckWinner(p_input, e_input))
			{
			case ��: currnet_turn = �÷��̾���;	break;
			case ��: currnet_turn = ����;		break;
			case ����:
			{
				if (currnet_turn == �÷��̾���)
				{
					printf("�÷��̾ �̱� %d -> %d\n", p_win_count, p_win_count + 1);
					p_win_count++;
				}
				else
				{
					printf("���� �̱� %d -> %d\n", e_win_count, e_win_count + 1);
					e_win_count++;
				}
				currnet_turn = ����;
				break;
			} // ����:
			} // switch (CheckWinner(p_input, e_input))  
		} while (currnet_turn != ����);

		if (p_win_count >= 2)
		{
			printf("�÷��̾� �¸�\n");
			break;
		}

		if (e_win_count >= 2)
		{
			printf("�� �¸�\n");
			break;
		}
	}

	return 0;
}