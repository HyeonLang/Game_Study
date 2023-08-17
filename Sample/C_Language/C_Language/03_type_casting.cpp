// 03_type_casting.cpp

/*
	프로그래밍을 하다보면 자료형이 다른 변수 끼리 대입하거나 연산을 하게 된다.
	이럴때 두 자료형의 형태를 일치시켜야 하는데 이때 형변환이 발생한다.

	형변환
	- 데이터의 자료형을 다른 자료형으로 변환하는 것
	- 서로 다른 자료형의 대입, 연산시 사용한다.
	- 지정하지 않은 경우 암시적으로 변환된다.

	종류
	암시적 형변환 : 따로 지정하지 않은 경우 컴파일러에 의해 자동으로 변환됨
	명시적 형변환 : 사용자가 명시적으로 자료형을 바꿔주는 것
*/

#include<stdio.h>

int main()
{
	// 자동 형변환

	// 작은 자료형에서 큰 자료형으로 변환
	short s = 10;
	int i1 = s; // (int)s

	float f1 = 100; // 100은 int형임
	// float f = (float)100

	// 큰 자료형에서 작은 자료형으로 변환
	// -> 데이터 손실이 발생할 수 있다.
	int i2 = 500;
	char c1 = i2;		// char가 표현할 수 있는 양수값을 벗어나 오버플로우 발생
	printf("%d\n", c1);

	float f2 = 1.25f;
	int i3 = f2;		// 실수를 정수형에 넣을경우 소수점이 버려짐
	printf("%d\n", i3);

	// 연산시에는 큰 자료형으로 바뀌어야 데이터 손실을 줄일 수 있으므로
	// 자료형의 우선순위에 따라 변환된다.
	//Ranking of types operations 자료형의 순위
	//	- long double > double > float
	//	- unsigned long long == long long
	//	- unsigned long == long
	//	- unsigned int == int
	//	- unsigned short int == short int
	//	- unsigned char == char
	//	- _Bool

	f2 = 10 + 1.25; // 연산시 가장 큰 자료형으로 변환

	// 명시적 형변환
	//int a = 10, b = 4;
	//float div = a / b; // int 끼리의 연산
	//printf("%f\n", div); // 2.0 출력

	int a = 10, b = 4;
	float div = (float)a / b; // float / int -> 계산결과가 실수형 데이터
	printf("%f\n", div); // 2.5 출력

	return 0;
}