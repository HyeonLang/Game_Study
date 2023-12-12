// 07_random_number.cpp
#include<stdio.h>
#include<stdlib.h> // 표준 함수 라이브러리, 난수 생성 함수가 포함되어 있다.
#include<time.h>	// 시간 관련 함수 라이브러리

int main()
{
	/*
		난수
		- 무작위 숫자
		- rand()를 사용하여 생성한다.
	*/
	printf("%d, ", rand() % 10 + 1);
	printf("%d, ", rand() % 10 + 1);
	printf("%d, ", rand() % 10 + 1);
	printf("%d, ", rand() % 10 + 1);
	printf("%d, ", rand() % 10 + 1);
	printf("\n\n");

	/*
		동일한 패턴으로 난수가 나오는 이유
		난수는 무작위로 만들어 지는 것이 아닌 시드값에 따른 일정한 규칙에 따라 생성된다.
		프로그램 실행시 초기시드값은 고정되어있어 시드값을 바꿔주지 않으면 난수는 같은 패턴으로 나오게 된다.
		srand()함수를 사용하여 시드값을 변경시킬 수 있다.
	*/

	// time() : 1970년 1월 1일 이후 경과된 시간을 초단위로 반환하는 함수
	// 현재 시간을 기준으로 반환값이 바뀌기 때문에 무작위 시드값으로 설정해주기 좋다.
	srand(time(NULL));

	printf("%d, ", rand());
	printf("%d, ", rand());
	printf("%d, ", rand());
	printf("%d, ", rand());
	printf("%d, ", rand());
	printf("\n\n");

	// 과제 : 가위 바위 보 게임 업그레이드
	//			- 상대가 무작위로 내도록 변경하기

	return 0;
}