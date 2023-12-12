// 08_while.cpp

/*
	while��
	- ���� true�� ���� ��ɹ��� �ݺ�
	- ������ �ݺ��ϰų� Ư�� ������ �����Ҷ����� �ݺ��ϴ� ��� ���� ���

	while(��)
	{
		��ɹ�
	}

	1. ���� true���� false���� Ȯ��
	2. true�� ��ɹ� ����, �ƴ϶�� while�� ����
	3. 1, 2���� �ݺ��Ѵ�.
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	/*
		���ѷ���
		- while�� ���ο��� ���ǽ��� ����� �ݿ��ϴ� ��ɹ��� ������ �߻���
		- ���ѷ����� �ǵ������� ����ų ��쿡�� �ݵ�� ���ǽ��� ����� �����ϴ�
		��ɹ��� �����ؾ��Ѵ�.
	*/
	
	//bool my_heart = true;
	//bool the_end_world = false;

	//while (the_end_world != true && my_heart)
	//{
	//	printf("I love you\n");

	//	// ���ǽ��� ����� �����ϴ� �ڵ带 �־�����.
	//	printf("������ �����? [�� : 1 �ƴϿ� : 0] : ");
	//	int answer = 0;
	//	scanf_s("%d", &answer);

	//	if (answer == 0)
	//		my_heart = false;
	//}
	//printf("\n");

	 
	//char key = '\0';
	//while (true)
	//{
	//	printf("�̵�Ű �Է�[w : �� s : �� a : �� d : ��] => ");
	//	key = _getch();

	//	if (key == 'q')
	//		break;

	//	switch (key)
	//	{
	//	case 'w': printf("��\n"); break;
	//	case 's': printf("��\n"); break;
	//	case 'a': printf("��\n"); break;
	//	case 'd': printf("��\n"); break;
	//	}
	//}


	/*
		do while
		- ��ɹ��� �ѹ� ������ ���ǽ��� �˻�
		- ���ǿ� ������� ��ɹ��� �ѹ��� �����ؾ��ϴ� ��� ���
	*/

	// ��� : ������ �ʴ� ��
	// const Ű���带 ����ϸ� �ʱ⿡ ������ �Ŀ��� ���� �������� ���ϴ� ������ �ȴ�.
	const int secret_code = 123123; // ��� ����
	int password = 0;
	int try_count = 0;

	// ��й�ȣ�Է� 5ȸ ���н� ��ݵǵ��� �ڵ��ۼ�
	do
	{
		if (try_count >= 5)
		{
			printf("������ ��ݵǾ����ϴ�\n");
			break;
		}

		printf("��й�ȣ �Է�(�õ� Ƚ�� %d) : ", try_count);
		scanf_s("%d", &password);

		try_count++;

		//if (secret_code == password) break;
	}
	while (secret_code != password);

	srand((unsigned)time(NULL));
	int key2 = rand() % 101;
	int answer = 0;

	int low = 0;
	int high = 100;

	printf("*****Up&Down*****\n");
	while (true)
	{
		printf("���� ���� %d ~ %d \n", low, high);
		printf("�Է� => ");
		scanf_s("%d", &answer);

		if (answer == key2) // �������
		{
			printf("����!\n");
			break;
		}
		else if (answer >= low && answer <= high)
		{
			if (answer > key2)
			{
				printf("DOWN!\n");
				high = answer - 1;
			}
			else
			{
				printf("UP!\n");
				low = answer + 1;
			}
		}
		else
			printf("�߸��� �Է�\n");
	}

	/*
		���� : ���� ���� �� ���� ���׷��̵�
			- 3�� 2���� �������� �����

		���� : �� �� �� ���� �����
	*/

	return 0;
}