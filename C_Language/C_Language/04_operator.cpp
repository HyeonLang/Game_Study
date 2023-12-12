// 04_operator.cpp

/*
	연산자
	- 프로그래밍 언어는 일반적인 수학과 유사한 연산자를 지원한다.
	- 대입, 산술, 복합 대입, 증갑, 비교, 논리, 조건, 비트
*/

/*
	대입 연산자
	- 변수에 값을 대입할 때 사용한다
	- 부호 : =

	a = b (변수 a에다가 변수 b의 값을 대입해준다)
*/

/*
	산술 연산자
	- 일반적인 산술 연산을 수행한다.
	- 부호 : +, -, *, /, %

	c = a + b;
	c = a - b;
	c = a * b; a와 b를 곱한다.
	c = a / b; a를 b로 나누어 몫을 구한다.
	c = a % b; a를 b로 나누어 나머지를 구한다.
*/

/*
	복합 대입 연산자
	 c = c + a 같은 상황일때
	 c += a같이 줄일 수 있다.
	 모든 이항 연산자에 적용가능
*/

/*
	증감 연산자
	- 값을 1증가 시키거나 감소 시킬 때 사용한다.
	- 부호가 붙는 위치에 따라 전위와 후위로 나뉜다.
	앞에 붙으면 전위, 뒤에 붙으면 후위
	- 부호 : ++, --

	전위
	- 증감 연산을 먼저 수행후 다른 연산을 수행한다.
	예시)
	{
		int a = 0;
		int b = 0;

		a = ++b; b를 먼저 1 증가시킨후 대입해준다
		=> a는 1이 된다.
	}

	후위
	- 다른 연산을 먼저 수행후 증감 연산을 수행한다.
	예시)
	{
		int a = 0;
		int b = 0;

		a = b++; b의 값을 대입 해주고 b를 1 증가시킨다.
		=> a는 0이 된다.
	}
*/

/*
	비교 연산자
	- 2개의 피연산자의 크기를 비교하여 참(true)과 거짓(false)를 반환한다.

	== : 같으면 true, 다르면 false반환
	!= : 같으면 false, 다르면 true반환

	a < b a가 b보다 작으면 true 그 외에 false
	a > b a가 b보다 크면 true 그 외에 false

	a <= b a가 b보다 작거나 같으면 true 그 외에 false
	a >= b a가 b보다 크거나 같으면 true 그 외에 false
*/

/*
	논리 연산자
	- 논리식을 판단하여 참과 거짓을 반환한다.

	&&	(and)	: 둘다 참이면 true 그외 false
	||	(or)	: 둘중 하나라도 참이면 true 그외 false
	!	(not)	: true면 false, false면 true반환 => 논리를 뒤집어 준다.
*/

/*
	조건 연산자
	- 유일한 삼항 연산자이다.
	- 조건식에 따라 2가지 반환값을 가진다.

	조건식 ? 반환값1 : 반환값2
	조건식이 참이면 반환값1, 거짓이면 반환값2를 반환한다.
	반환값1, 반환값2는 주로 값이지만 경우에 따라 연산식이 들어갈 수 있다.
*/

/*
	비트연산자
	- 비트를 단위로 다룰때 사용하는 연산자
	- 비트 플래그를 사용할 때 빼고는 거의 사용안한다.
	과제 : 비트 플래그가 무엇인지 조사하기.
*/

#include<stdio.h>

int main()
{
#pragma region Attack
	//int playerDamage = 50;
	//int enemyHp = 540;

	//printf("플레이어의 공격력 : %d\n", playerDamage);
	//printf("현재 적의 체력 : %d\n", enemyHp);

	//int attackCount = 0;
	//printf("몇 번 공격하시겠습니까? : ");
	//scanf_s("%d", &attackCount);

	//printf("플레이어가 적을 %d번 공격!\n", attackCount);
	//enemyHp -= playerDamage * attackCount;

	//printf("현재 적의 체력 : %d\n\n", enemyHp);
#pragma endregion

#pragma region Buy

	//int gold = 500;
	//printf("현재 소지 골드 : %d\n", gold);

	//int price = 0;
	//printf("구매할 물약 A의 값 : ");
	//scanf_s("%d", &price);

	//printf("물약 A의 구매 가능 개수 : %d\n", gold / price);
	//printf("물약 A를 최대치까지 구매후 남는 골드 %d\n\n", gold % price);

#pragma endregion


#pragma region ++, --


	int a = 0;
	int b = 0;

	printf("int ++a : %d\n", ++a);
	printf("int b++ : %d\n\n", b++);

	printf("int a : %d\n", a);
	printf("int b : %d\n\n", b);

#pragma endregion

#pragma region Grab

	int grabRange;
	int distance = 300;
	int enemySpeed = 50;

	printf("적과의 사거리 : %d\n", distance);

	printf("그랩 사거리 : ");
	scanf_s("%d", &grabRange);

	//grabRange >= distance ? distance = 50 : distance += enemySpeed;
	distance = ((grabRange >= distance) ? 50 : distance + enemySpeed);

	printf("적과의 사거리 : %d\n", distance);

#pragma endregion

	/*
	과제 논리 연산자 문제
		논리연산자(&&, ||, !)를 사용해서
		빈칸( )을 채워서 우측(=>) 값과 같은 결과를 만들어 보자
		정답이 복수인 경우 전부 적기

		1. true () false => false
		2. true () false => true
		3. true () true  => true
		4. ()true		 => false
		5. ()false		 => true
	*/

	/*
		과제 : 환율 계산기 만들기
		과제 : bmi 계산기 만들기
	*/

	return 0;
}