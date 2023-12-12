// 10_function.cpp

/*
	함수
	- 특정 작업을 수행하는 코드의 집합
	- 사용자는 함수의 코드를 몰라도 함수를 호출하는 것만으로
	함수의 기능을 사용할 수 있다(우리가 지금까지 printf를 사용하듯이)
	- 적절하게 사용하면 프로그램을 유지보수하는데 유용하다.
*/

/*
	함수 선언 방식

	1.반환값 2.함수명(3.매개변수...)
	{
		(명령문)
		4. return 값;
	}

	1 : 반환되는 값의 자료형, 반환값이 없다면 void를 입력하고 반환값이 있다면 함수 내부에서 return 키워드로 값을 반환한다.
	2 : 함수를 호출할 때 사용할 이름
	3 : 매개변수라고 부른다. 함수를 호출할 때 필요한 값을 정의하는 부분
	4 : 값을 반환하고 함수를 종료시킨다.
*/

#include<stdio.h>

//정수 x, y를 재료로 전달받아, 둘을 더한 정수 값을 돌려주는 함수 add
int add(int x, int y)
{
	return x + y;
}

// 함수에서 정수 값을 입력받아 해당 값을 반환하는 함수 get_int
int get_int(/*void*/) // 매개변수가 없을 경우 void, 생략가능
{
	int temp;
	printf("숫자를 입력해주세요!!!! : ");
	scanf_s("%d", &temp);
	return temp;
}

// 과제 : int형 값 num1, num2 를 받아 num1^num2 을 반환하는 함수 pow 작성


/*
	함수의 선언과 호출

	- 일반적으로  함수의 호출보다 정의가 앞에 작성되어 있어야한다.

	- 함수의 호출이 정의보다 앞설 경우 해당 함수에 대하여
	함수가 어떤 유형의 값을 돌려주는지와 어떤 유형의 값을 필요로 하는지
	명시할 필요가 있다. (function prototype)

*/
int sub(int x, int y); // function prototype

//int sub(int, int); // 변수 이름 생략가능

void test();

int main()
{
	test();

	int x1 = 0;
	int y1 = 0;

	// 반복되는 코드를 함수로 만들어 재활용 할 수 있게 해보자
	//printf("숫자를 입력해주세요! : ");
	//scanf_s("%d", &x1);

	//printf("숫자를 입력해주세요! : ");
	//scanf_s("%d", &y1);
	
	x1 = get_int();
	y1 = get_int();

	printf("%d + %d : %d\n", x1, y1, add(x1, y1));

	printf("%d - %d : %d\n", x1, y1, sub(x1, y1));

	return 0;
}

//정수 x, y를 재료로 전달받아, 둘을 뺀 정수 값을 돌려주는 함수 sub
int sub(int x, int y)
{
	return x - y;
}

void test()
{
	printf("1111111111111111111111111\n");

	// 반환값이 void여도 사용가능
	return; // 원하는 시점에 함수를 종료시킬 수 있다.

	printf("2222222222222222222222222\n");
}
