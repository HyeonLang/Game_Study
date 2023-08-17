// 17_string.cpp
#include<stdio.h>
#include<string.h>

void string();

int length(char string[]);
void copy(char dest[], int count, char src[]);
void catenate(char dest[], int count, char src[]);
int compare(char string1[], char string2[]);

int main()
{
	char hello[] = { 'H', 'e', 'l', 'l', 'o'};

	for (int i = 0; i < sizeof(hello) / sizeof(hello[0]); i++)
		printf("%c", hello[i]); // ���� ������ �ϳ��� ����Ҷ��� ������ ����.
	printf("\n");

	// ���ڿ� �������� ����ϸ� '\0' ���ڷ� ������ ���� ������� �ʾұ� ������
	// �� �� ���� �޸𸮸� ��� �аԵȴ�.(�쿬�� null���ڸ� ����������)
	printf("%s\n", hello);

	hello[4] = '\0';
	printf("%s\n", hello);

	//string();

	//printf("%d\n", strlen("Hello"));
	//printf("%d\n", length("Hello"));

	//{
	//	char dest[9] = "";
	//	char src[] = "Hello";

	//	copy(dest, 9, src);
	//	//strcpy_s(dest, 9, src);
	//	printf("%s\n", dest);
	//}

	//{
	//	char dest[9] = "Cat";
	//	char src[] = "Holic";

	//	catenate(dest, 9, src);
	//	//strcat_s(dest, 9, src);
	//	printf("%s\n", dest);
	//}

	//{
	//	char string1[] = "Hello";
	//	char string2[] = "Helloo";

	//	//int result = strcmp(string1, string2);
	//	int result = compare(string1, string2);

	//	printf("��� : %d\n", result);
	//}

	return 0;
}

void string()
{
	/*
		���ڿ�
		- NULL����('\0')�� ����Ǵ� ������ �迭
	*/

	{
		char hello[] = { 'H', 'e', 'l', 'l', 'o' };

		for (int i = 0; i < sizeof(hello) / sizeof(hello[0]); i++)
			printf("%c", hello[i]); // ���� ������ �ϳ��� ����Ҷ��� ������ ����.
		printf("\n");

		// ���ڿ� �������� ����ϸ� '\0' ���ڷ� ������ ���� ������� �ʾұ� ������
		// �� �� ���� �޸𸮸� ��� �аԵȴ�.(�쿬�� null���ڸ� ����������)
		printf("%s\n", hello);

		hello[3] = '\0';
		printf("%s\n", hello);
	}

	printf("\n\n");

	{
		char hello[] = { 'H', 'e', 'l', 'l', 'o', '\0' };

		for (int i = 0; i < sizeof(hello) / sizeof(hello[0]); i++)
			printf("%c", hello[i]);
		printf("\n");

		// ���ڿ� �������� �����͸� ������� '\0'�� ���������� ���ڸ� �о� ���
		printf("%s\n", hello);

		hello[2] = '\0'; 
		printf("%s\n", hello);
	}

	printf("\n\n");
	{
		// ���ڿ� ��� �����ʹ� ���ڿ��̱� ������ ������ ������ ������ �������� 
		// �ڵ����� '\0' ���ڸ� ���Խ����ش�.
		char hello[] = "Hello"; // ���ڿ� ����� ���� �ʱ�ȭ�Ҷ��� '\0' ���ڰ� ���Եȴ�.
		printf("%s\n", hello);
	}
}

int length(char string[])
{
	/*
		NULL���ڸ� ������ ���ڿ��� ���� ������ ��ȯ�ϴ� �Լ�
	*/

	int i = 0;

	while (string[i] != '\0')
	{
		i++;
	}

	return i;
}

void copy(char dest[], int count, char src[])
{
	/*
		src�� ���ڿ� ���̰� dest�� ���� �������� ª�� ���
		src�� ���ڿ��� dest�� �����ϴ� �Լ�
	*/

	// dest[9] : ""
	// src[6]  : "Hello"

	int length_src = length(src);

	if (length_src >= count)
		return;

	for (int i = 0; i <= length_src; i++)
		dest[i] = src[i];
}

void catenate(char dest[], int count, char src[])
{
	/*
		dest�� src�� ���ڿ� ������ ���� dest�� ���� �������� ª�� ���
		src�� ���ڿ��� dest�� ���ڿ��� �����ϴ� �Լ�
	*/

	// dest : "Cat'\0'"
	// src	: "Holic"

	int length_dest = length(dest);
	int length_src = length(src);

	if (length_dest + length_src >= count)
		return;
		
	for (int i = 0; i <= length_src; i++)
		dest[length_dest + i] = src[i];
}

int compare(char string1[], char string2[])
{
	/*
		�� ���ڿ��� ���Ͽ� ������� 0 ��ȯ

		���� �ٸ� ���ڸ� ������ ��ġ�� ���Ҹ� ���Ͽ�
		string1�� ũ�ٸ� 1 ��ȯ
		string2�� ũ�ٸ� -1 ��ȯ
	*/

	for (int i = 0; ; i++)
	{
		if (string1[i] > string2[i]) return +1;
		if (string1[i] < string2[i]) return -1;
		if (string1[i] == '\0' && string2[i] == '\0') return 0;
	}
	
	return 0;
}
