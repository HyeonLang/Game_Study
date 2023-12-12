//19_preprocessor.cpp

/*
	전처리기
	#으로 시작하는 컴파일 이전에 먼저 처리되는 구문
*/

/*
	inlcude
	해당 파일의 내용을 치환해준다.

	<>	: 컴파일러가 기본적으로 지정하고 있는 표준 라이브러리 경로에 있는 헤더파일 참조
	""	: 사용자가 사용중인 소스에 있는 위치를 기준(상대경로)로 헤더파일을 찾고, 만약에 없다면<>같이 동작
			-> 상대 경로가 아닌 절대경로로도 지정이 가능함

	/	: 현재 디렉터리의 루트(최상단 파일)로 이동
	./	: 현재 위치
	../	: 상위 디렉터리로 이동
*/

#include<stdio.h> // 지정된 경로에서 헤더를 탐색한다.
#include"stdio.h" // 상대경로나 절대경로를 기준으로 헤더를 탐색하고 없다면 <>와 같이 동작

// 둘다 같은의미, 현재 디렉터리에서 헤더를 찾는다.
#include"./test1.h"
#include"test1.h"  

// 상위 디렉터리로 이동 -> 상위 디렉터리에 있던 하위 디렉터리인 19_preprocessor_2로 이동
// -> 19_preprocessor_2안에 있던 test2.h파일을 추가
#include"../19_preprocessor_2/test2.h"

/*
	매크로 상수 
	- 매크로로 상수를 다른 이름으로 다룰 수 있다.
*/
#define NUM 10

/*
	매크로 함수
	- 단순 치환이기 때문에 인자의 자료형을 신경쓰지 않는다.
	- 함수 호출에 의한 성능 저하(오버헤드)가 일어나지 않아 실행속도가 향상
	- 단순 치환이므로 디버깅이 안된다.
	- 매크로 함수의 코드가 길어질수록 괄호가 많아져 가독성이 떨어짐
	=> 간단하고 자주 호출되는 함수에 사용하기에 적합하다
*/

#define MUL1(x, y) (x * y)
#define MUL2(x, y) ((x) * (y))

#define TEST
#define CANCEL

#ifdef TEST // 해당 매크로가 정의되어 있다면 아래 코드를 포함하라
int i = 10;
#else		// 예외처리
int i = 20;
#endif

#if defined TEST && defined CANCEL

#undef TEST // 매크로 정의를 해제한다

#endif

#ifndef TEST // 해당 매크로가 정의되어 있지 않다면 아래 코드를 포함하라
int j = 10;
#else		
int j = 20;
#endif

//  # : 인자를 문자열로 바꾸어준다.
// 연속된 문자열은 합쳐버린다. 결과 => print("x : %d\n", x)
#define PRINT(x) printf(#x" : %d\n", x)

// ## 하나로 합쳐준다.
// STRUCTURE_와 인자 x가 합쳐져 구조체의 별칭이 생성
#define STRUCTURE(x) typedef struct {int i;} STRUCTURE_##x

// 해당 위치에 test1_i를 정의한다는 의미
// -> test1.cpp 같은 이름의 전역변수를 정의하고 있으므로 중복 정의 문제 발생
//int test1_i;

// extern 키워드를 추가하면 외부에 존재하는 함수나 변수를 가져온다는 의미
extern int test1_i;

// extern 키워드를 사용하더라도 초기값을 주게 되면 여기서 변수를 만들겠다는 의미를 가지므로
// 전역 변수의 초기값은 하나의 소스파일에서만 해주어야 한다.
//extern int test1_i = 10;

// 함수는 extern 키워드를 생략해도 외부에 존재하는 함수 참조 가능
void print_test();

int main()
{
	printf("test1_i : %d\n", test1_i);

	print_test();
	print_hello();


	int a = 3;
	int b = 4;

	/*
		아래의 식의 결과가 다르게 나오는 이유
		매크로 함수는 해당 위치에 코드를 치환해주는 기능이기 때문에
		()가 없다면 치환된 후에 연산자 우선순위대로 처리될때 문제가 생길 수 있음

		MUL1(x, y) (x * y)
		MUL2(x, y) ((x) * (y)) 
	 
		MUL1(a + 1, b + 1) -> (a + 1 * b + 1)
		MUL2(a + 1, b + 1) -> ((a + 1) * (b + 1)) 
	*/

	int c1 = MUL1(a + 1, b + 1);
	int c2 = MUL2(a + 1, b + 1);
	printf("MUL1 = %d, MUL2 = %d\n", c1, c2);

	return 0;
};