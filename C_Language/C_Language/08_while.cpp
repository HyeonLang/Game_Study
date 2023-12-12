// 08_while.cpp

/*
	while문
	- 값이 true일 동안 명령문을 반복
	- 무한히 반복하거나 특정 조건을 만족할때까지 반복하는 경우 자주 사용

	while(값)
	{
		명령문
	}

	1. 값이 true인지 false인지 확인
	2. true면 명령문 실행, 아니라면 while문 종료
	3. 1, 2번을 반복한다.
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	/*
		무한루프
		- while문 내부에서 조건식의 결과를 반영하는 명령문이 없을시 발생함
		- 무한루프를 의도적으로 일으킬 경우에는 반드시 조건식의 결과를 변경하는
		명령문을 포함해야한다.
	*/
	
	//bool my_heart = true;
	//bool the_end_world = false;

	//while (the_end_world != true && my_heart)
	//{
	//	printf("I love you\n");

	//	// 조건식의 결과를 변경하는 코드를 넣어주자.
	//	printf("아직도 사랑해? [네 : 1 아니요 : 0] : ");
	//	int answer = 0;
	//	scanf_s("%d", &answer);

	//	if (answer == 0)
	//		my_heart = false;
	//}
	//printf("\n");

	 
	//char key = '\0';
	//while (true)
	//{
	//	printf("이동키 입력[w : 상 s : 하 a : 좌 d : 우] => ");
	//	key = _getch();

	//	if (key == 'q')
	//		break;

	//	switch (key)
	//	{
	//	case 'w': printf("상\n"); break;
	//	case 's': printf("하\n"); break;
	//	case 'a': printf("좌\n"); break;
	//	case 'd': printf("우\n"); break;
	//	}
	//}


	/*
		do while
		- 명령문을 한번 실행후 조건식을 검사
		- 조건에 상관없이 명령문을 한번은 실행해야하는 경우 사용
	*/

	// 상수 : 변하지 않는 값
	// const 키워드를 사용하면 초기에 선언한 후에는 값을 변경하지 못하는 변수가 된다.
	const int secret_code = 123123; // 상수 변수
	int password = 0;
	int try_count = 0;

	// 비밀번호입력 5회 실패시 잠금되도록 코드작성
	do
	{
		if (try_count >= 5)
		{
			printf("계정이 잠금되었습니다\n");
			break;
		}

		printf("비밀번호 입력(시도 횟수 %d) : ", try_count);
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
		printf("현재 범위 %d ~ %d \n", low, high);
		printf("입력 => ");
		scanf_s("%d", &answer);

		if (answer == key2) // 맞힌경우
		{
			printf("정답!\n");
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
			printf("잘못된 입력\n");
	}

	/*
		과제 : 가위 바위 보 게임 업그레이드
			- 3선 2승제 게임으로 만들기

		과제 : 묵 찌 빠 게임 만들기
	*/

	return 0;
}