//21_function_parameter.cpp

/*
	매개변수(parameter)
	- 함수를 호출할 때 받는 값을 가리킬 때 사용하는 변수
	- 함수의 정의부에 적힌 변수를 의미
	- 지역변수로 생성되기 때문에 함수의 시작에 생성되고 함수가 종료되면 사라진다.

	인자(argument)
	- 함수를 호출할 때 전달되는 실제 값
	- 함수를 호출할 때 사용한 실제 값.
*/

#include<stdio.h>

/*
	Call by value
	- 함수 호출시 받은 인자의 값을 복사하여 전달한다.
	- 값을 복사하여 가져가기 때문에 원본이 보존이 된다.
	- 값을 복사하여 넘기기 때문에 메모리 사용량이 늘어난다.
*/

void swap(int x, int y) // 매개 변수
{
	int tmep = x;
	x = y;
	y = tmep;

	return;
}

/*
	Call by address
	Call by pointer
	Call by reference
	- 함수를 호출시 받은 인자의 데이터 주소를 받아 전달한다.
	- 원본에 접근하기 때문에 수정할 경우 원본이 영향을 받는다.
	- 복사하지 않고 원본을 받아 속도가 빠르다.
*/

void swap_pointer(int* const x,  int * const y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

int main()
{
	int i = 5;
	int j = 10;

	printf("i : %d\n", i);
	printf("j : %d\n\n", j);

	swap(i, j); // 인자 : 함수를 호출할 때 사용한 실제 값

	printf("i : %d\n", i);
	printf("j : %d\n\n", j);

	swap_pointer(*i, &j);

	printf("i : %d\n", i);
	printf("j : %d\n\n", j);
	
	return 0;
}


