// 05_if.cpp

#include<stdio.h>

int main()
{
	/*
		if문
		- 조건식이 참이냐 거짓이냐에 따라 다른 명령을 수행하게 해준다.
		- else 키워드로 예외 처리가 가능

		if(참/거짓 값)
			명령어
		=> ()의 값이 참이면 명령어를 수행 아니라면 명령어를 무시한다.
	*/

	//int number = 0;
	//printf("정수를 입력해 주세요 : ");
	//scanf_s("%d", &number);

	//if (number % 2 == 0)
	//	printf("짝수입니다.\n");

	//if (number % 2 != 0)
	//{			// 괄호를 사용하여 복수의 명령어 실행가능
	//	printf("짝수가 아니네요\n");
	//	printf("홀수입니다.\n");
	//}

	/*
		if(참/거짓)
			명령1
		else
			명령2
		=> () 값이 거짓일 경우 else의 명령2를 실행
	*/
	//if (number % 2 == 0)
	//	printf("짝수입니다.\n");
	//else 
	//{			
	//	printf("짝수가 아니네요\n");
	//	printf("홀수입니다.\n");
	//}

	/*
		if - else를 중첩하여 사용가능
	*/

	char key;

	printf("어디로 가야하오? : ");
	scanf_s(" %c", &key, sizeof(key));

	/*
		과제 : %c를 띄어쓰지 않았을때 그냥 넘어가는 이유 조사하기
		과제 : 띄어쓰기를 제외한 다른 해결방법도 찾아보기
	*/

	if (key == 'w')
		printf("위로 가겠소\n");
	else if (key == 's')
		printf("아래로 가겠소\n");
	else if (key == 'a')
		printf("왼쪽으로 가겠소\n");
	else if (key == 'd')
		printf("오른쪽으로 가겠소\n");
	else
		printf("낭비할 시간이 없소\n");


	// 중첩 if문 -> if 안에 if 중첩가능

	int number2 = 0;
	printf("숫자를 입력해주세요 : ");
	scanf_s("%d", &number2);

	if (number2 < 10)
	{
		if (number2 < 5)
			printf("5미만입니다.\n");
		else
			printf("5이상 10미만입니다.\n");
	}
	else
		printf("10이상입니다.\n");

	// 과제 : bmi 계산기 업그레이드
	//	- 나온 bmi수치에 따라 저체중, 정상, 과체중, 비만 출력하기

	return 0;
}