// 02_data_type.cpp

/*
	Data Type - 자료형
	- 변수의 종류
	- 저장되는 값의 종류와 범위에 따라 다르게 표현

	variable - 변수
	- 데이터를 저장하기 위해 할당받은 메모리 공간
	- 메모리의 주소를 직접 다루지 않고도 데이터가 저장되있는 메모리를
	수학의 변수처럼 직관적으로 사용할 수 있게 해준다.
*/

/*
	bit와 byte
	- bit	: 가장 작은 데이터 단위, 0과 1만을 표현할 수 있는 2진수로 표현
	- byte	: 1byte == 8bit, 자료형의 크기 단위
*/

// 자료형의 종류

// 부호있는 정수형
// 음수인 경우 맨앞 비트가 1, 양수일 경우 0

char c = 'c';	 // 1byte, 주로 문자를 저장할때 사용, 범위 (-128 ~ 127),
// char 추가 설명 : 문자로 사용할 때는 앞의 7비트만 사용하고 뒤에 1자리는 패리티비트
//					패리티 비트란 오류를 검출하기위해 추가된 비트
short s = 1;	// 2byte, 정수를 저장, 범위(-32768 ~ 32767)
int i;			// 4byte, 정수를 저장, 범위(대략 -21억 ~ 21억)
/*
	2의 보수법
	음수를 표현할때는 정수의 비트를 뒤집고 +1을 해주어 표현
	ex) -24 표현
	0001 1000 => 24 양수의 비트표현
	1110 0111 => 비트를 뒤집어줌
	1110 1000 => 뒤집어진 비트에 +1을 해줌
*/
// 과제 : overflow와 underflow 조사

/*
	부호없는 정수형
	음수가 없는대신 양수가 2배로 늘어남
	부호있는 정수형 앞에 unsigned 키워드를 붙여 선언

	키워드
	- 프로그래밍 언어에서 이미 문법적으로 사용하고 있어 식별자로 사용할 수 없는 단어
*/

unsigned char c2;	// 0 ~ 255
unsigned short s2;	// 0 ~ 65,535
unsigned int i2;	// 대략 0 ~ 42억

#include<stdio.h>

int main()
{
	/*
		변수 선언 방법
		DataType name;
	*/
	int a; // declaration 선언하다
	
	//initialize(초기화)
	// 선언과 동시에 값을 대입하는 것
	int b = 10; // 변수 b를 선언함과 동시에 초기화
	b = 20;	// 대입, 할당
	// = : 대입 연산자, 우항의 값을 좌항에 대입

	// 변수 이름을 지을때 주의점

	//int int; // 키워드로 선언 안됨

	//int 1a; // 맨앞에 숫자가 들어가면 안됨
	int a1; 

	//int hello world; // 띄어쓰기 안됨
	int hello_world;

	// 같은 지역에서는 중볻된 이름으로 변수를 선언할 수 없음
	int test;
	//char test; // 중복되어 안됨

	// 변수 표기법
	 
	// 헝가리안 표기법 
	// - 가독성이 떨어져서 요즘에는 잘 안씀
	// - 변수의 이름을 지을때 맨앞에 자료형을 표시함
	int i_age;
	int intWeight;

	//과제 : 어떤 표현법인지 찾기
	int hpCount;
	int HpCount;
	int hp_count;

	// 문자형 
	char c1 = 'A';
	char c2 = 65;
	printf("character : %c\n", c1);
	printf("character : %c\n", c2);
	printf("character size : %d\n", sizeof(char));
	printf("character size : %d\n\n", sizeof(c1));

	// 둘다 문자형으로 출력하면 대문자 A가 출력
	// 문자를 저장할때 값자체는 숫자이지만 ASCI코드를 사용해 문자로 변환하여 출력
	// 과제 : ASCI코드 조사하기

	// alt + shift + 마우스 드래그 혹은 키보드 화살표(위아래)
	int num = 0;
	printf("num	: %d\n", num);
	printf("num + 1	: %d\n", num + 1);
	printf("int size : %d\n", sizeof(int));
	printf("int size : %d\n\n", sizeof(num));

	num = 10;
	printf("num	: %d\n", num);

	//실수형
	float f = 0.123f;	// 4byte
	double d = 1.1234;	// 8byte

	/*
		고정 소수점 방식
		- 소수점의 위치가 고정되어 표시되는 방식 ex) 0.123
		- 범위가 한정적이여서 좁은 범위밖에 표현을 못함
	*/

	/*
		부동 소수점 방식
		- 소수점의 위치가 바뀐다는 뜻 ex) 0.123e0
		- 실수 자료형을 저장할 때 사용하는 방식
		- 적은 비트로 넓은 범위를 표현할 수 있찌만 근사값을 표현하는거라 정확성이 떨어짐

		부동 소수점은 부호, 지수, 가수로 이루어져 있음
		지수 : 소수점의 위치, 비트를 표현할때 지수에 127을 더한후 표현
		가수 : 유효숫자
		float	: 부호(1bit), 지수(8bit), 가수(23bit)
		double	: 부호(1bit), 지수(11bit), 가수(52bit)
	*/
	/*
		표현 방식
		0.123을 각각의 방식을 사용해서 표현한다면

		고정 소수점 == 0.123

		부동 소수점 == 1.23e-1
		- e0, e1, e-1은 10의 제곱을 의미한다
	*/

	float f1 = 0.123f;
	double d1 = 0.123;
	printf("고정 소수점 : %.2f\n", f1);
	printf("부동 소수점 : %e\n", f1);	// 지수를 사용하는 형태로 출력
	printf("고정 소수점 : %lf\n", d1);
	printf("float size : %d\n", sizeof(f1));
	printf("double size : %05d\n", sizeof(d1));

	// 논리형
	true;
	false;
	bool isDash = false;
	// 정수로 true는 1, false는 0을 의미한다.

	return 0;
}