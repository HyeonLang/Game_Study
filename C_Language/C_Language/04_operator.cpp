// 04_operator.cpp

/*
	������
	- ���α׷��� ���� �Ϲ����� ���а� ������ �����ڸ� �����Ѵ�.
	- ����, ���, ���� ����, ����, ��, ��, ����, ��Ʈ
*/

/*
	���� ������
	- ������ ���� ������ �� ����Ѵ�
	- ��ȣ : =

	a = b (���� a���ٰ� ���� b�� ���� �������ش�)
*/

/*
	��� ������
	- �Ϲ����� ��� ������ �����Ѵ�.
	- ��ȣ : +, -, *, /, %

	c = a + b;
	c = a - b;
	c = a * b; a�� b�� ���Ѵ�.
	c = a / b; a�� b�� ������ ���� ���Ѵ�.
	c = a % b; a�� b�� ������ �������� ���Ѵ�.
*/

/*
	���� ���� ������
	 c = c + a ���� ��Ȳ�϶�
	 c += a���� ���� �� �ִ�.
	 ��� ���� �����ڿ� ���밡��
*/

/*
	���� ������
	- ���� 1���� ��Ű�ų� ���� ��ų �� ����Ѵ�.
	- ��ȣ�� �ٴ� ��ġ�� ���� ������ ������ ������.
	�տ� ������ ����, �ڿ� ������ ����
	- ��ȣ : ++, --

	����
	- ���� ������ ���� ������ �ٸ� ������ �����Ѵ�.
	����)
	{
		int a = 0;
		int b = 0;

		a = ++b; b�� ���� 1 ������Ų�� �������ش�
		=> a�� 1�� �ȴ�.
	}

	����
	- �ٸ� ������ ���� ������ ���� ������ �����Ѵ�.
	����)
	{
		int a = 0;
		int b = 0;

		a = b++; b�� ���� ���� ���ְ� b�� 1 ������Ų��.
		=> a�� 0�� �ȴ�.
	}
*/

/*
	�� ������
	- 2���� �ǿ������� ũ�⸦ ���Ͽ� ��(true)�� ����(false)�� ��ȯ�Ѵ�.

	== : ������ true, �ٸ��� false��ȯ
	!= : ������ false, �ٸ��� true��ȯ

	a < b a�� b���� ������ true �� �ܿ� false
	a > b a�� b���� ũ�� true �� �ܿ� false

	a <= b a�� b���� �۰ų� ������ true �� �ܿ� false
	a >= b a�� b���� ũ�ų� ������ true �� �ܿ� false
*/

/*
	�� ������
	- ������ �Ǵ��Ͽ� ���� ������ ��ȯ�Ѵ�.

	&&	(and)	: �Ѵ� ���̸� true �׿� false
	||	(or)	: ���� �ϳ��� ���̸� true �׿� false
	!	(not)	: true�� false, false�� true��ȯ => ���� ������ �ش�.
*/

/*
	���� ������
	- ������ ���� �������̴�.
	- ���ǽĿ� ���� 2���� ��ȯ���� ������.

	���ǽ� ? ��ȯ��1 : ��ȯ��2
	���ǽ��� ���̸� ��ȯ��1, �����̸� ��ȯ��2�� ��ȯ�Ѵ�.
	��ȯ��1, ��ȯ��2�� �ַ� �������� ��쿡 ���� ������� �� �� �ִ�.
*/

/*
	��Ʈ������
	- ��Ʈ�� ������ �ٷ궧 ����ϴ� ������
	- ��Ʈ �÷��׸� ����� �� ����� ���� �����Ѵ�.
	���� : ��Ʈ �÷��װ� �������� �����ϱ�.
*/

#include<stdio.h>

int main()
{
#pragma region Attack
	//int playerDamage = 50;
	//int enemyHp = 540;

	//printf("�÷��̾��� ���ݷ� : %d\n", playerDamage);
	//printf("���� ���� ü�� : %d\n", enemyHp);

	//int attackCount = 0;
	//printf("�� �� �����Ͻðڽ��ϱ�? : ");
	//scanf_s("%d", &attackCount);

	//printf("�÷��̾ ���� %d�� ����!\n", attackCount);
	//enemyHp -= playerDamage * attackCount;

	//printf("���� ���� ü�� : %d\n\n", enemyHp);
#pragma endregion

#pragma region Buy

	//int gold = 500;
	//printf("���� ���� ��� : %d\n", gold);

	//int price = 0;
	//printf("������ ���� A�� �� : ");
	//scanf_s("%d", &price);

	//printf("���� A�� ���� ���� ���� : %d\n", gold / price);
	//printf("���� A�� �ִ�ġ���� ������ ���� ��� %d\n\n", gold % price);

#pragma endregion


#pragma region ++, --


	int a = 0;
	int b = 0;

	printf("int ++a : %d\n", ++a);
	printf("int b++ : %d\n\n", b++);

	printf("int a : %d\n", a);
	printf("int b : %d\n\n", b);

#pragma endregion

#pragma region Grab

	int grabRange;
	int distance = 300;
	int enemySpeed = 50;

	printf("������ ��Ÿ� : %d\n", distance);

	printf("�׷� ��Ÿ� : ");
	scanf_s("%d", &grabRange);

	//grabRange >= distance ? distance = 50 : distance += enemySpeed;
	distance = ((grabRange >= distance) ? 50 : distance + enemySpeed);

	printf("������ ��Ÿ� : %d\n", distance);

#pragma endregion

	/*
	���� �� ������ ����
		��������(&&, ||, !)�� ����ؼ�
		��ĭ( )�� ä���� ����(=>) ���� ���� ����� ����� ����
		������ ������ ��� ���� ����

		1. true () false => false
		2. true () false => true
		3. true () true  => true
		4. ()true		 => false
		5. ()false		 => true
	*/

	/*
		���� : ȯ�� ���� �����
		���� : bmi ���� �����
	*/

	return 0;
}