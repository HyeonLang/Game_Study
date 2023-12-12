// 06_switch.cpp
/*
	switch문
	- 괄호안에 정수 값에 대응하는 case로 이동해 명령어를 수행
	- 정수값만 받을 수 있다. 실수값 안됨


	switch(정수)
	{
		case 정수값1:
			명령1
			break;

		case 정수값2:
			명령2
			break;

		default:
			예외처리 명령
			break;
	}
	default 
	- 정수값에 대응하는 case가 없을경우 해당 위치로 이동

	break
	- 현재 진행하고있는 statement를 종료한다.

	statement(문)
	- 프로그래밍에서 실행가능한 최소의 독립적인 코드 조각
	- 코드의 문법적 단위
*/

#include<stdio.h>

#define INTRO 1
#define GAME 2
#define OPTION 3
#define EXIT 4

int main()
{

	int sel_menu = 0;
	printf("메뉴를 선택하세요 [1: 인트로 2: 게임 3: 옵션 4: 종료]\n");
	printf("input -> ");
	scanf_s("%d", &sel_menu);

	switch (sel_menu)
	{
	case INTRO: 
		printf("인트로 로직을 움직입니다.");
		break;

	case GAME:
		printf("게임 로직을 움직입니다.");
		break;

	case OPTION:
		printf("옵션 로직을 움직입니다.");
		break;

	case EXIT:
		printf("종료 로직을 움직입니다.");
		break;

	default:
		printf("잘못된 입력입니다.\n");
		break;
	}

	// 과제 : 가위 바위 보 게임 만들기
	//	- 상대방은 가위로 고정
	//  - 플레이어가 내는 경우에 따라 승, 패, 무승부 출력
	//  - if, switch문을 사용하여 작성

	return 0;
}