// 06_switch.cpp
/*
	switch��
	- ��ȣ�ȿ� ���� ���� �����ϴ� case�� �̵��� ��ɾ ����
	- �������� ���� �� �ִ�. �Ǽ��� �ȵ�


	switch(����)
	{
		case ������1:
			���1
			break;

		case ������2:
			���2
			break;

		default:
			����ó�� ���
			break;
	}
	default 
	- �������� �����ϴ� case�� ������� �ش� ��ġ�� �̵�

	break
	- ���� �����ϰ��ִ� statement�� �����Ѵ�.

	statement(��)
	- ���α׷��ֿ��� ���డ���� �ּ��� �������� �ڵ� ����
	- �ڵ��� ������ ����
*/

#include<stdio.h>

#define INTRO 1
#define GAME 2
#define OPTION 3
#define EXIT 4

int main()
{

	int sel_menu = 0;
	printf("�޴��� �����ϼ��� [1: ��Ʈ�� 2: ���� 3: �ɼ� 4: ����]\n");
	printf("input -> ");
	scanf_s("%d", &sel_menu);

	switch (sel_menu)
	{
	case INTRO: 
		printf("��Ʈ�� ������ �����Դϴ�.");
		break;

	case GAME:
		printf("���� ������ �����Դϴ�.");
		break;

	case OPTION:
		printf("�ɼ� ������ �����Դϴ�.");
		break;

	case EXIT:
		printf("���� ������ �����Դϴ�.");
		break;

	default:
		printf("�߸��� �Է��Դϴ�.\n");
		break;
	}

	// ���� : ���� ���� �� ���� �����
	//	- ������ ������ ����
	//  - �÷��̾ ���� ��쿡 ���� ��, ��, ���º� ���
	//  - if, switch���� ����Ͽ� �ۼ�

	return 0;
}