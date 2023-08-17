// 11_variable_scope.cpp

/*
	변수의 유효 범위
	- 변수를 어느 위치에 선언하느냐에 따라서 변수는 유효범위, 소멸시기
	초기화 여부, 메모리에 저장되는 장소가 변경된다.

	- 크게 지역(local), 전역(global)으로 나뉜다.
*/

/*
	전역 변수
	- 특정 지역에 속하지 않는 변수
	- 전역 ,함수 외부에서 선언
	- 유효 범위는 프로그램 전체이며 프로그램 종료시 소멸한다.
	- 초기화하지 않으면 자동으로 0으로 초기화
	- 데이터 영역에 저장된다.
*/

#include<stdio.h>

static int global = 10;

int var1 = 'G';
void LocalCount();
void StaticCount();

int main()
{
	printf("초기화하지 않은 global 변수 : %d\n", global);

	/*
		지역 변수 
		- 특정 지역{} 내에서 생성된 변수
		- 접근 범위는 지역내이며 해당 지역을 이탈할 경우에 소멸한다.
		- 스택 영역에 저장된다.
	*/

	printf("main() : %c\n", var1);
	{ // 특정 지역
		char var1 = 'L'; // 지역이 다르다면 중복된 이름의 변수 선언가능

		// 해당 지역과 제일 가까운 변수가 선택된다.
		printf("{} : %c\n", var1);

	} // 지역을 벗어나면 해당 지역의 변수는 소멸한다.

	/*
		- static 키워드로 선언한 변수
		- 최초 선언시에만 초기화가 이루어진다.
		- 지역, 전역에 상관없이 프로그램 종료시 소멸한다. 
		- 유효 범위는 선언한 위치에 따른다.
		- 데이터 영역에 저장된다.
	*/

	for (int i = 0; i < 5; i++)
	{
		int j = 0;

		LocalCount();
		StaticCount();

		j++;
	}

	return 0;
}

void LocalCount()
{
	int count = 1;
	printf("local count : %d\n", count);
	count++;

	return;
}

void StaticCount()
{
	// 함수가 종료되도 소멸하지 않는다.
	// 초기화는 최초 선언시에만 이루어진다.
	static int count = 1;
	printf("static count : %d\n", count);
	count++;

	return;
}
