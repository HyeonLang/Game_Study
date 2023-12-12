// 25_bit_flag.cpp

/*
	bit flag

	- 2������ 1�� 0 �ΰ��� ������ ǥ���ϴµ� �̸� 1(on)/0(off)�� �������� ����ϴ� ��

	- �ϳ��� �����Ϳ� ���� ���°��� ������ �� �ִ�.

	- bool �ڷ����� ��(1)�� ����(0) �ΰ��� ��츸�� ǥ���ϱ� ������ 1��Ʈ��
	ũ�⸸ �ʿ������� �޸��� �ּ� ũ��� 1����Ʈ�̱� ������ bool�� 8��Ʈ��
	������ �־� ������ ����ǰ� �ִ�. ���� ũ�⸦ ���� char�ڷ����� ������
	��Ʈ�� ��Ʈ �÷��׷� ����ϸ� char �ڷ��� �ϳ��� 8���� on/off�� ������ �� �ִ�.
*/


#include<stdio.h>

void print_bit(unsigned char b);

void bit_operator();

void bit_flag_example();

int main()
{
	//bit_operator();
	bit_flag_example();

	return 0;
}

void print_bit(unsigned char b)
{
	for (int i = 7; i >= 0; i--)
	{
		printf("%d", (b >> i) & 1); // 1 => 0b 0001
	}
}

void bit_operator()
{
	/*
		AND (&) : �� ��Ʈ�� 1�϶� 1
		0000 1101
		0000 1011
		-----------
		0000 1001
	*/
	{
		unsigned char b1 = 0b0000'1101;
		unsigned char b2 = 0b0000'1011;
		unsigned char rb = b1 & b2;

		printf("------AND----\n");
		printf("b1 : ");
		print_bit(b1);
		printf("\n");

		printf("b2 : ");
		print_bit(b2);
		printf("\n-------------\n");

		printf("rb : ");
		print_bit(rb);
		printf("\n\n");
	}

	/*
		OR (|) : �� ��Ʈ�� �ϳ��� 1�̸� 1
		0000 1101
		0000 1011
		-----------
		0000 1111
	*/
	{
		unsigned char b1 = 0b0000'1101;
		unsigned char b2 = 0b0000'1011;
		unsigned char rb = b1 | b2;

		printf("------OR-----\n");
		printf("b1 : ");
		print_bit(b1);
		printf("\n");

		printf("b2 : ");
		print_bit(b2);
		printf("\n-------------\n");

		printf("rb : ");
		print_bit(rb);
		printf("\n\n");
	}

	/*
		NOT	(~)	: ��Ʈ ����
		0000 1101
		---------
		1111 0010
	*/
	{
		unsigned char b1 = 0b0000'1101;
		unsigned char rb = ~b1;

		printf("------NOT----\n");
		printf("b1 : ");
		print_bit(b1);

		printf("\n-------------\n");

		printf("rb : ");
		print_bit(rb);
		printf("\n\n");
	}

	/*
		XOR (^) : �� ��Ʈ�� ���� �ٸ��� 1
		0000 1101
		0000 1011
		-----------
		0000 0110
	*/
	{
		unsigned char b1 = 0b0000'1101;
		unsigned char b2 = 0b0000'1011;
		unsigned char rb = b1 ^ b2;

		printf("------XOR----\n");
		printf("b1 : ");
		print_bit(b1);
		printf("\n");

		printf("b2 : ");
		print_bit(b2);
		printf("\n-------------\n");

		printf("rb : ");
		print_bit(rb);
		printf("\n\n");
	}

	/*
		right shift (>>)	: ������ �� ��ŭ ��Ʈ�� ��� ���������� �̵�
		1100 1011
		--------- >> 4
		0000 1100
		--------- >> 3
		0000 0001

		0b1000 8
		0b0100 4
		0b0010 2
		0b0001 1
	*/
	{
		unsigned char b = 0b1100'1011;
		unsigned char rb1 = b >> 4;
		unsigned char rb2 = rb1 >> 3;

		printf("-----right----\n");
		printf("b   : ");
		print_bit(b);

		printf("\n-------------- >> 4\n");
		printf("rb1 : ");
		print_bit(rb1);

		printf("\n-------------- >> 3\n");
		printf("rb2 : ");
		print_bit(rb2);

		printf("\n\n");
	}

	/*
		left shift (<<)	: ������ �� ��ŭ ��Ʈ�� ��� �������� �̵�
		1100 1011
		--------- << 4
		1011 0000
		--------- << 3
		1000 0000

		0b0001 1
		0b0010 2
		0b0100 4
		0b1000 8
	*/
	{
		unsigned char b = 0b1100'1011;
		unsigned char rb1 = b << 4;
		unsigned char rb2 = rb1 << 3;

		printf("-----left-----\n");
		printf("b   : ");
		print_bit(b);

		printf("\n-------------- << 4\n");
		printf("rb1 : ");
		print_bit(rb1);

		printf("\n-------------- << 3\n");
		printf("rb2 : ");
		print_bit(rb2);

		printf("\n\n");
	}
}

enum status
{
	god_mode		= 0b1000'0000,
	invisible		= 0b0100'0000,
	jump			= 0b0010'0000,
	fly				= 0b0001'0000,
	swim			= 0b0000'1000,
	frozen			= 0b0000'0100,
	burn			= 0b0000'0010,
	bleeding		= 0b0000'0001,
};

void print_status(unsigned char status)
{
	printf("----�÷��̾� ����â----\n");
	if (status & god_mode)	printf("����\n");
	if (status & invisible) printf("����\n");
	if (status & jump)		printf("����\n");
	if (status & fly)		printf("����\n");
	if (status & swim)		printf("����\n");
	if (status & frozen)	printf("����\n");
	if (status & burn)		printf("ȭ��\n");
	if (status & bleeding)	printf("����\n");
	printf("\n");
}

void bit_flag_example()
{
	unsigned char player_status = 0b0000'0000;

	print_status(player_status);

	// �÷��� �߰�
	{
		player_status |= god_mode;
		player_status |= invisible;
		player_status |= jump;
		player_status |= fly;
		player_status |= burn;
	}

	print_status(player_status);

	// �÷��� ����
	/*
		player_status		== 1111 0010
		god_mode			== 1000 0000
		
		1111 0010
		0111 1111 <- ~(1000 0000)
		---------
		0111 0010
	*/
	{
		player_status &= ~god_mode;
		player_status &= ~burn;
	}

	print_status(player_status);
}
