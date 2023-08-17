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
		printf("%c", hello[i]); // 문자 단위로 하나씩 출력할때는 문제가 없다.
	printf("\n");

	// 문자열 형식으로 출력하면 '\0' 문자로 문장의 끝을 명시하지 않았기 때문에
	// 알 수 없는 메모리를 계속 읽게된다.(우연히 null문자를 읽을때까지)
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

	//	printf("결과 : %d\n", result);
	//}

	return 0;
}

void string()
{
	/*
		문자열
		- NULL문자('\0')로 종결되는 문자의 배열
	*/

	{
		char hello[] = { 'H', 'e', 'l', 'l', 'o' };

		for (int i = 0; i < sizeof(hello) / sizeof(hello[0]); i++)
			printf("%c", hello[i]); // 문자 단위로 하나씩 출력할때는 문제가 없다.
		printf("\n");

		// 문자열 형식으로 출력하면 '\0' 문자로 문장의 끝을 명시하지 않았기 때문에
		// 알 수 없는 메모리를 계속 읽게된다.(우연히 null문자를 읽을때까지)
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

		// 문자열 형식으로 데이터를 읽을경우 '\0'를 만날때까지 문자를 읽어 출력
		printf("%s\n", hello);

		hello[2] = '\0'; 
		printf("%s\n", hello);
	}

	printf("\n\n");
	{
		// 문자열 상수 데이터는 문자열이기 때문에 보이진 않지만 문장의 마지막에 
		// 자동으로 '\0' 문자를 포함시켜준다.
		char hello[] = "Hello"; // 문자열 상수로 값을 초기화할때는 '\0' 문자가 포함된다.
		printf("%s\n", hello);
	}
}

int length(char string[])
{
	/*
		NULL문자를 제외한 문자열의 문자 개수를 반환하는 함수
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
		src의 문자열 길이가 dest의 원소 개수보다 짧을 경우
		src의 문자열을 dest로 복사하는 함수
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
		dest와 src의 문자열 길이의 합이 dest의 원소 개수보다 짧을 경우
		src의 문자열을 dest의 문자열에 연결하는 함수
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
		두 문자열을 비교하여 같을경우 0 반환

		서로 다른 문자를 가지는 위치의 원소를 비교하여
		string1이 크다면 1 반환
		string2가 크다면 -1 반환
	*/

	for (int i = 0; ; i++)
	{
		if (string1[i] > string2[i]) return +1;
		if (string1[i] < string2[i]) return -1;
		if (string1[i] == '\0' && string2[i] == '\0') return 0;
	}
	
	return 0;
}
